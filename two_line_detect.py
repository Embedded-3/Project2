import cv2
import numpy as np

class Line:
    def __init__(self):
        self.window_margin = 40
        self.prevx = []
        self.current_fit = [np.array([False])]
        self.startx = None
        self.endx = None
        self.allx = None
        self.ally = None

def warp_image(img, src, dst, size):
    M = cv2.getPerspectiveTransform(src, dst)
    Minv = cv2.getPerspectiveTransform(dst, src)
    warp_img = cv2.warpPerspective(img, M, size, flags=cv2.INTER_LINEAR)
    return warp_img, M, Minv

def smoothing(lines, pre_lines=3):
    lines = np.squeeze(lines)
    avg_line = np.zeros((720))
    for ii, line in enumerate(reversed(lines)):
        if ii == pre_lines:
            break
        avg_line += line
    avg_line = avg_line / pre_lines
    return avg_line

def calculate_center_angle(left_line, right_line, xm_per_pix, ym_per_pix):
    if left_line.allx is None or right_line.allx is None:
        return None
    ploty = np.linspace(0, 720 - 1, 720)
    leftx = left_line.allx[::-1]
    rightx = right_line.allx[::-1]
    centerx = (leftx + rightx) / 2
    fit = np.polyfit(ploty * ym_per_pix, centerx * xm_per_pix, 2)
    y = -40 * ym_per_pix
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
    minpix = 50

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
            avg = smoothing(left_line.prevx, 5)
            left_fit = np.polyfit(ploty, avg, 2)
            left_fitx = left_fit[0] * ploty ** 2 + left_fit[1] * ploty + left_fit[2]
        left_line.allx, left_line.ally = left_fitx, ploty

    if len(rightx) > 0:
        right_fit = np.polyfit(righty, rightx, 2)
        right_fitx = right_fit[0] * ploty ** 2 + right_fit[1] * ploty + right_fit[2]
        right_line.prevx.append(right_fitx)
        if len(right_line.prevx) > 5:
            avg = smoothing(right_line.prevx, 5)
            right_fit = np.polyfit(ploty, avg, 2)
            right_fitx = right_fit[0] * ploty ** 2 + right_fit[1] * ploty + right_fit[2]
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
    src = np.float32([[435, 170], [242, 429], [794, 170], [977, 429]])
    dst = np.float32([[200, 0], [200, 720], [520, 0], [520, 720]])
    xm_per_pix = 1.5 / 320
    ym_per_pix = 1.5 / 720

    cameraMatrix = np.array([
        [909.10666688, 0, 680.29035139],
        [0, 907.69237377, 313.64665827],
        [0, 0, 1]
    ], dtype=np.float32)

    distCoeffs = np.array([[0.04561485, -0.04977711, -0.00178452, 0.00436709, 0.11888961]], dtype=np.float32)

    cap = cv2.VideoCapture(0, cv2.CAP_V4L2)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
    cap.set(cv2.CAP_PROP_FPS, 30)

    ret, frame = cap.read()
    if not ret:
        print("카메라로부터 프레임을 읽을 수 없습니다.")
        return

    h, w = frame.shape[:2]
    map1, map2 = cv2.initUndistortRectifyMap(cameraMatrix, distCoeffs, None, cameraMatrix, (w, h), cv2.CV_16SC2)

    left_line = Line()
    right_line = Line()

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        frame = cv2.remap(frame, map1, map2, interpolation=cv2.INTER_LINEAR)

        img = frame[int(0.4 * frame.shape[0]):, :]
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        _, binary = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)

        warp_img, M, Minv = warp_image(binary, src, dst, (720, 720))
        find_lines(warp_img, left_line, right_line)
        angle = calculate_center_angle(left_line, right_line, xm_per_pix, ym_per_pix)
        if angle is not None:
            print(f"Vehicle Steering Angle: {angle:.2f} degrees")

        visual = draw_center_lane(cv2.cvtColor(warp_img, cv2.COLOR_GRAY2BGR), left_line, right_line)
        cv2.imshow("Lane Detection", visual)
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()