#include <iostream>
#include "PetlaUAR.h"
#include "ModelARX.h"
#include "RegulatorPID.h"

PetlaUAR::PetlaUAR(std::string structure) {

    if(structure == "close")
        m_isClosedLoop = true;

    if(structure == "open")
        m_isClosedLoop = false;

    m_prevOutput = 0.0;

}

PetlaUAR::PetlaUAR(std::shared_ptr<ObiektSISO> RegulatorPID, std::shared_ptr<ObiektSISO> ModelARX, bool isClosed) : m_RegulatorPID(RegulatorPID), m_ModelARX(ModelARX), m_isClosedLoop(isClosed) {
    addObject(m_RegulatorPID);
    addObject(m_ModelARX);

    m_prevOutput = 0.0;
}

void PetlaUAR::addObject(std::shared_ptr<ObiektSISO> object) {

    m_objects.push_back(object);

}

void PetlaUAR::eraseObject(int index) {

    if (index >= 0 && index < m_objects.size()) {
        m_objects.erase(m_objects.begin() + index);
    }

}


double PetlaUAR::symuluj(double input) {

    double output = input - m_prevOutput;

    for(int i = 0; i < m_objects.size(); i++) {
        output = m_objects[i]->symuluj(output);
    }

    if (m_isClosedLoop) {
        m_prevOutput = output;
    }

    return output;

}