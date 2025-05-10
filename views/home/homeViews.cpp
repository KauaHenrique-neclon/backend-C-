#include "homeViews.h"



struct dadosUser{
    int totalAluno;
    int totalPedentes;
    int alunoMes;
};


std::vector<dadosUser> getDados(){
    std::vector<dadosUser> results;

    try{
        pqxx::connection conn("dbname=banco user=postgres password=5115 host=localhost");
        pqxx::work Wconn(conn);

        std::string query = "SELECT * FROM alunoModel";
        pqxx::result resultado = Wconn.exec(query);
        Wconn.commit();

        for(auto row : resultado){
            dadosUser dados;
            dados.totalAluno = row[0].as<int>();
            dados.totalPedentes = row[1].as<int>();
            dados.alunoMes = row[2].as<int>();
            results.push_back(dados);
            }
        } catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }
    return results;
}




void HomeBlueprint::homeMetodo(crow::SimpleApp &app) {
    crow::Blueprint home("home_prefix", "cstat", "ctemplate");

    CROW_BP_ROUTE(home, "/home")([]() {
        auto pageHome = crow::mustache::load("home.html");
        std::vector<dadosUser> dadosDash = getDados();

        std::string dadosContext;

        for(const auto& row : dadosDash){
            dadosContext += "totalAluno" + std::to_string(row.totalAluno) + "<br>";
            dadosContext += "totalPedentes" + std::to_string(row.totalPedentes) + "<br>";
            dadosContext += "alunoMes" + std::to_string(row.alunoMes) + "<br>";
        }     
        crow::mustache::context contextt;
        contextt["data"] = dadosContext;
        return pageHome.render(contextt);
    });

    app.register_blueprint(home);
}