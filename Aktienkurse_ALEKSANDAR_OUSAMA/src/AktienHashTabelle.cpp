#include "AktienHashTabelle.h"

//size für table wird erstellt
AktienHashTabelle::AktienHashTabelle()
{
    table.resize(TABLE_SIZE); //table size 2003
}

//es wird ein hash erstellt mit unserem key -> kürzel der Aktie
int AktienHashTabelle::hashFunction(std::string& key)
{
    unsigned long hash = 0; //keine negativen zahlen, deshalb unsigned

    for(char c : key){ //jeden buchstaben durchgehen
        hash = hash * 37 + static_cast<unsigned char>(c); // 37, weil primzahl und somit besserer verteilung, buchstabe wird umgewandelt in eine Zahl: static_cast<unsigned char>(c), z.B. A => 65
    }

    return hash % TABLE_SIZE; // der return wert, bleibt zwischen 0 ... 2002 (also der Table Size)
}

//mit sondierung einen index erstellen, der indirekt dafür sorgt platz zu finden für den Struct
int AktienHashTabelle::sondierungsIndex(std::string& key, int i)
{
    return (hashFunction(key) + i * i) % TABLE_SIZE; // das ganze hashen und das ergebnis des hashes einen wert dazu addieren, der in unique lassen lässt mit modulo table size, damit es im table size bleibt.
}

//einfügen in die Hashtabelle
bool AktienHashTabelle::insert(Aktie& aktie)
{
    std::string key = aktie.getKuerzel(); //key initialisieren (wird zum kürzel)

    for(int i = 0; i < TABLE_SIZE; i++){ //maximal table_size durchgänge
        int index = sondierungsIndex(key, i); // neues i wird übergeben und somit ein neuer versuch auf einen platz zu bekommen

        if(table[index].status == EMPTY || table[index].status == DELETED){
            table[index].aktie = aktie;
            table[index].status = OCCUPIED;
            return true;
        }

        if(table[index].status == OCCUPIED && table[index].aktie.getKuerzel() == key){ //wenn diese aktie bereits existiert, dann soll sie nicht nochmal eingefügt werden (keine versuche mehr)
            return false;
        }
    }

    return false; //wenn alle gegebenen spots occupied sind.
}

bool AktienHashTabelle::remove(std::string kuerzel) //struct status wird zu DELETED (NICHT WIRKLICH ENTFERNT) -> nicht mit search zu finden, aber mit insert zu befüllen möglich
{
    for(int i = 0; i < TABLE_SIZE; i++){
        int index = sondierungsIndex(kuerzel, i);

        if(table[index].status == EMPTY){
            return false; //nur für print nötig
        }

        if(table[index].status == OCCUPIED && table[index].aktie.getKuerzel() == kuerzel){
            table[index].status = DELETED;
            return true; //nur für print nötig
        }
    }

    return false; //nur für print nötig
}

Aktie* AktienHashTabelle::searchByKuerzel(std::string kuerzel)
//mit kürzel aktie bekommen (hash -> sondierung -> return int -> int als index nutzen für tabelle und schauen ob status occupied und kürzel gleich ist mit zugriff auf struct zuerst)
{
    for(int i = 0; i < TABLE_SIZE; i++){
        int index = sondierungsIndex(kuerzel, i);

        if(table[index].status == EMPTY){
            return nullptr;
        }

        if(table[index].status == OCCUPIED &&
           table[index].aktie.getKuerzel() == kuerzel){
            return &table[index].aktie;
        }
    }

    return nullptr;
}

//mit namen suchen. Keine Hash funktion für name sondern nur für kürzel, somit muss jeder slot durchsucht werden
Aktie* AktienHashTabelle::searchByName(std::string name) //keine lust eine hash funktion einzubauen, mit name, somit wird einfach durchgelaufen durch ganzen table
{
    for(int i = 0; i < TABLE_SIZE; i++){
        if(table[i].status == OCCUPIED && table[i].aktie.getName() == name){
            return &table[i].aktie;
        }
    }

    return nullptr;
}
std::vector<Aktie> AktienHashTabelle::getAllAktien() //alle slots durchgehen und checken ob befüllt und dann pushen
{
    std::vector<Aktie> result;

    for(int i = 0; i < TABLE_SIZE; i++){
        if(table[i].status == OCCUPIED){
            result.push_back(table[i].aktie);
        }
    }

    return result;
}

