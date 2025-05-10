#include "crow.h"
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <iostream>
#include <fstream>


// incluir blueprint
#include "controllers/loginControlles.h"
#include "controllers/homeControlles.h"
#include "controllers/cadastroControlles.h"



class Log : public crow::ILogHandler{
    public:
        void log(std::string message,  crow::LogLevel level) override {
            std::string levelStd;
            switch (level){
                case crow::LogLevel::Debug:
                    levelStd = "DEBUG";
                    break;
                case crow::LogLevel::Info:
                    levelStd = "INFO";
                    break;
                case crow::LogLevel::Error:
                    levelStd = "ERROR";
                    break;
                case crow::LogLevel::Warning:
                    levelStd = "WARNING";
                    break;
                case crow::LogLevel::Critical:
                    levelStd = "CRITICAL";
                    break;
                default:
                    levelStd = "UNKNOWN";
                    break;
                }

            std::cout << "[" << levelStd << "] " << message << std::endl;
        }
};

crow::response serve_file(const std::string &path) {
    std::ifstream file("static/" + path, std::ios::binary);
    if (!file) {
        return crow::response(404); 
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return crow::response{buffer.str()};
}

int main() {
    std::ofstream errorLog("error_log.txt");

    crow::SimpleApp app;

    try {
        

        LoginBlueprint::LoginMetodo(app);
        HomeBlueprint::homeMetodo(app);
        cadastroBlueprint::cadastroMetodo(app);



        Log logHandler;
        app.loglevel(crow::LogLevel::Debug);

        app.loglevel(crow::LogLevel::Debug).port(18080).run();
    } catch (const std::exception& e) {
        errorLog << "Erro: " << e.what() << std::endl;
        std::cout << "Ocorreu um erro, verifique o arquivo error_log.txt" << std::endl;
    }

    errorLog.close();


    CROW_ROUTE(app, "/static/<path>")([&](const std::string &path) {
        return serve_file(path);
    });

    // Mantém o console aberto
    std::cout << "Pressione qualquer tecla para sair...";
    std::cin.get();

    return 0;
}
