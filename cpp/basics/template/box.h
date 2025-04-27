template <typename T>
class Box {
public:
    Box(T value) : value_(value) {}

    T getValue() const {
        return value_;
    }

    void setValue(T value) { value_ = value; }

private:
    T value_;
};

class Box1 {
public:
    Box1(int value) 
    : value_(value)
     {

     }

    int getValue() const {
        return value_;
    }

    void setValue(int value) { value_ = value; }

private:
    int value_;
};

int main()
{
    int a{1};
    Box<int> box1(a);
}
