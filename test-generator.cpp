#include "test-generator.hpp"

// Constructor
TestGenerator::TestGenerator(string datasetPath, Redis& database) : database(database) {
    // Set dataset path
    this->datasetPath = datasetPath;
    
}

// Destructor
TestGenerator::~TestGenerator() {
    // End of the function
}

bool TestGenerator::readDataset() {
    fstream dataset;

    // Open dataset file READONLY
    dataset.open(this->datasetPath, ios::in);

    // Check if file is open correctly
    if (!dataset.is_open()) {
        cerr << "Error: Unable to open file " << this->datasetPath << endl;
        return false;
    }

    // Read dataset line by line
    // Let's suppose this function is god...
    // And does not return any error
    string line;
    while (getline(dataset, line)) {
        // Add line to list
        this->lines.push_back(line);
    }

    // Close dataset file 
    dataset.close();

    // Remove header
    lines.pop_front();

    // Set number of lines
    this->testSize = this->lines.size();

    // End of the function
    return true;
}

bool TestGenerator::loadDataset() {

    // Iterate through the list of lines
    int lineIndex = 1;
    for (string line : this->lines) {
        // Add line to Redis list
        if (!this->database.setData(to_string(lineIndex), line)) {
            cerr << "Error: Unable to set data in Redis. Line: " << lineIndex << endl;
            return false;
        }

        // Update line index
        lineIndex++;
    }

    // End of the function
    return true;
}

int TestGenerator::getTestSize() {
    return this->testSize;
}
