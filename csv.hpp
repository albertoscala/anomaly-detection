#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CSV {
    public:
        // Decode a CSV line
        static vector<string> decompose(string line) {
            vector<string> tokens;
            stringstream ss(line);
            string token;
            
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            
            return tokens;
        }
};