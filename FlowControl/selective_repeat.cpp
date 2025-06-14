#include <iostream>  
#include <cstdlib>   
#include <ctime>     

using namespace std;

// Selective Repeat ARQ Protocol
void selectiveRepeat(int totalFrames, int windowSize) {
    cout << "\n--- Selective Repeat ARQ ---\n";

    bool ack[100] = {false};  // ACK array to track received acknowledgments
    int i = 0;  // Frame pointer

    // Continue until all frames are acknowledged
    while (i < totalFrames) {
        // Sending frames in current window
        cout << "\nSending frames: ";
        for (int j = i; j < i + windowSize && j < totalFrames; ++j) {
            if (!ack[j]) {
                cout << j << " ";
            }
        }
        cout << endl;

        // Simulate ACK reception for each frame
        for (int j = i; j < i + windowSize && j < totalFrames; ++j) {
            if (!ack[j]) {
                int received = rand() % 2;  // 0 or 1 (50% chance)

                if (received) {
                    ack[j] = true;
                    cout << "ACK received for frame: " << j << endl;
                } else {
                    cout << "ACK lost for frame: " << j << endl;
                }
            }
        }

        // Slide window forward past acknowledged frames
        while (i < totalFrames && ack[i]) {
            ++i;
        }
    }

    cout << "\nAll frames sent successfully using Selective Repeat.\n";
}

int main() {
    srand(time(0));  // Seed the random number generator

    int totalFrames = 10;  // Total number of frames to send
    int windowSize;

    // Input window size
    cout << "Enter window size: ";
    cin >> windowSize;

    // Call the Selective Repeat function
    selectiveRepeat(totalFrames, windowSize);

    return 0;
}
