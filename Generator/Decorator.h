#pragma once

#include "Signal.h"
#include <memory>

class Decorator : public Signal 
{

    protected:
    std::shared_ptr<Signal> m_signal;

    public:
    Decorator(std::shared_ptr<Signal>);

    virtual ~Decorator() {};

};