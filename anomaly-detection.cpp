#include <iostream>
#include <utility>
#include "redis.hpp"
#include "test-generator.hpp"
#include "postgre.hpp"
#include "statistics.hpp"
#include "csv.hpp"
#include "json.hpp"

using namespace std;

// Number of tables
const int n_tables = 3;

// Array of the tables
const string tables[n_tables] = {"means", "variances", "covariances"};

// Array of queries to create the tables
const string tables_queries[n_tables] = {
    "CREATE TABLE means (id INT, mean JSON);",             // Query to create the means table
    "CREATE TABLE variances (id INT, variance JSON);",     // Query to create the variances table
    "CREATE TABLE covariances (id INT, covariance JSON);"  // Query to create the covariances table
};

// Get the window size from the command line
int getWindowSize(int argc, char **argv);

// Get the threshold from the command line
int getThreshold(int argc, char **argv);

// Setup the tables in the database
// Check if they exists and flush them
// If they don't exist, create them
void tableSetup(Postgre postgre);

// Function to convert a vector of strings into a vector of numbers
vector<double> convertToNumbers(vector<string> sensors);

// Function to calculate and prepare the values for the mean and variance
pair<vector<double>, vector<double>> computations(vector<vector<double>> matrix);

// Find the anomaly give a dataset, window size and a threshold
void findAnomalies(int windowSize, int threshold, Redis &database, Postgre &postgre, int testSize);

// Main function
int main(int argc, char **argv) {
    
    // Get the window size from the command line
    int windowSize = getWindowSize(argc, argv);
    
    cout << "Window size: " << windowSize << endl;

    // Get the threshold from the command line
    int threshold = getThreshold(argc, argv);

    cout << "Threshold: " << threshold << endl;

    // Create redis object
    Redis database = Redis("localhost", 6379);

    // Check if the redis database is alive
    if (!database.alive()) {
        cerr << "Error: Redis database is not alive." << endl;
        return 1;
    }

    // Create a TestGenerator object
    TestGenerator testGenerator("dataset/dataset_clean.csv", database);

    cout << "TestGenerator object created" << endl;

    // Read the dataset
    if (!testGenerator.readDataset()) {
        cerr << "Error: Unable to read the dataset." << endl;
        return 1;
    }

    // Load the dataset into Redis
    if (!testGenerator.loadDataset()) {
        cerr << "Error: Unable to load the dataset into Redis." << endl;
        return 1;
    }

    // Let's hope for the best -_-"

    // Create a Postgre object
    Postgre postgre = Postgre("127.0.0.1", 5432);
    
    // Check if the postgre database is alive
    if (!postgre.alive()) {
        cerr << "Error: Postgre database is not alive." << endl;
        return 1;
    }

    // Setup the tables for the databases
    //TODO: Forse lo dovremmo spostare in alto tra i preparativi non cambia nulla però...
    tableSetup(postgre);

    // Find anomalies
    findAnomalies(windowSize, threshold, database, postgre, testGenerator.getTestSize());

    // End of the program
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

// Get the threshold from the command line
int getThreshold(int argc, char **argv) {
    
    // Default threshold
    int threshold = 3;
    
    // Check if threshold is provided as a command line argument
    if (argc > 2) {
        // Convert the string to an integer
        threshold = atoi(argv[2]);
    }

    return threshold;
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
            cout << "Table " << tables[i] << " does not exist." << endl;
            cout << "Creating table " << tables[i] << "..." << endl;
            //postgre.createTable(tables_queries[i]);
        } else {
            // Flush/Clean the table
            cout << "Table " << tables[i] << " exists." << endl;
            cout << "Flushing table " << tables[i] << "..." << endl;
            //postgre.flushTable(tables[i]);
        }
    }
}

// Function to convert a vector of strings into a vector of numbers
vector<double> convertToNumbers(vector<string> sensors) {
    double number;
    vector<double> numbers;
    
    for (string sensor : sensors) {
        try {
            // Try to convert the string to a double
            number = stod(sensor);
            numbers.push_back(number);
        } catch (invalid_argument e) {
            // Report the error
            cerr << "Error: non numeric value found, will be zeroed" << endl;
            
            // Zero the value
            number = 0.0;
            numbers.push_back(number);
        }
    }

    return numbers;
}

// Function to calculate and prepare the values for the mean and variance
pair<vector<double>, vector<double>> computations(vector<vector<double>> matrix) {
    vector<double> values;
    vector<double> means;
    vector<double> variances;

    // Create the pair to store the values
    pair<vector<double>, vector<double>> result;

    for (int i=0; i<matrix[0].size(); i++) {
        // Create a vector to store the values of the sensors
        values.clear();
        
        // TODO: Check if the vector is empty

        // Set the for loop to get the values of the sensors
        for (int j=0; j<matrix.size(); j++) {
            values.push_back(matrix[j][i]);
        }

        // Calculate the mean
        double mean = Statistics::calculateMean(values);
        
        // Calculate the variance
        double variance = Statistics::calculateVariance(values, mean);
        
        // Insert the mean and variance in the vectors
        means.push_back(mean);
        variances.push_back(variance);
    }

    // Insert the vectors in the pair
    result.first = means;
    result.second = variances;

    // End of the function
    return result;
}

// Find the anomaly give a dataset, window size and a threshold
void findAnomalies(int windowSize, int threshold, Redis &database, Postgre &postgre, int testSize) {
    // Create a matrix to store the data
    vector<vector<double>> matrix;
    
    // Create a string to store the data
    string data;

    // Create a vector to store the sensors
    vector<string> s_sensors;
    vector<double> d_sensors;

    // Create a pair to store the values
    pair<vector<double>, vector<double>> values;

    // Start getting the data from the database

    // Setting the for loop for the window
    for (int i=1; i <= testSize; i+=windowSize) {

        cout << "I steps: " << i << endl;

        // Clear the matrix for the new window
        matrix.clear();

        // Check if the matrix is clear
        if (!matrix.empty()) {
            cerr << "Error: Matrix is not empty." << endl;
            return;
        }

        // Set the for loop to retrive the data from redis
        // Lower than the window size + i (for example 10+1=11 to 20 not 21)
        // Or lower than the test size
        for (int j=i; j < i+windowSize && j <= testSize; j++) {
            
            cout << "J steps: " << j << endl;
            
            // Get the data from the database
            data = database.getData(to_string(j));
            
            // Split the data
            s_sensors = CSV::decompose(data);
            
            // Drop the first element (timestamp)
            s_sensors.erase(s_sensors.begin());

            // Sensors are 999

            // Convert the sensors to numbers
            d_sensors = convertToNumbers(s_sensors);

            // Insert in the vector matrix
            matrix.push_back(d_sensors);
        }

        values = computations(matrix);

        // Debug

        //cout << "Means size: " << values.first.size() << endl;
        //cout << "Variances size: " << values.second.size() << endl;

        // Print the means
        //for (double mean : values.first) {
        //    cout << mean << " ";
        //}
        //cout << endl;



        break;
    }
}