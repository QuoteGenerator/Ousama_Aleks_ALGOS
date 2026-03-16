#ifndef AKTIE_H
#define AKTIE_H

#include <string>
#include <vector>

struct kursDaten_STRUCT {
    std::string date;
    double close;
    long volume;
    double open;
    double high;
    double low;
};

class Aktie
{
    public:
        Aktie(std::string k_name, std::string k_kuerzel, std::string k_WKN);
        std::string getName();
        void add_kursDaten(kursDaten_STRUCT datenPacket);
        std::vector<kursDaten_STRUCT> getKursDaten();


    private:
        std::string name = "KEIN_NAME";
        std::string kuerzel = "KEIN_KUERZEL";
        std::string WKN = "0";

        std::vector<kursDaten_STRUCT> kurse;

};

#endif // AKTIE_H
