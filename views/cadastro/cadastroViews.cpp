

#include "cadastroViews.h"




void cadastroBlueprint::cadastroMetodo(crow::SimpleApp &app){
    static bool isRegistered = false;

    if (isRegistered){
        std::cout << "Blueprint já registrada." << std::endl;
        return;
    }
    
    crow::Blueprint cadastro("cadastro","ctast", "templates");
    std::cout << "Registrando nova blueprint." << std::endl;

    CROW_BP_ROUTE(cadastro, "/cadastro")([](){
        auto pageCadastro = crow::mustache::load("cadastroUsuario.html");
        return pageCadastro.render();
    });

    CROW_BP_ROUTE(cadastro, "¹cadastro/submit")([&app](const crow::request &resq){
        auto dados = crow::json::load(resq.body);
        if(!dados){
            return crow::response(400, "Dados invalidos");
        }


        if (!dados["username"] || !dados["password"] || !dados["dataNascimento"] || !dados["sobrenome"]) {
            return crow::response(400, "Todos os campos são obrigatórios");
        }

        std::string username = dados["username"].s();
        std::string password = dados["password"].s();
        std::string dataNasci = dados["dataNascimento"].s();
        std::string sobrenome = dados["sobrenome"].s();

        try{
            pqxx::connection conn("dbname=banco user=postgres password=5115 host=localhost");
            pqxx::work Wconn(conn);

            std::string query = "INSERT INTO usuario (username, senha, dataNascimento, sobrenome) VALUES (" +
                                Wconn.quote(username) + ", " +
                                Wconn.quote(password) + ", " +
                                Wconn.quote(dataNasci) + ", " +
                                Wconn.quote(sobrenome) + ")";;

            pqxx::result resultado = Wconn.exec(query);
            Wconn.commit();
            return crow::response(200, "Usuário cadastrado com sucesso!");

        }catch(const std::exception &e){
            return crow::response(500, "Erro ao consultar banco de dados: " + std::string(e.what()));
        };

    });

    app.register_blueprint(cadastro);
    isRegistered = true;
}