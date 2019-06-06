#include "drawer.h"
#include "functions.h"

#include <windows.h>
#include <GL/gl.h>
#include <freeglut/freeglut.h>


bool closed = false;

const double translationSpeed = 0.2;
const double scalingSpeed = 0.1;

const int windowWidth = 800;
const int windowHeight = 600;

struct
{
    double xScale;
    double yScale;

    double lastX;
    double lastY;

    bool enabled;
} mouseMovement;

Drawer drawer;

enum FunctionType
{
    FT_LinearFunction = 0,
    FT_QuadraticFunction,
    FT_RationalFunction,
    FT_SinusFunction,
    FT_CosinusFunction,
    FT_TangensFunction,
    FT_ParabolaFunction
};

SinusFunction sinusFunction;
TangensFunction tangensFunction;
ParabolaFunction parabolaFunction;


void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    {
        drawer.drawCordinate();

        drawer.drawFunction();
        drawer.drawDerivative();
    }
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    double cordinateWidth = drawer.getCordinateXArm();
    double cordinateHeight = drawer.getCordinateYArm();

    mouseMovement.xScale = 2.0 * cordinateWidth / (double)width;
    mouseMovement.yScale = 2.0 * cordinateHeight / (double)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-cordinateWidth, cordinateWidth, -cordinateHeight, cordinateHeight);
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        mouseMovement.lastX = x;
        mouseMovement.lastY = y;

        mouseMovement.enabled = (state == 0);
    }
}

void motion(int x, int y)
{
    if(mouseMovement.enabled)
    {
        double dx = (x - mouseMovement.lastX) * mouseMovement.xScale;
        double dy = (mouseMovement.lastY - y) * mouseMovement.yScale;

        drawer.addXTranslation(dx);
        drawer.addYTranslation(dy);

        mouseMovement.lastX = x;
        mouseMovement.lastY = y;
    }
}

char keys[256];

void keyDown(unsigned char key, int width, int height)
{
    keys[key] = true;
}

void keyUp(unsigned char key, int width, int height)
{
    keys[key] = false;
}

void updateCamera()
{
    // przesuwanie wykresu

    if(keys['w'])
        drawer.addYTranslation(+translationSpeed);

    if(keys['s'])
        drawer.addYTranslation(-translationSpeed);

    if(keys['a'])
        drawer.addXTranslation(-translationSpeed * drawer.getXScale());

    if(keys['d'])
        drawer.addXTranslation(+translationSpeed * drawer.getXScale());

    // skalowanie wykresu

    if(keys['z'])
        drawer.addYScale(+scalingSpeed);

    if(keys['x'])
        drawer.addYScale(-scalingSpeed);

    if(keys['c'])
        drawer.addXScale(-scalingSpeed);

    if(keys['v'])
        drawer.addXScale(+scalingSpeed);

    // ustawianie wspolczynnikow funkcji

    if(keys['1'])
     //   funcDrawer.updateValueA(0.01);

    if(keys['2'])
        //funcDrawer.updateValueA(-0.01);

    if(keys['3'])
        //funcDrawer.updateValueB(0.01);

    if(keys['4'])
        //funcDrawer.updateValueB(-0.01);
int t;
    //if(keys['5'] && object == quadraticFunction)
        //funcDrawer.updateValueC(0.01);

    //if(keys['6'] && object == quadraticFunction)
        //funcDrawer.updateValueC(-0.01);
}

void close()
{
    closed = true;
}

void idle()
{
    if(closed)
        return;

    updateCamera();
    glutPostRedisplay();
    Sleep(20);
}

void menu(int choiceFunction)
{
    switch(choiceFunction)
    {
        case FT_LinearFunction:
            break;

        case FT_QuadraticFunction:
            break;

        case FT_RationalFunction:
            break;

        case FT_SinusFunction:
            drawer.setFunction(&sinusFunction);

            break;

        case FT_CosinusFunction:
            break;

        case FT_TangensFunction: drawer.setFunction(&tangensFunction);
            break;

        case FT_ParabolaFunction: drawer.setFunction(&parabolaFunction);
            break;
    }
}

int main(int argc, char *argv[])
{
    mouseMovement.enabled = false;

    drawer.setFunction(&sinusFunction);
    drawer.setStart(-10.0);
    drawer.setEnd(10.0);
    drawer.setStep(0.01);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("FunctionDrawer");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutCloseFunc(close);
    glutIdleFunc(idle);

    glutCreateMenu(menu);
    glutAddMenuEntry("linearFunction", FT_LinearFunction);
    glutAddMenuEntry("quadraticFunction", FT_QuadraticFunction);
    glutAddMenuEntry("rationalFunction", FT_RationalFunction);
    glutAddMenuEntry("sinusFunction", FT_SinusFunction);
    glutAddMenuEntry("cosinusFunction", FT_CosinusFunction);
    glutAddMenuEntry("tangensFunction", FT_TangensFunction);
    glutAddMenuEntry("parabolaFunction", FT_ParabolaFunction);
    //glutAddMenuEntry("clear", FT_ClearScreen);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
