#include "RegulatorPID.h"
#include "../Testy/Testy_RegulatorPID.h"

void RegulatorPID::setPIDSetting(double &m_setting, double setting) {
    if(setting < 0) {
        m_setting = 0.0;
    }
    else
        m_setting = setting;
}

void RegulatorPID::setK(double k) {
    setPIDSetting(m_k, k);
}

void RegulatorPID::setTI(double TI) {
    setPIDSetting(m_TI, TI);
}

void RegulatorPID::setTD(double TD) {
    setPIDSetting(m_TD, TD);
}

RegulatorPID::RegulatorPID(double k, double TI, double TD) {
    setK(k);
    setTI(TI);
    setTD(TD);
}

double RegulatorPID::calculateError(double input_signal) {
    double error;
    return error = input_signal - m_y;
}

double RegulatorPID::simulateK(double input_signal) {
    double u_k;

    return u_k = m_k * calculateError(input_signal);
}

double RegulatorPID::simulateI(double input_signal) {
    double u_I;

    if(m_TI == 0.0) {
        return 0.0;
    }

    u_I = 1/m_TI * (m_integralMemory + calculateError(input_signal));

    m_integralMemory += calculateError(input_signal);

    return u_I;
}

double RegulatorPID::simulateD(double input_signal) {
    double u_D;

    u_D = m_TD * (calculateError(input_signal) - m_DerivativeMemory);

    m_DerivativeMemory = calculateError(input_signal);

    return u_D;
}

double RegulatorPID::symuluj(double input_signal) {
    return simulateK(input_signal) + simulateI(input_signal)+ simulateD(input_signal);
}

RegulatorPID::~RegulatorPID() {
    
}
