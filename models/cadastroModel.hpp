#include <string>
#include <pqxx/pqxx>
#include <iostream>
#include <crow.h>

class CadastroModel{
    private:
        std::string nome;
        std::string username;
        std::string password;
        std::string email;
        std::string dataNascimento;

    public:
        // contrutor______
        CadastroModel(const std::string &nome, const std::string &username, const std::string &password,
                const std::string &email, const std::string &dataNascimento) 
                : nome(nome), username(username), password(password), email(email), dataNascimento(dataNascimento) {}

        std::string getUsername() const {return username; }
        std::string getPassword() const { return password; }

        crow::response cadastro(){
            try{
                pqxx::connection conn("dbname=banco user=postgres password=5115 host=localhost");
                pqxx::work Wconn(conn);
                
                std::string query = "INSERT INTO tabela(nome,username,password,email,datanascimento) VALUES(\$1, \$2, \$3, \$4, \$5)";
                Wconn.exec_params(query, nome, username, password, email, dataNascimento);
                Wconn.commit();
                return crow::response(201, "Usuário cadastrado com sucesso!");
            }catch(const std::exception &e){
                std::cerr << "Erro ao inserir dados: " << e.what() << std::endl;
                return crow::response(500, "Erro ao inserir dados!");
            }
        }
};