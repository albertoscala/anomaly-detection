#include <iostream>
#include <utility>
#include "redis.hpp"
#include "test-generator.hpp"
#include "postgre.hpp"
#include "statistics.hpp"
#include "csv.hpp"
#include "json.hpp"
#include <cmath>
#include "monitor.hpp"

using namespace std;

// Number of tables
const int n_tables = 2;

// Array of the tables
const string tables[n_tables] = {"means", "covariances"};

// Array of queries to create the tables
const string tables_queries[n_tables] = {
    "CREATE TABLE means (id INT PRIMARY KEY, data JSON);",          // Query to create the means table
    "CREATE TABLE covariances (id INT PRIMARY KEY, data JSON);"     // Query to create the covariances table
};

// Struct to store the anomalies
//struct Anomaly {
//    int window;
//    int meanAnomaly;
//    int covarianceAnomaly;
//};

// Get the window size from the command line
int getWindowSize(int argc, char **argv);

// Get the mean threshold from the command line
double getThresholdMean(int argc, char **argv);

// Get the covariance threshold from the command line
double getThresholdCovariance(int argc, char **argv);

// Setup the tables in the database
// Check if they exists and flush them
// If they don't exist, create them
void tableSetup(Postgre postgre);

// Function to convert a vector of strings into a vector of numbers
vector<double> convertToNumbers(vector<string>& sensors);

// Function to calculate and prepare the values for the mean
vector<double> meanComputation(vector<vector<double>>& matrix);

// Function to calculate and prepare the values for the covariance
vector<double> covarianceComputation(vector<vector<double>>& matrix_p, vector<vector<double>>& matrix_a, vector<double>& means_p, vector<double>& means_a);

// Function to upload data to the database
bool uploadData(Postgre& postgre, string table, int timestamp, string json_data);

// Function to verify the anomalies
void verifyAnomalies(int win_id, vector<vector<double>>& matrix_a, vector<double>& means, vector<double>& covariances, double threshold_m, double threshold_c, vector<struct Anomaly>& anomalies);

// Find the anomaly give a dataset, window size and a threshold
vector<Anomaly> findAnomalies(int windowSize, double threshold_m, double threshold_c, Redis &database, Postgre &postgre, int testSize);

// Function to display the results of the analysis
void displayResults(vector<Anomaly>& anomalies);

Monitor monitor = Monitor("anomaly_detection", "albys", "12", "127.0.0.1", 5432);

// Main function
int main(int argc, char **argv) {
    
    // Get the window size from the command line
    int windowSize = getWindowSize(argc, argv);
    
    // 1st non-functional monitor
    monitor.windowSizeMonitor(windowSize);

    cout << "Window size: " << windowSize << endl;

    // Get the mean threshold from the command line
    double threshold_m = getThresholdMean(argc, argv);

    // 2nd non-functional monitor
    monitor.thresholdMeanMonitor(threshold_m);

    cout << "Threshold Mean: " << threshold_m << endl;

    // Get the covariance threshold from the command line
    double threshold_c = getThresholdCovariance(argc, argv);

    // 3rd non-functional monitor
    monitor.thresholdCovarianceMonitor(threshold_c);

    cout << "Threshold Covariance: " << threshold_c << endl;

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
    Postgre postgre = Postgre("anomaly_detection", "albys", "12", "127.0.0.1", 5432);

    // Setup the tables for the databases
    //TODO: Forse lo dovremmo spostare in alto tra i preparativi non cambia nulla però...
    tableSetup(postgre);

    // Find anomalies
    vector<Anomaly> anomalies = findAnomalies(windowSize, threshold_m, threshold_c, database, postgre, testGenerator.getTestSize());

    // Display anomalies
    displayResults(anomalies);

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

    // Check if the window size is greater than 0
    if (windowSize < 1) {
        cerr << "Error: window size must be greater than 0." << endl;
        exit(1);
    }

    return windowSize;
}

// Get the mean threshold from the command line
double getThresholdMean(int argc, char **argv) {
    
    // Default threshold
    double threshold = 0.3;
    
    // Check if threshold is provided as a command line argument
    if (argc > 2) {
        // Convert the string to an integer
        threshold = stod(argv[2]);
    }

    return threshold;
}

// Get the covariance threshold from the command line
double getThresholdCovariance(int argc, char **argv) {
    
    // Default threshold
    double threshold = 0.3;
    
    // Check if threshold is provided as a command line argument
    if (argc > 3) {
        // Convert the string to an integer
        threshold = stod(argv[3]);
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
            postgre.createTable(tables_queries[i]);
        } else {
            // Flush/Clean the table
            cout << "Table " << tables[i] << " exists." << endl;
            cout << "Flushing table " << tables[i] << "..." << endl;
            postgre.flushTable(tables[i]);
        }
    }
}

// Function to convert a vector of strings into a vector of numbers
vector<double> convertToNumbers(vector<string>& sensors) {
    double number;
    vector<double> numbers;
    
    for (string sensor : sensors) {
        try {
            // Try to convert the string to a double
            number = stod(sensor);
            numbers.push_back(number);
        } catch (invalid_argument e) {
            // Report the error
            //cerr << "Error: non numeric value found, will be zeroed" << endl;
            
            // Zero the value
            number = 0.0;
            numbers.push_back(number);
        }
    }

    return numbers;
}

// Function to calculate and prepare the values for the mean
vector<double> meanComputation(vector<vector<double>>& matrix) {
    vector<double> values;
    vector<double> means;

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
        
        // Insert the mean and variance in the vectors
        means.push_back(mean);
    }

    // End of the function
    return means;
}

// Function to calculate and prepare the values for the covariance
vector<double> covarianceComputation(vector<vector<double>>& matrix_p, vector<vector<double>>& matrix_a, vector<double>& means_p, vector<double>& means_a) {
    // Create a vector to store the values
    vector<double> values_p;    // Values from the precedent matrix
    vector<double> values_a;    // Values from the actual matrix

    // Create a vector to store the covariances
    vector<double> covariances;

    // Create a variable to temporarily store the covariance
    double covariance;

    // Use matrix_a as limits since the two matrices have the same size
    for (int i=0; i<matrix_a[0].size(); i++) {
        // Create a vector to store the values of the sensors from the precedent and actual matrix
        values_p.clear();
        values_a.clear();

        // Set the for loop to get the values of the sensors
        // Use matrix_a as limits since the two matrices have the same size
        for (int j=0; j<matrix_a.size(); j++) {
            values_p.push_back(matrix_p[j][i]);
            values_a.push_back(matrix_a[j][i]);
        }

        // Calculate the covariance
        double covariance = Statistics::calculateCovariance(values_a, values_p, means_a[i], means_p[i]);

        // Insert the covariance in the vector
        covariances.push_back(covariance);
    }

    // End of the function
    return covariances;
}

// Function to verify the anomalies
void verifyAnomalies(int win_id, vector<vector<double>>& matrix_a, vector<double>& means, vector<double>& covariances, double threshold_m, double threshold_c, vector<struct Anomaly>& anomalies) {
    // Create a vector to store the distances
    vector<double> distances_means;

    // Calculate the distances
    distances_means = Statistics::calculateMeanDistance(matrix_a, means);

    // Create a variable to store the anomaly
    struct Anomaly anomaly;

    // Initialize the anomaly
    anomaly.window = -1;
    anomaly.meanAnomaly = 0;
    anomaly.covarianceAnomaly = 0;

    // Set the for loop to verify the mean anomalies
    for (int i=0; i<distances_means.size(); i++) {
        // Check if the distance is greater than the threshold
        if (abs(distances_means[i]) > threshold_m) {
            // Report the anomaly
            // Debug
            //cout << "Anomaly detected at sensor " << i << " with distance " << distances_means[i] << endl;
            anomaly.window = win_id;
            anomaly.meanAnomaly++;
        }
    }

    // Set the for loop to verify the covariance anomalies
    for (int i=0; i<covariances.size(); i++) {
        // Check if the covariance is greater than the threshold
        if (abs(covariances[i]) > threshold_c) {
            // Report the anomaly
            // Debug
            //cout << "Anomaly detected at sensor " << i << " with covariance " << covariances[i] << endl;
            anomaly.window = win_id;
            anomaly.covarianceAnomaly++;
        }
    }

    // Add the anomaly to the vector
    if (anomaly.window != -1)
        anomalies.push_back(anomaly);
}

// Find the anomaly give a dataset, window size and a threshold
vector<Anomaly> findAnomalies(int windowSize, double threshold_m, double threshold_c, Redis &database, Postgre &postgre, int testSize) {
    // Create the vectors to store the anomalies
    vector<struct Anomaly> anomalies;
    
    // Create a matrix to store the data
    vector<vector<double>> matrix_p;    // Precedent matrix
    vector<vector<double>> matrix_a;    // Actual matrix
    
    // Create a string to store the data
    string data;

    // Create a vector to store the sensors
    vector<string> s_sensors;
    vector<double> d_sensors;

    // Create a vector to store the means
    vector<double> means_p;     // Precedent means
    vector<double> means_a;     // Actual means

    // Create a vector to store the covariances
    vector<double> covariances_a;    // Actual covariances

    // Strings to store the JSON values
    string means;
    string covariances; 

    // Start getting the data from the database

    cout << "Starting the analysis..." << endl;

    // Setting the for loop for the window
    for (int i=1, k=1; i <= testSize; i+=windowSize, k++) {
        // Debug I steps
        cout << "I steps: " << i << endl;

        // Clear the matrix for the new window
        matrix_a.clear();

        cout << "Matrix cleared" << endl;

        // Check if the matrix is clear
        if (!matrix_a.empty()) {
            cerr << "Error: Matrix is not empty." << endl;
            exit(1);
        }

        cout << "Matrix is empty" << endl;

        // Set the for loop to retrive the data from redis
        // Lower than the window size + i (for example 10+1=11 to 20 not 21)
        // Or lower than the test size
        for (int j=i; j < i+windowSize && j <= testSize; j++) {
            // Debug J steps
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
            matrix_a.push_back(d_sensors);
        }

        means_a = meanComputation(matrix_a);

        // 1st functional monitor
        monitor.meanCalculationMonitor(means_a);

        // Encode the mean values in JSON
        means = JSON::compose(means_a);

        // Debug
        //cout << "Means: " << means << endl;

        // Upload the means and covariances to the database
        postgre.postData("means", k, means);

        // Debug
        //cout << "Means: " << means << endl;

        // Calculate the covariance if we are at the second window
        if (k > 1) {
            // Calculate the covariance
            covariances_a = covarianceComputation(matrix_a, matrix_p, means_a, means_p);

            // 2nd functional monitor
            monitor.covarianceCalculationMonitor(covariances_a);

            // Encode the covariance values in JSON
            covariances = JSON::compose(covariances_a);

            // Debug
            //cout << "Covariances: " << covariances << endl;

            // Upload the covariances to the database
            postgre.postData("covariances", k, covariances);
        
            // Verify the anomalies
            verifyAnomalies(i, matrix_a, means_p, covariances_a, threshold_m, threshold_c, anomalies);
        }

        // Swtich the matrices and vectors

        // Set the precedent matrix
        matrix_p = matrix_a;

        // Set the precedent means
        means_p = means_a;
    }

    // 3rd functional monitor
    monitor.anomalyCalculationMonitor(anomalies);

    // Return anomalies vector
    return anomalies;
}

// Function to display the results of the analysis
void displayResults(vector<Anomaly>& anomalies) {
    // Create template for a table
    cout << "| Window | Mean Anomalies | Covariance Anomalies |" << endl;
    cout << "|--------|----------------|-----------------------|" << endl;

    // Loop through the anomalies
    for (Anomaly anomaly : anomalies) {
        cout << "| " << anomaly.window << "\t | \t\t" << anomaly.meanAnomaly << "\t\t | \t\t\t" << anomaly.covarianceAnomaly << " \t\t|" << endl;
    }

    // Close the table
    cout << "|--------|----------------|-----------------------|" << endl;

    // End of the function
}