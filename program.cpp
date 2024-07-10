#include "./Konfiguracja/Configuration.h"
#include "./Obiekty/PetlaUAR.h"
#include "./Obiekty/ObiektStatyczny.h"
#include "./Konfiguracja/CLI.h"
#include <iostream>
#include <memory>
#include "json-3.11.2/single_include/nlohmann/json.hpp"
#include "./Testy/Testy_MODELARX.h"
#include "./Testy/Testy_RegulatorPID.h"

#define MAIN

#ifdef MAIN

int main() {

    std::shared_ptr<Configuration> config = std::make_shared<Configuration>();
    std::unique_ptr<CLI> cli;
    std::unique_ptr<PetlaUAR> petla;

    std::string option;

    std::string path;
    std::string exitPath;

    enum MainOptions
    {
        WCZYTAJ_KONFIGURACJE = 1,
        POKAZ_KONFIGURACJE,
        ZMIEN_KONFIGURACJE,
        ODPAL_SYMULACJE,
        ZAPIS_DO_PLIKU
    };

    while(true) {
        std::cout <<"Wybierz opcje:" <<std::endl;
        std::cout <<"1. Wczytaj konfiguracje" <<std::endl;
        std::cout <<"2. Wyswietl parametry symulacji" <<std::endl;
        std::cout <<"3. Zmien parametry symulacji" <<std::endl;
        std::cout <<"4. Uruchom symulacje" <<std::endl;
        std::cout <<"5. Zapisz do pliku" <<std::endl;
        std::cin >> option;

        switch(std::stoi(option))
        {
        case WCZYTAJ_KONFIGURACJE:
            std::cout << "Podaj sciezke do pliku z ktorego chcesz wczytasz konfiguracje:" <<std::endl;
            std::cin >> path;
            config -> loadConfigurationFromFile(path);
            cli = std::make_unique<CLI>(config);
            break;

        case POKAZ_KONFIGURACJE:    
            cli -> showConfig(config ->  m_jsonData["System"][0]);
            break;

        case ZMIEN_KONFIGURACJE:    
            cli -> changeConfiguration();

            break;

        case ODPAL_SYMULACJE:    
            config -> runSimulation();

            break;

        case ZAPIS_DO_PLIKU:
            config -> saveConfiguration(exitPath);

            break;

        default:
            break;
        }
    }
}


#endif

#ifdef TESTY

int main() {
    Testy_ModelARX::runTests();
    Testy_RegulatorPID::runTests();
}

#endif
