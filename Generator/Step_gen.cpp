#include "Step_gen.h"

Step_gen::Step_gen(std::shared_ptr<Signal> signal, double amplitude, double start, double finish) : 
    Decorator(signal), m_amplitude(amplitude), m_start(start), m_finish(finish) {

}

double Step_gen::simulate(double t) {

    if(t >= m_start && t <= m_finish)
        return m_signal -> simulate(t) + m_amplitude;
    else
        return m_signal -> simulate(t) + 0;

}