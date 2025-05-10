#include <crow.h>


class cadastroViews{
    public:
        static crow::mustache::template_t cadastroTemplates(){
            return crow::mustache::load("");
        }
};