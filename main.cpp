#include "TestHashTable.h"


int main() 
{

  HashTable table(5);
  table.addNode(3,3);
  table.addNode(4,4);
  table.addNode(1,1);
  table.addNode(2,2);
  table.addNode(5,5);
  table.printTable();
  
  table.resize(15);
  table.addNode(6, 6);
  table.printTable();
  table.resize(10);
  table.printTable();
  table.resize(7);
  table.printTable();

/*  TestHashTable tester;

    for (int size = 10; size < 200; size += 10)
        tester.test(size);*/
  return 0;
}