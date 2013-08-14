/*
 * Camera.hpp
 *
 *  Created on: Aug 11, 2013
 *      Author: abhimanyu
 */

#include "include/GL/gl.h"
#include "include/glm1/glm.hpp"
#include "include/glm/glm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ObjectRenderer.hpp"

#define MAX_OMEGA glm::vec2(0.1,0.1)
#define MIN_OMEGA glm::vec2(0.002, 0.002)
#define OMEGA_FRICTION 0.04

class Camera{
	public:
		glm::vec3 position;

		glm::vec3 direction;

		glm::vec2 theta;

		glm::vec2 omega;

		float speed;

		bool isFollower;

		Object* followingObject;

		Camera(glm::vec3 pos){
			position=pos;
			direction=glm::vec3(0.0f,0.0f,1.0f);
			theta=glm::vec2(0,0);
			omega=glm::vec2(0,0);
			speed=0.0f;
			isFollower=false;
			followingObject=NULL;
		}

		void setOrientation(glm::vec2 theta){
			if(!isFollower){
				direction[0]=sin(theta[0]);
				direction[1]=-sin(theta[1]);
				direction[2]=-cos(theta[0]);
			}
		}

		void updateOrientation(glm::vec2 dtheta){
			if(!isFollower){
				omega+=dtheta;
				for(int i=0;i<2;i++){
					if(omega[i]>MAX_OMEGA[i]){
						omega[i] = MAX_OMEGA[i];
					}
					if(omega[i]>-MIN_OMEGA[i] && omega[i]<MIN_OMEGA[i]){
						omega[i] = 0;
					}
					if(omega[i]<-MIN_OMEGA[i]){
						omega[i]+=OMEGA_FRICTION;
					}
					if(omega[i]>MIN_OMEGA[i]){
						omega[i]-=OMEGA_FRICTION;
					}
				}
				theta+=omega;
				direction[0]=sin(theta[0]);
				direction[1]=-sin(theta[1]);
				direction[2]=-cos(theta[0]);
			}
		}

		void setLocation(glm::vec3 pos){
			if(!isFollower){
				position=pos;
			}
			else{
				position=followingObject->position-followingObject->vel;
			}
		}

		void updateLocation(float speedOffset){
			if(!isFollower){
				speed+=speedOffset;
				position=position+direction*speed;
				glm::vec3 new_pos = position+direction;
				gluLookAt(position[0],position[1],position[2],new_pos[0],new_pos[1],new_pos[2],0.0,1.0,0.0);
			}
			else{
				glm::vec3 objectPos = followingObject->position;
				position=followingObject->position-glm::vec3(-1,-1,-1);
				gluLookAt(position[0],position[1],position[2],objectPos[0],objectPos[1],objectPos[2],0.0,1.0,0.0);
			}
		}
		void assignObject(Object* object){
			followingObject = object;
			isFollower=true;
		}
		void drawObject(int mode, Object* object, Terrain* _terrain, float scale, const char color[7]){
			glm::vec3 currentloc = object->position;
			glm::vec3 colors = getColor(color);
			float xpos = position[0];
			float ypos = position[1];
			float zpos = position[2];
			glTranslatef(-xpos+currentloc[0],-ypos+currentloc[1],-zpos+currentloc[2]);
			glScalef(scale,scale,scale);
			glColor3ub(colors[0],colors[1],colors[2]);
			glmDraw(object->model, mode);
			glScalef(1,1,1);
		}
};
