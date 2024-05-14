#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "postgre.hpp"

using namespace std;

// Schema for the monitor table
const string MONITOR_TABLE = "CREATE TABLE monitor (id INT AUTO_INCREMENT PRIMARY KEY,log VARCHAR(255));";

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
