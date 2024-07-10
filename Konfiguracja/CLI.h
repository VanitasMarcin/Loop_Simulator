#pragma once

#include "Configuration.h"

class CLI : public Configuration {

    private:
    std::vector<nlohmann::json> m_system_members;

    public:
    CLI(std::shared_ptr<Configuration>);
    std::shared_ptr<Configuration> m_config;

    void printTp();
    void printSimTime();
    void printParams();
    void printSignal();
    void printSystem(nlohmann::json&);
    void structureMove(nlohmann::json&);
    void toNextLoop(nlohmann::json&);
    void toNextLoopConfig(nlohmann::json&);
    void changeConfiguration();
    void changeTp();
    void changeSimTime();
    void modifySignal();
    void addSignal();
    void deleteSignal();
    void modifyStructure(nlohmann::json&);
    void editStructureMoving(nlohmann::json&);
    void deleteAllSignals();
    void addElement(nlohmann::json&);
    void showConfig(nlohmann::json&);
    void eraseElement(nlohmann::json&);
    void eraseAllElements(nlohmann::json&);

};