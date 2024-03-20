#include <iostream>
#include "test-generator.hpp"
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

    // Create a TestGenerator object
    TestGenerator testGenerator("dataset/dataset_clean.csv", "localhost", 6379);

    cout << "TestGenerator object created" << endl;

    // Read the dataset
    testGenerator.readDataset();

    cout << "Dataset read" << endl;

    // Load the dataset into Redis
    testGenerator.loadDataset();

    cout << "Dataset loaded" << endl;

    // Let's hope for the best -_-"
    return 0;
}