#ifndef TEST_GENERATOR_HPP
#define TEST_GENERATOR_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <hiredis/hiredis.h>

using namespace std;

class TestGenerator {
    private:
        string datasetPath;
        list<string> lines;
        redisContext* connection;
    public:
        // Constructor
        TestGenerator(string datasetPath, string hostname, int port);

        // Destructor
        ~TestGenerator();

        void readDataset();

        void loadDataset();
};

#endif // TEST_GENERATOR_HPP
