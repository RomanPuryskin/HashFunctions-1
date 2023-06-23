

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class HashFunction 
{
public:
  virtual int getHash(int key, int tableSize) = 0;
  virtual HashFunction *clone() = 0;
  virtual ~HashFunction() = default;
};

class HashFunction1 : public HashFunction 
{
public:
  int getHash(int key, int Size) override 
  {
    const int c = 18 % 5;
    const int d = 18 % 7;
    int hash = key % Size;
    for (int i = 1;; i++) 
    {
      hash = (hash + c * i + d * i * i) % Size;
      if (hash < Size)
        return hash;
    }
  }
  HashFunction *clone() override { return new HashFunction1(*this); }
};

class HashFunction3 : public HashFunction 
{
public:
  int getHash(int key, int Size) override 
  {
    int hash = key % Size;
    for (int i = 1;; i++) 
    {
      hash = (hash + i * (1 + key % (Size - 2))) % Size;
      if (hash < Size)
        return hash;
    }
  }
  HashFunction *clone() override { return new HashFunction3(*this); }
};

class HashTable 
{
public:
  class Node 
  {
  private:
    int m_key;
    int m_value;
    Node *m_next;

  public:
    int &GetAdressValue() { return m_value; }
    void SetKey(int key) { m_key = key; }
    int GetKey() { return m_key; }
    void SetValue(int value) { m_value = value; }
    int GetValue() { return m_value; }
    void SetNextNode(Node *next) { m_next = next; }
    Node *GetNextNode() { return m_next; }
    Node(int key, int value) 
    {
      SetKey(key);
      SetValue(value);
      SetNextNode(nullptr);
    }
    ~Node() = default;
  };

  HashTable() 
  {
    SetSize(0);
    SetCapacity(8);
    SetHashFunction(new HashFunction1());
    m_nodes.resize(m_capacity, nullptr);
  }

  HashTable(int Size) 
  {
    SetSize(0);
    SetCapacity(Size);
    SetHashFunction(new HashFunction1());
    m_nodes.resize(m_capacity, nullptr);
  }

  HashTable(const HashTable &copy) 
  {
    SetSize(0);
    SetCapacity(copy.m_capacity);
    SetHashFunction(copy.m_hashFunction->clone());
    copyTable(copy);
  }

  ~HashTable();
 
  void addNode(int key, int value);
  Node *isHasNode(int key) const;
  bool boolIsHasNode(int key);
  void printTable() const;
  void clear();
  void copyTable(const HashTable &copy);
  void rehash(HashFunction *hashFunction);
  HashTable &operator=(const HashTable &copy);
  int &operator[](int key);
  void resize(int newSize);
  void removeNode(int key);
private:
  std::vector<Node *> m_nodes;
  int m_size;
  int m_capacity;
  HashFunction *m_hashFunction;

int findPosition(Node *temp) 
{
  for (int i = 0; i < m_capacity; i++)
      if (m_nodes[i] == temp) 
      {
        return i;
      }
    return -1;
  }
int GetSize() { return m_size; }
void SetSize(int newSize) { m_size = newSize; }
int GetCapacity() { return m_capacity; }
void SetCapacity(int newCapacity) { m_capacity = newCapacity; }
std::vector<Node *> GetNodes() { return m_nodes; }
void SetHashFunction(HashFunction *hashFunction) { m_hashFunction = hashFunction;}
};
