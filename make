CXX = g++
CXXFLAGS = -std=c++17 -I"C:/msys64/mingw64/include" -I"C:/msys64/mingw64/include/crow" -I"C:/msys64/mingw64/include/asio"
LDFLAGS = -lws2_32 -lmswsock
SRC_DIR = c:/backend segredo
BIN = c:/backend segredo/output/app.exe

# Encontrar todos os arquivos .cpp, incluindo o específico
SRCS := $(wildcard $(SRC_DIR)/**/*.cpp)
OBJS := $(SRCS:.cpp=.o)

# Regra padrão
$(BIN): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Regra de compilação
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	del $(OBJS) $(BIN)