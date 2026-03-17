#include "AktienHashTabelle.h"

AktienHashTabelle::AktienHashTabelle()
{
    table.resize(TABLE_SIZE);
}

int AktienHashTabelle::hashFunction(std::string& key)
{
    unsigned long hash = 0;

    for(char c : key){
        hash = hash * 31 + static_cast<unsigned char>(c);
    }

    return hash % TABLE_SIZE;
}

int AktienHashTabelle::probeIndex(std::string& key, int i)
{
    return (hashFunction(key) + i * i) % TABLE_SIZE;
}

bool AktienHashTabelle::insert(Aktie& aktie)
{
    std::string key = aktie.getKuerzel();

    for(int i = 0; i < TABLE_SIZE; i++){
        int index = probeIndex(key, i);

        if(table[index].status == EMPTY || table[index].status == DELETED){
            table[index].aktie = aktie;
            table[index].status = OCCUPIED;
            return true;
        }

        if(table[index].status == OCCUPIED &&
           table[index].aktie.getKuerzel() == key){
            return false;
        }
    }

    return false;
}
