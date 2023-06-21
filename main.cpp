#include "TestHashTable.h"


int main() 
{
  /*HashTable table(10);
    table.addNode(1, 1);
    table.addNode(2, 2);

    table.addNode(3, 3);

    table.addNode(4,4);

    table.addNode(5, 5);

   table.addNode(8,8);

    table.addNode(7,7);
    table.addNode(9,9);
    table.addNode(10,10);
    table.addNode(11,11);

  table.removeNode(1);
  table.printTable();*/

  TestHashTable tester;

    for (int size = 10; size < 200; size += 10)
        tester.test(size);
  return 0;
}