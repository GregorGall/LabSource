/*###################################################################################################################*/
// Класс генератор

#pragma once

#include "DMath.h"
#include "LSModulation.h"

/*###################################################################################################################*/

class LabSource:public DMath
{
    
    using field = std::vector<std::vector<double>>;

private:

    double stop;                                              // Начальный момент времени (запись в аргумент now + end)
    double start;                                             // Конечный момент времени
    double timeDiscrete;                                      // Временной дискрет

    double frequency;                                         // Частота
    double mult = 1;                                          // Множитель частоты
    double phase = 0;                                         // Начальная фаза
    double amplitude = 1;                                     // Амплитуда

    int dotsPerOsc = 64;                                      // Количество точек моделируемых на единицу частоты
    int dotsPerModel;                                         // Количество точек моделируемых за один вызов
    bool sampling{true};                                      // Режим расчета временного дискрета
    ModParameters modParameters{};                            // Параметры модуляции

public:

    LabSource(double start, double stop, double frequency);   // Конструктор (начальное время, конечное время, частота)

    auto sin()                              -> LabSource&;    // Синусоида
    auto level(double  level)               -> LabSource&;    // Уровень
    auto sin(ModParameters modPr)           -> LabSource&;    // Модулированная синусоида
    auto ambguity(double lFreq,
                  double rFreq,
                  double step)              -> field;         // Функция неопределенности сигнала

    auto clear()                            -> LabSource&;    // Очистка вывода
    auto modelDots()                        -> void;          // Расчет количества моделируемых точек

    static auto ambguity(double lFreq,
                         double rFreq,
                         double step,
                         LabSource& source1,
                         LabSource& source2) -> field;         // Функция неопределенности сигнала

/*-------------------------------------------------------------------------------------------------------------------*/

    auto setFrequency(double frequency)     -> LabSource&;
    auto setPhase(double phase)             -> LabSource&;
    auto setMult(double mult)               -> LabSource&;
    auto setTime(double start, double stop) -> LabSource&;
    auto setAmplitude(double amplitude)     -> LabSource&;
    auto setTimeDiscrete(double discrete)   -> LabSource&;
    auto setDotsPerOsc(int dotsPerOsc)      -> LabSource&;
    auto setModParameters(ModParameters)    -> LabSource&;
    auto AutoSampling(bool mode)            -> LabSource&;

    double getTimeDiscrete() { return timeDiscrete; }

};

/*===================================================================================================================*/

