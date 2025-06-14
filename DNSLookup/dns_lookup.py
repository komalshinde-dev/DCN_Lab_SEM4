import socket

def dns_lookup():
    print("DNS Lookup Tool")
    print("1. Get IP from URL")
    print("2. Get URL from IP")
    
    choice = input("Enter your choice (1 or 2): ")

    if choice == '1':
        domain = input("Enter domain name (e.g. google.com): ")
        try:
            ip = socket.gethostbyname(domain)
            print(f"IP address of {domain} is {ip}")
        except socket.gaierror:
            print("Could not resolve domain name.")
    
    elif choice == '2':
        ip_address = input("Enter IP address (e.g. 8.8.8.8): ")
        try:
            host = socket.gethostbyaddr(ip_address)
            print(f"Domain name for {ip_address} is {host[0]}")
        except socket.herror:
            print("Could not resolve IP address.")
    
    else:
        print("Invalid choice.")


dns_lookup()



"""

DNS Tool
1. URL to IP
2. IP to URL
Enter the Choice : 2
Enter the IP adress: 8.8.8.8
Domain for 8.8.8.8 id dns.google

DNS Tool
1. URL to IP
2. IP to URL
Enter the Choice : 1
Enter the URL: dns.google
IP for dns.google if 8.8.8.8
""”
