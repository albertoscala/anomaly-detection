#include <iostream>
#include "redis.hpp"
#include "test-generator.hpp"
#include "postgre.hpp"
#include "statistics.hpp"
#include "csv.hpp"
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

    // Create redis database
    Redis database = Redis("localhost", 6379);

    // Create a TestGenerator object
    TestGenerator testGenerator("dataset/dataset_clean.csv", database);

    cout << "TestGenerator object created" << endl;

    // Read the dataset
    testGenerator.readDataset();

    cout << "Dataset read" << endl;

    // Load the dataset into Redis
    testGenerator.loadDataset();

    //TODO: Controllare come gestire se non li carica XD
    cout << "Dataset loaded" << endl;

    // Let's hope for the best -_-"

    Postgre postgre = Postgre("127.0.0.1", 5432);
    // boh
    return 0;
}