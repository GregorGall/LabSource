/*###################################################################################################################*/

#include "LabSource.h"

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� �������:

auto LabSource::setFrequency(double frequency) -> LabSource& {
    
    LabSource::frequency = frequency;
    modelDots();

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� ��������� �������:

auto LabSource::setMult(double mult) -> LabSource&
{
    LabSource::mult = mult;
    modelDots();

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� ��������� ����:

auto LabSource::setPhase(double phase) -> LabSource&
{
    LabSource::phase = phase;

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� ��������� ������:

auto LabSource::setTime(double start, double stop) -> LabSource&
{
    LabSource::start = start;
    LabSource::stop = stop;
    modelDots();

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� ���������:

auto LabSource::setAmplitude(double amplitude) -> LabSource&
{
    LabSource::amplitude = amplitude;

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� ���������� ��������:

auto LabSource::setTimeDiscrete(double discrete) -> LabSource&
{
    LabSource::timeDiscrete = discrete;
    sampling = false;
    modelDots();

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� ������ ������������� (auto/self):

auto LabSource::AutoSampling(bool mode) -> LabSource&
{
    try {
        if (timeDiscrete <= 0) { throw "Error: auto_sampling mode = true with timeDiscret <= 0 \n"; }
        sampling = mode;
    }
    catch (std::string& error) {
        std::cout << error;
    }
    
    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� ���������� ����� ������������ �� ���� ���������:

auto LabSource::setDotsPerOsc(int dotsPerOsc) -> LabSource&
{
    LabSource::dotsPerOsc = dotsPerOsc;
    modelDots();

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� ���������� ���������:

auto LabSource::setModParameters(ModParameters modParameters) -> LabSource&
{
    LabSource::modParameters.depth = modParameters.depth;
    LabSource::modParameters.modType = modParameters.modType;
    LabSource::modParameters.modFunction = modParameters.modFunction;

    return *this;
}

/*===================================================================================================================*/