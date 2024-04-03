#ifndef POSTGRE_HPP
#define POSTGRE_HPP

#include <iostream>
#include <string>
#include <pqxx/pqxx>

using namespace std;

class Postgre {
    private:
        pqxx::connection* connection;
    public:
        // Constructor
        Postgre(string hostname, int port);

        // Destructor
        ~Postgre();

        bool alive();

        bool tableExists(string tableName);

        bool flushTable(string tableName);

        bool createTable(string query);

        void postData(string table, int timestamp, string json_data);

        string getData(string query);
};

#endif // POSTGRE_HPP
