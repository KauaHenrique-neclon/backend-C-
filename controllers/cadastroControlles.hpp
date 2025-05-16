#include <crow.h>
#include "views/cadastroViews.h"
#include "models/cadastroModel.h"


class cadastroBlueprint{
public:
    static void cadastroMetodo(crow::SimpleApp &app){
        crow::Blueprint cadastro("cadastro_prefix", "cstat", "ctemplate");



        CROW_BP_ROUTE(cadastro, "/cadastro")([](const crow::request& req){
            try {
                auto pageCadastro = cadastroViews::cadastroTemplates();
                auto renderTemplate = pageCadastro.render();

                return crow::response(renderTemplate);
            } catch (const std::exception &e) {
                return crow::response(500, "Erro ao carregar a página: " + std::string(e.what()));
            }
        });



        CROW_BP_ROUTE(cadastro, "/cadastrar").methods("POST"_method)([](const crow::request& req){
            auto dadosCadastro = crow::json::load(req.body);

            if(!dadosCadastro){
                return crow::response(400, "Preencha todos os campos!");
            }
            auto nome = dadosCadastro["nome"].s();
            auto username = dadosCadastro["username"].s();
            auto password = dadosCadastro["password"].s();
            auto email = dadosCadastro["email"].s();
            auto dataNascimento = dadosCadastro["dataNascimento"].s();

            CadastroModel cadastroModel(nome, username, password, email, dataNascimento);
            crow::response response = cadastroModel.cadastro();

            if (response.code == 200) {
                return crow::response(200, "Cadastro realizado com sucesso!");
            } else {
                return crow::response(500, "Erro ao realizar o cadastro: " + response.body);
            }
        });
    
        app.register_blueprint(cadastro);
    }

};