#include "Aktie.h"
#include <string>

Aktie::Aktie(std::string name, std::string kuerzel, std::string WKN){
    m_name = name;
    m_kuerzel = kuerzel;
    m_WKN = WKN;
}

std::string Aktie::getName(){
    return m_name;
}

void Aktie::updateKursDaten(const std::vector<kursDaten_STRUCT>& kurse){
    m_kurse = kurse;
}

std::vector<kursDaten_STRUCT> Aktie::getKursDaten(){
    return m_kurse;
}
