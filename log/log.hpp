#include <crow.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>


class Log : public crow::ILogHandler{
    public:
        void log(std::string message,  crow::LogLevel level) override {
            std::string levelStd;
            switch (level){
                case crow::LogLevel::Debug:
                    levelStd = "DEBUG";
                    break;
                case crow::LogLevel::Info:
                    levelStd = "INFO";
                    break;
                case crow::LogLevel::Error:
                    levelStd = "ERROR";
                    break;
                case crow::LogLevel::Warning:
                    levelStd = "WARNING";
                    break;
                case crow::LogLevel::Critical:
                    levelStd = "CRITICAL";
                    break;
                default:
                    levelStd = "UNKNOWN";
                    break;
                }

            std::cout << "[" << levelStd << "] " << message << std::endl;
        }
};