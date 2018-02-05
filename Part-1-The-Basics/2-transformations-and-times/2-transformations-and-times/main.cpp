#include <iostream>
#include <stdlib.h> //Needed for "exit" function
#include <time.h>

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

bool mov = false;
float r,g,b;
float _angle = 30.0f;
float _cameraAngle = 0.0f;

//Initializes 3D rendering
//Initializes our rendering parameters
void initRendering() {
    //Makes 3D drawing work when something is in front of something else
    glEnable(GL_DEPTH_TEST);
}

void idle() {
    mov = true;
    //cout << "Im updating" << '\n';
    glutPostRedisplay();
}

void updateWithTimer(int value) {
    
    _angle += 2.0f;
    if (_angle > 360) {
        _angle -= 360;
        r = ((float) rand() / (RAND_MAX));
        g = ((float) rand() / (RAND_MAX));
        b = ((float) rand() / (RAND_MAX));
        cout << r << " - " << g << " - " << b;
    }
    
    glutPostRedisplay(); //Tell GLUT that the scene has changed
    
    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, updateWithTimer, 0);
}

void display() {
    //Clear information from last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    glRotatef(-_cameraAngle, 0.0f, 1.0f, 0.0f); //Rotate the camera
    glTranslatef(0.0f, 0.0f, -5.0f); //Move forward 5 units
    
    glPushMatrix();//Save the transformations performed thus far
    {
        glTranslatef(0.0f, -1.0f, 0.0f); //Move to the center of the trapezoid
        glRotatef(_angle, 0.0f, 0.0f, 1.0f);
        glColor3f(r, g, b);
        glBegin(GL_QUADS); //Begin quadrilateral coordinates
        {
            //Trapezoid
            glVertex3f(-0.7f, -0.5f, 0.0f);
            glVertex3f(0.7f, -0.5f, 0.0f);
            glVertex3f(0.4f, 0.5f, 0.0f);
            glVertex3f(-0.4f, 0.5f, 0.0f);
        }
        glEnd(); //End quadrilateral coordinates
    }
    glPopMatrix();//Undo the move to the center of the trapezoid
    
    glPushMatrix();
    {
        glTranslatef(-1.0f, 1.0f, 0.0f);
        glRotatef(_angle, 1.0f, 2.0f, 3.0f);
        glColor3f(g, r, b);
        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0.5f, -0.5f, 0.0f);
            glVertex3f(0.0f, 0.5f, 0.0f);
            glVertex3f(-0.5f, -0.5f, 0.0f);
        }
        glEnd();
    }
    glPopMatrix();
    
    glPushMatrix();
    {
        glTranslatef(1.0f, 1.0f, 0.0f); //Move to the center of the pentagon
        glRotatef(_angle, 0.0f, 1.0f, 0.0f);
        glColor3f(b, r, g);
        glBegin(GL_TRIANGLES);
        {
            //Pentagon
            glVertex3f(-0.5f, -0.5f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.0f);
            glVertex3f(-0.5f, 0.0f, 0.0f);
            
            glVertex3f(-0.5f, 0.0f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.0f);
            glVertex3f(0.5f, 0.0f, 0.0f);
            
            glVertex3f(-0.5f, 0.0f, 0.0f);
            glVertex3f(0.5f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.5f, 0.0f);
        }
        glEnd();
    }
    glPopMatrix();
    
    glutSwapBuffers();
}

//Called when the window is resized
void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

void handleKeyboard(unsigned char key, //The key that was pressed
                    int x, int y) {
    if ( (int)key == 32 ) {
        exit(0);
    }
}

int main(int argc, char** argv) {
    
    srand (time(NULL));
    r = g = b = 1.0f;
    
    /*
     * 1. Initialice GLUT
     */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    
    
    /*
     * 2. Create your window
     */
    glutCreateWindow("2. Basic Shapes - Transformations and Timers");
    initRendering();
    
    
    /*
     * Set functions to handle
     * rendering
     * key press
     * resize
     * idle
     */
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(handleKeyboard);
    glutTimerFunc(25, updateWithTimer, 0);
    
    glutMainLoop();
    
    
}
