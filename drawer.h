#ifndef DRAWER_H
#define DRAWER_H

#include "function.h"


class Drawer
{
private:
    double _cordinateXArm;
    double _cordinateYArm;

    double _start, _end; // poczatek i koniec rysowanego przedzialu
    double _step; // krok co jaki obliczana jest wartosc funkcji

    double _dx; // dokladnosc dla obliczen pochodnej

    double _xTranslation, _yTranslation;
    double _xScale, _yScale;

    Function *_function;

    double calculateFunction(double x);
    double calculateDerivarive(double x);

public:
    Drawer();

    void setFunction(Function *function);

    void setCordinateXArm(double value);
    void setCordinateYArm(double value);

    void setStart(double value);
    void setEnd(double value);
    void setStep(double value);

    void setXTranslation(double value);
    void setYTranslation(double value);
    void setXScale(double value);
    void setYScale(double value);

    double getCordinateXArm();
    double getCordinateYArm();

    double getStart();
    double getEnd();
    double getStep();

    double getXTranslation();
    double getYTranslation();
    double getXScale();
    double getYScale();

    void addXTranslation(double value);
    void addYTranslation(double value);
    void addXScale(double value);
    void addYScale(double value);

    void drawCordinate();
    void drawFunction();
    void drawDerivative();
};

#endif // DRAWER_H
