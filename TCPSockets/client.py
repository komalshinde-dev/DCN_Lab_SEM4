import socket

def say_hello(client_socket):
    message = "Hello from Client!"
    client_socket.send(message.encode())
    response = client_socket.recv(1024).decode()
    print(f"Server says: {response}")#decode and encode hotay msg

def file_transfer(client_socket):
    filename = input("Enter filename to request: ")
    client_socket.send(filename.encode())#file name is send

    data = b""#Start with an empty bytes object to collect the file data.
    while True:
        packet = client_socket.recv(1024)
        if not packet:
            break
        data += packet#Till here data is collected 

    if data.startswith(b"ERROR"):
        print(data.decode())
    else:
        with open(f"received_{filename}", "wb") as f:
            f.write(data)
        print(f"File '{filename}' received and saved as 'received_{filename}'")#recieved and saved to recievedd_filename

def calculator(client_socket):
    expr = input("Enter arithmetic expression (e.g., 3 + 4 * 2): ")
    client_socket.send(expr.encode())
    result = client_socket.recv(1024).decode()#here results comes from server decode hota ithe
    print(f"Result: {result}")

def main():
    HOST = '127.0.0.1'  # Change to server IP if needed
    PORT = 8081

    print("Choose mode: hello / file / calc")
    mode = input("Enter mode: ").strip()

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)#it uses tcp(SOCK_STREAM)
    client_socket.connect((HOST, PORT))

    # Send mode and wait for server acknowledgment
    client_socket.send(mode.encode())#mode is sent
    ack = client_socket.recv(1024).decode()

    if ack != "OK":
        print(f"Server error or invalid mode: {ack}")
        client_socket.close()
        return

    if mode == "hello":
        say_hello(client_socket)
    elif mode == "file":
        file_transfer(client_socket)
    elif mode == "calc":
        calculator(client_socket)
    else:
        print("Invalid mode selected")

    client_socket.close()

if __name__ == "__main__":
    main()#import kela tar direct use karta yeta 

    
