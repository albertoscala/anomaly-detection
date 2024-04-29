#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>
#include <cmath>
#include <numeric>
#include <iostream>

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

        // Calculate the distance from the mean and the values
        static vector<double> calculateMeanDistance(vector<vector<double>>& values_a, vector<double>& mean_p) {
            // Create a vector to store the distances
            vector<vector<double>> distances(values_a.size(), vector<double>(values_a[0].size(), 0.0));
            
            // Create vector to store the means of the distances
            vector<double> distances_means;

            // Calculate the distances
            for (int i=0; i<values_a.size(); i++) {
                for (int j=0; j<values_a[i].size(); j++) {
                    values_a[i][j] = values_a[i][j] - mean_p[i];
                }
            }

            // Calculate mean of the distances for each feature
            for (int j=0; j<values_a[0].size(); j++) {
                // Create a temporary vector to store the values of the column
                vector<double> column;

                for (int i=0; i<values_a.size(); i++) {
                    // Store the values of the columns
                    column.push_back(values_a[i][j]);
                }

                // Calculate the mean of the column
                distances_means.push_back(calculateMean(column));
            }

            return distances_means;
        }

        static vector<double> calculateCovarianceDistance(vector<vector<double>>& values_a, vector<double>& mean_p);
};

#endif // STATISTICS_HPP