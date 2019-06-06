#ifndef FUNCTION_H
#define FUNCTION_H

class Function
{
public:
    virtual double calculate(double x) = 0;

    virtual double getScaleXStep();
    virtual double getScaleYStep();
};

#endif // FUNCTION_H
