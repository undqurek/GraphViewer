#include "functions.h"

#include <math.h>


double SinusFunction::calculate(double x)
{
    return ::sin(x);
}

double SinusFunction::getScaleXStep()
{
    return 3.1415 * 0.25;
}

double SinusFunction::getScaleYStep()
{
    return 0.5;
}


double TangensFunction::calculate(double x)
{
    return ::tan(x);
}

double TangensFunction::getScaleXStep()
{
    return 3.1415 * 0.25;
}

double TangensFunction::getScaleYStep()
{
    return 0.5;
}


double ParabolaFunction::calculate(double x)
{
    return x * x;
}
