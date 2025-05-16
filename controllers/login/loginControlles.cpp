#include <iostream>
#include "loginBlueprint.hpp"

void LoginBlueprint::LoginMetodo(crow::SimpleApp &app,PGconn* conn) {
    crow::Blueprint login("login_prefix", "static", "template");

    std::cout << "Iniciado LoginMetodo dentro do LoginMetodo.." << std::endl;

    CROW_BP_ROUTE(login, "/")([]() {
        std::cout << "Iniciado A ROUTE / do LoginMetodo..." << std::endl;
        LoginView loginviews;
        auto pageLogin = loginviews.loginTemplate();
        return crow::response(pageLogin.render());
    });

    std::cout << "Antes do /submit" << std::endl;
    CROW_BP_ROUTE(login, "/submit")([conn](const crow::request &resq) {
        auto dados = crow::json::load(resq.body);
        std::cout << "Iniciado dentro do /submit do login para receber os dados..." << std::endl;

        if (!dados) {
            return crow::response(400, "Dados inválidos");
        }

        std::string username = dados["username"].s();
        std::string password = dados["password"].s();

        if (username.empty() || password.empty()) {
            std::cout << "Nenhum dado foi enviado ou preenchido" << std::endl;
            return crow::response(400, crow::json::wvalue{{"error", "Dados inválidos"}});
        }

        if (username.size() > 256 || password.size() > 256) {
            std::cout << "Usuário ou senha muito longos" << std::endl;
            return crow::response(400, "Usuário ou senha muito longos.");
        }

        try {
            std::cout << "Tentando autenticar usuário: " << username << std::endl;

            Login loginChamando(username, password, conn);
            crow::response response = loginChamando.authenticate(conn);

            std::cout << "Autenticação concluída." << std::endl;
            return response;
        } catch (const std::exception &e) {
            std::cerr << "Erro na autenticação: " << e.what() << std::endl;
            return crow::response(500, "Erro interno do servidor");
        }
    });
    std::cout << "Antes do blueprint" << std::endl;

    app.register_blueprint(login);
}