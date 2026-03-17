#include <iostream>
#include "Aktie.h"

#include <vector>
#include <fstream>
#include <sstream>


void ADD(std::vector<Aktie>& aktien);
void DELETE(std::vector<Aktie>& aktien);
void IMPORT(std::vector<Aktie>& aktien);
void PLOT(std::vector<Aktie>& aktien);
void QUIT();
void clearTerminal();


void DEBUG(std::vector<Aktie>& aktien); //NICHT WICHTIG!!!

int main()
{
    //Liste von Aktien Objekten
    std::vector<Aktie> aktien;

    //Menu
    int eingabe = 0;
    while(1){
        //clearTerminal();
        std::cout << "\n(1): ADD; (2): DELETE; (3): IMPORT; (5): PLOT; (8): QUIT; (10): DEBUG;\n" << std::endl;
        std::cout << "Waehlen Sie aus: "; std::cin >> eingabe;
        std::cin.ignore();
        switch(eingabe){
            case 1:
                ADD(aktien);
            break;

            case 2:
                DELETE(aktien);
            break;

            case 3:
                IMPORT(aktien);
            break;

            case 5:
                PLOT(aktien); break;

            case 8:
                QUIT();
                return 0;
            break;

            case 10:
                DEBUG(aktien);
            break;
        }
    }
    return 0;
}

//
void ADD(std::vector<Aktie>& aktien){
    std::string aktienName = "";
    std::string aktienKuerzel = "";
    std::string WKN = "0";

    std::cout << "Geben Sie den Namen der Aktie an: "; std::cin >> aktienName; std::cout << std::endl;
    std::cout << "Geben Sie den Kuerzel der Aktie an: "; std::cin >> aktienKuerzel; std::cout << std::endl;
    std::cout << "Geben Sie die WKN an: "; std::cin >> WKN; std::cout << std::endl;

    aktien.emplace_back(aktienName, aktienKuerzel, WKN);

    std::cout << "Folgende Aktie wurde hinzugefuegt: " << aktien.back().getName() << std::endl;
}

void DELETE(std::vector<Aktie>& aktien){
    std::string nameEingabe = "";
    std::cout << "Geben Sie den Namen der Aktie ein: "; std::cin >> nameEingabe; std::cout << std::endl;
    for(size_t i = 0; i < aktien.size(); i++){
        if(aktien[i].getName() == nameEingabe){
            aktien.erase(aktien.begin()+i);
            break;
        }
    }
}

std::string readFile(){
    std::string filename;
    std::cout << "Geben Sie den Pfad zur Aktie: "; std::cin >> filename; std::cout << std::endl;

    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if(!file){
        exit(1);
    }

    std::streamsize size = file.tellg();
    file.seekg(std::ios::beg);

    std::string buffer(size, '\0');

    if(file.read(&buffer[0], size)){
        return buffer;
    }

    return std::string();
}

std::vector<kursDaten_STRUCT> extractData(){
    int reserveAmount = 30;
    kursDaten_STRUCT kursDaten;
    std::vector<kursDaten_STRUCT> daten;
    daten.reserve(reserveAmount);
    std::string buffer = readFile();

    int columnAmount = 6;
    int column = 0;
    bool entry = false;
    size_t start = buffer.find('\n') + 1; //skip first line
    for(size_t i = start; i < buffer.size(); ++i){

        if(buffer[i] == '$'){
            ++start;
            continue;
        }

        if(buffer[i] == ',' || buffer[i] == '\n'){
            std::string cell = buffer.substr(start, i - start);

            switch (column) {
                case 0: kursDaten.date = cell; break;
                case 1: kursDaten.close = std::stof(cell); break;
                case 2: kursDaten.volume = std::stol(cell); break;
                case 3: kursDaten.open = std::stof(cell); break;
                case 4: kursDaten.high = std::stof(cell); break;
                case 5: kursDaten.low = std::stof(cell); break;
            }

            column = (column + 1) % columnAmount;
            start = i + 1;
            entry = true;
        }

        if(entry && column % columnAmount == 0){
            daten.push_back(kursDaten);
            entry = false;
        }
    }
    return daten;
}

void IMPORT(std::vector<Aktie>& aktien){

    std::string nameInput = "";

    std::cout << "Geben Sie den Namen der Aktie ein: "; std::cin >> nameInput; std::cout << std::endl;

    //check if found first

    for(auto& aktie : aktien){
        if(aktie.getName() == nameInput){
            aktie.updateKursDaten(extractData());
        }
    }
}

void PLOT(std::vector<Aktie>& aktien){

    std::string name;
    std::cout << "Geben Sie den Namen der Aktie ein: ";
    std::cin >> name;
    std::cout << '\n';

    //check if found first

    int scale = 4;
    for(Aktie aktie : aktien){
        if(aktie.getName() == name){
            std::cout << "ASCII-Grafik der Schlusskurse von " << aktie.getName() << '\n';
            std::vector<kursDaten_STRUCT> kurse = aktie.getKursDaten();
            for(size_t i = 0; i < kurse.size(); ++i){
                std::string bar;
                bar.reserve(6);
                std::string date = kurse[i].date;
                float close = kurse[i].close;

                int length = close / scale;

                for (int i = 0; i < length; i++) {
                    bar += '#';
                }

                std::cout << date << ' ' << close << ' ' << bar << '\n';
            }
        }
    }
}

void QUIT(){
    std::cout << "Goodbye!!!";
}


void DEBUG(std::vector<Aktie>& aktien){
    int DEBUG_eingabe = 0;
    while(1){
        std::cout << "\n(1): Aktien Zeigen!; (2): DEBUG schliessen;\n" << std::endl;
        std::cout << "Waehlen Sie aus: "; std::cin >> DEBUG_eingabe;
        if(DEBUG_eingabe == 1){
            for(auto i = aktien.begin(); i != aktien.end(); i++){
                std::cout << i->getName() << std::endl;
                std::cout << "date, close, volume, open, high, low" << std::endl;
                kursDaten_STRUCT datenpaket;
                auto daten = i->getKursDaten();
                if(!daten.empty()){
                    for(auto it = daten.begin(); it != daten.end(); it++){
                        datenpaket = *it;
                        std::cout << datenpaket.date << " ";
                        std::cout << datenpaket.close << " ";
                        std::cout << datenpaket.volume << " ";
                        std::cout << datenpaket.open << " ";
                        std::cout << datenpaket.high << " ";
                        std::cout << datenpaket.low << " " << std::endl;
                    }
                }
            }
            continue;
        }else if(DEBUG_eingabe == 2){
            break;
        }
    }
}

void clearTerminal(){
    for(int i = 0; i < 20; i++){
        std::cout << "\033[A\r\033[K";
    }
}




