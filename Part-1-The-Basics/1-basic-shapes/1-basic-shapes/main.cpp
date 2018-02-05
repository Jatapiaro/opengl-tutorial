#include <iostream>
#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float angle = 45;
float dist = -5.0f;
int width, height;

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
                    int x, int y) {    //The current mouse coordinates
    
    cout << (int)key << '\n';
    switch (key) {
        case 32: //Escape key
            exit(0); //Exit the program
    }
}

//Initializes 3D rendering
//Initializes our rendering parameters
void initRendering() {
    //Makes 3D drawing work when something is in front of something else
    glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

//Draws the 3D scene
void drawScene() {
    
    
    //Clear information from last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    

    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    {
        //Trapezoid
        glColor3f(0, 0, 1);
        glVertex3f(-0.7f, -1.5f, -5.0f);
        glVertex3f(0.7f, -1.5f, -5.0f);
        glVertex3f(0.4f, -0.5f, -5.0f);
        glVertex3f(-0.4f, -0.5f, -5.0f);
    }
    glEnd(); //End quadrilateral coordinates
    
    glBegin(GL_TRIANGLES); //Begin triangle coordinates
    {
        //Pentagon
        glColor3f(1, 0, 0);
        glVertex3f(0.5f, 0.5f, dist);
        glVertex3f(1.5f, 0.5f, dist);
        glVertex3f(0.5f, 1.0f, dist);
        
        glVertex3f(0.5f, 1.0f, dist);
        glVertex3f(1.5f, 0.5f, dist);
        glVertex3f(1.5f, 1.0f, dist);
        
        glVertex3f(0.5f, 1.0f, dist);
        glVertex3f(1.5f, 1.0f, dist);
        glVertex3f(1.0f, 1.5f, dist);
        
        
        //Triangle
        glColor3f(0, 1, 0);
        glVertex3f(-0.5f, 0.5f, -5.0f);
        glVertex3f(-1.0f, 1.5f, -5.0f);
        glVertex3f(-1.5f, 0.5f, -5.0f);
    }
    glEnd();
    glutSwapBuffers();
}

void idle() {
    //angle += 0.1f;
    angle = 45;
    if ( dist <= 0 ) {
        dist += 0.1f;
    } else if ( dist > 0 ) {
        dist = -5.0f;
    }
    //cout << "Angle: " << angle;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    width = 600;
    height = 600;
    glutInitWindowSize(width, height); //Set the window size
    
    //Create the window
    glutCreateWindow("Basic Shapes - videotutorialsrock.com");
    initRendering(); //Initialize rendering
    
    //Set handler functions for drawing, keypresses, and window resizes
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutIdleFunc(idle);
    
    glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
    
}
    


