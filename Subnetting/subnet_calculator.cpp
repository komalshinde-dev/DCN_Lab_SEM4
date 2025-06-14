#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

// Structure to represent an IPv4 address
struct IPv4 {
    unsigned int addr;

    // Default constructor sets address to 0
    IPv4() : addr(0) {}

    // Constructor from an unsigned int
    IPv4(unsigned int a) : addr(a) {}

    // Constructor from string like "192.168.1.1"
    IPv4(const string& ip) {
        addr = 0;
        int parts[4];
        char dot;
        stringstream ss(ip);

        // Try parsing the IP into 4 parts
        ss >> parts[0] >> dot >> parts[1] >> dot >> parts[2] >> dot >> parts[3];
        if (ss.fail() || dot != '.') {
            addr = 0xFFFFFFFF; // invalid IP flag
            return;
        }

        // Check if each octet is in valid range
        for (int i = 0; i < 4; ++i) {
            if (parts[i] < 0 || parts[i] > 255) {
                addr = 0xFFFFFFFF;
                return;
            }
        }

        // Convert 4 octets into a single 32-bit number
        addr = (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | parts[3];
    }

    // Convert internal 32-bit IP back to dotted decimal string
    string to_string() const {
        return std::to_string((addr >> 24) & 0xFF) + "." +
               std::to_string((addr >> 16) & 0xFF) + "." +
               std::to_string((addr >> 8) & 0xFF) + "." +
               std::to_string(addr & 0xFF);
    }
};

// Determine default (classful) subnet prefix length
int get_classful_prefix(const string& ip) {
    int first_octet = 0;
    size_t pos = ip.find('.');
    if (pos != string::npos)
        first_octet = stoi(ip.substr(0, pos));
    else
        return -1;

    // Class A: 1-127 => /8, Class B: 128-191 => /16, Class C: 192-223 => /24
    if (first_octet >= 1 && first_octet <= 127)
        return 8;
    else if (first_octet >= 128 && first_octet <= 191)
        return 16;
    else if (first_octet >= 192 && first_octet <= 223)
        return 24;
    else
        return -1; // unsupported IP class
}

// Generate subnet mask from prefix length
unsigned int netmask_from_prefix(int prefix) {
    if (prefix == 0) return 0;
    return 0xFFFFFFFF << (32 - prefix);
}

int main() {
    string ip_input;
    cout << "Enter IP Address: ";
    cin >> ip_input;

    // Extract IP and prefix if given in CIDR format
    size_t slash_pos = ip_input.find('/');
    string ip_part;
    int prefix = -1;

    if (slash_pos == string::npos) {
        // No prefix given, use classful addressing
        ip_part = ip_input;
        prefix = get_classful_prefix(ip_part);
        if (prefix == -1) {
            cout << "Only Class A, B, and C IPs are supported.\n";
            return 1;
        }
    } else {
        // Extract prefix from CIDR notation
        ip_part = ip_input.substr(0, slash_pos);
        prefix = stoi(ip_input.substr(slash_pos + 1));
        if (prefix < 0 || prefix > 32) {
            cout << "Invalid prefix length.\n";
            return 1;
        }
    }

    // Get number of subnets user wants to create
    int num_subnets;
    cout << "Enter no of Subnets: ";
    cin >> num_subnets;
    if (num_subnets <= 0) {
        cout << "Number of subnets must be positive.\n";
        return 1;
    }

    // Convert IP to IPv4 struct
    IPv4 ip_addr(ip_part);
    if (ip_addr.addr == 0xFFFFFFFF) {
        cout << "Invalid IP address format.\n";
        return 1;
    }

    // Calculate original network address and subnet mask
    unsigned int network_mask = netmask_from_prefix(prefix);
    unsigned int network_addr = ip_addr.addr & network_mask;
    int total_ips = 1 << (32 - prefix);
    int total_hosts = total_ips - 2;

    // Display original network info
    cout << "\nOriginal network : "
         << IPv4(network_addr).to_string() << "/" << prefix << "\n";
    cout << "Original subnet mask : "
         << IPv4(network_mask).to_string() << "\n";
    cout << "Total Available hosts : " << (total_hosts > 0 ? total_hosts : 0) << "\n";

    // Determine how many bits are needed to represent required number of subnets
    int bits_needed = (int)ceil(log2(num_subnets));
    int new_prefix = prefix + bits_needed;

    if (new_prefix > 32) {
        cout << "Not enough bits to create the subnet.\n";
        return 1;
    }

    // Calculate new subnet mask and host counts
    unsigned int new_mask = netmask_from_prefix(new_prefix);
    int ips_per_subnet = 1 << (32 - new_prefix);
    int usable_hosts = ips_per_subnet - 2;

    // Display new subnet info
    cout << "\nNew subnet mask : " << IPv4(new_mask).to_string() << "\n";
    cout << "Number of subnets : " << (1 << bits_needed) << "\n";
    cout << "IP's per subnet : " << ips_per_subnet << "\n";
    cout << "Usable hosts per subnet : " << (usable_hosts > 0 ? usable_hosts : 0) << "\n";

    // Iterate and display information for each subnet
    for (int i = 0; i < (1 << bits_needed); ++i) {
        // Compute the subnet's base address
        unsigned int subnet_addr = network_addr | (i << (32 - new_prefix));
        unsigned int first_host = subnet_addr + (usable_hosts > 0 ? 1 : 0);
        unsigned int last_host = subnet_addr + (usable_hosts > 0 ? ips_per_subnet - 2 : 0);
        unsigned int broadcast_addr = subnet_addr + ips_per_subnet - 1;

        cout << "\nSubnet " << (i + 1) << " :\n";
        cout << "Network address : " << IPv4(subnet_addr).to_string() << "\n";
        if (usable_hosts > 0) {
            cout << "First host : " << IPv4(first_host).to_string() << "\n";
            cout << "Last host : " << IPv4(last_host).to_string() << "\n";
        } else {
            cout << "First host : N/A\n";
            cout << "Last host : N/A\n";
        }
        cout << "Broadcast Address : " << IPv4(broadcast_addr).to_string() << "\n";
        cout << "Total IP's : " << ips_per_subnet << "\n";
        cout << "Usable Hosts : " << (usable_hosts > 0 ? usable_hosts : 0) << "\n";
    }

    return 0;
}


//EXAMPLE-192.168.100.0/24
//FOR 4 SUBNETS
