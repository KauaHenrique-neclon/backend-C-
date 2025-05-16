#include "crow.h"
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <fstream>
#include <sstream>
#include <exception>

// incluir blueprint
#include "controllers/login/loginBlueprint.hpp"
//#include "log/log.hpp"
#include "conexao/conectar.hpp"

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

    //app.loglevel(crow::LogLevel::Debug);

    DatabaseConnection dbConn;

    PGconn* conn = dbConn.getConnection();

    if(!conn){
        std::cerr << "Erro ao iniciar conexao ao banco de dados" << std::endl;
        return 1;
    }

    std::cout << "Iniciando o aplicativo..." << std::endl;

    CROW_ROUTE(app, "/static/<path>")([&](const std::string &path) {
        return serve_file(path);
    });

    std::ofstream errorLog("erros.txt", std::ios::app);
    if (!errorLog) {
        std::cerr << "Erro ao abrir o arquivo de log!" << std::endl;
        return 1;
    }

    try {

        std::cout << "Chamada para LoginMetodo..." << std::endl;
        LoginBlueprint loginBlueprint;
        loginBlueprint.LoginMetodo(app, conn);
        std::cout << "LoginMetodo executado com sucesso." << std::endl;

        
        app.port(18080).run();

        // .concurrency(4)
        //std::cout << "Servidor iniciado. Pressione enter para sair..." << std::endl;
        //std::cin.get();

    

    } catch (const std::exception &e) {
        errorLog << "Erro no código: " << e.what() << std::endl;
        std::cerr << "Erro no código: " << e.what() << std::endl;
        errorLog.flush();
    } catch (...) {
        errorLog << "Erro desconhecido ocorreu." << std::endl;
        std::cerr << "Erro desconhecido ocorreu." << std::endl;
        errorLog.flush();
    }

    errorLog.close();
    std::cout << "Pressione enter para sair..." << std::endl;
    std::cin.get();

    return 0;
}