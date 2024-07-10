#pragma once

#include <iostream>
#include "ObiektSISO.h"
#include "ModelARX.h"
#include "RegulatorPID.h"
#include <memory>

class PetlaUAR : public ObiektSISO {

    private:
    std::shared_ptr<ObiektSISO> m_RegulatorPID;
    std::shared_ptr<ObiektSISO> m_ModelARX;
    std::vector<std::shared_ptr<ObiektSISO>> m_objects;

    double m_prevOutput;

    bool m_isClosedLoop;

    public:

    PetlaUAR() {};
    PetlaUAR(std::string);
    PetlaUAR(std::shared_ptr<ObiektSISO>, std::shared_ptr<ObiektSISO>, bool);

    double symuluj(double);

    void addObject(std::shared_ptr<ObiektSISO>);
    void eraseObject(int);

};