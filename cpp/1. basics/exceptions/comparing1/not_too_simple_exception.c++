#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Custom exception for file errors
class FileError : public std::runtime_error {
public:
    FileError(const std::string& msg) : std::runtime_error(msg) {}
};

// Custom exception for invalid data
class InvalidDataError : public std::runtime_error {
public:
    InvalidDataError(const std::string& msg) : std::runtime_error(msg) {}
};

// A struct to hold user data
struct UserProfile {
    std::string name;
    int age;
    bool is_admin;
};

// Loads a user profile (throws exceptions on failure)
UserProfile loadUserProfile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw FileError("Could not open file: " + filename);
    }

    std::string name;
    int age;
    bool is_admin;

    if (!(file >> name >> age >> is_admin)) {
        throw InvalidDataError("Failed to read user data from file");
    }

    if (age < 0 || age > 120) {
        throw InvalidDataError("Invalid age: " + std::to_string(age));
    }

    if (name.empty()) {
        throw InvalidDataError("Name cannot be empty");
    }

    return UserProfile{name, age, is_admin}; // NRVO (no copy)
}

// Main function (clean and simple)
int main() {
    try {
        UserProfile user = loadUserProfile("user.txt");
        std::cout << "Loaded user: " << user.name << "\n";
    }
    catch (const FileError& e) {
        std::cerr << "File error: " << e.what() << "\n";
        return 1;
    }
    catch (const InvalidDataError& e) {
        std::cerr << "Data error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}