#include "LoginModel.hpp"




Login::Login(const std::string &username, const std::string &password, PGconn* conn)
    : username(username), password(password),  conn(conn) {
    std::cout << "Passou nessa poha aqui" << std::endl;
}


std::string Login::getUsername() const { return username; }
std::string Login::getPassword() const { return password; }

crow::response Login::authenticate(PGconn* conn) {
    if (username.empty() || password.empty() || username.size() > 256 || password.size() > 256) {
        return crow::response(400, "Usuário ou senha muito longos ou vazios.");
    }

    try {
        std::cout << "Abrindo a conexão" << std::endl;
        std::cout << "Conexão estabelecida" << std::endl;

        std::cout << "Preparando a Query" << std::endl;

        char* usernameEscapa = PQescapeLiteral(conn, username.c_str(), username.size());
        char* passwordEscapa = PQescapeLiteral(conn, password.c_str(), password.size());

        std::string query = "SELECT * FROM usuarios WHERE username = " + std::string(usernameEscapa) + " AND password = " + std::string(passwordEscapa);

        //  libera a memoria allocada
        PQfreemem(usernameEscapa);
        PQfreemem(passwordEscapa);


        PGresult* res = PQexec(conn, query.c_str());

        std::cout << "Executando a query com exec" << std::endl;
        if(!PQresultStatus(res) != PGRES_TUPLES_OK){
            PQclear(res);
            return crow::response(500, "Erro ao consultar banco de dados.");
        }

        std::cout << "Vendo resultado" << std::endl;
        if (PQntuples(res) == 1) {
            PQclear(res);
            crow::response res(302);
            res.add_header("Location", "/home"); 
            return res;
        } else {
            PQclear(res);
            return crow::response(401, "Usuário ou senha inválidos.");
        }
    } catch (const std::exception &e) {
        return crow::response(500, crow::json::wvalue{{"error", "Erro inesperado: " + std::string(e.what())}});
    }

    std::cout << "Final crow response Model" << std::endl;
}