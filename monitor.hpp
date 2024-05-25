#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "postgre.hpp"

using namespace std;

// Schema for the monitor table
const string MONITOR_TABLE = "CREATE TABLE monitor (id INT AUTO_INCREMENT PRIMARY KEY,log VARCHAR(255));";

// Messages for the monitors
const string MEAN_CALCULATION_MONITOR       = "meanCalculation monitor test passed";
const string COVARIANCE_CALCULATION_MONITOR = "covarianceCalculation monitor test passed";
const string ANOMALY_CALCULATION_MONITOR    = "anomalyCalculation monitor test passed";
const string WINDOW_SIZE_MONITOR            = "windowSize monitor test passed";
const string THRESHOLD_MEAN_MONITOR         = "thresholdMean monitor test passed";
const string THRESHOLD_COVARIANCE_MONITOR   = "thresholdCovariance monitor test passed";

// Monitor class
class Monitor {
    private:
        Postgre *postgre;

    public:
        // Constructor
        Monitor(string dbname, string user, string password, string hostname, int port);

        // Destructor
        ~Monitor();

        // Functional monitors
        
        void meanCalculationMonitor(string message);

        void covarianceCalculationMonitor(string message);

        void anomalyCalculationMonitor(string message);

        // Non-functional monitors
        
        void windowSizeMonitor(int windowSize);

        void thresholdMeanMonitor(double threshold);

        void thresholdCovarianceMonitor(double threshold);
};

#endif // MONITOR_HPP
