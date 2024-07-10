#include <iostream>
#include "ModelARX.h"
#include "../Testy/Testy_MODELARX.h"
#include <random>

void ModelARX::setDenominator(const std::vector<double> &denominator) {
    m_denominator = denominator;

    m_input_signals_deque.resize(denominator.size(), 0.0);
}

void ModelARX::setNominator(const std::vector<double> &nominator) {
    m_nominator = nominator;

    m_output_signals_deque.resize(m_nominator.size(), 0.0);
}

void ModelARX::setDelay_order(int &delay_order) {
    if(delay_order > 0) {
        m_delay_order = delay_order;
    }
    else
        m_delay_order = 1;

    m_delay_deque.resize(m_delay_order, 0.0);
}

void ModelARX::setStandard_deviation(double &standard_deviation) {
    if(standard_deviation >= 0.0) {
        m_standard_deviation = standard_deviation;
    }
    else
        m_standard_deviation = 0.0;
}

ModelARX::ModelARX(const std::vector<double> &m_denominator, const std::vector<double> &m_nominator, int m_delay_order = 1, double m_standard_deviation = 0.0)  {
    setDenominator(m_denominator);
    setNominator(m_nominator);
    setDelay_order(m_delay_order);
    setStandard_deviation(m_standard_deviation);
}

double ModelARX::calculatePolynomial(const std::vector<double> &polynomial, std::deque<double> &m_deque) {
	
	double output = 0.0;

	output += std::inner_product(polynomial.begin(), polynomial.end(), m_deque.begin(), 0.0);

    return output;
}

double ModelARX::symuluj(double input_signal) {
 
 	m_delay_deque.push_front(input_signal); 

    m_input_signals_deque.push_front(m_delay_deque.back());
    m_delay_deque.pop_back();

    double output = 0.0;

	output += calculatePolynomial(m_nominator, m_input_signals_deque);

    output -= calculatePolynomial(m_denominator, m_output_signals_deque);

    m_input_signals_deque.pop_back();

    m_output_signals_deque.push_front(output);
    m_output_signals_deque.pop_back();

    output += simulate_disruption(m_standard_deviation);

    return output;
}

double ModelARX::simulate_disruption(double standard_deviation) {
    std::normal_distribution<double> normal_distribution(0, standard_deviation);
	std::mt19937 generator(std::random_device{}());
    return normal_distribution(generator);
}

ModelARX::~ModelARX() {

}