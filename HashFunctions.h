
#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
public:
    // интерфейсный класс
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
            for (int i = 1; true; i++) 
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
            for (int i = 1;; i++) 
            {
                hash = (hash + i * (1 + key % (size - 2))) % size;
                if (hash < size)
                    return hash;
            }
        }
  };


  class Node 
  {
    private:
        int m_key;
        int m_value;
        Node* m_next;
    public:
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

    void SetSize(int size) {m_size = size;}
    int GetKey() {return m_size;}
    void SetCapacity(int capacity) {m_capacity = capacity;}
    int GetCapacity() {return m_capacity;}
    void SetHashFunction(HashFunction* function) { m_hashFunction = function;}
    HashFunction* GetHashFunction(){return m_hashFunction;}
    
    HashTable();
    HashTable(int size);
    HashTable(const HashTable& other);
    ~HashTable() {clearTable(); delete m_hashFunction;}
    void clearTable(); 
    void addNode(int key, int value);
    void remove(int key);


private:

    std::vector<Node*> m_nodes;
    int m_size;
    int m_capacity;
    HashFunction* m_hashFunction;

};
