#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "postgre.hpp"

using namespace std;

// Messages for the monitors

// Functional monitors messages

// Positive outcome
const string MEAN_CALCULATION_MONITOR_POSITIVE       = "meanCalculation monitor test passed";
const string COVARIANCE_CALCULATION_MONITOR_POSITIVE = "covarianceCalculation monitor test passed";
const string ANOMALY_CALCULATION_MONITOR_POSITIVE    = "anomalyCalculation monitor test passed";

// Negative outcome
const string MEAN_CALCULATION_MONITOR_NEGATIVE       = "meanCalculation monitor test failed";
const string COVARIANCE_CALCULATION_MONITOR_NEGATIVE = "covarianceCalculation monitor test failed";
const string ANOMALY_CALCULATION_MONITOR_NEGATIVE    = "anomalyCalculation monitor test failed";


// Non-functional monitors messages

// Positive outcome
const string WINDOW_SIZE_MONITOR_POSITIVE           = "windowSize monitor test passed";
const string THRESHOLD_MEAN_MONITOR_POSITIVE        = "thresholdMean monitor test passed";
const string THRESHOLD_COVARIANCE_MONITOR_POSITIVE  = "thresholdCovariance monitor test passed";

// Negative outcome
const string WINDOW_SIZE_MONITOR_NEGATIVE           = "windowSize monitor test failed";
const string THRESHOLD_MEAN_MONITOR_NEGATIVE        = "thresholdMean monitor test failed";
const string THRESHOLD_COVARIANCE_MONITOR_NEGATIVE  = "thresholdCovariance monitor test failed";

// Utility struct
// Struct to store the anomalies
struct Anomaly {
    int window;
    int meanAnomaly;
    int covarianceAnomaly;
};

// Monitor class
class Monitor {
    private:
        Postgre *postgre;

    public:
        // Constructor
        Monitor(string dbname, string user, string password, string hostname, int port);

        // Functional monitors
        
        void meanCalculationMonitor(vector<double> mean);

        void covarianceCalculationMonitor(vector<double> covariance);

        void anomalyCalculationMonitor(vector<Anomaly> anomalies);

        // Non-functional monitors
        
        void windowSizeMonitor(int windowSize);

        void thresholdMeanMonitor(double threshold);

        void thresholdCovarianceMonitor(double threshold);
};

#endif // MONITOR_HPP
