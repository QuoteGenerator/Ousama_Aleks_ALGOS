#ifndef AKTIENHASHTABELLE_H
#define AKTIENHASHTABELLE_H

#include "Aktie.h"
#include <vector>
#include <string>

enum SlotStatus {
    EMPTY,
    OCCUPIED,
    DELETED
};

struct HashSlot {
    Aktie aktie;
    SlotStatus status = EMPTY;
};

class AktienHashTabelle
{
    public:
        AktienHashTabelle();
        bool insert(Aktie& aktie);
        bool remove(std::string kuerzel);

    private:
        static const int TABLE_SIZE = 2003;
        std::vector<HashSlot> table;

        int hashFunction(std::string& key);
        int probeIndex(std::string& key, int i);


};

#endif
