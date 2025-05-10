#include <crow.h>




class LoginView {
    public:
        static crow::mustache::template_t loginTemplate() {
           return crow::mustache::load("login.html");
    }
};