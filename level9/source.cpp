#include <cstdlib>
#include <cstring>

class N {
public:
    int value;

    N(int v) : value(v) {}

    virtual int operator+(N& other) {
        return this->value + other.value;
    }

    virtual int operator-(N& other) {
        return this->value - other.value;
    }

    void setAnnotation(char* str) {
        size_t len = strlen(str);
        memcpy((char*)this + 4, str, len);
    }
};

int main(int argc, char** argv) {
    if (argc <= 1)
        _exit(1);

    N* a = new N(5);
    N* b = new N(6);

    a->setAnnotation(argv[1]);

    int result = b->operator+(*a);

    return result;
}