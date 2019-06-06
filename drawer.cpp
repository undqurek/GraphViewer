#include "drawer.h"

#include <windows.h>
#include <GL/gl.h>
#include <stddef.h>


double Drawer::calculateFunction(double x)
{
    double tmp = this->_xScale * (x - this->_xTranslation);

    return this->_yScale * this->_function->calculate(tmp) + this->_yTranslation;
}

double Drawer::calculateDerivarive(double x)
{
    x = this->_xScale * (x - this->_xTranslation); // skalujemy i przesowamy w x'ie

    double dy = this->_function->calculate(x + this->_dx) - this->_function->calculate(x); // obliczamy przyrost wartosci y
    double derivative = dy / this->_dx; // obliczamy wartosc pochodnej w punkcie

    return this->_yScale * derivative + this->_yTranslation; // skalujemy i przesowamy w y'u
}

Drawer::Drawer()
{
    this->_cordinateXArm = 10.0;
    this->_cordinateYArm = 10.0;

    this->_start = 0.0;
    this->_end = 1.0;
    this->_step = 0.1;

    this->_dx = 0.01;

    this->_xTranslation = 0.0;
    this->_yTranslation = 0.0;

    this->_xScale = 1.0;
    this->_yScale = 1.0;

    this->_function = NULL;
}

void Drawer::setFunction(Function *function)
{
    this->_function = function;
}

void Drawer::setCordinateXArm(double value)
{
    this->_cordinateXArm = value;
}

void Drawer::setCordinateYArm(double value)
{
    this->_cordinateYArm = value;
}

void Drawer::setStart(double value)
{
    this->_start = value;
}

void Drawer::setEnd(double value)
{
    this->_end = value;
}

void Drawer::setStep(double value)
{
    this->_step = value;
}

void Drawer::setXTranslation(double value)
{
    this->_xTranslation = value;
}

void Drawer::setYTranslation(double value)
{
    this->_yTranslation = value;
}

void Drawer::setXScale(double value)
{
    this->_xScale = value;
}

void Drawer::setYScale(double value)
{
    this->_yScale = value;
}

double Drawer::getCordinateXArm()
{
    return this->_cordinateXArm;
}

double Drawer::getCordinateYArm()
{
    return this->_cordinateYArm;
}

double Drawer::getStart()
{
    return this->_start;
}

double Drawer::getEnd()
{
    return this->_end;
}

double Drawer::getStep()
{
    return this->_step;
}

double Drawer::getXTranslation()
{
    return this->_xTranslation;
}

double Drawer::getYTranslation()
{
    return this->_yTranslation;
}

double Drawer::getXScale()
{
    return this->_xScale;
}

double Drawer::getYScale()
{
    return this->_yScale;
}

void Drawer::addXTranslation(double value)
{
    this->_xTranslation += value;
}

void Drawer::addYTranslation(double value)
{
    this->_yTranslation += value;
}

void Drawer::addXScale(double value)
{
    this->_xScale += value;
}

void Drawer::addYScale(double value)
{
    this->_yScale += value;
}

void Drawer::drawCordinate()
{
    double valueArm = 0.1;

    double xStep = this->_function->getScaleXStep() / this->_xScale;
    double yStep = this->_function->getScaleYStep() * this->_yScale;

    glPushMatrix();
    {
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);

        // X axis
        glVertex2f(-this->_cordinateXArm, this->_yTranslation);
        glVertex2f(+this->_cordinateXArm, this->_yTranslation);

        if(xStep < 0.0)
            xStep = -xStep;

        if(xStep > 0.1)
        {
            double yStart = this->_yTranslation - valueArm;
            double yStop = this->_yTranslation + valueArm;

            for(double x = this->_xTranslation - xStep; x > -this->_cordinateXArm; x -= xStep)
            {
                glVertex2f(x, yStart);
                glVertex2f(x, yStop);
            }

            for(double x = this->_xTranslation + xStep; x < this->_cordinateXArm; x += xStep)
            {
                glVertex2f(x, yStart);
                glVertex2f(x, yStop);
            }
        }

        // Y axis
        glVertex2f(this->_xTranslation, -this->_cordinateYArm);
        glVertex2f(this->_xTranslation, +this->_cordinateYArm);

        if(yStep < 0.0)
            yStep = -yStep;

        if(yStep > 0.2)
        {
            double xStart = this->_xTranslation - valueArm;
            double xStop = this->_xTranslation + valueArm;

            for(double y = this->_yTranslation - yStep; y > -this->_cordinateYArm; y -= yStep)
            {
                glVertex2f(xStart, y);
                glVertex2f(xStop, y);
            }

            for(double y = this->_yTranslation + yStep; y < this->_cordinateYArm; y += yStep)
            {
                glVertex2f(xStart, y);
                glVertex2f(xStop, y);
            }
        }

        glEnd();
    }
    glPopMatrix();
}

void Drawer::drawFunction()
{
    ::glPushMatrix();
    {
        ::glBegin(GL_LINE_STRIP);
        ::glColor3f(0.0, 1.0, 0.0);

        for(double x = this->_start; x <= this->_end; x += this->_step)
            ::glVertex2f(x, this->calculateFunction(x));

        ::glEnd();
    }
    ::glPopMatrix();

//    double lastX = this->_start;
//    double lastY = this->calculateFunction(this->_start);

//    ::glPushMatrix();
//    {
//        ::glPointSize(4.0);
//        ::glColor3f(0.0, 1.0, 0.0);

//        for(double x = this->_start + this->_step; x <= this->_end; x += this->_step)
//        {
//            double y = this->calculateFunction(x);

//            ::glBegin(GL_LINES);
//            ::glVertex2f(lastX, lastY);
//            ::glVertex2f(x, y);
//            ::glEnd();

//            lastX = x;
//            lastY = y;
//        }
//    }
//    ::glPopMatrix();
}

void Drawer::drawDerivative()
{
    ::glPushMatrix();
    {
        ::glBegin(GL_LINE_STRIP);
        ::glColor3f(0.0, 1.0, 1.0);

        for(double x = this->_start; x <= this->_end; x += this->_step)
           ::glVertex2f(x, this->calculateDerivarive(x));

        ::glEnd();
    }
    ::glPopMatrix();

}
