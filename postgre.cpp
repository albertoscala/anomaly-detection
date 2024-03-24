#include "postgre.hpp"

// Constructor
Postgre::Postgre(string hostname, int port) {
    // Create a postgre connection
    this->hostname = hostname;
    this->port = port;
    this->conn = PQsetdbLogin(hostname.c_str(), port, NULL, NULL, NULL, NULL, NULL);
}

// Destructor
Postgre::~Postgre() {

}

void Postgre::postData(string query) {

}

string Postgre::getData(string query) {
    
}