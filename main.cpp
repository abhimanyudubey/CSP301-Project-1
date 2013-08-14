/*
 * Main Function for CSP301 Project 1.
 */

#include <stdio.h>

#include "include/GL/glut.h"
#include "include/glm1/glm.hpp"
#include "include/glm/glm.h"

#include "TerrainRenderer.hpp"
#include "Camera.hpp"
//#include "ObjectRenderer.hpp"
#include "Physics.hpp"

/* Global variables */
//char title [] = "Motorcycle Race - CSP301 Project 1";
//static float angle;
Terrain* _terrain;
/* Initialize OpenGL Graphics */
//Declaring local camera variables.
static Camera mainView(glm::vec3(60,0,60));
Object cube("objects/tree 1.obj");
static glm::vec2 dimensions;
static glm::vec2 old_mouse_coords;
void initGL() {
	glClearColor(0,200/255.0f,232/255.0f,240/255.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	//setObjectVel(&cube,glm::vec3(0.10,0.20,0.10));
	//mainView.assignObject(&cube);
	   setObjectPos(&cube,glm::vec3(40,_terrain->getHeight(40,40),40));
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glScalef(0.5,0.5,0.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	initPhysics();
	mainView.updateLocation(0.0);
	mainView.updateOrientation(glm::vec2(0.0,0.0));
	//Getting environment for rendering the object.
	updateCameraPhysics(&mainView,_terrain);
	renderTerrain(_terrain);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	Object* cubes [50];
//	for(int i=0;i<50;i++){
//		cubes[i] = &(Object("objects/airboat.obj"));
//		setObjectPos(cubes[i],glm::vec3(i*2,i,i*3));
//		cubes[i]->drawObject(GLM_SMOOTH, &mainView, _terrain);
//	}
	//glScalef(0.006,0.006,0.006);
	mainView.drawObject(GLM_SMOOTH, &cube, _terrain, 0.01,"77FFFF");
	updateObjectPhysics(&cube,_terrain);
	mainView.updateLocation(0.0);
	//Rendering the follower object.

	//Setting the camera to the assigned location on rendered terrain.

	glutSwapBuffers();
	//Position updates

}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
   dimensions = glm::vec2(width,height);
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(_terrain->getWidth()/2, (double)width / (double)height, 0.001f, 400.0f);
}

void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_UP :
			mainView.speed+=OBJ_ACC;
			break;
		case GLUT_KEY_DOWN :
			mainView.speed-=OBJ_RET;
			break;
	}
}
/* Main function: GLUT runs as a console application starting at main() */
void passiveMouse(int x, int y){
	float width = dimensions[0];
	float height = dimensions[1];
	float newx = x - old_mouse_coords[0];
	float newy = y - old_mouse_coords[1];
	mainView.updateOrientation(glm::vec2((x-width/2)/width*0.001*2*PI,(y-height/2)/height*0.001*PI));
	old_mouse_coords[0]=x;
	old_mouse_coords[1]=y;
	printf("%d %d \n",x,y);
}
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(1440,900);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("blah blah");          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutIdleFunc(display);
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   const char* fname = "bitmaps/heightmap.bmp";
	_terrain = loadTerrainFromHeightmap(fname,5.0f);
   initGL();                       // Our own OpenGL initialization
   glutSpecialFunc(processSpecialKeys);
   glutPassiveMotionFunc(passiveMouse);
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
