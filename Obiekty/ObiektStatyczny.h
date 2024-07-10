#pragma once

#include "ObiektSISO.h"

class ObiektStatyczny : public ObiektSISO
{   
    private:
    double m_left_x;
    double m_right_x;
    
    public:
    ObiektStatyczny(double, double);

    double symuluj(double) override;

};