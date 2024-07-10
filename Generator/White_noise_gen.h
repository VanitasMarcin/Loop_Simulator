#pragma once

#include "Decorator.h"
#include "Signal.h"

class White_noise_gen : public Decorator {

    private:
    double m_average;
    double m_variation;
    double m_start;
    double m_finish;

    public:
    White_noise_gen(std::shared_ptr<Signal>, double, double, double, double);
    double simulate(double) override;

};