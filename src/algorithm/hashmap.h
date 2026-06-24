#pragma once
#include <string>

struct HashEntry{
    std::string key;
    std::string value;
    HashEntry* next; //chaining
};

class HashMap{

    private: 
        static const int TABLE_SIZE = 101;
        HashEntry* table[TABLE_SIZE];

        int hashFunction(std::string key);

    public:
        HashMap();
        ~HashMap();
        
        void insert(std::string key, std::string value);
        string search(std::string key);
        void remove(std::string key);
};
