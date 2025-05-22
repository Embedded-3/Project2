import serial
import struct
import time

# ——— 프로토콜 정의 ———
START_BYTE = 0xAA
END_BYTE   = 0x55

def calc_checksum(payload: bytes) -> int:
    return sum(payload) & 0xFF

def parse_stream(buf: bytearray):
    """buf에서 완전한 패킷을 찾아 payload 리턴 (없으면 None)"""
    while len(buf) >= 4:
        # START 찾기
        if buf[0] != START_BYTE:
            buf.pop(0)
            continue
        length = buf[1]
        pkt_len = 1 + 1 + length + 1 + 1
        if len(buf) < pkt_len:
            return None
        if buf[pkt_len-1] != END_BYTE:
            buf.pop(0)
            continue

        payload = bytes(buf[2:2+length])
        recv_chk = buf[2+length]
        if recv_chk != calc_checksum(payload):
            # 잘못된 체크섬
            del buf[:pkt_len]
            continue

        # 올바른 패킷
        del buf[:pkt_len]
        return payload
    return None

def main():
    com_port = 'COM4'   # USB-TTL 디바이스 확인해서 맞게 설정
    uart = serial.Serial(com_port, 115200, timeout=0.1)

    buf = bytearray()
    try:
        while True:
            data = uart.read(64)
            if data:
                buf.extend(data)

            pkt = parse_stream(buf)
            if pkt:
                # 1 바이트 페이로드 → signed char
                values = struct.unpack('b', pkt)
                print("Received floats:", values)

            time.sleep(0.05)

    except KeyboardInterrupt:
        print("Stopping receiver…")

    finally:
        uart.close()

if __name__ == '__main__':
    main()
