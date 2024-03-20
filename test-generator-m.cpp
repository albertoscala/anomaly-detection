#include <iostream>
#include <fstream>
#include <list>
#include <hiredis/hiredis.h>

using namespace std;

list<string> readDataset(string filename) {

    list<string> lines;
    fstream dataset;

    // Open dataset file READONLY
    dataset.open(filename, ios::in);

    // Check if file is open correctly
    if (!dataset.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return lines;
    }

    // Read dataset line by line
    string line;
    while (getline(dataset, line)) {
        // Add line to list
        lines.push_back(line);
    }


    // Close dataset file 
    dataset.close();

    // Remove header
    lines.pop_front();

    // Return list of lines
    return lines;
}

// Function that handles connection to Redis server
redisContext* connectToRedis(string hostname, int port) {

    // Connect to Redis server
    redisContext* context = redisConnect(hostname.c_str(), port);

    // Check if connection is successful
    if (context == NULL || context->err) {
        if (context) {
            cerr << "Connection error: " << context->errstr << endl;
            redisFree(context);
        } else {
            cerr << "Error: Failed to allocate Redis context" << endl;
        }

        return nullptr;
    }

    // Return Redis context
    return context;
}

bool loadDataset(redisContext* connection, const list<string>& lines) {
    // Load dataset into Redis
    int line_number = 1;

    for(string line : lines) {
        redisReply* reply = (redisReply*) redisCommand(connection, "SET %d %s", line_number, line.c_str());

        if (!reply) {
            cerr << "Failed to execute Redis command" << endl;
            return false;
        }

        freeReplyObject(reply);

        line_number++;
    }

    return true;
}

int main(int argc, char **argv) {

    // Read dataset
    list<string> lines = readDataset("dataset/dataset_clean.csv");
    
    // Check if dataset is correctly read
    if (lines.empty()) {
        cerr << "Error: Failed to read dataset" << endl;
        return 1;
    }

    cout << "Dataset loaded" << endl;

    // TODO: Dopo sistemare bene errori
    redisContext* connection = connectToRedis("localhost", 6379);
    if (!connection) {
        cerr << "Error: Failed to connect to Redis server" << endl;
        return 1;
    }

    cout << "Connected to Redis server" << endl;

    // Load dataset into Redis
    bool status = loadDataset(connection, lines);
    
    // Check if dataset is correctly loaded
    if(!status) {
        cerr << "Error: Failed to load dataset into Redis" << endl;
        return 1;
    }

    cout << "Dataset loaded" << endl;

    return 0;
}