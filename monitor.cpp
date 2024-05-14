#include "monitor.hpp"

// Constructor
Monitor::Monitor(string dbname, string user, string password, string hostname, int port) {
    // Create the Postgre object
    this->postgre = new Postgre(dbname, user, password, hostname, port);

    // Create the table for the monitor
    this->postgre->createTable(MONITOR_TABLE);
}

// Functional monitors

void Monitor::meanCalculationMonitor(string message) {
    // Insert the message into the monitor table
    this->postgre->postData("monitor", message);
}

void Monitor::covarianceCalculationMonitor(string message) {
    // Insert the message into the monitor table
    this->postgre->postData("monitor", message);
}

void Monitor::anomalyCalculationMonitor(string message) {
    // Insert the message into the monitor table
    this->postgre->postData("monitor", message);
}

// Non-functional monitors

void Monitor::windowSizeMonitor(int windowSize) {
    // Monitor control
    if (windowSize != 0) {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", "windowSize monitor test passed");
    } else {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", "windowSize monitor test failed");
    }
}

void Monitor::thresholdMeanMonitor(double threshold) {
    // Monitor control
    if (threshold != NULL) {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", "thresholdMean monitor test passed");
    } else {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", "thresholdMean monitor test failed");
    }
}

void Monitor::thresholdCovarianceMonitor(double threshold) {
    // Monitor control
    if (threshold != NULL) {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", "thresholdCovariance monitor test passed");
    } else {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", "thresholdCovariance monitor test failed");
    }
}