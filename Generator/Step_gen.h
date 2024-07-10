#pragma once

#include "Decorator.h"
#include "Signal.h"

class Step_gen : public Decorator {

    private:
    double m_amplitude;
    double m_start;
    double m_finish;

    public:
    Step_gen(std::shared_ptr<Signal>, double, double, double);
    double simulate(double) override;

};