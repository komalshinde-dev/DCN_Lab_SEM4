import socket

def udp_file_receiver(server_ip, server_port, output_file):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    #It creates a socket object (like a phone line),AF_INET means "Address Family = Internet", which is IPv4 
    #SOCK_DGRAM stands for datagram socket (user datagram protocol)
    sock.bind((server_ip, server_port))
    print(f"Server listening on {server_ip}:{server_port}")

    with open(output_file, 'wb') as f:
        while True:
            data, addr = sock.recvfrom(4096)  # buffer size
            if data == b'EOF':  # End of file signal
                print("File transfer complete.")
                break
            f.write(data)
            print(f"Received {len(data)} bytes from {addr}")

    sock.close()

if __name__ == "__main__":
    # Set your server IP and port here
    SERVER_IP = "0.0.0.0"
    SERVER_PORT = 5005
    OUTPUT_FILE = "received_file"

    udp_file_receiver(SERVER_IP, SERVER_PORT, OUTPUT_FILE)

#127.0.0.0.1



//terminal 1 -python server.py
//terminal 2-python client.py 127.0.0.1 5005 path/to/yourfile.txt(in the same folder save example.txt) or python client.py 0.0.0.0 5005 example.txt
// 1-python server.py
//2 -python client.py 0.0.0.0 5005 komal.mp3


