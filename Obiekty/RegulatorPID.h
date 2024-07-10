#pragma once

#include "ObiektSISO.h"

class RegulatorPID : public ObiektSISO
{   
    private:
    double m_k;
    double m_TI;
    double m_TD;

    double m_y = 0.0;

    double m_integralMemory = 0.0;
    double m_DerivativeMemory = 0.0;

    void setPIDSetting(double &, double);

    double simulateK(double);
    double simulateI(double);
    double simulateD(double);

    double calculateError(double);

    public:
    void setK(double k);
    void setTI(double TI);
    void setTD(double TD);

    RegulatorPID() = delete;
    RegulatorPID(double, double = 0.0, double = 0.0);
    ~RegulatorPID();

    double symuluj(double) override;
};