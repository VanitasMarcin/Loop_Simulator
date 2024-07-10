#pragma once

#include "ObiektSISO.h"
#include <vector>
#include <deque>
#include <iomanip>

class ModelARX : public ObiektSISO
{   
    private:
    std::vector<double> m_denominator;
    std::vector<double> m_nominator;
    unsigned int m_delay_order;
    double m_standard_deviation;
    std::deque<double> m_input_signals_deque;
    std::deque<double> m_output_signals_deque;
    std::deque<double> m_delay_deque;
    int m_denominator_degree;
    int m_nominator_degree;
    int m_delay_degree;

    public:
    void setDenominator(const std::vector<double> &);
    void setNominator(const std::vector<double> &);

    void setDelay_order(int &);
    void setStandard_deviation(double &);

    ModelARX() = delete;
    ModelARX(const std::vector<double>&, const std::vector<double>&, int, double);
    ~ModelARX();

    double symuluj(double) override;

    private:
    double calculatePolynomial(const std::vector<double> &, std::deque<double> &);
    double simulate_disruption(double);
};