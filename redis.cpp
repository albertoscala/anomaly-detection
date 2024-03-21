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

void Redis::setData(string key, string value) {
    redisReply *reply = (redisReply *)redisCommand(this->connection, "SET %s %s", key.c_str(), value.c_str());
    
    if (!reply) {
        cerr << "Error: Failed to set key '" << key << "'." << endl;
        
        //TODO: Gestire errore
    }

    freeReplyObject(reply);
    
    // End of function
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