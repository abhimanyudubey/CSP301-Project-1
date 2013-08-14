
#include "include/GL/gl.h"
#include "include/glm1/glm.hpp"
#include "include/glm/glm.h"

#include <stdio.h>
#include <stdlib.h>

class Object{
	private:

	//The model for the object, loaded from the .obj file present.
	public:
	GLMmodel *model;

	glm::vec3 position;
	//Position vector of the object, to be updated by the physics engine.

	glm::vec3 vel;
	//Velocity vector of the object.

	glm::vec3 acc;
	//Acceleration vector of the object.

	GLfloat mass;
	//Mass of the object;

	bool isStationary;
	//Boolean value to specify if the object is stationary or not( assuming mass= infinity)

	GLfloat mu;
	/*Float to specify the coefficient of friction of the object with respect to the general formula of calculation:
	 * 						mu(s1,s2) = mu(s1)*mu(s2)
	 *
	 * Where s1 and s2 are the surfaces in question. This method is an average approximation and saves a lot of time
	 * when it comes to simulating the real world friction situation.
	 */

	GLfloat re;
	/*Float to specify the coefficient of restitution of the object with respect to the general formula of calculation:
	 * 						re(s1,s2) = re(s1)*re(s2)
	 *
	 * Where s1 and s2 are the surfaces in question. This method is an average approximation and saves a lot of time
	 * when it comes to simulating the real world collision situation.
	 */

	glm::vec3 outwardNormal;
	/* The outward normal vector for the object. This will handle collisions with the ground. For other collisions, i.e.
	 * with objects the normals will be calculated based on relative positioning of the items.
	 */

		Object(const char* filename, float m, bool stationary = false, float fric = 1.0f, float cre = 1.0f){
			model = glmReadOBJ(filename);
			position = glm::vec3(0.0);
			vel = glm::vec3(0.0);
			acc = glm::vec3(0.0);
			isStationary = stationary;
			mass = m;
			mu = fric;
			re = cre;
			outwardNormal = glm::vec3(0.0,-1.0,0.0);
			//For all objects the outward normal will be towards the negative y-axis.
		}
		//Constructor for Object class.

		~Object(){
			//delete model;

		}
		//Destructor

//		void loadModelFromObj(Object* object, std::string filename){
//			char* filenew = filename.c_str();
//			object->model = glmReadOBJ(filenew);
//
//		}
		//Function to load a model from a .obj file and initialize position,velocity and acceleration variables.


		glm::vec3 getPosition(){
			return position;
		}
		glm::vec3 getVelocity(){
			return vel;
		}
		glm::vec3 getAcceleration(){
			return acc;
		}
};

		glm::vec3 getColor(const char color [7]){
			glm::vec3 temp;
			for(int i=0;i<3;i++){
				char c1 = color[2*i];
				char c2 = color[2*i+1];

				switch(c2){
				case '1':
					temp[i]+=1;
					break;
				case '2':
					temp[i]+=2;
					break;
				case '3':
					temp[i]+=3;
					break;
				case '4':
					temp[i]+=4;
					break;
				case '5':
					temp[i]+=5;
					break;
				case '6':
					temp[i]+=6;
					break;
				case '7':
					temp[i]+=7;
					break;
				case '8':
					temp[i]+=8;
					break;
				case '9':
					temp[i]+=9;
					break;
				case 'A':
					temp[i]+=10;
					break;
				case 'B':
					temp[i]+=11;
					break;
				case 'C':
					temp[i]+=12;
					break;
				case 'D':
					temp[i]+=13;
					break;
				case 'E':
					temp[i]+=14;
					break;
				case 'F':
					temp[i]+=15;
					break;
				case '0':
					temp[i]+=0;
					break;
				}

				temp[i]*=16;

				switch(c1){
				case '1':
					temp[i]+=1;
					break;
				case '2':
					temp[i]+=2;
					break;
				case '3':
					temp[i]+=3;
					break;
				case '4':
					temp[i]+=4;
					break;
				case '5':
					temp[i]+=5;
					break;
				case '6':
					temp[i]+=6;
					break;
				case '7':
					temp[i]+=7;
					break;
				case '8':
					temp[i]+=8;
					break;
				case '9':
					temp[i]+=9;
					break;
				case 'A':
					temp[i]+=10;
					break;
				case 'B':
					temp[i]+=11;
					break;
				case 'C':
					temp[i]+=12;
					break;
				case 'D':
					temp[i]+=13;
					break;
				case 'E':
					temp[i]+=14;
					break;
				case 'F':
					temp[i]+=15;
					break;
				case '0':
					temp[i]+=0;
					break;
				}
			}

			int red = temp[0];
			int green = temp[1];
			int blue = temp[2];
			return glm::vec3(red,green,blue);
}
