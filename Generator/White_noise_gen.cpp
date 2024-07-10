#include "White_noise_gen.h"

#include <random>

White_noise_gen::White_noise_gen(std::shared_ptr<Signal> signal, double average, double variation, double start, double finish) : 
    Decorator(signal), m_average(average), m_variation(variation), m_start(start), m_finish(finish) {
}

double White_noise_gen::simulate(double t) {

    if(t >= m_start && t <= m_finish) {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> dis(m_average, m_variation);

        double noise = dis(gen);

        return m_signal -> simulate(t) + noise;
    }

    else
        return m_signal -> simulate(t) + 0;

}