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
    public:
        // Constructor
        TestGenerator(string datasetPath, Redis& database);

        // Destructor
        ~TestGenerator();

        void readDataset();

        void loadDataset();
};

#endif // TEST_GENERATOR_HPP
