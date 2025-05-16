#include <crow.h>
#include <iostream>



class LoginView {
    public:

        static crow::mustache::template_t loginTemplate() {
            std::cout << "Iniciado dentro do LoginViews" << std::endl;
            return crow::mustache::load("login.html");
    }
};