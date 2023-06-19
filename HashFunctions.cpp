#include "HashFunctions.h"

//-----------------Деструктор----------------//
HashTable::~HashTable()
{
  clear();
  delete m_hashFunction;
} 
//-------------------------------------------//

//------------------------Добавление-----------------------//
void HashTable::addNode(const int key, const int value)
{
  if(m_size == m_capacity)
    resize(m_capacity+1);
  // вычислим хэш
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
//-----------------------------------------------------------------------//

//----------------------------Вывод в консоль--------------------------//
void HashTable::printTable() const 
{
  std::cout << "Hash" << '\t' << "Key, Val"<< std::endl;
  for (int i = 0; i < m_capacity; i++) 
  {
    std::cout << "Hash " << i <<'\t';
    if (m_nodes[i] != nullptr) 
      std::cout << m_nodes[i]->GetKey() << ", " << m_nodes[i]->GetValue();
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
    Node* temp = m_nodes[i];
    //удалим всех потомков этой ноды
    while (temp != nullptr) 
    {
      Node* deleteTemp = temp;
      temp = temp->GetNextNode();
      if (temp != nullptr)
        delete deleteTemp;
    }
    m_nodes[i] = nullptr;
  }
  m_size = 0;
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

  if(this!=&copy)
  {
    clear();
    delete m_hashFunction;
    SetHashFunction(copy.m_hashFunction);
    m_nodes.resize(copy.m_capacity,nullptr);
    copyTable(copy);
  }
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
  std::vector<Node*> prev;
  prev.resize(m_capacity,nullptr);
//заполним новый вектор значениями из старого(без потомков,они нам не нужны)
  for (int i = 0; i < m_capacity; i++) 
  {
    if(m_nodes[i]!=nullptr)
    {
      Node* newNode = new Node(m_nodes[i]->GetKey(), m_nodes[i]->GetValue());
      newNode->SetNextNode(nullptr);
      prev[i] = newNode;
    }
  }
//пересоздаем m_nodes
  m_capacity = newSize;
  clear();
  m_nodes.resize(m_capacity,nullptr);

//остортируем по возрастаниб
std::sort(prev.begin(),prev.end(),[](Node* left, Node* right)
      {
        return left->GetKey() < right->GetKey();
    });

  for(int i = 0;i<prev.size();i++)
    {
      addNode(prev[i]->GetKey(),prev[i]->GetValue());
    }
  prev.clear();
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
