/*###################################################################################################################*/

#include "LSModulation.h"

/*-------------------------------------------------------------------------------------------------------------------*/
// Линейая функция:

double linear(double now) { return now; }

/*-------------------------------------------------------------------------------------------------------------------*/
// Линейая функция:

double v_line(double now) {

    double start{ 0 };
    double stop{ 1 };

    if (now < 0.5) { return now; }
    else { return -now; }
};

/*-------------------------------------------------------------------------------------------------------------------*/
// Кодовая функция:

double code(double now) {

    double start{ 0 };
    double stop{ 1 };

    std::vector<double> code{ 1,1,1,0,0,1,0 };

    auto size = code.size();
    double period = (stop - start) / size;
    int index = int(now / period);

    return code[index];
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Ступенчатая функция:

double step(double now) {

    double period{ 0.2 };
    double deviation{ 15 };
    double value = deviation * int(now / period);

    return value;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Генератор модулирующей синусоиды:

ModParameters::modF getSinMod(double time, int number) {
    double pi = 4 * atan(1);
    return [=](double now) { return sin(2 * pi * number / time * now);  };
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Генератор модулирующей последовательности:

ModParameters::modF getCodeMod(double discret, std::vector<double> code) {
    auto coder = [=](double now) { 
        auto index = size_t(now / discret);
        return index < code.size() ? code[index] : 0;  
    };
    return coder;
}

/*===================================================================================================================*/