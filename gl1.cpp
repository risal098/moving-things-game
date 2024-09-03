#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>  
#include <unistd.h> 
using namespace std;
const int mts = 100000;   //time sleep, 1 second
    float ssize=0.3f;
    float scolor=0.6f; 
//win situation
//target position
float targetx = 0.2f;
float targety = 0.8f;
// Square position
float x_pos = 0.0f;
float y_pos = 0.5f; // Start slightly above the center

float x_pos1 = -0.0f;
float y_pos1 = -0.5f; // Start slightly above the center

int grabStatus=0;
int win=0;
// Display function to draw the square
void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a red square
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(x_pos - 0.1f, y_pos - 0.1f);
        glVertex2f(x_pos + 0.1f, y_pos - 0.1f);
        glVertex2f(x_pos + 0.1f, y_pos + 0.1f);
        glVertex2f(x_pos - 0.1f, y_pos + 0.1f);
    glEnd();
    
    // pink square
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(x_pos1 - 0.1f, y_pos1 - 0.1f);
        glVertex2f(x_pos1 + 0.1f, y_pos1 - 0.1f);
        glVertex2f(x_pos1 + 0.1f, y_pos1 + 0.1f);
        glVertex2f(x_pos1 - 0.1f, y_pos1 + 0.1f);
    glEnd();
    
    // target drop
    glColor3f(0.8f, 0.6f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(targetx- 0.1f, targety - 0.1f);
        glVertex2f(targetx + 0.1f, targety - 0.1f);
        glVertex2f(targetx+ 0.1f, targety + 0.1f);
        glVertex2f(targetx - 0.1f, targety + 0.1f);
    glEnd();
    if(win==1){

   
    glColor3f(0.8f, scolor, 3.0f);
    glBegin(GL_POLYGON);
        glVertex2f(targetx- ssize, targety - ssize);
        glVertex2f(targetx + ssize, targety - ssize);
        glVertex2f(targetx+ ssize, targety + ssize);
        glVertex2f(targetx - ssize, targety + ssize);
    glEnd();
    
    
    
    }

    // Flush drawing commands
    glFlush();
}

// Function to handle keyboard input
void handleKeys(unsigned char key, int x, int y) {
    float tempx_pos=x_pos;
    float tempy_pos=y_pos;
    
    switch (key) {
        case 'w': y_pos += 0.02f; break; // Move up
        case 's': y_pos -= 0.02f; break; // Move down
        case 'a': x_pos -= 0.02f; break; // Move left
        case 'd': x_pos += 0.02f; break; // Move right
        case 'f':if(abs(x_pos1-x_pos)<0.2&&abs(y_pos1-y_pos)<0.2){grabStatus=1;cout<<"hooked"<<"\n";}break; //grab item
        case 'g':if(abs(x_pos1-x_pos)<0.2&&abs(y_pos1-y_pos)<0.2){grabStatus=0;cout<<"dropped"<<"\n";}break; //drop item
    }
    float xMovementGapx=tempx_pos-x_pos;
    float xMovementGapy=tempy_pos-y_pos;
    if(grabStatus==1||abs(x_pos1-x_pos)<0.181&&abs(y_pos1-y_pos)<0.181){
    	cout<<"touched "<<grabStatus<<"\n";
    	switch (key) {
        case 'w': y_pos1 += 0.02f; break; // Move up
        case 's': y_pos1 -= 0.02f; break; // Move down
        case 'a': x_pos1 -= 0.02f; break; // Move left
        case 'd': x_pos1 += 0.02f; break; // Move right
    }
    }
    if(abs(x_pos1-x_pos)<0.181&&abs(y_pos1-y_pos)<0.181){
    cout<<"valid: "<<grabStatus<<"\n";
    }
    cout<<"gap="<<abs(x_pos1-x_pos)<<" "<<abs(y_pos1-y_pos)<<"\n";
    cout<<x_pos<<"\n"<<y_pos<<"\n";
    cout<<x_pos1<<"\n"<<y_pos1<<"\n\n";
    
    
    glutPostRedisplay();// Redraw the screen with the updated position
    if(abs(x_pos1-targetx)<0.01&&abs(y_pos1-targety)<0.01){
    	cout<<"mission succes";
    	win=1;
    	glutPostRedisplay();
    
    	}
    	
    }
    


// Initialization function
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set background to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Move the Red Square");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeys); // Register the keyboard handler
    glutMainLoop();
    return 0;
}

