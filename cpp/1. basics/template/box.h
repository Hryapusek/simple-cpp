template <typename T>
class Box {
public:
    Box(T value) : value_(value) {
        // value_ = value;
    }

    T getValue() const {
        return value_;
    }

    void setValue(T value) { value_ = value; }

private:
    T value_;
};

int main()
{
    int a{1};
    Box<int> box1(a);
}
