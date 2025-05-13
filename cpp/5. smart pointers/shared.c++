#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

class DatabaseConnection {
public:
    DatabaseConnection(const std::string& dbName) : name(dbName) {
        std::cout << "Connected to database: " << name << "\n";
    }
    
    ~DatabaseConnection() {
        std::cout << "Disconnected from database: " << name << "\n";
    }
    
    void executeQuery(const std::string& query) {
        std::cout << "Executing query on " << name << ": " << query << "\n";
    }
    
private:
    std::string name;
};

// 1. Basic shared ownership
void shared_ownership() {
    std::cout << "\n=== Shared Ownership ===\n";
    auto conn = std::make_shared<DatabaseConnection>("MainDB");
    
    {
        auto conn2 = conn; // Copy increases ref count
        conn2->executeQuery("SELECT * FROM users");
        std::cout << "Reference count inside scope: " << conn.use_count() << "\n";
    }
    
    std::cout << "Reference count after scope: " << conn.use_count() << "\n";
    conn->executeQuery("DROP TABLE temp");
}

// 2. Using in containers
void shared_in_containers() {
    std::cout << "\n=== Shared in Containers ===\n";
    std::vector<std::shared_ptr<DatabaseConnection>> connections;
    
    connections.push_back(std::make_shared<DatabaseConnection>("AnalyticsDB"));
    connections.push_back(std::make_shared<DatabaseConnection>("LogDB"));
    
    auto mainConn = connections[0];
    mainConn->executeQuery("CREATE TABLE events");
}

// 3. Circular reference problem (and solution with weak_ptr)
void circular_reference() {
    std::cout << "\n=== Circular Reference ===\n";
    
    struct Node {
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev; // Solution: use weak_ptr for back references
        int id;
        
        Node(int i) : id(i) {}
        ~Node() { std::cout << "Node " << id << " destroyed\n"; }
    };
    
    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);
    
    // Create circular reference
    node1->next = node2;
    node2->prev = node1; // Using weak_ptr breaks the strong cycle
    
    std::cout << "Node1 ref count: " << node1.use_count() << "\n";
    std::cout << "Node2 ref count: " << node2.use_count() << "\n";
}

// 4. Factory pattern with shared_ptr
class CacheManager {
public:
    static std::shared_ptr<DatabaseConnection> getConnection(const std::string& name) {
        auto it = connectionCache.find(name);
        if (it != connectionCache.end()) {
            return it->second;
        }
        
        auto conn = std::make_shared<DatabaseConnection>(name);
        connectionCache[name] = conn;
        return conn;
    }
    
private:
    static std::unordered_map<std::string, std::shared_ptr<DatabaseConnection>> connectionCache;
};

// Initialize static member
std::unordered_map<std::string, std::shared_ptr<DatabaseConnection>> CacheManager::connectionCache;

int main() {
    shared_ownership();
    shared_in_containers();
    circular_reference();
    
    // Using the cache
    std::cout << "\n=== Connection Cache ===\n";
    auto conn1 = CacheManager::getConnection("ProductsDB");
    auto conn2 = CacheManager::getConnection("ProductsDB"); // Gets same instance
    
    conn1->executeQuery("SELECT price FROM items");
    std::cout << "Reference count: " << conn1.use_count() << "\n";
    
    return 0;
}