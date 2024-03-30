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
const string tables[3] = {"means", "variances", "covariances"};

// Array of queries to create the tables
const string tables_queries[3] = {
    "CREATE TABLE means (id INT, mean FLOAT);",             // Query to create the means table
    "CREATE TABLE variances (id INT, variance FLOAT);",     // Query to create the variances table
    "CREATE TABLE covariances (id INT, covariance FLOAT);"  // Query to create the covariances table
}

// Get the window size from the command line
int getWindowSize(int argc, char **argv);

// Setup the tables in the database
// Check if they exists and flush them
// If they don't exist, create them
bool tableSetup(Postgre postgre);

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
    
    // Check if the table exists
    if (!(
        postgre.tableExists("means") && 
        postgre.tableExists("variances") && 
        postgre.tableExists("covariances"))
        ) {
        // Create the table
        postgre.createTable("CREATE TABLE anomalies (timestamp TIMESTAMP, value FLOAT, anomaly BOOLEAN);");
    }

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
bool tableSetup(Postgre postgre) {
    // Setup all the tables
    for (int i=0; i<; i++) {

    }

}