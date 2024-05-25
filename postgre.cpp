#include "postgre.hpp"

// Constructor
Postgre::Postgre(string dbname, string user, string password, string hostname, int port) {
    // Set the credentials
    this->dbname = dbname;
    this->user = user;
    this->password = password;
    this->hostname = hostname;
    this->port = to_string(port);
}

// Destructor
Postgre::~Postgre() {
    
}

// Function to open the connection to the database
void Postgre::openConnection() {
    // Create the connection string
    string connection_string = "dbname=" + this->dbname + " user=" + this->user + " password=" + this->password + " hostaddr=" + this->hostname + " port=" + this->port;

    try {
        // Create the connection object
        this->connection = new pqxx::connection(connection_string);
    } catch (const exception &e) {
        // Error occurred
        cerr << e.what() << ": openconnection" << endl;
    }
}

// Function to close the connection to the database
void Postgre::closeConnection() {
    // Close the connection
    this->connection->close();
}

// Function to check if a table exists in the database
bool Postgre::tableExists(string tableName) {
    pqxx::result result;
    
    // Create a query to check if the table exists
    string query = "SELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_name = '" + tableName + "');";

    // Open the connection
    this->openConnection();

    try {
        // Execute the query
        pqxx::work work(*this->connection);
        result = work.exec(query);
        work.commit();
    } catch (const exception &e) {
        // Error occurred
        cerr << e.what() << ": tableexists" << endl;
        return false;
    }

    // Close the connection
    this->closeConnection();

    // Get the result of the query
    bool exists = result[0][0].as<bool>();
    return exists;
}

// Function to clean the table from old values
bool Postgre::flushTable(string tableName) {
    // Create the query to delete all rows in the table
    string query = "DELETE FROM " + tableName + ";";

    // Open the connection
    this->openConnection();

    try {
        // Execute the query
        pqxx::work work(*this->connection);
        work.exec(query);
        work.commit();
    } catch (const exception &e) {
        // Error occurred
        cerr << e.what() << ": flushtable" << endl;
        return false;
    }

    // Close the connection
    this->closeConnection();

    // Table flushed correctly
    cout << "Table " << tableName << " flushed" << endl;
    return true;
}

// Function to create the table if it doesn't exist
bool Postgre::createTable(string query) {
    // Open the connection
    this->openConnection();

    cout << "query tabella" << endl;
    cout << query << endl;

    try {
        // Execute the query
        pqxx::work work(*this->connection);
        work.exec(query);
        work.commit();
    } catch (const exception &e) {
        // Error occurred
        cerr << e.what() << ": createtable" << endl;
        return false;
    }

    // Close the connection
    this->closeConnection();

    //Debug 
    cout << query << endl;

    // Table created correctly
    cout << "Table created" << endl;
    return true;
}

// Function to insert the date in the database
void Postgre::postData(string table, int timestamp, string json_data) {
    // Create the query to insert data into the table
    string query = "INSERT INTO " + table + " (id, data) VALUES (" + to_string(timestamp) + ", '" + json_data + "');";

    // Open the connection
    this->openConnection();

    try {
        // Execute the query
        pqxx::work work(*this->connection);
        work.exec(query);
        work.commit();
    } catch (const exception &e) {
        // Error occurred
        cerr << e.what() << ": postdata" << endl;
    }

    // Close the connection
    this->closeConnection();
}

// Function to insert the message in the database
void Postgre::postData(string table, string message) {
    // Create the query to insert data into the table
    string query = "INSERT INTO " + table + " (log) VALUES ('" + message + "');";

    // Open the connection
    this->openConnection();

    try {
        // Execute the query
        pqxx::work work(*this->connection);
        work.exec(query);
        work.commit();
    } catch (const exception &e) {
        // Error occurred
        cerr << e.what() << ": postdata" << endl;
    }

    // Close the connection
    this->closeConnection();
}