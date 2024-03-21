#include "test-generator.hpp"

// Constructor
TestGenerator::TestGenerator(string datasetPath, Redis database) {
    // Set dataset path
    this->datasetPath = datasetPath;
    
    // Set redis database
    this->database = database;
}

// Destructor
TestGenerator::~TestGenerator() {
    // End of the function
}

void TestGenerator::readDataset() {
    fstream dataset;

    // Open dataset file READONLY
    dataset.open(this->datasetPath, ios::in);

    // Check if file is open correctly
    if (!dataset.is_open()) {
        cerr << "Error: Unable to open file " << this->datasetPath << endl;
        return;
    }

    // Read dataset line by line
    string line;
    while (getline(dataset, line)) {
        // Add line to list
        this->lines.push_back(line);
    }

    // Close dataset file 
    dataset.close();

    // Remove header
    lines.pop_front();

    // End of the function
}

void TestGenerator::loadDataset() {

    // Iterate through the list of lines
    int lineIndex = 1;
    for (string line : this->lines) {
        // Add line to Redis list
        this->database.setData(to_string(lineIndex), line);

        // Update line index
        lineIndex++;
    }

    // End of the function
}

