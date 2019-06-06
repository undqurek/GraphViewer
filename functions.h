#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "function.h"


class SinusFunction
    : public Function
{
public:
    double calculate(double x);

    double getScaleXStep();
    double getScaleYStep();
};

class TangensFunction
    : public Function
{
public:
    double calculate(double x);

    double getScaleXStep();
    double getScaleYStep();
};

class ParabolaFunction
    : public Function
{
public:
    double calculate(double x);
};

#endif // FUNCTIONS_H
