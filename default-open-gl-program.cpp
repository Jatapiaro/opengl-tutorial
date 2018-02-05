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

//Initializes 3D rendering
//Initializes our rendering parameters
void initRendering() {
    //Makes 3D drawing work when something is in front of something else
    glEnable(GL_DEPTH_TEST);
}

void idle() {
    mov = true;
    glutPostRedisplay();
}


/*
* In case you need to execute something each
* n miliseconds
*/
/*void updateWithTimer(int value) {
    
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
}*/


void display() {
    //Clear information from last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    
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

    //In case you need to execute something each n miliseconds
    //glutTimerFunc(25, updateWithTimer, 0);
    
    glutMainLoop();
    
    
}
