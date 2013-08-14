/*
 * Physics.hpp
 *
 *  Created on: Aug 11, 2013
 *      Author: abhimanyu
 */
#include "include/GL/gl.h"
#include "include/glm1/glm.hpp"
#include "include/glm/glm.h"

#include "TerrainRenderer.hpp"
//#include "ObjectRenderer.hpp"

//Global definitions for environment in physics.

#define PI 3.14159f

#define X_AXIS glm::vec3(1.0f,0.0f,0.0f)
#define Y_AXIS glm::vec3(0.0f,1.0f,0.0f)
#define Z_AXIS glm::vec3(0.0f,0.0f,1.0f)

#define OBJ_ACC 0.03f
#define OBJ_HEIGHT_RET 0.009f
#define OBJ_RET 0.09f
#define OBJ_MU 0.0002f

#define DELTA_ANGLE 0.05f

#define GLOBAL_SCALE 1.0f

void initPhysics(){
	glScalef(GLOBAL_SCALE,GLOBAL_SCALE,GLOBAL_SCALE);

}
//Function to initialize the Physics engine.

void updateCameraPhysics(Camera* camera, Terrain* _terrain){
	//Updating location so that it remains within terrain.
	glm::vec3 location  = camera->position;
	float maxLength = _terrain->getLength()*GLOBAL_SCALE;
	float maxWidth = _terrain->getWidth()*GLOBAL_SCALE;

	if (location[0] > maxLength -3){
		camera->position[0]=maxLength-3;
	}

	if (location[2] > maxWidth -3){
		camera->position[2]=maxWidth-3;
	}

	if (location[0] < 3){
		camera->position[0]=3;
	}

	if (location[2] < 3){
		camera->position[2]=3;
	}

	if(location[1]  < _terrain->getHeight(location[0],location[2])+1){
		camera->position[1]=_terrain->getHeight(location[0],location[2]) + 1;
	}
	float speed = camera->speed;
	//Adding slope friction

	//Adding ground friction
	speed-=OBJ_MU;

	if(speed<0){
		speed = 0;
	}

	camera->speed = speed;
}

void updateObjectPhysics(Object* object, Terrain* _terrain){

}

void setObjectAcc(Object* object, glm::vec3 acc){
	object->acc=acc;
}

void setObjectPos(Object* object, glm::vec3 pos){
	object->position=pos;
}

void setObjectVel(Object* object, glm::vec3 vel){
	object->vel=vel;
}
