#ifndef JSON_HPP
#define JSON_HPP

#include <string>
#include <vector>

using namespace std;

class JSON {
    public:
        // Encode a JSON line
        static string compose(vector<double> values) {
            // Begin the line
            string line = "[";

            // Add the tokens
            for (int i = 0; i < values.size(); i++) {
                // Add the value
                line += "\"" + to_string(values[i]) + "\"";
                
                // Add the comma to separate the values
                if (i < values.size() - 1) {
                    line += ",";
                }
            }

            // End the line
            line += "]";

            // Return the line
            return line;
        }

        // Decode a JSON line
        static vector<double> decompose(string line) {
            vector<double> values;
            string value = "";

            // Set the for loop to get the values
            for (int i = 0; i < line.size(); i++) {
                // Check if the character is a number
                if (isdigit(line[i]) || line[i] == '.') {
                    // Add the character to the values
                    value += line[i];
                } else if (line[i] == ',' || line[i] == ']') {
                    // Add the token to the values
                    values.push_back(stod(value));
                    
                    // Clear the value
                    value = "";
                }
            }

            // Return the values
            return values;
        }
};

#endif // JSON_HPP