#include "Signal.h"
#include "Decorator.h"
#include "Step_gen.h"
#include "Sin_gen.h"
#include "Signal_base.h"
#include "White_noise_gen.h"
#include "Rec_gen.h"
#include "Triangle_gen.h"

#include <memory>
#include <iostream>

int main() {

    double Tp = 0.01;

    std::shared_ptr<Signal> base = std::make_shared<Signal_base>();
    std::shared_ptr<Signal> step1 = std::make_shared<Step_gen>(base, 0, 0, 100);
    std::shared_ptr<Signal> sin1 = std::make_shared<Sin_gen>(step1, 1, 2, Tp, 0, 100);
    std::shared_ptr<Signal> rec1 = std::make_shared<Rec_gen>(sin1, 1, 10, Tp, 0.5, 0, 100);
    std::shared_ptr<Signal> tri1 = std::make_shared<Triangle_gen>(rec1, 1, 10, Tp, 0.5, 0, 100);
    std::shared_ptr<Signal> noise1 = std::make_shared<White_noise_gen>(tri1, 0, 0.1, 0, 100);

    for(double t = 0; t < 100; t += 1) {
        std::cout << t * Tp << "s: " << noise1->simulate(t) << std::endl;
    }

}