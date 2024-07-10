#include "Signal.h"
#include "Decorator.h"

#include <iostream>
#include <memory>

Decorator::Decorator(std::shared_ptr<Signal> signal) : m_signal(signal) {

}
