#ifndef LOGINMODEL_HPP
#define LOGINMODEL_HPP

#include <string>
#include <crow.h>
#include <iostream>
#include "../../conexao/conectar.hpp"
// #include <bcrypt/BCrypt.hpp>

class Login {
private:
    std::string username;
    std::string password;
    PGconn* conn;

public:

    Login(const std::string &username, const std::string &password, PGconn* conn);

    std::string getUsername() const;
    std::string getPassword() const;

    crow::response authenticate(PGconn* conn);
};

#endif // LOGINMODEL_HPP