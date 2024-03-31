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

bool Postgre::alive() {
    // Check if connection is alive
    if (this->connection == nullptr || !this->connection->is_open()) {
        cerr << "Error: Connection to Postgre server failed." << endl;
        return false;
    }

    return true;
}

bool Postgre::tableExists(string tableName) {
    pqxx::result result;
    
    // Create a query to check if the table exists
    string query = "SELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_name = '" + tableName + "');";

    try {
        // Execute the query
        pqxx::work work(*this->connection);
        result = work.exec(query);
        work.commit();
    } catch (const exception &e) {
        // Error occurred
        cerr << e.what() << endl;
        return false;
    }

    // Get the result of the query
    bool exists = result[0][0].as<bool>();
    return exists;
}

bool Postgre::flushTable(string tableName) {
    // Create the query to delete all rows in the table
    string query = "DELETE FROM " + tableName + ";";

    try {
        // Execute the query
        pqxx::work work(*this->connection);
        work.exec(query);
        work.commit();
    } catch (const exception &e) {
        // Error occurred
        cerr << e.what() << endl;
        return false;
    }

    // Table flushed correctly
    cout << "Table " << tableName << " flushed" << endl;
    return true;
}

bool Postgre::createTable(string query) {
    try {
        // Execute the query
        pqxx::work work(*this->connection);
        work.exec(query);
        work.commit();
    } catch (const exception &e) {
        // Error occurred
        cerr << e.what() << endl;
        return false;
    }

    // Table created correctly
    cout << "Table created" << endl;
    return true;
}

void Postgre::postData(string query) {

}

string Postgre::getData(string query) {
    
}