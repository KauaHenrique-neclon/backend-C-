#ifndef CONNECT_BANCO_H
#define CONNECT_BANCO_H

#include <libpq-fe.h>
#include <string>
#include <iostream>

class DatabaseConnection {
public:
    DatabaseConnection() {
        std::string connectionString = "dbname=backend user=postgres password=5115 host=localhost port=5432";
        connect(connectionString);
    }

    DatabaseConnection(const std::string& connectionString) {
        connect(connectionString);
    }

    ~DatabaseConnection() {
        if (conn) {
            PQfinish(conn);
        }
    }

    PGconn* getConnection() {
        return conn;
    }

private:
    PGconn* conn;

    void connect(const std::string& connectionString) {
        conn = PQconnectdb(connectionString.c_str());

        if (PQstatus(conn) != CONNECTION_OK) {
            std::cerr << "Erro ao conectar ao banco de dados: " << PQerrorMessage(conn) << std::endl;
            PQfinish(conn);
            conn = nullptr; 
        }
    }
};

#endif // CONNECT_BANCO_H