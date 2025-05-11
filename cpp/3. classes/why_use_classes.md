## What Problem Do Classes Solve?
Imagine you’re writing a program to manage a library:

Without classes: 
- You’d have separate variables like bookTitles, bookAuthors, bookIDs… and functions like borrowBook(), returnBook().

With classes: 
- You bundle all this into a Book class that contains both data and actions related to books.

Before (Chaos):

```c++
// Unrelated variables and functions floating around
std::string bookTitles[100];
std::string bookAuthors[100];
bool isBorrowed[100];

void borrowBook(int bookID) { 
    isBorrowed[bookID] = true; 
}
```

After (Organized with Classes):
```c++
class Book {
private:
    std::string title;
    std::string author;
    bool isBorrowed;

public:
    void borrow() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }
};
```

## The 4 Pillars of OOP (Why Classes Exist)
Classes enable these core OOP principles:

### Encapsulation
What: 
- Bundle data (variables) and methods (functions) that operate on that data into a single unit (class).

Why:
- Hide internal complexity (e.g., you don’t need to know how borrow() works internally).
- Protect data from invalid states (e.g., prevent isBorrowed from being modified directly without checks).

Example:

```c++
class BankAccount {
private:
    double balance; // Hidden from direct access
public:
    void deposit(double amount) {
        if (amount > 0) balance += amount; // Validation
    }
};
```

### Abstraction
What: 
- Expose only essential features while hiding implementation details.

Why:
- Simplify usage (e.g., you press "start" on a car ignition without knowing engine mechanics).

Example:

```c++
class Engine {
public:
    void start() { 
        // Complex internal logic hidden
        checkFuel(); 
        igniteSpark(); 
    }
};
```

### Inheritance
What: 
- Create new classes (child) based on existing ones (parent) to reuse code.

Why:
- Avoid duplication (e.g., ElectricCar inherits from Car and adds battery-related features).

```c++
class Car {
public:
    void drive() { std::cout << "Moving...\n"; }
};

class ElectricCar : public Car {
public:
    void charge() { std::cout << "Charging...\n"; }
};
```

### Polymorphism
What: 
- Let objects of different classes be treated as objects of a common parent class.

Why:
- Write flexible code (e.g., a Shape base class with Circle and Square subclasses that override draw()).

Example:

```c++
class Shape {
public:
    virtual void draw() = 0; // Pure virtual function
};

class Circle : public Shape {
public:
    void draw() override { std::cout << "Drawing a circle\n"; }
};
```

## When Should You Use Classes?
✅ Use Classes When:
- You need to model real-world entities (e.g., User, Product, Sensor).
- You want to group related data + behavior (e.g., File class with read(), write() methods).
- You need to enforce rules (e.g., a Temperature class that prevents negative Kelvin values).

❌ Avoid Classes For:
- Simple procedural tasks (e.g., a one-off math calculation).
- When just a struct (plain data container) suffices.

## Practical Example: OOP vs. Procedural Code
Task: Calculate the area of shapes.

Procedural Approach (Messy):

```c++
double calculateCircleArea(double radius) { /* ... */ }
double calculateSquareArea(double side) { /* ... */ }
```

Class-based Approach (Clean):
```c++
class Shape {
public:
    virtual double area() = 0; // Force subclasses to implement
};

class Circle : public Shape {
    double radius;
public:
    double area() override { return 3.14 * radius * radius; }
};
```

Benefit: You can now write generic code that works with any Shape:

```c++
void printArea(Shape* shape) {
    std::cout << shape->area(); // Works for Circle, Square, etc.
}
```
