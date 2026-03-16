#include "Aktie.h"
#include <string>

Aktie::Aktie(std::string k_name, std::string k_kuerzel, std::string k_WKN)
{
    name = k_name;
    kuerzel = k_kuerzel;
    WKN = k_WKN;
}


std::string Aktie::getName(){
    return name;
}

void Aktie::add_kursDaten(kursDaten_STRUCT datenPacket){
    kurse.push_back(datenPacket);
}

std::vector<kursDaten_STRUCT> Aktie::getKursDaten(){
    return kurse;
}
