#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

// Non-copyable Socket class
class Socket {
public:
    explicit Socket(int fd) : fd_(fd) {
        if (fd_ == -1) throw std::runtime_error("Connection failed");
        std::cout << "🌐 Socket " << fd_ << " opened\n";
    }

    // Non-copyable
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    // Movable
    Socket(Socket&& other) noexcept : fd_(other.fd_) { other.fd_ = -1; }
    Socket& operator=(Socket&& other) noexcept {
        if (this != &other) {
            close();
            fd_ = other.fd_;
            other.fd_ = -1;
        }
        return *this;
    }

    ~Socket() { close(); }

    void send(const std::string& msg) const {
        if (fd_ == -1) throw std::runtime_error("Socket closed");
        std::cout << "📤 [" << fd_ << "] Sending: " << msg << "\n";
    }

private:
    void close() {
        if (fd_ != -1) {
            std::cout << "🌐 Socket " << fd_ << " closed\n";
            // In real code: ::close(fd_);
            fd_ = -1;
        }
    }

    int fd_;
};

// Connection manager using unique_ptr
class Connection {
    std::unique_ptr<Socket> socket_;
public:
    explicit Connection(int fd) : socket_(std::make_unique<Socket>(fd)) {}
    void send(const std::string& msg) { socket_->send(msg); }
};

// Broadcast group using shared_ptr
class BroadcastGroup {
    std::vector<std::shared_ptr<Socket>> subscribers_;
public:
    void add(std::shared_ptr<Socket> socket) {
        subscribers_.push_back(socket);
    }
    void broadcast(const std::string& msg) {
        for (auto& sub : subscribers_) {
            sub->send(msg);
        }
    }
};

// Connection monitor using weak_ptr
class ConnectionMonitor {
    std::vector<std::weak_ptr<Socket>> connections_;
public:
    void watch(std::shared_ptr<Socket> socket) {
        connections_.push_back(socket);
    }
    void check_connections() {
        std::cout << "\n🔍 Connection status:\n";
        for (auto& weak_conn : connections_) {
            auto conn = weak_conn.lock();
            if (conn) {
                std::cout << "✅ Active connection\n";
            } else {
                std::cout << "❌ Disconnected\n";
            }
        }
    }
};

int main() {
    try {
        // 1. Unique ownership (TCP connection)
        Connection conn(1234);
        conn.send("Hello server!");

        // 2. Shared ownership (Broadcast group)
        BroadcastGroup group;
        auto socket1 = std::make_shared<Socket>(5678);
        auto socket2 = std::make_shared<Socket>(9012);
        group.add(socket1);
        group.add(socket2);
        group.broadcast("Server restarting soon!");

        // 3. Weak monitoring
        ConnectionMonitor monitor;
        monitor.watch(socket1);
        monitor.watch(socket2);
        
        // Release one socket
        socket1.reset();
        monitor.check_connections();

        std::cout << "\n=== End of scope ===\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
