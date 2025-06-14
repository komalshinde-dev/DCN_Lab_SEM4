#include <iostream>
using namespace std;

// Function to encode data using Hamming Code (7,4)
void encodeHammingCode(int data[]) {
    // Calculate parity bits using XOR
    data[0] = data[2] ^ data[4] ^ data[6];  // Parity bit 1 (position 1, p1)
    data[1] = data[2] ^ data[5] ^ data[6];  // Parity bit 2 (position 2, p2)
    data[3] = data[4] ^ data[5] ^ data[6];  // Parity bit 4 (position 4, p4)
}

// Function to detect and correct errors in the received data
void detectAndCorrectError(int receivedData[]) {
    int c1, c2, c3, c;

    // Calculate the error-checking bits (c1, c2, c3)
    c1 = receivedData[0] ^ receivedData[2] ^ receivedData[4] ^ receivedData[6];  // p1 checks d7, d5, d3
    c2 = receivedData[1] ^ receivedData[2] ^ receivedData[5] ^ receivedData[6];  // p2 checks d7, d6, d3
    c3 = receivedData[3] ^ receivedData[4] ^ receivedData[5] ^ receivedData[6];  // p4 checks d5, d6, d3

    
    c = c3 * 4 + c2 * 2 + c1;

    if (c == 0) {
        cout << "No error during transmission." << endl;
    } else {
        cout << "Error detected at position " << c << endl;

        // Display received (faulty) data
        cout << "\nData received: ";
        for (int i = 0; i < 7; i++) {
            cout << receivedData[i] << " ";
        }

        // Correct the error
        // The position to correct is `c-1` (0-based index)
        if (receivedData[c - 1] == 0) {
            receivedData[c - 1] = 1;
        } else {
            receivedData[c - 1] = 0;
        }

        // Display the corrected message
        cout << "\nCorrected message is: ";
        for (int i = 0; i < 7; i++) {
            cout << receivedData[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    int data[7];           // Data array with 7 bits (3 parity + 4 data)
    int receivedData[7];   // Received data array (possibly with errors)

    // Input 4 data bits for positions d7, d6, d5, d3
    cout << "Enter 4 bits of data (7-bit ASCII code, data bits):\n";
    cout << "Enter data bits (positions d7, d6, d5, d3): ";
    cin >> data[6] >> data[5] >> data[4] >> data[2];  // d7, d6, d5, d3

    // Encoding the data using Hamming Code
    encodeHammingCode(data);

    // Display the encoded data
    cout << "\nEncoded data (7 bits including parity):\n";
    for (int i = 0; i < 7; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    // Simulating data transmission with errors (received data)
    cout << "\nEnter received data bits one by one (with possible errors):\n";
    for (int i = 0; i < 7; i++) {
        cin >> receivedData[i];  // Received data bits (with possible errors)
    }

    // Detect and correct errors in the received data
    detectAndCorrectError(receivedData);

    return 0;
}


//1011
//1010101
//1011101
//1010101
