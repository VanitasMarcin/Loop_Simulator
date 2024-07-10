#pragma once

#include "Decorator.h"
#include "Signal.h"

class Rec_gen : public Decorator 
{

    private:
    double m_amplitude;
    double m_frequency;
    double m_duty_cycle;
    double m_start;
    double m_finish;

    double m_period;

    public:
    Rec_gen() = delete;
    Rec_gen(std::shared_ptr<Signal>, double, double, double, double, double, double);
    double simulate(double) override;

};