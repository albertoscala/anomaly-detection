#include <iostream>
#include "redis.hpp"
#include "test-generator.hpp"
#include "postgre.hpp"
#include "statistics.hpp"
#include "csv.hpp"

using namespace std;

// Number of tables
const int n_tables = 3;

// Array of the tables
const string tables[n_tables] = {"means", "variances", "covariances"};

// Array of queries to create the tables
const string tables_queries[n_tables] = {
    "CREATE TABLE means (id INT, mean FLOAT);",             // Query to create the means table
    "CREATE TABLE variances (id INT, variance FLOAT);",     // Query to create the variances table
    "CREATE TABLE covariances (id INT, covariance FLOAT);"  // Query to create the covariances table
};

// Get the window size from the command line
int getWindowSize(int argc, char **argv);

// Get the threshold from the command line
int getThreshold(int argc, char **argv);

// Setup the tables in the database
// Check if they exists and flush them
// If they don't exist, create them
void tableSetup(Postgre postgre);

// Find the anomaly give a dataset, window size and a threshold
void findAnomalies(int windowSize, int threshold, Redis database, Postgre postgre);

// Main function
int main(int argc, char **argv) {
    
    // Get the window size from the command line
    int windowSize = getWindowSize(argc, argv);
    
    cout << "Window size: " << windowSize << endl;

    // Create redis database
    Redis database = Redis("localhost", 6379);

    // Create a TestGenerator object
    TestGenerator testGenerator("dataset/dataset_clean.csv", database);

    cout << "TestGenerator object created" << endl;

    // Read the dataset
    testGenerator.readDataset();

    cout << "Dataset read" << endl;

    // Load the dataset into Redis
    testGenerator.loadDataset();

    //TODO: Controllare come gestire se non li carica XD
    cout << "Dataset loaded" << endl;

    // Let's hope for the best -_-"

    Postgre postgre = Postgre("127.0.0.1", 5432);
    
    // Setup the tables for the databases
    //TODO: Forse lo dovremmo spostare in alto tra i preparativi non cambia nulla però...
    tableSetup(postgre);

    return 0;
}

// Get the window size from the command line
int getWindowSize(int argc, char **argv) {
    
    // Default window size
    int windowSize = 10;
    
    // Check if window size is provided as a command line argument
    if (argc > 1) {
        // Convert the string to an integer
        windowSize = atoi(argv[1]);
    }

    return windowSize;
}

// Setup the tables in the database
// Check if they exists and flush them
// If they don't exist, create them
void tableSetup(Postgre postgre) {
    // Setup all the tables
    for (int i=0; i<n_tables; i++) {
        // Check if the table exists
        if (!postgre.tableExists(tables[i])) {
            // Create the table
            postgre.createTable(tables_queries[i]);
        } else {
            // Flush/Clean the table
            postgre.flushTable(tables[i]);
        }
    }
}

// Find the anomaly give a dataset, window size and a threshold
void findAnomalies(int windowSize, int threshold, Redis database, Postgre postgre) {
    
}