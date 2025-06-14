import socket
import sys #to get input
import time #to delay

def udp_file_sender(server_ip, server_port, input_file):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    with open(input_file, 'rb') as f:
        while True:
            bytes_read = f.read(4096)
            if not bytes_read:
                break
            sock.sendto(bytes_read, (server_ip, server_port))
            print(f"Sent {len(bytes_read)} bytes")
            time.sleep(0.001)  # small delay to avoid overwhelming UDP buffer

    # Send EOF signal
    sock.sendto(b'EOF', (server_ip, server_port))
    print("File transfer complete.")
    sock.close()

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print(f"Usage: python {sys.argv[0]} <server_ip> <server_port> <file_path>")
        sys.exit(1)

    SERVER_IP = sys.argv[1]
    SERVER_PORT = int(sys.argv[2])
    INPUT_FILE = sys.argv[3]
    #Ensures you gave 3 arguments when running:
    udp_file_sender(SERVER_IP, SERVER_PORT, INPUT_FILE)

