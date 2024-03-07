#include <iostream>
using namespace std;

int getWindowSize(int argc, char **argv) {
    
    // Default window size
    int windowSize = 10;
    
    // Check if window size is provided as a command line argument
    if (argc > 1) {
        // Convert the string to an integer
        windowSize = atoi(argv[1]);
    }

    return windowSize;
}

int main(int argc, char **argv) {
    
    // Get the window size from the command line
    int windowSize = getWindowSize(argc, argv);
    
    cout << "Window size: " << windowSize << endl;

    return 0;
}