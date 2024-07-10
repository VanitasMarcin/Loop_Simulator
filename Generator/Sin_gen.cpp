#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "Sin_gen.h"

Sin_gen::Sin_gen(std::shared_ptr<Signal> signal, double amplitude, double frequency, double Tp, double start, double finish) : 
    Decorator(signal), m_amplitude(amplitude), m_frequency(frequency), m_start(start), m_finish(finish) {

    m_period = m_frequency * Tp;

}

double Sin_gen::simulate(double t) {

    if(t >= m_start && t <= m_finish) {
 
        if(m_count == 0) {
            m_x0 = 0.0; 
            m_x1 = sin(2 * M_PI * m_period);
        }

        m_xn = (2 * cos(2 * M_PI * m_period) * m_x1 - m_x0);

        double temp_amp = m_x0 * m_amplitude;

        m_x0 = m_x1; 
        m_x1 = m_xn;

        m_count++;

        return m_signal -> simulate(t) + temp_amp;
    }

    else
        return m_signal -> simulate(t) + 0;
}