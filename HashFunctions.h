
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


class HashFunction 
{
public:
    virtual int getHash(int key, int size) = 0;
    virtual ~HashFunction() = default;
};

class HashFunction1 : public HashFunction 
{
public:
    int getHash(int key, int size) override 
    {
      const int c = 18 % 5;
      const int d = 18 % 7;
      int hash = key % size;
      for (int i = 1; ; i++) 
      {
        hash = (hash + c * i + d * i * i) % size;
        if (hash < size)
          return hash;
      }
    }
};


class HashFunction3 : public HashFunction 
{
public:
    int getHash(int key, int size) override 
    {
      int hash = key % size;
      for (int i = 1; ; i++) 
       {
        hash = (hash + i * (1 + key % (size - 2))) % size;
        if (hash < size)
          return hash;
      }
    }
};


class HashTable {
public:

  class Node 
  {
    private:
        int m_key;
        int m_value;
        Node* m_next;
    public:
        int& GetAdressValue(){return m_value;}
        void SetKey(int key) {m_key = key;}
        int GetKey() {return m_key;}
        void SetValue(int value) {m_value = value;}
        int GetValue() {return m_value;}
        void SetNextNode(Node* next){ m_next = next; }
        Node* GetNextNode(){return m_next;}
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
      SetCapacity(1);
      SetHashFunction(new HashFunction1());
      m_nodes.resize(m_capacity,nullptr);
    }
    HashTable(int size) 
    {
      SetSize(0);
      SetCapacity(size);
      SetHashFunction(new HashFunction1());
      m_nodes.resize(m_capacity, nullptr);
    }

    HashTable(const HashTable& copy)
    {  
      SetSize(0);
      SetCapacity(copy.m_capacity);
      SetHashFunction(copy.m_hashFunction);
      copyTable(copy);
    }

    ~HashTable();
    void addNode(const int key, const int value);
    Node* isHasNode(int key) const ;
    void printTable() const;
    void copyTable(const HashTable& copy);
    void rehash(HashFunction *hashFunction);
    void resize(int newSize);
    HashTable& operator=(const HashTable& copy);
    int GetSize(){return m_size;}
    void SetSize(int newSize){m_size = newSize;}
    int GetCapacity(){return m_capacity;}
    void SetCapacity(int newCapacity){m_capacity = newCapacity;}
    std::vector<Node*> GetNodes(){return m_nodes;}
    void SetHashFunction(HashFunction *hashFunction){m_hashFunction = hashFunction;}
    int& operator[](int key);
private:
    std::vector<Node*> m_nodes;
    int m_size;
    int m_capacity;
    HashFunction* m_hashFunction;
 void clear();
};
