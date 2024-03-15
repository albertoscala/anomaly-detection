#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <hiredis/hiredis.h>

using namespace std;

bool readDataset(const string& filename, list<string>& lines) {

    ifstream file(filename);
    // check for errors while opening file
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    // read first line of db to define all features
    string line;
    if (getline(file, line)) {
        lines.push_back(line);
    }


    // close file and return 
    file.close();
    return true;
}

// Function that handles connection to Redis server
redisContext* connectToRedis(const char* hostname, int port) {

    redisContext* context = redisConnect(hostname, port);

    // failed to connect
    if (context == NULL || context->err) {
        if (context) {
            cerr << "Connection error: " << context->errstr << endl;
            redisFree(context);
        } else {
            cerr << "Error: Failed to allocate Redis context" << endl;
        }
        return nullptr;
    }

    // connection successful 
    cout << "Connected to Redis server" << endl;
    return context;
}

bool loadDataset(const char* hostname, int port, const list<string>& lines) {
    // connect to Redis server
    redisContext* context = connectToRedis(hostname, port);

    int line_numb = 1;
    for(const auto& line : lines) {
        redisReply* reply = (redisReply*)redisCommand(context, "SET %d %s", line_numb, line.c_str());
        if (!reply) {
            cerr << "Failed to execute Redis command" << endl;
            redisFree(context);
            return false;
        }
        freeReplyObject(reply);
        line_numb++;
    }

    redisFree(context);
    return true;
}

int main(int argc, char **argv) {

    list<string> lines;
    readDataset("dataset/dataset_clean.csv", lines);
    loadDataset("localhost", 6379, lines);
    
    return 0;
}