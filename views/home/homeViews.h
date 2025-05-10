#ifndef HOME_VIEWS_H
#define HOME_VIEWS_H

#include <crow.h>
#include <pqxx/pqxx>
#include <iostream>
#include <vector>
#include <map>


class HomeBlueprint {
public:
    static void homeMetodo(crow::SimpleApp &app);
};

#endif // HOME_VIEWS_H