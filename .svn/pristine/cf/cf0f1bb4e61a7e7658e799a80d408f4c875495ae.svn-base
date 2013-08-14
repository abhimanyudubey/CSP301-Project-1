/*
 * TerrainRenderer.hpp
 *
 *  Created on: Aug 7, 2013
 *      Author: abhimanyu
 */

#ifndef TERRAINRENDERER_HPP_
#define TERRAINRENDERER_HPP_


#include "include/GL/gl.h"
#include "include/GL/glu.h"
#include "include/GL/glut.h"
#include "include/glm1/glm.hpp"
#include "include/glm/glm.h"

#include <stdio.h>
#include <stdlib.h>

#include "imageloader.h"

//Importing necessary libraries.

using namespace std;

class Terrain{
	private:
		int width;
		// Width of the terrain.
		int length;
		// Length of the terrain.
		float** heights;
		// Height array for each point in the terrain.
		glm::vec3** normals;
		// Normal vectors (3d, using GLM) in each point of the terrain.
		bool computedNormals;
		//To check whether the normals have been computed or not.
	public:
		// Constructor for initializing the terrain with widths and heights as inputs.
		Terrain(int inpw, int inph){
			//Initialize the width and height of the terrain.
			width = inpw;
			length = inph;
			//Initialize the height array (width*length)
			heights = new float*[length];
			for(int i=0;i< length; i++){
				heights[i]= new float[width];
			}
			//Initialize the normal vectors.
			normals = new glm::vec3*[length];
			for(int i=0;i<length;i++){
				normals[i]= new glm::vec3[width];
			}
			computedNormals = false;
		}
		~Terrain(){
			for(int i=0;i< length; i++){
				delete[] normals[i];
				delete[] heights[i];
			}
		}
		// Destructor for deleting all values of a particular terrain.

		int getWidth(){
			return width;
		}
		//Function to return width of a terrain object.

		int getLength(){
			return length;
		}
		//Function to return the length of a terrain object.

		float getAverageHeight(){
			float sum;
			for(int i=0;i<length;i++){
				float* row = heights[i];
				for(int j=0;j<width;j++){
					sum+=row[j];
				}
			}
			float average = sum/(length*width);
			return average;
		}
		//Function to return the average height of a terrain object.

		void setHeight(int xloc, int yloc, float height){
			heights[xloc][yloc] = height;
			computedNormals = false;
		}
		//Function to set the height of a particular location in the Terrain graph to a particular value.

		float getHeight(int xloc, int yloc){
			return heights[xloc][yloc];
		}
		//Function to return the height at a particular index.

		glm::vec3 getNormal(int xloc, int yloc){
			if (!computedNormals) {
				computeNormals();
			}
			return normals[xloc][yloc];
		}
		//Function to return the normal at a point.

		void computeNormals(){
			if (computedNormals) {
				return;
			}
			//If the normals are already computed, do not recompute.

			glm::vec3** normals2 = new glm::vec3*[length];
			for(int i = 0; i < length; i++) {
				normals2[i] = new glm::vec3[width];
			}
			//Initializing the default values of the normals.

			for(int z = 0; z < length; z++) {
				for(int x = 0; x < width; x++) {
					glm::vec3 sum(0.0f, 0.0f, 0.0f);
					glm::vec3 out;
					if (z > 0) {
						out = glm::vec3(0.0f, heights[z - 1][x] - heights[z][x], -1.0f);
					}
					glm::vec3 in;
					if (z < length - 1) {
						in = glm::vec3(0.0f, heights[z + 1][x] - heights[z][x], 1.0f);
					}
					glm::vec3 left;
					if (x > 0) {
						left = glm::vec3(-1.0f, heights[z][x - 1] - heights[z][x], 0.0f);
					}
					glm::vec3 right;
					if (x < width - 1) {
						right = glm::vec3(1.0f, heights[z][x + 1] - heights[z][x], 0.0f);
					}
					if (x > 0 && z > 0) {
						sum += glm::normalize(glm::cross(out,left));
					}
					if (x > 0 && z < length - 1) {
						sum += glm::normalize(glm::cross(left,in));
					}
					if (x < width - 1 && z < length - 1) {
						sum += glm::normalize(glm::cross(in,right));
					}
					if (x < width - 1 && z > 0) {
						sum += glm::normalize(glm::cross(right,out));
					}
					normals2[z][x] = sum;
					normals[z][x] = sum;
				}
				/* The normals are computed roughly as the sum of the cross products of several
				 * output vectors (in,out, left, right) based on the position of the pixels in the
				 * heightmap. The final normal vector is calculated as the sum of all these four vectors.
				 *
				 * This method of calculating the normals is taken from
				 * www.opengl.org/wiki/Calculating_a_Surface_Normal
				 *
				 */
			}
			const float FALLOUT_RATIO = 0.5f;
						for(int z = 0; z < length; z++) {
							for(int x = 0; x < width; x++) {
								glm::vec3 sum = normals2[z][x];
								if (x > 0) {
									sum += normals2[z][x - 1] * FALLOUT_RATIO;
								}
								if (x < width - 1) {
									sum += normals2[z][x + 1] * FALLOUT_RATIO;
								}
								if (z > 0) {
									sum += normals2[z - 1][x] * FALLOUT_RATIO;
								}
								if (z < length - 1) {
									sum += normals2[z + 1][x] * FALLOUT_RATIO;
								}

								if (glm::dot(sum,sum) == 0) {
									sum = glm::vec3(0.0f, 1.0f, 0.0f);
								}
								normals[z][x] = sum;
							}
						}
						for(int i = 0; i < length; i++) {
							delete[] normals2[i];
						}
						delete[] normals2;
						computedNormals = true;
		}
		//Function to compute the normal vectors in the heightmap for the terrain.

};
	Terrain* loadTerrainFromHeightmap(const char* filename, float height){
				Image* image = loadBMP(filename);
				Terrain* t = new Terrain(image->width, image->height);
				for(int y = 0; y < image->height; y++) {
					for(int x = 0; x < image->width; x++) {
						unsigned char color =
								(unsigned char)image->pixels[3 * (y * image->width + x)];
						float h = height * ((color / 255.0f) - 0.5f);
						t->setHeight(x, y, h);
					}
				}
				delete image;
				t->computeNormals();
				return t;
	}
		/* This function reads in a heightmap using the imread() function defined in OpenCV, and
		 * returns a Terrain object with heights and normals computed. This terrain object can be
		 * directly rendered (drawn) on the screen. This method returns a NULL pointer if the
		 * image cannot be read correctly.
		 * If a non-grayscale image is input, the function reduces the image to grayscale and then
		 * computes the terrain features.
		 */

	void renderTerrain(Terrain* _terrain){
		 	//GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
		   	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

		   	GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};
		   	GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
		   	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
		   	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		   	Image* texture = loadBMP("bitmaps/grass.bmp");
		   	Image* path = loadBMP("bitmaps/path.bmp");
		   	GLuint textureID;
		   	GLuint pathID;
		   	glGenTextures(1, &textureID);
		   	glBindTexture(GL_TEXTURE_2D, textureID);

		   	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, texture->width, texture->height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->pixels);

		   	glGenTextures(2, &pathID);
		   	//glBindTexture(GL_TEXTURE_2D, pathID);
		   	//glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, path->width, path->height, 0, GL_BGR, GL_UNSIGNED_BYTE, path->pixels);

		   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glEnable(GL_TEXTURE_2D);
		   	for(int z = 0; z < _terrain->getLength() - 1; z++) {
		   		//Makes OpenGL draw a triangle at every three consecutive vertices
		   		glBegin(GL_TRIANGLE_STRIP);
		   		for(int x = 0; x < _terrain->getWidth(); x++) {
		   			glm::vec3 normal = _terrain->getNormal(x, z);
		   			glNormal3f(normal[0], normal[1], normal[2]);
		   			//glColor3f(0.3f, 0.9f*_terrain->getHeight(x,z), 0.0f);
		   			float loch = _terrain->getHeight(x,z);
		   			if(loch < 2){
		   				glBindTexture(GL_TEXTURE_2D, pathID);
		   			}
		   			else{
		   				glBindTexture(GL_TEXTURE_2D, textureID);
		   			}
		   			glTexCoord2f(x,z);
		   			glVertex3f(x, _terrain->getHeight(x, z), z);
		   			normal = _terrain->getNormal(x, z + 1);
		   			glNormal3f(normal[0], normal[1], normal[2]);
		   			//glColor3f(0.3f, 0.9f*_terrain->getHeight(x,z+1), 0.0f);
		   			glTexCoord2f(x,z+1);
		   			glVertex3f(x, _terrain->getHeight(x, z + 1), z + 1);
		   		}
		   		glEnd();
		   	}
	}
	/*This function renders the target terrain in the existing OpenGL window using the
	 * GL_TRIANGLE_STRIP method.
	 *
	 */

#endif /* TERRAINRENDERER_H_ */
