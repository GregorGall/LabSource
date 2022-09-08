/*###################################################################################################################*/

#pragma once
#include <vector>

/*-------------------------------------------------------------------------------------------------------------------*/
// ����� ����� ���������:

enum class Modulation
{

    NON,                                                                     // ����������
    AMP,                                                                     // �����������
    FRQ,                                                                     // ���������
    PH                                                                       // �������

};

/*-------------------------------------------------------------------------------------------------------------------*/
// ��������� �������� ���������� ���������:

struct ModParameters
{
    using modF = double (*)(double);                                         // ��� - ��������� �� ������������ �������

    modF modFunction = nullptr;                                              // ������������ ������� (���������)
    Modulation modType = Modulation::NON;                                    // ��� ���������
    double depth = 0;                                                        // ������� ���������

};

/*-------------------------------------------------------------------------------------------------------------------*/
// ������������ �������:

double v_line(double now);
double linear(double now);                                  
double code(double now);
double step(double now);

/*===================================================================================================================*/