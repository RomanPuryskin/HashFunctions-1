#include "TestHashTable.h"
#include <assert.h>

void TestHashTable::test(const int capacity) 
{
    testCapacity = capacity;
    addNode();
    remove();
}

void TestHashTable::addNode() 
{
    HashTable tester (testCapacity);
    for (int i = 0; i < testCapacity; i++)
        tester.addNode(i, i);

    for (int i = 0; i < testCapacity; i++)
        assert(tester.boolIsHasNode(i));

}


void TestHashTable::remove() 
{
    HashTable tester(testCapacity);
    for (int i = 0; i < testCapacity; i++)
        tester.addNode(i, i);

    for (int i = 0; i < testCapacity; i++) 
    {
        tester.removeNode(i);
        assert(!tester.boolIsHasNode(i));
    }
}

