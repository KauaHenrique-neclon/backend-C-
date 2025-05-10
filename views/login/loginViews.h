#ifndef LOGIN_VIEWS_H
#define LOGIN_VIEWS_H

#include <crow.h>
#include <pqxx/pqxx>

class LoginBlueprint{
    public:
        static void LoginMetodo(crow::SimpleApp &app);
};

#endif // LOGIN_VIEWS_H