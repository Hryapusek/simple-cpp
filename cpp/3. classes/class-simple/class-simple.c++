#include <iostream>
#include <string>

class Rectangle {
private:
    T *data;
    size_t size;

    double width;
    double height;
    std::string color;

public:
    Rectangle() : width(1.0), height(1.0), color("red"), data(NULL), size(0) {}

    Rectangle(double w, double h, const std::string& c) 
        : width(w), height(h), color(c) {}

    double getWidth() const { return width; }
    double getHeight() const { return height; }
    std::string getColor() const { return color; }

    void setWidth(double w) { width = w; }
    void setHeight(double h) { height = h; }
    void setColor(const std::string& c) { color = c; }

    double area() const {
        return width * height;
    }

    void print() const {
        std::cout << "Rectangle: " << color << ", "
                  << width << "x" << height 
                  << " (Area: " << area() << ")\n";
    }
};

int main() {
    Rectangle rect1;
    Rectangle rect2(3.0, 4.0, "blue");

    rect1.print();
    rect2.print(); 

    rect1.setWidth(2.5);
    rect1.setColor("green");
    std::cout << "Updated width: " << rect1.getWidth() << "\n"; // 2.5
    rect1.print();

    return 0;
}
