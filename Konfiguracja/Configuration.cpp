#include "Configuration.h"
#include "../json-3.11.2/single_include/nlohmann/json.hpp"
#include "../Generator/Signal.h"
#include "../Generator/Signal_base.h"
#include "../Generator/Step_gen.h"
#include "../Generator/Sin_gen.h"
#include "../Generator/Rec_gen.h"
#include "../Generator/Triangle_gen.h"
#include "../Generator/White_noise_gen.h"
#include <iostream>
#include <fstream>
#include "../Obiekty/PetlaUAR.h"

Configuration::Configuration(std::string path) : m_path(path) {

}

bool Configuration::loadConfigurationFromFile(std::string filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        file >> m_jsonData;
        file.close();
        return true;
    } else {
        std::cout << "Blad podczas otwierania pliku" << std::endl;
        return false;
    }
}


bool Configuration::saveConfiguration(std::string filePath) {

    std::cout << "Podaj sciezke gdzie chcesz zapisac konfiguracje:" << std::endl;
    std::cin >> filePath;

    std::filesystem::path outputFilePath(filePath);
    std::filesystem::path outputDirectory = outputFilePath.parent_path();
    if (!std::filesystem::exists(outputDirectory)) {
        std::cout << "Sciezka '" << outputDirectory.string() << "' nie istnieje. Czy chcesz ja utworzyc? (Y/N): ";
        char createDirectoryChoice;
        std::cin >> createDirectoryChoice;
        if ((createDirectoryChoice) == 'Y' || createDirectoryChoice == 'y') {
            if (!std::filesystem::create_directories(outputDirectory)) {
                std::cout << "Nie udalo sie utworzyc sciezki" << std::endl;
                return 1;
            }
        } else {
            std::cout << "Operacja anulowana" << std::endl;
            return 1;
        }
    }

    std::ifstream outputFileStream(filePath);
    if (outputFileStream.is_open()) {
        std::cout << "Wyjsciowy plik '" << filePath << "' juz istnieje. Czy chcesz go nadpisac? (Y/N): ";
        char overwriteChoice;
        std::cin >> overwriteChoice;
        if (overwriteChoice != 'y' && overwriteChoice != 'Y') {
            std::cout << "Operacja anulowana" << std::endl;
            outputFileStream.close();
            return 1;
        }
        outputFileStream.close();
    }

    std::ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << this -> m_jsonData;
        outputFile.close();
        std::cout << "Konfiguracja zapisana do pliku: " << filePath << std::endl;
    } else {
        std::cout << "Nie udalo sie otworzyc pliku: " << filePath << std::endl;
        return 1;
    }

    return 0;

}

void Configuration::runSimulation() {

    getTime(m_jsonData);
    getTp(m_jsonData);
    getProbes(getSignal(m_jsonData));

    std::shared_ptr<ObiektSISO> petla = getOutput(m_jsonData);

    int i = 1;

    for (const auto& probe : getProbes(getSignal(m_jsonData))) {
        double result = i * m_Tp;
        std::cout << result << "s: "<< petla -> symuluj(probe) << std::endl;
        i++;
    }

}

void Configuration::getTime(nlohmann::json parsed) {

    m_steps = parsed["Params"]["SimTime"];

}

void Configuration::getTp(nlohmann::json parsed) {

    m_Tp = parsed["Params"]["Tp"];

}

std::shared_ptr<Signal> Configuration::getSignal(nlohmann::json parsed) {

    for (auto& signal : parsed["Signal"]) {
        if(signal["type"] == "signal_base") {
            std::shared_ptr<Signal> signal = std::make_shared<Signal_base>();
            m_signals.push_back(signal);
        }
        if (signal["type"] == "step") {
            std::shared_ptr<Signal> lastSignal = m_signals.back();
            double amplitude = signal["amplitude"];
            double start = signal["start"];
            double stop = signal["stop"];

            std::shared_ptr<Signal> signal = std::make_shared<Step_gen>(lastSignal, amplitude, start, stop);
            
            m_signals.push_back(signal);
        }
        if (signal["type"] == "sin") {
            std::shared_ptr<Signal> lastSignal = m_signals.back();
            double amplitude = signal["amplitude"];
            double frequency = signal["frequency"];
            double start = signal["start"];
            double stop = signal["stop"];

            std::shared_ptr<Signal> signal = std::make_shared<Sin_gen>(lastSignal, amplitude, frequency, m_Tp, start, stop);

            m_signals.push_back(signal);
        }
        if (signal["type"] == "rec") {
            std::shared_ptr<Signal> lastSignal = m_signals.back();
            double amplitude = signal["amplitude"];
            double frequency = signal["frequency"];
            double dutyCycle = signal["duty_cycle"];
            double start = signal["start"];
            double stop = signal["stop"];

            std::shared_ptr<Signal> signal = std::make_shared<Rec_gen>(lastSignal, amplitude, frequency, dutyCycle, m_Tp, start, stop);

            m_signals.push_back(signal);
        }
        if (signal["type"] == "tri") {
            std::shared_ptr<Signal> lastSignal = m_signals.back();
            double amplitude = signal["amplitude"];
            double frequency = signal["frequency"];
            double dutyCycle = signal["duty_cycle"];
            double start = signal["start"];
            double stop = signal["stop"];

            std::shared_ptr<Signal> signal = std::make_shared<Triangle_gen>(lastSignal, amplitude, frequency, dutyCycle, m_Tp, start, stop);

            m_signals.push_back(signal);
        }

        if (signal["type"] == "noise") {
            std::shared_ptr<Signal> lastSignal = m_signals.back();
            double mean = signal["mean"];
            double variance = signal["variance"];
            double start = signal["start"];
            double stop = signal["stop"];

            std::shared_ptr<Signal> signal = std::make_shared<White_noise_gen>(lastSignal, mean, variance, start, stop);

            m_signals.push_back(signal);
        }
    }

    return m_signals.back();
}

std::vector<double> Configuration::getProbes(std::shared_ptr<Signal> lastSignal) {

    m_probes.clear();

    for(int t = 0; t < m_steps; t++) {
        m_probes.push_back(lastSignal -> simulate(t));
    }

    return m_probes;
}

std::shared_ptr<ObiektSISO> Configuration::getOutput(nlohmann::json parsed) {

    std::shared_ptr<PetlaUAR> uar_ptr;

    for (auto& system_element : parsed["System"]) {
        if (system_element["type"] == "petla") {
            std::string m_main_petla = system_element["structure"];
            uar_ptr = std::make_shared<PetlaUAR>(m_main_petla);
            processNestedElements(system_element["structure"], system_element["elements"], uar_ptr);
        }
        else {
            std::cout << "Petla wymagana" << std::endl;
            break;
        }
    }

    return uar_ptr;
}

std::shared_ptr<ObiektSISO> Configuration::processNestedElements(nlohmann::json structure, nlohmann::json elements, std::shared_ptr<PetlaUAR> uar_ptr) {

    for (const auto& nested_element : elements) {
        std::shared_ptr<ObiektSISO> p;

        if (nested_element["type"] == "petla") {
            p = processNestedElements(nested_element["structure"], nested_element["elements"], std::make_shared<PetlaUAR>(nested_element["structure"]));
        }
        else if (nested_element["type"] == "arx") {
            p = std::make_shared<ModelARX>(nested_element["A"], nested_element["B"], nested_element["delay_order"], nested_element["standard_deviation"]);
        }
        else if (nested_element["type"] == "pid") {
            p = std::make_shared<RegulatorPID>(nested_element["k"], nested_element["TI"], nested_element["TD"]);
        }
        else if (nested_element["type"] == "static") {
            p = std::make_shared<ObiektStatyczny>(nested_element["x_left"], nested_element["x_right"]);
        }

        uar_ptr->addObject(p);
    }

    return uar_ptr;
}


