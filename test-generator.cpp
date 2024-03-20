#include "test-generator.hpp"

// Constructor
TestGenerator::TestGenerator(string datasetPath, string hostname, int port) {
    // Set dataset path
    this->datasetPath = datasetPath;
    
    // Connect to Redis server
    this->connection = redisConnect(hostname.c_str(), port);
}

// Destructor
TestGenerator::~TestGenerator() {
    // Free Redis connection
    redisFree(this->connection);
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
    for (auto line : this->lines) {
        // Add line to Redis list
        redisReply* reply = (redisReply*)redisCommand(connection, "LPUSH dataset %s", line.c_str());

        // Check if command was successful
        if (reply == NULL) {
            cerr << "Error: " << connection->errstr << endl;
            return;
        }

        // Free reply
        freeReplyObject(reply);
    }

    // End of the function
}

