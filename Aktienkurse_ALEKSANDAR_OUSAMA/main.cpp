#include <iostream>
#include "Aktie.h"

#include <vector>
#include <fstream>


void ADD(std::vector<Aktie>& aktien);
void DELETE(std::vector<Aktie>& aktien);
void IMPORT(std::vector<Aktie>& aktien);
void QUIT();
void clearTerminal();


void DEBUG(std::vector<Aktie>& aktien); //NICHT WICHTIG!!!

int main()
{
    std::vector<Aktie> aktien;

    int eingabe = 0;
    while(1){
        clearTerminal();
        std::cout << "\n(1): ADD; (2): DELETE; (3): IMPORT; (4): QUIT; (10): DEBUG;\n" << std::endl;
        std::cout << "Waehlen Sie aus: "; std::cin >> eingabe;
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

           case 4:
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

void ADD(std::vector<Aktie>& aktien){
    std::string aktienName = "";
    std::string aktienKuerzel = "";
    std::string WKN = "0";

    std::cout << "Geben Sie den Namen der Aktie an: "; std::cin >> aktienName; std::cout << std::endl;
    std::cout << "Geben Sie den Kuerzel der Aktie an: "; std::cin >> aktienKuerzel; std::cout << std::endl;
    std::cout << "Geben Sie die WKN an: "; std::cin >> WKN; std::cout << std::endl;

    aktien.emplace_back(aktienName, aktienKuerzel, WKN);

    std::cout << "Folgende Aktie wurde hinzugefuegt: " << aktien[aktien.size()-1].getName() << std::endl;
}

void DELETE(std::vector<Aktie>& aktien){
    std::string nameEingabe = "";
    std::cout << "Geben Sie den Namen der Aktie ein: "; std::cin >> nameEingabe; std::cout << std::endl;
    for(int i = 0; i < aktien.size(); i++){
        if(aktien[i].getName() == nameEingabe){
            aktien.erase(aktien.begin()+i);
            break;
        }
    }
}

void IMPORT(std::vector<Aktie>& aktien){
    kursDaten_STRUCT datenpaket;

    //for loop erstellen, die alle daten aus der csv rausliesst,
    //Zeile pro Zeile und add_kursdaten den datenpaket übergeben

    datenpaket.date = "02.02.2020";
    datenpaket.close = 0;
    datenpaket.volume = 0;
    datenpaket.open = 0;
    datenpaket.high = 0;
    datenpaket.low = 0;

    std::string nameInput = "";

    std::cout << "Geben Sie den Namen der Aktie ein: "; std::cin >> nameInput; std::cout << std::endl;

        for(auto it = aktien.begin(); it != aktien.end(); it++){
            if(it->getName() == nameInput){
                it->add_kursDaten(datenpaket);
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




