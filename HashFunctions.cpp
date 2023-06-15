
#include <iostream>
#include <vector>
#include <cmath>
#include "HashFunctions.h"


HashTable::HashTable()
{
  SetSize(0);
  SetCapacity(1);
}

HashTable::HashTable(int size)
{
  SetSize(0);
  SetCapacity(size);
  SetHashFunction(new HashFunction1());
}

HashTable::HashTable(const HashTable& copy)
{
  SetSize(copy.m_size);
  SetCapacity(copy.m_capacity);
  SetHashFunction(copy.m_hashFunction);
  for (int i = 0; i < copy.m_capacity; i++) 
  {
    Node* temp = copy.m_nodes[i];
    while (temp != nullptr) // для каждого узла будет перебирать всех потомков(при наличии коллизий), чтобы потом назначить их потомками в полученной таблице
    {
      Node* newNode = new Node(temp->GetKey(),temp->GetValue());
      newNode->SetNextNode(m_nodes[i]);
      m_nodes[i] = newNode;
      temp = temp->GetNextNode();
    }
  }
}

void HashTable::addNode(int key , int value)
{
  int hash = m_hashFunction->getHash(key , m_capacity);
  //создадим нашу новую ноду
  Node* addNode = new Node (key , value);
  // а теперь найдем место куда ее впихнуть
  if ( m_nodes[hash] == nullptr)
    m_nodes[hash] = addNode;
  // если у нас произошла коллизия
  else
  {
    Node* temp = m_nodes[hash];//запомнили ноду с существующим хэшем чтобы для нее установить потомка
      // если у нас уже есть нода с таким ключом, то просто поменяем значение и выйдем
     if (temp->GetKey() == key) 
     {
        temp->SetValue(value);
        return;
      }
    // найдем первое свободное место чтобы вставить ноду
    int position = 0;
    while(position < m_capacity && m_nodes[position] != nullptr)
      position++;

    if (position<m_capacity)
    {
      // определили потомка и выставляем ноду
      temp->SetNextNode(addNode);
      m_nodes[position] = addNode; 
    }
    else
      return;

  }

  m_size ++;
}


void HashTable::clearTable() 
{
  for (int i = 0; i < m_capacity; i++) 
    {
      Node* temp = m_nodes[i];
      while (temp != nullptr) 
      {
          Node* temp1 = temp;
          temp = temp->GetNextNode();
          delete temp1;
      }
      m_nodes[i] = nullptr;
    }
     m_size = 0;
}

