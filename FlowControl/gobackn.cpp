#include <iostream>  
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time() to seed rand()

using namespace std;

// Go-Back-N ARQ Protocol
void goBackN(int totalFrames, int windowSize) {
    cout << "\n--- Go-Back-N ARQ ---\n";

    int base = 0;  // The starting point of the current window

    // Continue until all frames are sent
    while (base < totalFrames) {
        // Sending window of frames
        cout << "\nSending frames: ";
        for (int i = base; i < base + windowSize && i < totalFrames; ++i) {
            cout << i << " ";  // Frame numbers
        }
        cout << endl;

        // Simulate ACK loss randomly
        int ackLostIndex = rand() % windowSize;  // Random index in window
        int lostFrame = base + ackLostIndex;

        if (lostFrame < totalFrames) {
            cout << "ACK lost for frame: " << lostFrame << endl;
            cout << "Resending from frame: " << lostFrame << endl;

            base = lostFrame;  // Restart from the lost frame
        } else {
            // All frames in window acknowledged
            base += windowSize;
        }
    }

    cout << "\nAll frames sent successfully using Go-Back-N.\n";
}

int main() {
    srand(time(0));  // Seed the random number generator

    int totalFrames = 10;  // Total number of frames to send
    int windowSize;

    // Input window size
    cout << "Enter window size: ";
    cin >> windowSize;

    // Call the Go-Back-N function
    goBackN(totalFrames, windowSize);

    return 0;
}
