#include <crow.h>
#include <views/homeViews.h>
#include <pqxx/pqxx>

class HomeBlueprint {
public:
    static void homeMetodo(crow::SimpleApp &app) {
        crow::Blueprint home("home_prefix", "cstat", "ctemplate");

        CROW_BP_ROUTE(home, "/home")([](const crow::request& req) {
            try {
                auto pageHome = homeViews::homeTemplates(); 
                auto renderedTemplate = pageHome.render();  //renderiza o template

                return crow::response(renderedTemplate);
            } catch (const std::exception &e) {
                return crow::response(500, "Erro ao carregar a página inicial: " + std::string(e.what()));
            }
        });

        app.register_blueprint(home); // Registra o blueprint no app
    }
};