#include <iostream>
#include <string>
#include <cstring>

// Error codes
enum ErrorCode {
    SUCCESS = 0,
    FILE_NOT_FOUND,
    INVALID_DATA,
    PERMISSION_DENIED,
    UNKNOWN_ERROR
};

// A struct to hold user data
struct UserProfile {
    std::string name;
    int age;
    bool is_admin;
};

// Loads a user profile (returns error code)
ErrorCode loadUserProfile(const char* filename, UserProfile* outProfile) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return FILE_NOT_FOUND;
    }

    char name[256];
    int age;
    int is_admin;

    if (fscanf(file, "%255s %d %d", name, &age, &is_admin) != 3) {
        fclose(file);
        return INVALID_DATA;
    }

    if (age < 0 || age > 120) {
        fclose(file);
        return INVALID_DATA;
    }

    if (strlen(name) == 0) {
        fclose(file);
        return INVALID_DATA;
    }

    outProfile->name = name;
    outProfile->age = age;
    outProfile->is_admin = is_admin;

    fclose(file);
    return SUCCESS;
}

// Main function (error handling mess)
int main() {
    UserProfile user;
    ErrorCode error = loadUserProfile("user.txt", &user);

    switch (error) {
        case SUCCESS:
            std::cout << "Loaded user: " << user.name << "\n";
            break;
        case FILE_NOT_FOUND:
            std::cerr << "Error: File not found\n";
            return 1;
        case INVALID_DATA:
            std::cerr << "Error: Invalid data format\n";
            return 1;
        case PERMISSION_DENIED:
            std::cerr << "Error: Permission denied\n";
            return 1;
        default:
            std::cerr << "Unknown error\n";
            return 1;
    }

    return 0;
}