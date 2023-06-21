
#include "HashFunctions.h"

class TestHashTable {
public:
    TestHashTable() = default;
    ~TestHashTable() = default;

    void test(const int capacity);
protected:
    void addNode();
    void remove();
    int testCapacity;
};
