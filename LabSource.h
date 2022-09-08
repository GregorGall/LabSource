/*###################################################################################################################*/
// ����� ���������

#pragma once

#include "../DMath/DMath.h"
#include "LSModulation.h"

/*###################################################################################################################*/

class LabSource:public DMath
{
    
    using field = std::vector<std::vector<double>>;

private:

    double stop;                                              // ��������� ������ ������� (������ � �������� now + end)
    double start;                                             // �������� ������ �������
    double timeDiscrete;                                      // ��������� �������

    double frequency;                                         // �������
    double mult = 1;                                          // ��������� �������
    double phase = 0;                                         // ��������� ����
    double amplitude = 1;                                     // ���������

    int dotsPerOsc = 64;                                      // ���������� ����� ������������ �� ������� �������
    int dotsPerModel;                                         // ���������� ����� ������������ �� ���� �����
    bool sampling{true};                                      // ����� ������� ���������� ��������
    ModParameters modParameters{};                            // ��������� ���������

public:

    LabSource(double start, double stop, double frequency);   // ����������� (��������� �����, �������� �����, �������)

    auto sin()                              -> LabSource&;    // ���������
    auto level(double  level)               -> LabSource&;    // �������
    auto sin(ModParameters modPr)           -> LabSource&;    // �������������� ���������
    auto ambguity(double lFreq,
                  double rFreq,
                  double step)              -> field;         // ������� ���������������� �������

    auto clear()                            -> LabSource&;    // ������� ������
    auto modelDots()                        -> void;          // ������ ���������� ������������ �����

    static auto ambguity(double lFreq,
                         double rFreq,
                         double step,
                         LabSource& source1,
                         LabSource& source2) -> field;         // ������� ���������������� �������

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

