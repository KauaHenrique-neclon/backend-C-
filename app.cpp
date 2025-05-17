#include "crow.h"
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <fstream>
#include <sstream>
#include <thread>
#include <time.h>



#include "controllers/login/loginBlueprint.hpp"
#include "log/log.hpp"
#include "conexao/conectar.hpp"

// Função para servir arquivos estáticos
crow::response serve_file(const std::string &path) {
    std::ifstream file("static/" + path, std::ios::binary);
    if (!file) {
        return crow::response(404);
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return crow::response{buffer.str()};
}

int main() {
    crow::SimpleApp app;

    std::cout << "Tentando abrir o arquivo de log." << std::endl;
    std::ofstream errorLog("erros.txt", std::ios::app);
    if (!errorLog) {
        std::cerr << "Erro ao abrir o arquivo de log!" << std::endl;
        return 1;
    }
    
    try{
        std::cout << "Tentando obter conexão com o banco de dados." << std::endl;
        DatabaseConnection dbConn;
        PGconn* conn = dbConn.getConnection();

        if (!conn) {
            std::cerr << "Erro ao iniciar conexão ao banco de dados." << std::endl;
            return 1;
        }

        CROW_ROUTE(app, "/static/<path>")(serve_file);

        LoginBlueprint loginBlueprint;
        loginBlueprint.LoginMetodo(app, conn);

        // Iniciando o servidor
        app.port(18080).run();
        std::cout << "Servidor iniciado na porta 18080. Pressione Ctrl+C para sair..." << std::endl;
    } catch (const std::exception &e) {
        errorLog << "Erro no código funcão APP: " << e.what() << std::endl;
        std::cerr << "Erro no código função APP: " << e.what() << std::endl;

    } catch (...) {
        errorLog << "Erro desconhecido ocorreu." << std::endl;
        std::cerr << "Erro desconhecido ocorreu." << std::endl;
    }

    std::cout << "Servidor encerrado. Pressione enter para sair..." << std::endl;
    std::cin.get();
    errorLog.close();
    return 0;
}