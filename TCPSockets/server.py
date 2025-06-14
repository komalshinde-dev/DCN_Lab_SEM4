import socket

def say_hello(client_socket):
    data = client_socket.recv(1024).decode()
    print(f"Client says: {data}")
    response = "Hello from Server!"
    client_socket.send(response.encode())#decode and encode hotay msg

def file_transfer(client_socket):
    filename = client_socket.recv(1024).decode()#It waits for file name 
    print(f"Client requested file: {filename}")
    try:
        with open(filename, "rb") as f:#It reads the file in binary language
            data = f.read()
            client_socket.sendall(data)#send with the help of sendall
        print("File sent successfully.")
    except FileNotFoundError:
        client_socket.send(b"ERROR: File not found.")
        print("File not found.")

def calculator(client_socket):
    expr = client_socket.recv(1024).decode()#recieves maths expression
    print(f"Received expression: {expr}")
    try:
        # Warning: eval can be dangerous, only use trusted input!
        result = str(eval(expr))#it is evaluate with the help of eval()
    except Exception as e:
        result = f"ERROR: {e}"
    client_socket.send(result.encode())#msg is encoded

def main():
    HOST = ''
    PORT = 8081
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST, PORT))
    server_socket.listen(5)#Till here the socket is made and then listening(waits for client)
    print(f"Server listening on port {PORT}...")

    while True:
        client_socket, addr = server_socket.accept()
        print(f"Connection from {addr}")#it waits to check if any client is coming

        mode = client_socket.recv(1024).decode().strip()#IT is used to say hello and etc
        print(f"Mode selected: '{mode}'")

        if mode in ("hello", "file", "calc"):
            client_socket.send(b"OK")#acknowlegment is there
        else:
            client_socket.send(b"Invalid mode")
            client_socket.close()
            continue

        if mode == "hello":
            say_hello(client_socket)
        elif mode == "file":
            file_transfer(client_socket)
        elif mode == "calc":
            calculator(client_socket)

        client_socket.close()

if __name__ == "__main__":
    main()


//1-  python3 server.py
//2-  python3 client.py

