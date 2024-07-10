#include "RegulatorPID.h"
#include "ModelARX.h"
#include "TESTY.h"
#include "Testy_MODELARX.h"
#include <iomanip>

double simulate_feedback(RegulatorPID &PIDobj, ModelARX &ARXobj, double input_value) {
    static double ARX_output = ARXobj.symuluj(input_value);
    double error = input_value - ARX_output;
    double PID_output = PIDobj.symuluj(error);
    ARX_output = ARXobj.symuluj(PID_output);

    return ARX_output;
}

void test_1()
{   
    std::cout.precision(3);

    std::cerr << "RegP (k = 0.5) with ARX: ";

	try
	{
		// Przygotowanie danych:
		ModelARX instancjaTestowaARX({ -0.4 }, { 0.6 }, 1, 0);
        RegulatorPID instancjaTestowaPID(0.5);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++) {
			faktSygWy[i] = simulate_feedback(instancjaTestowaPID, instancjaTestowaARX, sygWe[i]);
            std::cout << faktSygWy[i] << ' ';
        }   
        std::cout << std::endl;
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_2()
{
    std::cerr << "RegP (k = 2.0) with ARX: ";

	try
	{
		// Przygotowanie danych:
		ModelARX instancjaTestowaARX({ -0.4 }, { 0.6 }, 1, 0);
        RegulatorPID instancjaTestowaPID(2.0);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++) {
			faktSygWy[i] = simulate_feedback(instancjaTestowaPID, instancjaTestowaARX, sygWe[i]);
            std::cout << faktSygWy[i] << ' ';
        }
        std::cout << std::endl;
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_3()
{
    std::cerr << "RegP (k = 0.5, I = 10.0) with ARX: ";

	try
	{
		// Przygotowanie danych:
		ModelARX instancjaTestowaARX({ -0.4 }, { 0.6 }, 1, 0);
        RegulatorPID instancjaTestowaPID(0.5, 10.0);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++) {
			faktSygWy[i] = simulate_feedback(instancjaTestowaPID, instancjaTestowaARX, sygWe[i]);
            std::cout << faktSygWy[i] << ' ';
        }
        std::cout << std::endl;
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_4()
{
    std::cerr << "RegP (k = 0.4, I = 2.0) with ARX: ";

	try
	{
		// Przygotowanie danych:
		ModelARX instancjaTestowaARX({ -0.4 }, { 0.6 }, 1, 0);
        RegulatorPID instancjaTestowaPID(0.5, 2.0);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++) {
			faktSygWy[i] = simulate_feedback(instancjaTestowaPID, instancjaTestowaARX, sygWe[i]);
            std::cout << faktSygWy[i] << ' ';
        }
        std::cout << std::endl;
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

int main()
{
    test_1();
    test_2();
    test_3();
    test_4();
}