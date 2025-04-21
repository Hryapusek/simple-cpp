#include <iostream>
#include <string>

class Rectangle {
private:
    // Private member variables (encapsulation)
    double width;
    double height;
    std::string color;

public:
    // ===== 1. Constructors =====
    // Default constructor
    Rectangle() : width(1.0), height(1.0), color("red") {}

    // Parameterized constructor
    Rectangle(double w, double h, const std::string& c) 
        : width(w), height(h), color(c) {}

    // ===== 2. Member Functions (Methods) =====
    // Getters (accessors)
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    std::string getColor() const { return color; }

    // Setters (mutators)
    void setWidth(double w) { width = w; }
    void setHeight(double h) { height = h; }
    void setColor(const std::string& c) { color = c; }

    // Calculate area
    double area() const {
        return width * height;
    }

    // Display rectangle info
    void print() const {
        std::cout << "Rectangle: " << color << ", "
                  << width << "x" << height 
                  << " (Area: " << area() << ")\n";
    }
};

int main() {
    // ===== 3. Using the Class =====
    Rectangle rect1; // Default constructor (1.0x1.0, red)
    Rectangle rect2(3.0, 4.0, "blue"); // Parameterized constructor

    // Call methods
    rect1.print(); // Output: Rectangle: red, 1x1 (Area: 1)
    rect2.print(); // Output: Rectangle: blue, 3x4 (Area: 12)

    // Modify properties
    rect1.setWidth(2.5);
    rect1.setColor("green");
    std::cout << "Updated width: " << rect1.getWidth() << "\n"; // 2.5
    rect1.print(); // Output: Rectangle: green, 2.5x1 (Area: 2.5)

    return 0;
}
