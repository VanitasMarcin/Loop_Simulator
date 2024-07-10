#include <iostream>
#include <cmath>

#include "Triangle_gen.h"

Triangle_gen::Triangle_gen(std::shared_ptr<Signal> signal, double amplitude, double frequency, double Tp, double duty_cycle, double start, double finish) : 
    Decorator(signal), m_amplitude(amplitude), m_frequency(frequency), m_duty_cycle(duty_cycle), m_start(start), m_finish(finish) {

    m_period = 1.0 / m_frequency / Tp;

}

double Triangle_gen::simulate(double t) {

    if(t >= m_start && t <= m_finish) {

        double temp_amp =  (0.5 * m_period - std::fabs(std::fmod(t - m_start, m_period) - 0.5 * m_period)) / (0.5 * m_period) * m_amplitude * (std::fmod(t - m_start, m_period) < m_period * m_duty_cycle);

        return m_signal -> simulate(t) + temp_amp;
    }

    else
        return m_signal -> simulate(t) + 0;

}