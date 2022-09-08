/*###################################################################################################################*/

#include "LabSource.h"

/*-------------------------------------------------------------------------------------------------------------------*/
// �����������:

LabSource::LabSource(double start, double stop, double frequency) {

    LabSource::stop = stop;
    LabSource::start = start;
    LabSource::frequency = frequency;

    modelDots();

}

/*-------------------------------------------------------------------------------------------------------------------*/
// ������ ���������� ������������ �����:

auto LabSource::modelDots() -> void {

    double time = stop - start;

    /* �������� ������ �������������, ���� true - ����� ������� ���������� �������� �������������� */
    if (sampling) {
     
        dotsPerModel = static_cast<int>(time * abs(frequency) * dotsPerOsc);
        timeDiscrete = time / dotsPerModel;
    
    }
    else {

        dotsPerModel = static_cast<int>(time / timeDiscrete);
    
    }

    return;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ������� �������� �������� ������� � ���������:

auto LabSource::clear() -> LabSource& {

    function.clear();
    argument.clear();

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// �������:

auto LabSource::level(double level) -> LabSource& {

    /* �������� ������� ������� ���������� � ��������� ���������� ������� */
    double end = argument.size() ? argument.back().real() : 0;

    for (int i = 0; i < dotsPerModel; ++i) {

        double value;
        double now = start + (stop - start) * i / dotsPerModel;
        
        value = level;

        if (modParameters.modType == Modulation::AMP) {
            value *= (1 + modParameters.depth * modParameters.modFunction(now));
        }

        function.push_back(value);
        argument.push_back(now + end);
    }

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ���������:

auto LabSource::sin(ModParameters modulation) -> LabSource& {

    /* �������� ������� ������� ���������� � ��������� ���������� ������� */
    double end = argument.size()? argument.back().real() : 0;     
                                                                                
    for (int i = 0; i < dotsPerModel; ++i) {

        double now = start + (stop - start) * i / dotsPerModel;
        
        double amplitude = LabSource::amplitude;
        double phase = 8 * atan(1) * LabSource::frequency * now;
        double originPhase = LabSource::phase;
        
        if (modulation.modType == Modulation::AMP) {
            amplitude *= (1 + modulation.depth * modulation.modFunction(now));
        }

        if (modulation.modType == Modulation::PH) {
            originPhase += 8 * atan(1) * modulation.depth * modulation.modFunction(now);
        }

        /* �����������: ���������� ������� ��������� �� ������ ��������� �� ���������� */
        if (modulation.modType == Modulation::FRQ) {
            auto a = integral(modulation.modFunction, start, now, timeDiscrete);
            phase += 8 * atan(1) * modulation.depth * integral(modulation.modFunction, start, now, timeDiscrete);
        }
        
        double value, fullPhase;
        fullPhase = phase + originPhase;
        value = amplitude * std::sin(fullPhase);

        function.push_back(value);
        argument.push_back(now + end);
    }

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ���������:

auto LabSource::sin() -> LabSource& {
    
    sin(modParameters);

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ������ ������� ����������������:

auto LabSource::ambguity(double lFreq, double rFreq, double step, LabSource& source1, LabSource& source2) -> field
{

    field temp;
    source2.setFrequency(lFreq);

    source1.sin();
    source2.setTimeDiscrete(source1.timeDiscrete);

    int dots = static_cast<int>((rFreq - lFreq) / step);
    for (int i = 0; i <= dots; ++i) {

        source2.sin();
        source2.convFFT(source1.function).roll();

        temp.push_back(source2.getValue(Format::ABS, Type::FUNCTION));
        
        source2.frequency += step;
        source2.clear();
        
    }

    return temp;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ������ ������� ����������������:

auto LabSource::ambguity(double lFreq, double rFreq, double step) -> field
{
    LabSource source(start, stop, this->frequency);
    source.setModParameters(modParameters);

    return ambguity(lFreq, rFreq, step, *this, source);
}

/*===================================================================================================================*/