#include "HashFunctions.h"


int main() {
    std::cout << "addNode" << std::endl;
    HashTable table(10);
    table.addNode(1, 1);
    table.addNode(2, 2);
    //table.resizeAndRehash(3);
    table.addNode(3, 3);
    //table.resizeAndRehash(4);
    table.addNode(4,4);
  //table.resizeAndRehash(5);
    table.addNode(5, 5);

   table.addNode(8,8);
   // table.resizeAndRehash(6);
    //
    //table.resizeAndRehash(7);
    table.addNode(7,7);
    table.addNode(9,9);
    table.addNode(10,10);
    table.addNode(11,11);

    table.printTable();
  return 0;
}