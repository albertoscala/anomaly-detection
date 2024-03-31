#ifndef REDIS_HPP
#define REDIS_HPP

#include <iostream>
#include <string>
#include <hiredis/hiredis.h>

using namespace std;

class Redis {
    private:
        redisContext* connection;
    public:
        // Constructor
        Redis(string hostname, int port);

        // Destructor
        ~Redis();

        bool alive();

        bool setData(string key, string value);

        string getData(string key);
};

#endif // REDIS_HPP
