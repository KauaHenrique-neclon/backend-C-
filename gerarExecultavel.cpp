









//  g++ -o app app.cpp LoginBlueprint.cpp -I/path/para/crow/include -I/path/para/pqxx/include -L/path/para/pqxx/lib -lpqxx -lpq






//  g++ -std=c++17 -o "c:/backend segredo/output/app.exe" "c:/backend segredo/app.cpp" -I"C:/msys64/mingw64/include" -I"C:/msys64/mingw64/include/crow" -I"C:/msys64/mingw64/include/asio" -lws2_32 -lmswsock



//  g++ -std=c++17 -o "c:/backend segredo/output/app.exe" "c:/backend segredo/**/*.cpp" -I"C:/msys64/mingw64/include" -I"C:/msys64/mingw64/include/crow" -I"C:/msys64/mingw64/include/asio" -lws2_32 -lmswsock


// g++ -std=c++17 -o "output/app.exe" "C:/backend segredo/app.cpp" "C:/backend segredo/views/cadastro/cadastroViews.cpp" "C:/backend segredo/views/login/loginViews.cpp" "C:/backend segredo/views/home/homeViews.cpp" -I"C:/msys64/mingw64/include" -I"C:/msys64/mingw64/include/crow" -I"C:/msys64/mingw64/include/asio" -lws2_32 -lmswsock -lpqxx -lpq

// executavel
//  g++ -std=c++17 -o "output/app.exe" "app.cpp" "controllers/login/loginBlueprint.h" -I"C:/msys64/mingw64/include" -I"C:/msys64/mingw64/include/crow" -I"C:/msys64/mingw64/include/asio" -lws2_32 -lmswsock -lpqxx -lpq

// g++ -std=c++17 -o "output/app.exe" "app.cpp" "controllers/login/loginControlles.cpp" "models/login/loginModel.cpp" -I"C:/msys64/mingw64/include" -I"C:/msys64/mingw64/include/crow" -I"C:/msys64/mingw64/include/asio" -lws2_32 -lmswsock -lpqxx -lpq