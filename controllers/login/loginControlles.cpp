#include <iostream>
#include "loginBlueprint.hpp"

void LoginBlueprint::LoginMetodo(crow::SimpleApp &app,PGconn* conn) {
    crow::Blueprint login("login_prefix", "static", "template");

    std::ofstream errorLog("erros.txt", std::ios::app);
    if (!errorLog) {
        std::cerr << "Erro ao abrir o arquivo de de erro LoginContolles!" << std::endl;
    }

    try{
        std::cout << "Iniciado LoginMetodo dentro do LoginMetodo.." << std::endl;

        CROW_BP_ROUTE(login, "/")([]() {
            std::cout << "Iniciado A ROUTE / do LoginMetodo..." << std::endl;
            LoginView loginviews;
            auto pageLogin = loginviews.loginTemplate();
            return crow::response(pageLogin.render());
        });
    } catch (const std::exception &e) {
        errorLog << "Erro no código do / no login: " << e.what() << std::endl;
        std::cerr << "Erro no código do / no login:" << e.what() << std::endl;
    }
    std::cout << "Try di / foi concluido" << std::endl;

    try{
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
                Login loginChamando(username, password, conn);
                crow::response response = loginChamando.authenticate(conn);
                return response;
            } catch (const std::bad_alloc& e) {
                std::cerr << "Erro de alocação de memória: " << e.what() << std::endl;
                return crow::response(500, "Erro interno do servidor");
            }catch (const std::exception& e) {
                std::cerr << "Erro na autenticação: " << e.what() << std::endl;
                return crow::response(500, "Erro interno do servidor");
            } 
            std::cout << "Antes do blueprint" << std::endl;
        });
    }catch (const std::exception &e) {
        errorLog << "Erro no código do LoginMetodo: " << e.what() << std::endl;
        std::cerr << "Erro no código do LoginMetodo: " << e.what() << std::endl;
    }catch (const std::exception& e) {
        std::cerr << "Erro na autenticação: " << e.what() << std::endl;
    } 
    app.register_blueprint(login);
}