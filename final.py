from picamera2 import Picamera2
import cv2
import numpy as np
import time

class Line:
    def __init__(self):
        self.window_margin = 20
        self.prevx = []
        self.allx = None
        self.ally = None

def warp_image(img, src, dst, size):
    M = cv2.getPerspectiveTransform(src, dst)
    Minv = cv2.getPerspectiveTransform(dst, src)
    warp_img = cv2.warpPerspective(img, M, size, flags=cv2.INTER_LINEAR)
    return warp_img, M, Minv

def smoothing(lines, pre_lines=5):
    lines = np.squeeze(lines)
    avg_line = np.zeros((lines.shape[1]))
    for ii, line in enumerate(reversed(lines[-pre_lines:])):
        avg_line += line
    avg_line = avg_line / pre_lines
    return avg_line

def calculate_center_angle(left_line, right_line, xm_per_pix, ym_per_pix):
    if left_line.allx is None or right_line.allx is None:
        return None
    ploty = np.linspace(0, 240 - 1, 240)
    leftx = left_line.allx[::-1]
    rightx = right_line.allx[::-1]
    centerx = (leftx + rightx) / 2
    fit = np.polyfit(ploty * ym_per_pix, centerx * xm_per_pix, 2)
    y = -30 * ym_per_pix
    slope = 2 * fit[0] * y + fit[1]
    angle = np.arctan(slope) * (180 / np.pi)
    return angle

def find_lines(binary_img, left_line, right_line):
    histogram = np.sum(binary_img[binary_img.shape[0] // 2:, :], axis=0)
    midpoint = np.int32(histogram.shape[0] / 2)
    start_leftx = np.argmax(histogram[:midpoint])
    start_rightx = np.argmax(histogram[midpoint:]) + midpoint
    window_height = np.int32(binary_img.shape[0] / 10)
    nonzero = binary_img.nonzero()
    nonzeroy = np.array(nonzero[0])
    nonzerox = np.array(nonzero[1])
    margin = left_line.window_margin
    minpix = 30

    leftx_current = start_leftx
    rightx_current = start_rightx
    left_lane_inds = []
    right_lane_inds = []

    for window in range(10):
        win_y_low = binary_img.shape[0] - (window + 1) * window_height
        win_y_high = binary_img.shape[0] - window * window_height
        win_xleft_low = leftx_current - margin
        win_xleft_high = leftx_current + margin
        win_xright_low = rightx_current - margin
        win_xright_high = rightx_current + margin

        good_left_inds = ((nonzeroy >= win_y_low) & (nonzeroy < win_y_high) &
                          (nonzerox >= win_xleft_low) & (nonzerox < win_xleft_high)).nonzero()[0]
        good_right_inds = ((nonzeroy >= win_y_low) & (nonzeroy < win_y_high) &
                           (nonzerox >= win_xright_low) & (nonzerox < win_xright_high)).nonzero()[0]

        left_lane_inds.append(good_left_inds)
        right_lane_inds.append(good_right_inds)

        if len(good_left_inds) > minpix:
            leftx_current = np.int32(np.mean(nonzerox[good_left_inds]))
        if len(good_right_inds) > minpix:
            rightx_current = np.int32(np.mean(nonzerox[good_right_inds]))

    left_lane_inds = np.concatenate(left_lane_inds)
    right_lane_inds = np.concatenate(right_lane_inds)

    leftx = nonzerox[left_lane_inds]
    lefty = nonzeroy[left_lane_inds]
    rightx = nonzerox[right_lane_inds]
    righty = nonzeroy[right_lane_inds]

    ploty = np.linspace(0, binary_img.shape[0] - 1, binary_img.shape[0])

    if len(leftx) > 0:
        left_fit = np.polyfit(lefty, leftx, 2)
        left_fitx = left_fit[0] * ploty ** 2 + left_fit[1] * ploty + left_fit[2]
        left_line.prevx.append(left_fitx)
        if len(left_line.prevx) > 5:
            left_fitx = smoothing(np.array(left_line.prevx))
        left_line.allx, left_line.ally = left_fitx, ploty

    if len(rightx) > 0:
        right_fit = np.polyfit(righty, rightx, 2)
        right_fitx = right_fit[0] * ploty ** 2 + right_fit[1] * ploty + right_fit[2]
        right_line.prevx.append(right_fitx)
        if len(right_line.prevx) > 5:
            right_fitx = smoothing(np.array(right_line.prevx))
        right_line.allx, right_line.ally = right_fitx, ploty

def draw_center_lane(img, left_line, right_line):
    if left_line.allx is None or right_line.allx is None:
        return img
    centerx = (left_line.allx + right_line.allx) / 2
    pts = np.array([np.transpose(np.vstack([centerx, left_line.ally]))])
    warp_zero = np.zeros_like(img).astype(np.uint8)
    cv2.polylines(warp_zero, np.int32([pts]), isClosed=False, color=(0, 255, 255), thickness=4)
    result = cv2.addWeighted(img, 1, warp_zero, 0.6, 0)
    return result

def main():
    src = np.float32([[0, 239], [320, 239], [30, 1], [290, 1]])
    dst = np.float32([[0, 240], [320, 240], [0, 0], [320, 0]])

    xm_per_pix = 1.5 / 160
    ym_per_pix = 1.5 / 240

    left_line = Line()
    right_line = Line()

    # 내부 파라미터와 왜곡 계수
    camera_matrix = np.array([[948.11755267, 0., 309.19349325],
                              [0., 945.69368955, 240.09964196],
                              [0., 0., 1.]])
    dist_coeffs = np.array([1.12977633e-02, -5.46902964e-01, -3.48949862e-04, -2.24273528e-04, 8.55525684e+00])

    picam2 = Picamera2()
    config = picam2.create_preview_configuration(main={"format": "RGB888", "size": (320, 240)})
    picam2.configure(config)
    picam2.start()
    time.sleep(1)

    while True:
        frame = picam2.capture_array()

        # 왜곡 보정
        frame = cv2.undistort(frame, camera_matrix, dist_coeffs)

        warp_rgb, M, Minv = warp_image(frame, src, dst, (320, 240))

        hsv = cv2.cvtColor(warp_rgb, cv2.COLOR_RGB2HSV)
        white_mask = cv2.inRange(hsv, (0, 0, 140), (180, 45, 255))
        masked = cv2.bitwise_and(warp_rgb, warp_rgb, mask=white_mask)
        gray = cv2.cvtColor(masked, cv2.COLOR_RGB2GRAY)
        _, binary = cv2.threshold(gray, 100, 255, cv2.THRESH_BINARY)

        find_lines(binary, left_line, right_line)
        angle = calculate_center_angle(left_line, right_line, xm_per_pix, ym_per_pix)
        if angle is not None:
            print(f"Steering Angle: {angle:.2f} degrees")

        lane_view = draw_center_lane(cv2.cvtColor(binary, cv2.COLOR_GRAY2BGR), left_line, right_line)
        combined = np.hstack((warp_rgb, lane_view))
        cv2.imshow("Bird's Eye RGB + Lane Detection", combined)

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    picam2.stop()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()