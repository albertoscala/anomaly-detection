#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

bool readDataset(const string& filename, list<string>& lines) {

    ifstream file(filename);
    // check for errors while opening file
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    // read first line of db to define all features
    string line;
    if (getline(file, line)) {
        lines.push_back(line);
    }


    // close file and return 
    file.close();
    return true;
}

bool loadDataset() {
    // Load dataset
    return true;
}

int main(int argc, char **argv) {

    list<string> lines;
    readDataset("dataset/dataset_clean.csv", lines);
    
    return 0;
}