#include "loginViews.h"




void LoginBlueprint::LoginMetodo(crow::SimpleApp &app){
    crow::Blueprint login("login_prefix",  "cstat", "ctemplate");

    CROW_BP_ROUTE(login, "/")([](){ 
        auto pageLogin = crow::mustache::load("login.html");
        return pageLogin.render();
    });

    CROW_BP_ROUTE(login, "/submit")([&app](const crow::request &resq){
        auto dados = crow::json::load(resq.body);

        if(!dados){
            return crow::response(400, "Dados invalidos");
        }
        
        // pegando dados do input
        std::string username = dados["username"].s();
        std::string password = dados["password"].s();

        try{
            pqxx::connection conn("dbname=banco user=postgres password=5115 host=localhost");
            pqxx::work Wconn(conn);

            std::string query = "SELECT * FROM usuarios WHERE username = " + Wconn.quote(username) + " AND password = " + Wconn.quote(password) + "";
            pqxx::result resultado = Wconn.exec(query);
            Wconn.commit();

            if(resultado.size() == 1){
                crow::response resq(302);
                resq.add_header("Location", "/home"); //passando a rota
                return resq;
            }else{
                return crow::response(302, "Usuario ou senha invalidas.");
            }
        }catch(const std::exception &e){
            return crow::response(500, "Erro ao consultar banco de dados: " + std::string(e.what()));     
        };
    });

    app.register_blueprint(login);
}