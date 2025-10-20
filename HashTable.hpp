#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

template <typename Key, typename Value>
class HashTable
{
private:
    vector<list<pair<Key, Value>>> table; // vector for random access, list for insert and remove, pair to hold Key, Value
    int capacity;
    int size;

    // std::hash so I don't manually have to hash
    int hashFunction(const Key &key) const
    {
        return hash<Key>{}(key) % capacity; // within 1000
    }

public:
    HashTable(int cap = 1000) : table(cap), capacity(cap), size(0) {}

    void insert(const Key &key, const Value &value)
    {
        int index = hashFunction(key);
        for (auto &node : table[index])
        {
            if (node.first == key) // update value if key is the same
            {
                node.second = value;
                return;
            }
        }
        table[index].push_back({key, value}); // else insert new key, value
        ++size;
    }

    Value *find(const Key &key)
    {
        int index = hashFunction(key);
        for (auto &node : table[index])
        {
            if (node.first == key)
                return &node.second;
        }
        return nullptr; // not found
    }
};

#endif