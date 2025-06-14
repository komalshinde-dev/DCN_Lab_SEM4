#include <iostream>
#include <string>

using namespace std;

string xorOperation(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string mod2Division(string dividend, string divisor) {
    int pick = divisor.length();
    string temp = dividend.substr(0, pick);

    while (pick < dividend.length()) {
        if (temp[0] == '1') {
            temp = xorOperation(divisor, temp) + dividend[pick];
        } else {
            temp = xorOperation(string(pick, '0'), temp) + dividend[pick];
        }
        pick++;
    }

    if (temp[0] == '1') {
        temp = xorOperation(divisor, temp);
    } else {
        temp = xorOperation(string(pick, '0'), temp);
    }

    return temp;
}

int main() {
    string data, divisor;

    cout << "Enter 7 or 8-bit ASCII binary data (e.g., 1000001 for 'A'): ";
    cin >> data;

    cout << "Enter generator polynomial (binary form, e.g., 1001): ";
    cin >> divisor;

    string appendedData = data + string(divisor.length() - 1, '0');

    string remainder = mod2Division(appendedData, divisor);
    string transmittedData = data + remainder;

    cout << "\nCRC Remainder: " << remainder << endl;
    cout << "Transmitted data (data + CRC): " << transmittedData << endl;

    string received;
    cout << "\nEnter received data: ";
    cin >> received;

    string checkRemainder = mod2Division(received, divisor);

    if (checkRemainder.find('1') != string::npos) {
        cout << "Error detected in received data!" << endl;
    } else {
        cout << "No error detected. Data is correct." << endl;
    }

    return 0;
}





#include <iostream>
#include <string>

using namespace std;

// Function to perform XOR between two binary strings (excluding the first bit)
// Used in the modulo-2 division step of CRC
string xorOperation(string a, string b) {
    string result = "";
    // Start from index 1 because the leftmost bit is dropped in CRC division
    for (int i = 1; i < b.length(); i++) {
        // XOR of bits: if bits are same, result is 0; else 1
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Function to perform modulo-2 division (CRC division)
// dividend: input data appended with zeros (length = data length + divisor length - 1)
// divisor: the generator polynomial
string mod2Division(string dividend, string divisor) {
    int pick = divisor.length();                // Number of bits to consider initially
    string temp = dividend.substr(0, pick);    // Initial segment of the dividend

    // Process each bit until all bits in dividend are processed
    while (pick < dividend.length()) {
        // If the leftmost bit is 1, perform XOR with divisor
        if (temp[0] == '1') {
            temp = xorOperation(divisor, temp) + dividend[pick];
        } else { // If leftmost bit is 0, XOR with all-zero string of divisor length
            temp = xorOperation(string(pick, '0'), temp) + dividend[pick];
        }
        pick++;
    }

    // Final XOR step after processing all bits
    if (temp[0] == '1') {
        temp = xorOperation(divisor, temp);
    } else {
        temp = xorOperation(string(pick, '0'), temp);
    }

    return temp;  // The remainder is the CRC bits
}

int main() {
    string data, divisor;

    // Input the binary data string (7 or 8 bits representing ASCII)
    cout << "Enter 7 or 8-bit ASCII binary data (e.g., 1000001 for 'A'): ";
    cin >> data;

    // Input the generator polynomial in binary form
    cout << "Enter generator polynomial (binary form, e.g., 1001): ";
    cin >> divisor;

    // Append zeros to data equal to degree of divisor (length - 1)
    string appendedData = data + string(divisor.length() - 1, '0');

    // Calculate CRC remainder using modulo-2 division
    string remainder = mod2Division(appendedData, divisor);

    // Transmitted data is original data plus CRC remainder
    string transmittedData = data + remainder;

    cout << "\nCRC Remainder: " << remainder << endl;
    cout << "Transmitted data (data + CRC): " << transmittedData << endl;

    // Simulate reception of data (with or without errors)
    string received;
    cout << "\nEnter received data: ";
    cin >> received;

    // Perform CRC check on received data
    string checkRemainder = mod2Division(received, divisor);

    // If remainder contains any '1', error is detected
    if (checkRemainder.find('1') != string::npos) {
        cout << "Error detected in received data!" << endl;
    } else {
        cout << "No error detected. Data is correct." << endl;
    }

    return 0;
}


//1010000
//1001
/011
