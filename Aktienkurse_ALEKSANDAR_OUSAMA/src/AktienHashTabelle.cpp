#include "AktienHashTabelle.h"

AktienHashTabelle::AktienHashTabelle()
{
    table.resize(TABLE_SIZE); //table size 2003
}

int AktienHashTabelle::hashFunction(std::string& key)
{
    unsigned long hash = 0;

    for(char c : key){
        hash = hash * 37 + static_cast<unsigned char>(c); // 37, weil primzahl und somit besserer verteilung, buchstabe wird umgewandelt in eine Zahl: static_cast<unsigned char>(c), z.B. A => 65
    }

    return hash % TABLE_SIZE; // der return wert, bleibt zwischen 0 ... 2002 (also der Table Size)
}

int AktienHashTabelle::probeIndex(std::string& key, int i)
{
    return (hashFunction(key) + i * i) % TABLE_SIZE; // das ganze hashen und das ergebnis des hashes einen wert dazu addieren, der in unique lassen lässt mit modulo table size, damit es im table size bleibt.
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

        if(table[index].status == OCCUPIED && table[index].aktie.getKuerzel() == key){ //wenn diese aktie bereits existiert
            return false;
        }
    }

    return false;
}

bool AktienHashTabelle::remove(std::string kuerzel)
{
    for(int i = 0; i < TABLE_SIZE; i++){
        int index = probeIndex(kuerzel, i);

        if(table[index].status == EMPTY){
            return false;
        }

        if(table[index].status == OCCUPIED &&
           table[index].aktie.getKuerzel() == kuerzel){
            table[index].status = DELETED;
            return true;
        }
    }

    return false;
}
