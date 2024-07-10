#pragma once

#include "../json-3.11.2/single_include/nlohmann/json.hpp"
#include <string>
#include "../Generator/Signal.h"
#include "../Obiekty/ObiektSISO.h"
#include "../Obiekty/ObiektStatyczny.h"
#include "../Obiekty/PetlaUAR.h"

class Configuration {

    private:
    std::string m_path;

    int m_steps;
    double m_Tp;
    std::vector<std::shared_ptr<Signal>> m_signals;

    std::string m_main_petla;

    public:

    nlohmann::json m_jsonData;
    std::vector<double> m_probes;

    Configuration() {};
    Configuration(std::string);

    std::shared_ptr<Signal> getSignal(nlohmann::json);
    std::vector<double>getProbes(std::shared_ptr<Signal>);
    std::shared_ptr<ObiektSISO> getOutput(nlohmann::json);
    std::shared_ptr<ObiektSISO> processNestedElements(nlohmann::json, nlohmann::json, std::shared_ptr<PetlaUAR>); 
    void getTime(nlohmann::json);
    void getTp(nlohmann::json);

    bool loadConfigurationFromFile(std::string);
    bool saveConfiguration(std::string);
    void runSimulation();

};
