#ifndef AKTIE_H
#define AKTIE_H

#include <string>
#include <vector>

// Struktur für einen einzelnen Kurseintrag
struct kursDaten_STRUCT {
    std::string date;
    float close;
    long volume;
    float open;
    float high;
    float low;
};

class Aktie
{
    public:
        Aktie(std::string name, std::string kuerzel, std::string WKN);
        std::string getName();

        //Aktualisiert die Kursdaten (z.B nach Import)
        void updateKursDaten(const std::vector<kursDaten_STRUCT>& kurse);

        std::vector<kursDaten_STRUCT> getKursDaten();

        std::string getWKN(); //<--------------- neu
        std::string getKuerzel(); //<----------- neu


    private:
        std::string m_name;
        std::string m_kuerzel;
        std::string m_WKN;

        //Liste von Kursdaten
        std::vector<kursDaten_STRUCT> m_kurse;

};

#endif // AKTIE_H
