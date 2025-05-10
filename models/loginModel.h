#include <string>
#include <pqxx/pqxx>
#include <crow.h>

class Login {
private:
    std::string username;
    std::string password;

public:

    // Construtor____
    Login(const std::string &username, const std::string &password)
        : username(username), password(password) {}


    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }


    crow::response authenticate() {
        try {
            pqxx::connection conn("dbname=banco user=postgres password=5115 host=localhost");
            pqxx::work Wconn(conn);

            std::string query = "SELECT * FROM usuarios WHERE username = " + Wconn.quote(username) + " AND password = " + Wconn.quote(password) + "";
            pqxx::result resultado = Wconn.exec(query);
            Wconn.commit();

            if (resultado.size() == 1) {
                crow::response res(302);
                res.add_header("Location", "/home"); 
                return res;
            } else {
                return crow::response(401, "Usuário ou senha inválidos.");
            }
        } catch (const std::exception &e) {
            return crow::response(500, "Erro ao consultar banco de dados: " + std::string(e.what()));
        }
    }
};