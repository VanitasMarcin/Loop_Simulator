#include "ObiektStatyczny.h"

ObiektStatyczny::ObiektStatyczny(double left_x, double right_x) : m_left_x(left_x), m_right_x(right_x) {

}

double ObiektStatyczny::symuluj(double input) {

    if(input < m_left_x) 
        return m_left_x;
    
    if(input > m_right_x) 
        return m_right_x;

    return input;

}