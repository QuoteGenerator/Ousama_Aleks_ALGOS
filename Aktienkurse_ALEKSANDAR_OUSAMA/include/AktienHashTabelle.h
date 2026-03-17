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

        Aktie* searchByKuerzel(std::string kuerzel); //Aktie Pointer (Keine Kopie geben)
        Aktie* searchByName(std::string name); //Aktie Pointer (Keine Kopie geben)

        std::vector<Aktie> getAllAktien();
    private:
        static const int TABLE_SIZE = 2003;
        std::vector<HashSlot> table; //hash tabelle

        int hashFunction(std::string& key);
        int sondierungsIndex(std::string& key, int i);


};

#endif
