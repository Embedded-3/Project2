import serial
import struct
import time

# ——— 프로토콜 정의 ———
START_BYTE = 0xAA
END_BYTE   = 0x55

def calc_checksum(payload: bytes) -> int:
    return sum(payload) & 0xFF

def make_packet(payload: bytes) -> bytes:
    length   = len(payload)
    checksum = calc_checksum(payload)
    return bytes([START_BYTE, length]) + payload + bytes([checksum, END_BYTE])

def main():
    # 포트 열기 (must run as root or with proper permissions)
    uart = serial.Serial(
        port='/dev/ttyAMA3',
        baudrate=115200,
        timeout=0.1
    )

    count = 0
    try:
        while True:
            # 추종점 각도 : signed char -128 ~ 127
            values = [23 + count]
            # little-endian 1개 signed char(-128 ~ 127) → 1 바이트
            payload = struct.pack('<b', *values)

            pkt = make_packet(payload)
            uart.write(pkt)
            print(f"Sent packet: {pkt.hex()}")
            count += 1

            time.sleep(1)

    except KeyboardInterrupt:
        print("Stopping sender…")

    finally:
        uart.close()

if __name__ == '__main__':
    main()
