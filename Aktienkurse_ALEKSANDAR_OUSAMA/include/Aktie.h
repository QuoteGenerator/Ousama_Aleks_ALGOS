#ifndef AKTIE_H
#define AKTIE_H

#include <string>
#include <vector>

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
        void updateKursDaten(const std::vector<kursDaten_STRUCT>& kurse);
        std::vector<kursDaten_STRUCT> getKursDaten();


    private:
        std::string m_name;
        std::string m_kuerzel;
        std::string m_WKN;

        std::vector<kursDaten_STRUCT> m_kurse;

};

#endif // AKTIE_H
