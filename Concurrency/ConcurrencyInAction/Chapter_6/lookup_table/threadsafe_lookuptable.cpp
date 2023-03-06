#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
#include <list>
#include <memory>

template <typename Key, typename ValueType, typename HashType = std::hash<Key>>
class ThreadSafeLookupTable
{
private:
    class Bucket
    {
        std::pair<Key, ValueType> data;
        
    };

    std::vector<std::shared_ptr<Bucket>> hash_table;

    void add(Key key, ValueType value)
    {
    }

    ThreadSafeLookupTable operator[]
    {
    }

    std::shared_ptr<ValueType> get(Key key)
    {
    }

    bool erase(Key key)
    {
    }
};