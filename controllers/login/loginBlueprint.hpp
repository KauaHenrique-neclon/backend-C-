#ifndef LOGIN_H
#define LOGIN_H



#include <crow.h>
#include "../../models/login/loginModel.hpp"
#include "../../views/LoginViews.hpp"

class LoginBlueprint {
public:
    static void LoginMetodo(crow::SimpleApp &app, PGconn* conn);
};

#endif // LOGIN_H