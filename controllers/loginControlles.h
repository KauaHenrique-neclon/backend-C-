#include <crow.h>
#include "models/loginModel.h"
#include "views/LoginViews.h"
#include <pqxx/pqxx>

class LoginBlueprint {
public:
    static void LoginMetodo(crow::SimpleApp &app) {
        crow::Blueprint login("login_prefix", "cstat", "ctemplate");

        CROW_BP_ROUTE(login, "/")([]() { 
            LoginView loginviews;
            auto pageLogin = loginviews.loginTemplate();
            crow::response(pageLogin.render());
        });
       
        CROW_BP_ROUTE(login, "/submit")([](const crow::request &resq) {
            auto dados = crow::json::load(resq.body);

            if (!dados) {
                return crow::response(400, "Dados inválidos");
            }
            
            
            std::string username = dados["username"].s();
            std::string password = dados["password"].s();

            
            if (username.empty() || password.empty()) {
                return crow::response(400, "Usuário e senha não podem estar vazios.");
            }

            // verificando usuario 
            Login login(username, password);
            crow::response response = login.authenticate();

        });

        app.register_blueprint(login);  
    }
};