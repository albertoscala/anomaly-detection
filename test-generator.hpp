#ifndef TEST_GENERATOR_HPP
#define TEST_GENERATOR_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "redis.hpp"

using namespace std;

class TestGenerator {
    private:
        string datasetPath;
        list<string> lines;
        Redis& database;
        int testSize;
    public:
        // Constructor
        TestGenerator(string datasetPath, Redis& database);

        // Destructor
        ~TestGenerator();

        bool readDataset();

        bool loadDataset();

        int getTestSize();
};

#endif // TEST_GENERATOR_HPP
