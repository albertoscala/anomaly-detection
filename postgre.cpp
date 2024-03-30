#include "postgre.hpp"

// Constructor
Postgre::Postgre(string hostname, int port) {
    // Create a postgre connection using pqxx library
    this->connection = new pqxx::connection("dbname=anomaly_detection user=albys password=12 hostaddr=" + hostname + " port=" + to_string(port));

    // Check if the connection is successful
    if(this->connection->is_open()) {
        cout << "Opened database successfully: " << this->connection->dbname() << endl;
    } else {
        cout << "Can't open database" << endl;
        this->connection = nullptr;
    }
}

// Destructor
Postgre::~Postgre() {
    // Close the connection
    this->connection->close();
}

void Postgre::postData(string query) {

}

string Postgre::getData(string query) {
    
}