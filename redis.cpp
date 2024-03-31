#include "redis.hpp"

// Constructor
Redis::Redis(string hostname, int port) {
    // Connect to Redis server
    this->connection = redisConnect(hostname.c_str(), port);
}

// Destructor
Redis::~Redis() {
    // Free Redis connection
    redisFree(this->connection);

}

bool Redis::alive() {
    // Check if connection is alive
    if (this->connection == NULL || this->connection->err) {
        cerr << "Error: Connection to Redis server failed." << endl;
        return false;
    }

    return true;

    // End of function
}

bool Redis::setData(string key, string value) {
    redisReply *reply = (redisReply *)redisCommand(this->connection, "SET %s %s", key.c_str(), value.c_str());
    
    if (!reply) {
        cerr << "Error: Failed to set key '" << key << "'." << endl;
        
        return false;
    }

    freeReplyObject(reply);
    
    // End of function
    return true;
}

string Redis::getData(string key) {
    redisReply *reply = (redisReply *)redisCommand(this->connection, "GET %s", key.c_str());
    
    if (!reply || reply->type == REDIS_REPLY_NIL) {
        cerr << "Error: Key '" << key << "' not found." << endl;
        
        if (reply) 
            freeReplyObject(reply);
    }

    string value = reply->str;
    freeReplyObject(reply);
    return value;

    // End of function
}