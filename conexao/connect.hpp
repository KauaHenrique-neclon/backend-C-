#ifndef CONNECT_BANCO_H
#define CONNECT_BANCO_H


//#include <pqxx/pqxx>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <pqxx/pqxx>

class ConnectionPool {
public:
    ConnectionPool(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            connections.push(std::make_shared<pqxx::connection>("dbname=backend user=postgres password=5115 host=localhost port=5432"));
        }
    }

    std::shared_ptr<pqxx::connection> acquire() {
        std::unique_lock<std::mutex> lock(mutex);
        condVar.wait(lock, [this] { return !connections.empty(); });
        auto conn = connections.front();
        connections.pop();
        return conn;
    }

    void release(std::shared_ptr<pqxx::connection> conn) {
        std::lock_guard<std::mutex> lock(mutex);
        connections.push(conn);
        condVar.notify_one();
    }

private:
    std::queue<std::shared_ptr<pqxx::connection>> connections;
    std::mutex mutex;
    std::condition_variable condVar;
};

#endif //CONNECT_BANCO_H