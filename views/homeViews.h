#include <crow.h>


class homeViews{
    public:
        static crow::mustache::template_t homeTemplates(){
            return crow::mustache::load("home.html");
        }
};