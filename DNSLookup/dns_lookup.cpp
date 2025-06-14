#include <iostream>     
#include <string>       
#include <netdb.h>      // For gethostbyname(), gethostbyaddr(), struct hostent
#include <arpa/inet.h>  // For inet_ntoa(), inet_aton(), struct in_addr
#include <unistd.h>     // For POSIX compatibility (optional but common)

using namespace std;     

void urlToIP(const string& hostname) {
    // Use gethostbyname() to get host information
    struct hostent* host = gethostbyname(hostname.c_str());

    // Check if resolution failed
    if (host == nullptr) {
        cout << "Could not resolve domain name." << endl;
        return;
    }

    // Convert the first IP address from the hostent structure to readable string
    cout << "IP address of " << hostname << " is "
         << inet_ntoa(*(struct in_addr*)host->h_addr) << endl;
}

// Function to resolve an IP address to a domain name
void ipToURL(const string& ip_address) {
    struct in_addr addr;

    // Convert IP address from text to binary form
    if (inet_aton(ip_address.c_str(), &addr) == 0) {
        cout << "Invalid IP address format." << endl;
        return;
    }

    // Use gethostbyaddr() to resolve IP to hostname
    struct hostent* host = gethostbyaddr(&addr, sizeof(addr), AF_INET);

    // Check if resolution failed
    if (host == nullptr) {
        cout << "Could not resolve IP address." << endl;
        return;
    }

    // Output the resolved domain name
    cout << "Domain name for " << ip_address << " is " << host->h_name << endl;
}

int main() {
    int choice;        // To store user menu choice
    string input;      // To store user input (hostname or IP)

    // Loop so user can make multiple lookups until choosing to exit
    while (true) {
        // Print menu
        cout << "\nDNS Lookup Tool" << endl;
        cout << "1. URL to IP" << endl;
        cout << "2. IP to URL" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";

        cin >> choice;      // Read user's menu choice
        cin.ignore();       // Ignore leftover newline in input buffer

        // Perform corresponding action
        if (choice == 1) {
            // URL to IP
            cout << "Enter the domain name (e.g., google.com): ";
            getline(cin, input);  // Get full line input (supports spaces)
            urlToIP(input);       // Call function to resolve hostname
        } else if (choice == 2) {
            // IP to URL
            cout << "Enter the IP address (e.g., 8.8.8.8): ";
            getline(cin, input);  
            ipToURL(input);       
        } else if (choice == 3) {
            // Exit the program
            break;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0; 
}
