#ifndef POSTGRE_HPP
#define POSTGRE_HPP

#include <iostream>
#include <string>
#include <pqxx/pqxx>

using namespace std;

class Postgre {
    private:
        // Credentials
        string dbname;
        string user;
        string password;
        string hostname;
        string port;

        // Connection object
        pqxx::connection *connection;

        // Connection functions
        void openConnection();
        void closeConnection();
    public:
        // Constructor
        Postgre(string dbname, string user, string password, string hostname, int port);

        // Destructor
        ~Postgre();

        // Methods

        // Check if a table exists
        bool tableExists(string tableName);

        // Clean the table entries
        bool flushTable(string tableName);

        // Create a table from a query
        bool createTable(string query);

        // Insert data into a table
        void postData(string table, int timestamp, string json_data);

        // Insert data into a table
        void postData(string table, string message);
        // Not today ;)
        //string getData(string query);
};

#endif // POSTGRE_HPP
