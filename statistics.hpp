#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>
#include <cmath>
#include <numeric>
#include <iostream>
// Ты - единственная причина, по которой я не ложусь спать рано.
#include <eigen3/Eigen/Dense>

using namespace std;

class Statistics {
    private:
        // TODO: WE HAVE TO IMPLEMENT COMPATIBILITY FUNCTIONS FOR THE DISTANCE PLS GOD
    public:
        // Calculate the mean of a vector of values
        static double calculateMean(vector<double>& values) {
            double sum = accumulate(values.begin(), values.end(), 0.0);
            double mean =  sum / values.size();

            return mean;
        }

        // Calculate the covariance of a vector of values
        static double calculateCovariance(vector<double>& actual, vector<double>& precedent, double m_act, double m_pre) {
            // Check if the vectors have the same size
            if (actual.size() != precedent.size()) {
                cerr << "Error: vectors have different lengths, they must be of same size";
                return 0.0;
            }

            // Variables to store the sum of the products
            double sum = 0.0;
            
            // Calculate the covariance
            for (int i=0; i<actual.size(); i++) {
                sum += (actual[i] - m_act) * (precedent[i] - m_pre);
            }

            // Return the covariance with the final result
            return sum / (actual.size() -1);
        }

        // Calculate the Mahalanobis distance
        static double calculateMahalanobisDistance(vector<vector<double>>& values_p, vector<vector<double>>& values_a, vector<double>& mean_p, vector<double> covariance) {
            // Convert the vectors to matrices
            // TODO: We will do this, just tomorrow
        }
};

#endif // STATISTICS_HPP