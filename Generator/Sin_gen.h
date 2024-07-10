#pragma once

#include "Decorator.h"
#include "Signal.h"

class Sin_gen : public Decorator 
{

    private:
    double m_amplitude;
    double m_frequency;
    double m_start;
    double m_finish;
    double m_x0;
    double m_x1;
    double m_xn;

    double m_period;

    double m_count = 0;

    public:
    Sin_gen() = delete;
    Sin_gen(std::shared_ptr<Signal>, double, double, double, double, double);
    double simulate(double) override;

};