#include "monitor.hpp"

// Constructor
Monitor::Monitor(string dbname, string user, string password, string hostname, int port) {
    // Create the Postgre object
    this->postgre = new Postgre(dbname, user, password, hostname, port);

    // Create the table for the monitor or flush it if it already exists
    if (!this->postgre->tableExists("monitor")) {
            // Create the table
            cout << "Table monitor does not exist." << endl;
            cout << "Creating table monitor..." << endl;
            this->postgre->createTable("CREATE TABLE monitor (id SERIAL PRIMARY KEY,log VARCHAR(255));");
        } else {
            // Flush/Clean the table
            cout << "Table monitor exists." << endl;
            cout << "Flushing table monitor..." << endl;
            this->postgre->flushTable("monitor");
        }
}

// Functional monitors

void Monitor::meanCalculationMonitor(vector<double> mean) {
    // Check if the mean vector is empty
    if (mean.empty()) {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", MEAN_CALCULATION_MONITOR_NEGATIVE);
    } else {
        // Check if the mean vector has the correct size
        if (mean.size() == 999) {
            // Insert the message into the monitor table
            this->postgre->postData("monitor", MEAN_CALCULATION_MONITOR_POSITIVE);
        } else {
            // Insert the message into the monitor table
            this->postgre->postData("monitor", MEAN_CALCULATION_MONITOR_NEGATIVE);
        }
    }   
}

void Monitor::covarianceCalculationMonitor(vector<double> covariance) {
    // Check if the covariance vector is empty
    if (covariance.empty()) {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", COVARIANCE_CALCULATION_MONITOR_NEGATIVE);
    } else {
        // Check if the covariance vector has the correct size
        if (covariance.size() == 999) {
            // Insert the message into the monitor table
            this->postgre->postData("monitor", COVARIANCE_CALCULATION_MONITOR_POSITIVE);
        } else {
            // Insert the message into the monitor table
            this->postgre->postData("monitor", COVARIANCE_CALCULATION_MONITOR_NEGATIVE);
        }
    }
}

void Monitor::anomalyCalculationMonitor(vector<Anomaly> anomalies) {
    // Check if the anomalies vector is allocated
    if (!anomalies.empty()) {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", ANOMALY_CALCULATION_MONITOR_POSITIVE);
    } else {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", ANOMALY_CALCULATION_MONITOR_NEGATIVE);
    }
}

// Non-functional monitors

void Monitor::windowSizeMonitor(int windowSize) {
    // Monitor control
    if (windowSize != 0) {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", WINDOW_SIZE_MONITOR_POSITIVE);
    } else {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", WINDOW_SIZE_MONITOR_NEGATIVE);
    }
}

void Monitor::thresholdMeanMonitor(double threshold) {
    // Monitor control
    if (threshold) {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", THRESHOLD_MEAN_MONITOR_POSITIVE);
    } else {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", THRESHOLD_MEAN_MONITOR_NEGATIVE);
    }
}

void Monitor::thresholdCovarianceMonitor(double threshold) {
    // Monitor control
    if (threshold) {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", THRESHOLD_COVARIANCE_MONITOR_POSITIVE);
    } else {
        // Insert the message into the monitor table
        this->postgre->postData("monitor", THRESHOLD_COVARIANCE_MONITOR_NEGATIVE);
    }
}