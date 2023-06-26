#include "HashFunctions.h"
#include <iomanip>
//-----------------Деструктор----------------//
HashTable::~HashTable()
{
  clear();
  delete m_hashFunction;
} 
//-------------------------------------------//

//------------------------Добавление-----------------------//
void HashTable::addNode(int key,int value) 
{
  int hash = m_hashFunction->getHash(key, m_capacity);
  //создадим нашу новую ноду
  Node* addNode = new Node(key, value);
  //если нода с этим хэшем свободна то просто вставляем
  if (m_nodes[hash] == nullptr)
  {
    m_nodes[hash] = addNode;
    m_size++;
  }
  //если произошла коллизия нужно найти первое подходящее место чтобы вставить ноду 
  else 
  {
    Node* temp = m_nodes[hash];//запомнили ноду с существующим хэшем чтобы для нее установить потомка
    // если у нас уже есть нода с таким ключом, то просто найдем ее по хэшу, поменяем значение и выйдем
    while (temp->GetNextNode() != nullptr) 
    {
      if (temp->GetKey() == key) 
      {
        temp->SetValue(value);
        delete addNode;
        return ;
      }
        temp = temp->GetNextNode();
    }

    temp->SetNextNode(addNode);
  //находим первое подходящее место для ноды(если есть), увеличим размер при надобности
    for(int position = 0;position<m_capacity;position++)
      {
        if(m_nodes[position] == nullptr)
        {
          m_nodes[position] = addNode;
          m_size++;
          break;
        }
      }
  }
}
//-----------------------------------------------------------//

//---------------------Проверка на наличие(поиск)------------------------//
HashTable::Node *HashTable::isHasNode(int key) const 
{
  //вычислим хэш (чтобы попасть на ноды которые могут хранить наш ключ) и запомним ноду с ним
  int hash = m_hashFunction->getHash(key, m_capacity);
  Node* temp = m_nodes[hash];
  // вычислили хэш и двигаемся по потомкам  чтобы найти нужного с ключом
  while (temp != nullptr) 
  {
    if (temp->GetKey() == key) 
      return temp;
    temp = temp->GetNextNode();
  }
  return nullptr;
}

bool HashTable::boolIsHasNode(int key)
{
  if(isHasNode(key) == nullptr)
    return false;
  return true;
}
//-----------------------------------------------------------------------//


//----------------------------Вывод в консоль--------------------------//
void HashTable::printTable() const 
{
   std::cout << "Hash" << std::setw(18) << "(Key, Value)" << std::setw(26) << "(_table[i], _next)" << std::endl;
        for (int i = 0; i < m_capacity; i++) {
            std::cout << "Hash " << i << ":" << std::setw(4);
            Node* current = m_nodes[i];
            if (current != nullptr) { // while (current != nullptr)
                std::cout << std::setw(4) << "(" << current->GetKey() << ", " << current->GetValue() << ")";
                std::cout << std::setw(9) << "(" << current << ", " << current->GetNextNode() << ") ";
                //current = current->_next;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
}
//---------------------------------------------------------------------//

//------------------------Удаление таблицы-------------------------//
void HashTable::clear() 
{
  for (int i = 0; i < m_capacity; i++) 
  {
    delete m_nodes[i];
    m_nodes[i] = nullptr;
  }
 // m_size = 0;
}
//-----------------------------------------------------------------//



//---------------------------Копирование------------------------------//
void HashTable::copyTable(const HashTable& copy) 
{
  SetSize(copy.m_size);
  SetCapacity(copy.m_capacity);
  for (int i = 0; i < copy.m_nodes.size(); i++) 
  {
    Node* temp = copy.m_nodes[i];
    Node* newNode = new Node(temp->GetKey(), temp->GetValue());
    // для каждой ноды определим ее потомка
    Node* next = temp->GetNextNode();
    if(next == nullptr)
      newNode->SetNextNode(nullptr);
     // найдем номер ноды которая является потомкой данной и сделаем ноду с этим номером в новой таблице потомкой данной 
    else
    {
      for(int k = 0 ; k<copy.m_nodes.size() ; k++)
        {
          if(copy.m_nodes[k] == next)
          {
            newNode->SetNextNode(m_nodes[k]);
          }
        }  
    }
  }
}
//---------------------------------------------------------------------//


//----------------Оператор присваивания--------------//
HashTable& HashTable::operator=(const HashTable& copy) 
{

  if(this==&copy)
    return *this;
  delete m_hashFunction;
  clear();
  m_nodes.resize(copy.m_capacity,nullptr);
  copyTable(copy);
  m_hashFunction = copy.m_hashFunction->clone();
  return *this;
}
//---------------------------------------------------//


//-------------------Замена хэш функции------------------//
void HashTable::rehash(HashFunction *hashFunction) 
{
  delete m_hashFunction;
  m_hashFunction = hashFunction;
  resize(m_capacity);//нам нужно заново создать таблицу (тк поменялся хэш,но размер оставить тем же)
}
//-------------------------------------------------------//


//------------------Пересоздание таблицы--------------------//
void HashTable::resize(int newSize)
{
  std::vector<Node*> prev = m_nodes;
  m_nodes.clear();
  m_nodes.resize(newSize,nullptr);
  for(int i = 0;i<prev.size();i++)
    {
      addNode(prev[i]->GetKey(),prev[i]->GetValue());
    }
  SetCapacity(newSize);
}
//-----------------------------------------------------------//


//-------------Получение ссылки----------------//
int& HashTable::operator[](int key)
{
  Node* temp = isHasNode(key);
  if(temp == nullptr)
    throw "invalid key";
  return temp->GetAdressValue();
}
//---------------------------------------------//

//------------------------------Удаление--------------------------//
void HashTable::removeNode(int key) 
{
  if(!boolIsHasNode(key))
    return;
  else
  {
    int hash = m_hashFunction->getHash(key, m_capacity);
    Node* temp = m_nodes[hash];
    Node* parent = nullptr;
    while (temp != nullptr) 
    {
      if (temp->GetKey() == key) 
      {
        // если у удаляемого узла есть потомки,то их нужно все сдвинуть по позициям
        Node* child = temp->GetNextNode();
        int childPosition;
        while (child != nullptr) 
        {
          int childPosition = findPosition(child);
          m_nodes[findPosition(temp)] = child;
          child = child->GetNextNode();
        }

        //ставим потомка на это место
        m_nodes[findPosition(temp)] = m_nodes[findPosition(temp)]->GetNextNode();
        if(temp->GetNextNode()!= nullptr)
          m_nodes[childPosition] = m_nodes[childPosition]->GetNextNode();

        //если у удалямеого узла кроме потомков есть родитель, то теперь он отцом а не дедом
        if(parent != nullptr)
            parent->SetNextNode(temp->GetNextNode());
        
        delete temp;
        return;
      }
      //если не совпадает с ключом то "сдвигаем ноды по хэшу"
      parent = temp;
      temp = temp->GetNextNode();
    }
  }
}
//----------------------------------------------------------------//
