#ifndef VIEWS_CADASTRO_H
#define VIEWS_CADASTRO_H

#include <crow.h>
#include <pqxx/pqxx>


class cadastroBlueprint{
    public:
        static void cadastroMetodo(crow::SimpleApp &app);
};


#endif