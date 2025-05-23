from picamera2 import Picamera2
import cv2
import time
import os

def main():
    # 저장 폴더가 없으면 생성
    os.makedirs("images", exist_ok=True)

    # Picamera2 초기화
    picam2 = Picamera2()
    config = picam2.create_preview_configuration(main={"format": "RGB888", "size": (640, 480)})
    picam2.configure(config)
    picam2.start()
    time.sleep(1)  # 카메라 안정화 대기

    save_idx = 1

    while True:
        frame = picam2.capture_array()
        frame_bgr = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
        cv2.imshow("Camera", frame_bgr)

        key = cv2.waitKey(1) & 0xFF
        if key == ord('s'):
            filename = f'images/image_{save_idx}.png'
            cv2.imwrite(filename, frame_bgr)
            print('saved!')
            save_idx += 1
        elif key == ord('q'):
            break

    picam2.stop()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()