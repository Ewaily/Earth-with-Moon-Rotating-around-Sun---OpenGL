/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#include <windowsx.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#define SunSize 0.5
#define EarthSize 0.10
#define MoonSize 0.05


GLfloat SpeedMultiplicator = 1.0;
GLfloat DaysPerYear = 10.0;
GLfloat year = 0.0;   //degrees
GLfloat day = 0.0;
GLfloat moonAroundEarth = 0.0;
GLfloat moonItsSelf = 0.0;
GLfloat EarthOrbitRadius = 1.25;
GLfloat MoonOrbitRadius = 0.20;
GLfloat daySpeed = 5.0 * SpeedMultiplicator;
GLfloat yearSpeed = DaysPerYear / 360.0 * daySpeed * SpeedMultiplicator;
GLfloat moonAroundEarthSpeed = 1.25 * SpeedMultiplicator;
GLfloat moonItsSelfSpeed = 1 * SpeedMultiplicator;



static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix();

            gluLookAt(0.0,0.0,-4.0,0.0,0.0,1.0,0.0,-3.0,0.0); // controlling the camera ><><
            glColor3f(1.0,0.5,0.0);
            glutSolidSphere(SunSize,50,50);   // Display Sun as solid object
            glRotatef(year,0.0,1.0,0.0);   // Rotation of Earth around Sun
            glTranslatef(EarthOrbitRadius,0.0,0.0);
            glPushMatrix();
            glRotatef(day,0.25,1.0,0.0);


            glColor3f(0.0,0.0,0.61);
            glutSolidSphere(EarthSize,10,10);    //Display Earth as a solid object
            glPopMatrix();

            // Rotation of Moon around Earth
            glRotatef(moonAroundEarth,0.0,1.0,0.0);
            glRotatef(moonItsSelf,0.0,1.0,0.0);
            glTranslatef(MoonOrbitRadius,0.0,0.0);
            glColor3f(1.0,1.0,1.0);
            glutSolidSphere(MoonSize,8,8);   //Display Moon as a solid object
            glPopMatrix();

    glutSwapBuffers();
}
void Reshape(int x, int y)
{
            if (y == 0) return;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0,0,x,y);
            display();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
      day += daySpeed;
            year += yearSpeed;
            moonItsSelf += moonItsSelfSpeed;
            moonAroundEarth += moonAroundEarthSpeed;
            display();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(Reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
