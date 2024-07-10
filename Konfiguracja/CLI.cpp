#include "CLI.h"

CLI::CLI(std::shared_ptr<Configuration> config) : m_config(config)
{

}

void CLI::printTp()
{

    double samplingPeriod = m_config->m_jsonData["Params"]["Tp"];
    std::cout << "Okres probkowania: " << samplingPeriod << std::endl;
}

void CLI::printSimTime()
{

    double simulationTime = m_config->m_jsonData["Params"]["SimTime"];
    std::cout << "Liczba probek symulacji: " << simulationTime << std::endl;
}

void CLI::printParams()
{

    std::cout << "Parametry symulacji:" << std::endl;

    printTp();
    printSimTime();
}

void CLI::printSignal()
{

    const auto &signalData = m_config->m_jsonData["Signal"];
    std::cout << "Sygnaly:" << std::endl;

    for (size_t index = 0; index < signalData.size(); ++index)
    {
        const auto &signal = signalData[index];
        std::string signalType = signal["type"];

        std::cout << "#" << index << ": ";

        if (signalType == "signal_base")
        {
            std::cout << "Sygnal bazowy" << std::endl;
        }
        if (signalType == "step")
        {
            double amplitude = signal["amplitude"];
            double start = signal["start"];
            double stop = signal["stop"];
            std::cout << "Skok: amplituda = " << amplitude << ", start = " << start << ", stop = " << stop << std::endl;
        }
        if (signalType == "sin")
        {
            double amplitude = signal["amplitude"];
            double frequency = signal["frequency"];
            double start = signal["start"];
            double stop = signal["stop"];
            std::cout << "Sinus: amplituda = " << amplitude << ", czestotliwosc = " << frequency << ", start = " << start << ", stop = " << stop << std::endl;
        }
        if (signalType == "rec")
        {
            double amplitude = signal["amplitude"];
            double frequency = signal["frequency"];
            double dutyCycle = signal["duty_cycle"];
            double start = signal["start"];
            double stop = signal["stop"];
            std::cout << "Prostokat: amplituda = " << amplitude << ", czestotliwosc = " << frequency << ", wypelnienie = " << dutyCycle << ", start = " << start << ", stop = " << stop << std::endl;
        }
        if (signalType == "tri")
        {
            double amplitude = signal["amplitude"];
            double frequency = signal["frequency"];
            double dutyCycle = signal["duty_cycle"];
            double start = signal["start"];
            double stop = signal["stop"];
            std::cout << "Trojkat: amplituda = " << amplitude << ", czestotliwosc = " << frequency << ", wypelnienie = " << dutyCycle << ", start = " << start << ", stop = " << stop << std::endl;
        }
        if (signalType == "noise")
        {
            double mean = signal["mean"];
            double variance = signal["variance"];
            double start = signal["start"];
            double stop = signal["stop"];
            std::cout << "Szum: srednia = " << mean << ", odchylenie standardowe = " << variance << ", start = " << start << ", stop = " << stop << std::endl;
        }
    }
}

void CLI::printSystem(nlohmann::json& systemElements) {

    int index = 0;
    
    std::cout << "Struktura:" <<std::endl;

    for (auto it = systemElements.items().begin(); it != systemElements.items().end(); ++it) {
        const auto& element = it.value();
        const std::string& elementType = element["type"];

        if (elementType == "petla") {
            std::string structure = element["structure"] == "close" ? "zamknieta" : "otwarta";
            std::cout << "Element #" << index << ": Petla: struktura: " << structure << std::endl;
        } else if (elementType == "pid") {
            double k = element["k"];
            double TI = element["TI"];
            double TD = element["TD"];

            std::cout << "Element #" << index << ": Pid: k = " << k << ", TI = " << TI << ", TD = " << TD << std::endl;
        } else if (elementType == "arx") {
            std::vector<double> A = element["A"];
            std::vector<double> B = element["B"];
            int delay = element["delay_order"];
            double deviation = element["standard_deviation"];

            std::cout << "Element #" << index << ": ARX: A = [";
            for (const auto& value : A) {
                std::cout << value << ", ";
            }
            std::cout << "\b\b], ";

            std::cout << "B = [";
            for (const auto& value : B) {
                std::cout << value << ", ";
            }
            std::cout << "\b\b], ";

            std::cout << "opoznienie = " << delay << ", zaklocenie: " << deviation << std::endl;
        } else if (elementType == "static") {
            double x_left = element["x_left"];
            double x_right = element["x_right"];

            std::cout << "Element #" << index << ": Obiekt statyczny: Nasycenie dolne = " << x_left << ", Nasycenie gorne = " << x_right << std::endl;
        }

        index++;
    }
}


void CLI::toNextLoop(nlohmann::json& inp) {

    int index_option;
    
    std::cout << "Wybierz indeks petli ktorej elementy chcesz zobaczyc" <<std::endl;
    std:: cin >> index_option;
    
    if (inp["elements"][index_option]["type"] == "petla") {
        
        editStructureMoving(inp["elements"][index_option]);

    }
    else {
        std::cout <<"Podano zly indeks albo na tym indeksie nie ma petli" << std::endl;
    }

}

void CLI::changeConfiguration()
{

    std::string option;

    enum MainOptions
    {
        ZMIEN_TP = 1,
        ZMIEN_CZAS,
        ZMIEN_SYGNAL,
        DODAJ_SYGNAL,
        USUN_SYGNAL,
        USUN_WSZYSTKIE_WYGNALY,
        ZMIEN_STRUKTURE,
        ZAKONCZ
    };

    while (true)
    {
        std::cout << "Wybierz opcje:" << std::endl;
        std::cout << "1. Zmien okres probkowania" << std::endl;
        std::cout << "2. Zmien liczbe probek" << std::endl;
        std::cout << "3. Zmodyfikuj parametry sygnalow" << std::endl;
        std::cout << "4. Dodaj sygnal" << std::endl;
        std::cout << "5. Usun sygnal" << std::endl;
        std::cout << "6. Usun wszystkie sygnaly" << std::endl;
        std::cout << "7. Zmodyfikuj parametry struktury" << std::endl;
        std::cout << "8. Zakoncz modyfikacje symulacji" << std::endl;
        std::cin >> option;

        switch (std::stoi(option))
        {
        case ZMIEN_TP:
            changeTp();
            break;

        case ZMIEN_CZAS:
            changeSimTime();
            break;

        case ZMIEN_SYGNAL:
            modifySignal();
            break;

        case DODAJ_SYGNAL:
            addSignal();
            break;

        case USUN_SYGNAL:
            deleteSignal();
            break;

        case USUN_WSZYSTKIE_WYGNALY:
            deleteAllSignals();
            break;

        case ZMIEN_STRUKTURE:
            editStructureMoving(m_config -> m_jsonData["System"][0]);
            break;

        case ZAKONCZ:
            return;
            break;

        default:
            break;
        }
    }
}

void CLI::deleteAllSignals() {

    m_config->m_jsonData["Signal"] = nlohmann::json::array();

    nlohmann::json baseSignal = {
        {"type", "signal_base"}
    };
    m_config->m_jsonData["Signal"].push_back(baseSignal);

    printSignal();

}

void CLI::structureMove(nlohmann::json& inp) {

    std::string option;

    printSystem(inp);

    enum MainOptions
    {
        WEJDZ_DO_PETLI = 1,
        ZAKONCZ
    };

    while (true)
    {   
        std::cout << "Wybierz opcje:" << std::endl;
        std::cout << "1. Wejdz do petli" << std::endl;
        std::cout << "2. Zakoncz" << std::endl;
        std::cin >> option;

        switch (std::stoi(option))
        {
        case WEJDZ_DO_PETLI:
            toNextLoop(inp);
            break;

        case ZAKONCZ:
            return;

        default:
            break;
        }
    }
}

void CLI::showConfig(nlohmann::json& inp) {
    std::string option;
    std::string temp;

    enum MainOptions {
        WEJDZ_DO_PETLI = 1,
        POWROT,
        ZAKONCZ
    };

    while (true) {
        printParams();
        printSignal();
        inp["structure"] == "open" ? temp = "otwarta" : temp = "zamknieta";
        std::cout << "Petla w ktorej sie znajdujesz jest " << temp << std::endl;
        printSystem(inp["elements"]);

        std::cout << "Wybierz opcje:" << std::endl;
        std::cout << "1. Wejdz do petli" << std::endl;
        std::cout << "2. Cofnij" << std::endl;  
        std::cin >> option;

        switch (std::stoi(option)) {
            case WEJDZ_DO_PETLI:
                toNextLoopConfig(inp);
                break;

            case POWROT:  
                return;

            default:
                break;
        }
    }
}


void CLI::toNextLoopConfig(nlohmann::json& inp) {

    int index_option;
    
    std::cout << "Wybierz indeks petli ktorej elementy chcesz zobaczyc" <<std::endl;
    std:: cin >> index_option;

    if (inp["elements"][index_option]["type"] == "petla") {

        showConfig(inp["elements"][index_option]);

    }
    else {
        std::cout <<"Podano zly indeks albo na tym indeksie nie ma petli" << std::endl;
    }

}


void CLI::editStructureMoving(nlohmann::json& inp) {

    std::string option;
    std::string temp;

    enum Options
    {
        MODYFIKUJ_STRUKTURE = 1,
        ZMIEN_PETLE,
        DODAJ_ELEMENT,
        USUN_ELEMENT,
        USUN_ELEMENTY_PETLI,
        ZMIEN_OTWARTOSC,
        ZAKONCZ
    };

    while (true)
    {   
        std::string tmp;
        inp["structure"] == "open" ? tmp = "otwarta" : tmp = "zamknieta";
        std::cout << "Petla w ktorej sie znajdujesz jest " <<tmp <<std::endl;

        printSystem(inp["elements"]);

        std::cout << "Wybierz opcje:" << std::endl;
        std::cout << "1. Zmien element systemu w obecnej petli" << std::endl;
        std::cout << "2. Zmien aktualna petle" << std::endl;
        std::cout << "3. Dodaj element w aktualnej petli" << std::endl;
        std::cout << "4. Usun element w aktualnej petli" << std::endl;
        std::cout << "5. Usun wszystkie elementy petli" << std::endl;
        std::cout << "6. Zmien strukture petli na przeciwna" << std::endl;
        std::cout << "7. Cofnij" <<std::endl;
        std::cin >> option;

        switch (std::stoi(option))
        {
        case MODYFIKUJ_STRUKTURE:
            modifyStructure(inp["elements"]);
            break;

        case ZMIEN_PETLE:
            toNextLoop(inp);
            break;

        case DODAJ_ELEMENT:
            addElement(inp["elements"]);
            break;

        case USUN_ELEMENT:
            eraseElement(inp["elements"]);
            break;

        case USUN_ELEMENTY_PETLI:
            eraseAllElements(inp["elements"]);
            break;

        case ZMIEN_OTWARTOSC:
            inp["structure"] = inp["structure"] == "open" ? "close" : "open";
            inp["structure"] == "open" ? temp = "otwarta" : temp = "zamknieta";
            std::cout << "Zmieniono strukture aktualnej petli na " << temp << std::endl;
            break;

        case ZAKONCZ:
            return;
            break;

        default:
            break;
        }
    }
}

void CLI::addElement(nlohmann::json& inp) {

    int index;
    std::string structureType;

    nlohmann::json& tmp = inp;

    std::cout << "Podaj indeks na ktorym chcesz dodac nowa strukture: ";
    std::cin >> index;

    if (index < 0 || index > inp.size()) {
        std::cout << "Podano nieprawidlowy indeks." << std::endl;
        return;
    }

    std::cout << "Podaj typ elementu ktory chcesz dodac (petla, pid, arx, static): ";
    std::cin >> structureType;

    nlohmann::json newStructure;

    if (structureType == "petla") {
        std::cout << "Wybierz jaka strukture ma miec petla: close/open" << std::endl;
        std::string str;
        std::cin >> str;

        newStructure = {
            {"type", "petla"}, {"structure", str}, {"elements", nlohmann::json::array()}
        };

        tmp.insert(tmp.begin() + index, newStructure);
    }
    else if (structureType == "pid") {
        std::cout << "Podaj po kolei wartosci: k, TI, TD" << std::endl;
        double k, TI, TD;
        std::cin >> k >> TI >> TD;

        newStructure = {
            {"type", "pid"}, {"k", k}, {"TI", TI}, {"TD", TD}
        };

        tmp.insert(tmp.begin() + index, newStructure);
    }
    else if (structureType == "arx") {
        std::cout << "Podaj po kolei wartosci: A, B, opoznienie, zaklocenie. Uzyj srednika by zakonczyc wpisywanie elementow A i B" << std::endl;
        std::vector<double> A, B;
        int delay_order;
        double standard_deviation;

        double aValue;
        while (std::cin >> aValue) {
            A.push_back(aValue);

            char lastChar;
            std::cin >> std::ws >> lastChar;
            if (lastChar == ';') {
                break;
            }
        }

        double bValue;
        while (std::cin >> bValue) {
            B.push_back(bValue);

            char lastChar;
            std::cin >> std::ws >> lastChar;
            if (lastChar == ';') {
                break;
            }
        }

        std::cin >> delay_order >> standard_deviation;

        newStructure = {
            {"type", "arx"}, {"A", A}, {"B", B}, {"delay_order", delay_order}, {"standard_deviation", standard_deviation}
        };

        tmp.insert(tmp.begin() + index, newStructure);
    }
    else if (structureType == "static") {
        std::cout << "Podaj po kolei wartosci: nasycenie dolne, nasycenie gorne" << std::endl;
        double x_left, x_right;
        std::cin >> x_left >> x_right;

        newStructure = {
            {"type", "static"}, {"x_left", x_left}, {"x_right", x_right}
        };

        tmp.insert(tmp.begin() + index, newStructure);
    }

    else {
        std::cout << "Nieznany typ struktury" <<std::endl;
    }

    std::cout << "Struktura zostala zmieniona" << std::endl;

    std::cout << "Struktura po zmianach:" << std::endl;

}

void CLI::changeTp()
{

    printTp();

    double Tp;

    std::cout << "Wpisz nowy okres probkowania:" << std::endl;
    std::cin >> Tp;

    m_config->m_jsonData["Params"]["Tp"] = Tp;

    std::cout << "Nowy okres probkowania: " << Tp << std::endl;
    printTp();
}

void CLI::changeSimTime()
{

    printSimTime();

    double SimTime;

    std::cout << "Wpisz nowa liczbe probek:" << std::endl;
    std::cin >> SimTime;

    m_config->m_jsonData["Params"]["SimTime"] = SimTime;

    std::cout << "Nowa liczba probek: " << SimTime << std::endl;
    printSimTime();
}

void CLI::modifySignal()
{

    printSignal();

    int index;

    std::cout << "Wybierz ktory sygnal chcesz zmienic" << std::endl;
    std::cin >> index;

    if (index < 0 || index > m_config->m_jsonData["Signal"].size() - 1)
    {
        std::cout << "Podano nieprawidlowy indeks" << std::endl;

        return;
    }

    std::string signalType = m_config->m_jsonData["Signal"][index]["type"];

    nlohmann::json newSignal;

    if (index == 0)
    {
        std::cout << "Sygnal bazowy nie moze byc zmieniony." << std::endl;
        return;
    }

    if (signalType == "step")
    {
        std::cout << "Podaj po kolei wartosci: amplituda, start, stop" << std::endl;
        double amplitude, start, stop;
        std::cin >> amplitude >> start >> stop;

        nlohmann::json newSignal =
            {
                {"type", "step"}, {"amplitude", amplitude}, {"start", start}, {"stop", stop}
            };

        m_config->m_jsonData["Signal"][index] = newSignal;
    }

    if (signalType == "sin")
    {
        std::cout << "Podaj po kolei wartosci: amplituda, czestotliwosc, start, stop" << std::endl;
        double amplitude, frequency, start, stop;
        std::cin >> amplitude >> frequency >> start >> stop;

        nlohmann::json newSignal =
            {
                {"type", "sin"}, {"amplitude", amplitude}, {"frequency", frequency}, {"start", start}, {"stop", stop}
            };

        m_config->m_jsonData["Signal"][index] = newSignal;
    }

    if (signalType == "rec")
    {
        std::cout << "Podaj po kolei wartosci: amplituda, czestotliwosc, wypelnienie, start, stop" << std::endl;
        double amplitude, frequency, duty_cycle, start, stop;
        std::cin >> amplitude >> frequency >> duty_cycle >> start >> stop;

        nlohmann::json newSignal =
            {
                {"type", "rec"}, {"amplitude", amplitude}, {"frequency", frequency}, {"duty_cycle", duty_cycle}, {"start", start}, {"stop", stop}
            };

        m_config->m_jsonData["Signal"][index] = newSignal;
    }

    if (signalType == "tri")
    {
        std::cout << "Podaj po kolei wartosci: amplituda, czestotliwosc, wypelnienie, start, stop" << std::endl;
        double amplitude, frequency, duty_cycle, start, stop;
        std::cin >> amplitude >> frequency >> duty_cycle >> start >> stop;

        nlohmann::json newSignal =
            {
                {"type", "tri"}, {"amplitude", amplitude}, {"frequency", frequency}, {"duty_cycle", duty_cycle}, {"start", start}, {"stop", stop}
            };

        m_config->m_jsonData["Signal"][index] = newSignal;
    }

    if (signalType == "noise")
    {
        std::cout << "Podaj po kolei wartosci: srednia, odchylenie standardowe, start, stop" << std::endl;
        double mean, variance, start, stop;
        std::cin >> mean >> variance >> start >> stop;

        nlohmann::json newSignal =
            {
                {"type", "noise"}, {"mean", mean}, {"variance", variance}, {"start", start}, {"stop", stop}
            };

        m_config->m_jsonData["Signal"][index] = newSignal;
    }

    std::cout << "Sygnal zostal zmieniony" << std::endl;

    std::cout << "Sygnaly po zmianach:" << std::endl;
    printSignal();
}

void CLI::addSignal()
{

    printSignal();

    int index;

    std::cout << "Wybierz na ktorym indeksie chcesz dodac nowy sygnal: " << std::endl;
    std::cin >> index;

    if (index < 0 || index > m_config->m_jsonData["Signal"].size())
    {
        std::cout << "Podano nieprawidlowy indeks" << std::endl;

        return;
    }

    if (index == 0)
    {
        std::cout << "Na tym indeksie wystepuje sygnal bazowy. Nie mozna umiescic sygnalu na tym indeksie." << std::endl;
        return;
    }

    std::string signalType;

    std::cout << "Podaj typ sygnalu ktory chcesz dodac (step, sin, rec, tri, noise): ";
    std::cin >> signalType;

    nlohmann::json newSignal;

        if (signalType == "step")
            {
            std::cout << "Podaj po kolei wartosci: amplituda, start, stop" << std::endl;
            double amplitude, start, stop;
            std::cin >> amplitude >> start >> stop;

            nlohmann::json newSignal =
                {
                    {"type", "step"}, {"amplitude", amplitude}, {"start", start}, {"stop", stop}
                };

            nlohmann::json &tmp = m_config->m_jsonData["Signal"];
            tmp.insert(tmp.begin() + index, newSignal);
        }

        else if (signalType == "sin")
        {
            std::cout << "Podaj po kolei wartosci: amplituda, czestotliwosc, start, stop" << std::endl;
            double amplitude, frequency, start, stop;
            std::cin >> amplitude >> frequency >> start >> stop;

            nlohmann::json newSignal =
                {
                    {"type", "sin"}, {"amplitude", amplitude}, {"frequency", frequency}, {"start", start}, {"stop", stop}
                };

            nlohmann::json &tmp = m_config->m_jsonData["Signal"];
            tmp.insert(tmp.begin() + index, newSignal);
        }

        else if (signalType == "rec")
        {
            std::cout << "Podaj po kolei wartosci: amplituda, czestotliwosc, wypelnienie, start, stop" << std::endl;
            double amplitude, frequency, duty_cycle, start, stop;
            std::cin >> amplitude >> frequency >> duty_cycle >> start >> stop;

            nlohmann::json newSignal =
                {
                    {"type", "rec"}, {"amplitude", amplitude}, {"frequency", frequency}, {"duty_cycle", duty_cycle}, {"start", start}, {"stop", stop}
                };

            nlohmann::json &tmp = m_config->m_jsonData["Signal"];
            tmp.insert(tmp.begin() + index, newSignal);
        }

        else if (signalType == "tri")
        {
            std::cout << "Podaj po kolei wartosci: amplituda, czestotliwosc, wypelnienie, start, stop" << std::endl;
            double amplitude, frequency, duty_cycle, start, stop;
            std::cin >> amplitude >> frequency >> duty_cycle >> start >> stop;

            nlohmann::json newSignal =
                {
                    {"type", "tri"}, {"amplitude", amplitude}, {"frequency", frequency}, {"duty_cycle", duty_cycle}, {"start", start}, {"stop", stop}
                };

            nlohmann::json &tmp = m_config->m_jsonData["Signal"];
            tmp.insert(tmp.begin() + index, newSignal);
        }

        else if (signalType == "noise")
        {
            std::cout << "Podaj po kolei wartosci: srednia, odchylenie standardowe, start, stop" << std::endl;
            double mean, variance, start, stop;
            std::cin >> mean >> variance >> start >> stop;

            nlohmann::json newSignal =
                {
                    {"type", "noise"}, {"mean", mean}, {"variance", variance}, {"start", start}, {"stop", stop}
                };

            nlohmann::json &tmp = m_config->m_jsonData["Signal"];
            tmp.insert(tmp.begin() + index, newSignal);
        }
        else
        {
            std::cout << signalType.size() << std::endl;

            std::cout << "Nieznany typ sygnalu." << std::endl;
            return;
        }

    std::cout << "Sygnal zostal dodany." << std::endl;

    std::cout << "Sygnaly po zmianach:" << std::endl;

    printSignal();
}

void CLI::deleteSignal()
{

    printSignal();

    int index;

    std::cout << "Wybierz ktory sygnal chcesz usunac: " << std::endl;
    std::cin >> index;

    if (index < 0 || index > m_config->m_jsonData["Signal"].size() - 1)
    {
        std::cout << "Podano nieprawidlowy indeks" << std::endl;

        return;
    }

    if (index == 0)
    {
        std::cout << "Na tym indeksie wystepuje sygnal bazowy. Nie mozna usunac tego sygnalu." << std::endl;
        return;
    }

    m_config->m_jsonData["Signal"].erase(m_config->m_jsonData["Signal"].begin() + index);

    std::cout << "Sygnal zostal usuniety." << std::endl;

    std::cout << "Sygnaly po zmianach:" << std::endl;
    printSignal();
}

void CLI::modifyStructure(nlohmann::json& inp)
{

    int index;

    std::cout << "Wybierz ktory element chcesz zmienic" << std::endl;
    std::cin >> index;

    if (index < 0 || index > inp.size() - 1)
    {
        std::cout << "Podano nieprawidlowy indeks" << std::endl;
        return;
    }

    std::string structureType = inp[index]["type"];

    if (structureType == "petla")
    {
        std::cout << "Wybierz jaka strukture ma miec petla: close/open" << std::endl;
        std::string str;
        std::cin >> str;

        inp[index]["structure"] = str;
    }
    else if (structureType == "pid")
    {
        std::cout << "Podaj po kolei wartosci: k, TI, TD" << std::endl;
        double k, TI, TD;
        std::cin >> k >> TI >> TD;

        nlohmann::json newStructure = {
            {"type", "pid"}, {"k", k}, {"TI", TI}, {"TD", TD}
        };

        inp[index] = newStructure;
    }
    else if (structureType == "arx")
    {
        std::cout << "Podaj po kolei wartosci: A, B, opoznienie, zaklocenie. Uzyj srednika by zakonczyc wpisywanie elementow A i B" << std::endl;
        std::vector<double> A, B;
        int delay_order;
        double standard_deviation;

        double aValue;
        while (std::cin >> aValue)
        {
            A.push_back(aValue);

            char lastChar;
            std::cin >> std::ws >> lastChar;
            if (lastChar == ';')
            {
                break;
            }
        }

        double bValue;
        while (std::cin >> bValue)
        {
            B.push_back(bValue);

            char lastChar;
            std::cin >> std::ws >> lastChar;
            if (lastChar == ';')
            {
                break;
            }
        }

        std::cin >> delay_order >> standard_deviation;

        nlohmann::json newStructure = {
            {"type", "arx"}, {"A", A}, {"B", B}, {"delay_order", delay_order}, {"standard_deviation", standard_deviation}
        };

        inp[index] = newStructure;
    }
    else if (structureType == "static")
    {
        std::cout << "Podaj po kolei wartosci: nasycenie dolne, nasycenie gorne" << std::endl;
        double x_left, x_right;
        std::cin >> x_left >> x_right;

        nlohmann::json newStructure = {
            {"type", "static"}, {"x_left", x_left}, {"x_right", x_right}
        };

        inp[index] = newStructure;
    }
    else
    {
        std::cout << "Nieznany typ struktury" << std::endl;
    }

    std::cout << "Struktura zostala zmieniona" << std::endl;

    std::cout << "Struktura po zmianach:" << std::endl;
}

void CLI::eraseElement(nlohmann::json& inp)
{
    int index;
    std::cout << "Wybierz indeks elementu do usuniecia: ";
    std::cin >> index;

    if (index < 0 || index >= inp.size())
    {
        std::cout << "Podano nieprawidlowy indeks" << std::endl;
        return;
    }

    nlohmann::json& element = inp[index];

    if (element.contains("basic"))
    {
        std::cout << "Tego elementu nie mozna usunac" << std::endl;
        return;
    }

    inp.erase(inp.begin() + index);

    std::cout << "Element zostal usuniety" << std::endl;

    printSystem(inp);
}

void CLI::eraseAllElements(nlohmann::json& inp) {

    std::cout << "Usun wszystkie elementy petli w ktorej sie znajdujesz" << std::endl;

    inp.clear();

    std::cout << "Usunieto wszystkie elementy petli w ktorej sie znajdujesz" << std::endl;

}

