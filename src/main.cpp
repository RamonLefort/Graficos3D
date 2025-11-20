/*  Base code by Alun Evans 2016 LaSalle (aevanss@salleurl.edu) modified by: Conrado Ruiz, Ferran Ruiz 2024*/

// student name: Ramón Lefort and Martí Polo

//include some standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

//include OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//include some custom code files
#include "glfunctions.h"	//include all OpenGL stuff
#include "Shader.h"			// class to compile shaders

#define M_PI 3.14159265358979323846

using namespace std;
using namespace glm;

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//1er Objeto
const char filename_earth[] = "assets/sphere.obj";
vector <tinyobj::shape_t> shapes_earth;

//2do Objeto
const char filename_moon[] = "assets/sphere.obj";
vector <tinyobj::shape_t> shapes_moon;

//10er Objeto
vector <tinyobj::shape_t> shapes_pokeball;
const char filename_pokeball[] = "assets/pokeball.obj";

//4to Objeto
vector <tinyobj::shape_t> shapes_plane;

//5er Objeto
vector <tinyobj::shape_t> shapes_tree;

//6er Objeto
vector <tinyobj::shape_t> shapes_taylor;

//7er Objeto
vector <tinyobj::shape_t> shapes_barbie;
const char filename_barbie[] = "assets/barbiebox.obj";

//8er Objeto
vector <tinyobj::shape_t> shapes_cars;
const char filename_cars[] = "assets/cars_1.obj";

//9er Objeto
vector <tinyobj::shape_t> shapes_goomba;
const char filename_goomba[] = "assets/goomba.obj";

//10er Objeto
vector <tinyobj::shape_t> shapes_droid;
const char filename_droid[] = "assets/starWarsDroid.obj";

//Texture 1
char path_earth[] = "textures/earth.bmp";
int width, height, numChannels;

//Texture 2
char path_moon[] = "textures/moon.bmp";

//Texture 5
char path_pokeball[] = "textures/pokeball.bmp";

//Texture 5
char path_tree[] = "textures/christmasTree.png";

//Texture 6
char path_taylor[] = "textures/taylorswift.jpg";

//Texture 7
char path_barbie[] = "textures/Barbiebox.png";

//Texture 8
char path_cars[] = "textures/cars.png";

//Texture 9
char path_goomba[] = "textures/goomba.png";

//Texture 10
char path_droid[] = "textures/starWarsDroid.jpeg";

//SkyBox
const char filename_sky[] = "assets/sphere.obj";
vector <tinyobj::shape_t> shapes_sky;

//Texture SkyBox
char path_sky[] = "textures/winter_night.jpg";
int width_sky, height_sky, numChannels_sky;

float color1 = 1.0, xx1 = 0.0, yy1 = 0.0, xx2 = 0.0, yy2 = 0.0, angle1 = 0.0, camera_x = 0.0, camera_y = 0.0, camera_z = 1.0, angle2 = 0.0, angle3 = 0.0, moon_x = 0.0, moon_z = 0.0, angle_droid = 0.0, droid_speed = 2.0, droid_amplitude = 3.0, lastTime = 0.0, goombaY = 0.0, lastTime2 = 0.0, lastTime3 = 0.0;
int change = 1, up_down = 0, object1 = 0, mix_color = 0, times_mixed = 0, view_type = 1, orbital = 1, mouseClick = 0;
vec3 cameraFront(0.0, -1.0, -2.0);
vec3 cameraPos(0.0, 1.0, 2.0);
vec3 cameraUp(0.0f, 1.0f, 0.0f);
vec3 cameraCenter(0.0, 0.0, 0.0);
vec3 cameraSide(0.0, 0.0, 0.0);
vec3 g_light_dir(1.0, 1.0, 0.0);
float lastX = 0.0, lastY = 0.0, yaww = -90.0, pitchh = 0;

//Goomba jump movement
bool Space2 = false, isMoving = false;
float moveDuration = 1.0, moveTime = 0.0, initialY = -3.0, maxOffsetY = 2.0, currentY = initialY, maxOffsetIncrement = 0.5, timeElapsed = 0.0, speed = 0.5, A = 0.5, B = 0.25;

//Car drifting 8's movement
vec3 carPosition = vec3(0.0, -1.0, 0.0);
float carRotation = 0.0, cycleDuration = 0.0, heightMax = 0.0, lastTime4 = 0.0;

vec3 droidPosition = vec3(-1.0, -1.0, 0.0);
//Taylor jump movement
vec3 objectPosition = vec3(-1.0, 0.0, 0.0);
float jumpHeight = 1.0, jumpDuration = 1.0, elapsedTime = 0.0, randomInterval = 0.0, timeSinceLastJump = 0.0;
bool isJumping = false;

//Barbie box movement
float targetX = 1.0, targetZ = 1.0, lastTime5 = 0.0f, lastTime6 = 0.0f;
bool hasJumped = false, jumpingProcess = false, jumping = false;
const float jump_height = 2.0, jump_duration = 2.0;
float jump_time = 0.0, angle_barbie = 0.0f;
vec3 barbiePosition = vec3(-3.0, -1.0, 0.0);

//Multitexture
GLuint texture_id_earth_normal;
GLuint texture_id_earth_spec;
GLuint texture_id_earth_night;
GLuint texture_id_earth_1k;

//global variables to help us do things
int g_ViewportWidth = 1012; int g_ViewportHeight = 1012; // Default window size, in pixels
double mouse_x, mouse_y;	//variables storing mouse position
const vec3 g_backgroundColor(0.2f, 0.2f, 0.2f); // background colour - a GLM 3-component vector

//Variables globales del SkyBox
GLuint g_simpleShader_sky = 0;// skybox shader identifier
GLuint g_Vao_sky = 0;// skybox vao
GLuint g_NumTriangles_sky = 0;// number of triangles of the skybox
GLuint texture_id_sky;// global texture id

GLuint g_simpleShader = 0;	//shader identifier

//1er Objeto
GLuint g_Vao_moon = 0;
GLuint g_NumTriangles_moon = 0;

//2do objeto
GLuint g_Vao_earth = 0;
GLuint g_NumTriangles_earth = 0;

//3er objeto
GLuint g_Vao_pokeball = 0;
GLuint g_NumTriangles_pokeball = 0;

//4to objeto
GLuint g_Vao_plane = 0;
GLuint g_NumTriangles_plane = 0;

//5er objeto
GLuint g_Vao_tree = 0;
GLuint g_NumTriangles_tree = 0;

//6er objeto
GLuint g_Vao_barbie = 0;
GLuint g_NumTriangles_barbie = 0;

//7er objeto
GLuint g_Vao_cars = 0;
GLuint g_NumTriangles_cars = 0;

//8er objeto
GLuint g_Vao_taylor = 0;
GLuint g_NumTriangles_taylor = 0;

//9er objeto
GLuint g_Vao_goomba = 0;
GLuint g_NumTriangles_goomba = 0;

//10er objeto
GLuint g_Vao_droid = 0;
GLuint g_NumTriangles_droid = 0;

//Texture 1
GLuint texture_id_moon;

//Texture 2
GLuint texture_id_earth;

//Texture 3
GLuint texture_id_pokeball;

//Texture 4
GLuint texture_id_plane;

//Texture 5
GLuint texture_id_tree;

//Texture 6
GLuint texture_id_taylor;

//Texture 7
GLuint texture_id_barbie;

//Texture 8
GLuint texture_id_cars;

//Texture 9
GLuint texture_id_goomba;

//Texture 10
GLuint texture_id_droid;

// ------------------------------------------------------------------------------------------
// This function randomly chooses a number from 1 to 5
// ------------------------------------------------------------------------------------------
void initializeRandomJump() {
	srand(time(NULL));
	randomInterval = 1.0f + (rand() % 5);
}

// ------------------------------------------------------------------------------------------
// This function automaticly makes Taylor object jump when a random time passes
// ------------------------------------------------------------------------------------------
void updateTaylorPosition() {
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime4;
	lastTime4 = currentTime;
	timeSinceLastJump += deltaTime;

	if (!isJumping && !hasJumped) {
		if (timeSinceLastJump >= randomInterval) {
			isJumping = true;
			elapsedTime = 0.0f;
			timeSinceLastJump = 0.0f;

			randomInterval = 1.0f + (rand() % 5);
		}
	}

	if (isJumping) {
		elapsedTime += deltaTime;

		float normalizedTime = elapsedTime / jumpDuration;
		if (normalizedTime <= 1.0f) {
			objectPosition.y = jumpHeight * (1.0f - (2.0f * normalizedTime - 1.0f) * (2.0f * normalizedTime - 1.0f));
		}
		else {
			objectPosition.y = 0.0f;
			isJumping = false;
		}
	}
}

// ------------------------------------------------------------------------------------------
// This function automaticly makes Car object drift in eight's and change his orientation
// ------------------------------------------------------------------------------------------
void updateCarPosition() {
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime2;
	lastTime2 = currentTime;

	timeElapsed += deltaTime * speed;

	carPosition.x = A * sin(timeElapsed);
	carPosition.z = B * sin(2 * timeElapsed);

	targetX = carPosition.x * std::sin(speed);
	targetZ = carPosition.z * std::sin(2 * speed);

	carRotation = std::atan2(-targetZ, -targetX) * 180.0f / M_PI;
}

// ------------------------------------------------------------------------------------------
// This function automaticly makes Taylor object jump when a random time passes
// ------------------------------------------------------------------------------------------
void updateTaylorMovement() {
	if (isMoving) {
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime3;
		lastTime3 = currentTime;
		moveTime += deltaTime;

		float t = moveTime / moveDuration;

		if (t >= 1.0f) {
			t = 1.0f;
			isMoving = false;
			maxOffsetY = 1.0f;
		}

		currentY = initialY + maxOffsetY * (1 - (2 * t - 1) * (2 * t - 1));
	}
}

// ------------------------------------------------------------------------------------------
// This function automaticly makes the Droid move onwards and backwards
// ------------------------------------------------------------------------------------------
void updateAngleDroid() {
	float currentTime2 = glfwGetTime();
	float deltaTime = currentTime2 - lastTime;
	lastTime = currentTime2;

	angle_droid = sin(currentTime2 * droid_speed) * droid_amplitude;
}

// ------------------------------------------------------------------------------------------
// This function automaticly makes the Droid move to the position of the Barbie box
// ------------------------------------------------------------------------------------------
void updateMovementDroid() {
	if (isJumping) {
		jumpingProcess = true;
	}else{
		if(jumpingProcess){
			jumpingProcess = false;
			hasJumped = true;
		}
	}
	if (hasJumped) {
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime5;
		lastTime5 = currentTime;
		float dir_x = -2.7 - droidPosition.x;
		float dir_y = -1.0 - droidPosition.y;
		float dir_z = 0.0 - droidPosition.z;

		float distance = std::sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);

		if (distance > 0.0f) {
			dir_x /= distance;
			dir_y /= distance;
			dir_z /= distance;
		}

		float step = 0.25f * deltaTime;
		if (distance > step) {
			droidPosition.x += dir_x * step;
			droidPosition.y += dir_y * step;
			droidPosition.z += dir_z * step;
		}
		else {
			droidPosition.x = -2.7;
			droidPosition.y = -1.0;
			droidPosition.z = 0.0;
			jumping = true;
		}
	}
}

// ------------------------------------------------------------------------------------------
// This function automaticly makes the Barbie Box jump when the Droid it's at his position
// ------------------------------------------------------------------------------------------
void updateBarbieBox() {
	if (jumping) {
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime6;
		lastTime6 = currentTime;
		jump_time += deltaTime;

		float t = jump_time / jump_duration;
		if (t <= 1.0f) {
			barbiePosition.y = 4.0f * jump_height * t * (1.0f - t);
		}
		else {
			jumping = false;
			barbiePosition.y = 0.0f;
			jump_time = 0.0f;
		}

		angle_barbie += 360.0f * deltaTime / jump_duration;
	}
}


// ------------------------------------------------------------------------------------------
// This function manually animate some objects of the project
// ------------------------------------------------------------------------------------------
void animaciones(){
	if (angle2 == 360) {
		angle2 = 0;
	}
	else {
		angle2 += 0.01;
	}

	float eje_z = 3.0;

	angle3 += 0.0005;
	if (angle3 != 0.0) {
		moon_x = eje_z * cos(angle3);
		moon_z = (eje_z * sin(angle3)) - 4.0f;
	}
	else {
		moon_x = -3.0;
		moon_z = -4.0;
	}
	if (angle3 == 360) {
		angle3 = 0;
	}

	updateAngleDroid();
	updateMovementDroid();
	updateTaylorMovement();
	updateCarPosition();
	updateTaylorPosition();
	updateBarbieBox();
}

// ------------------------------------------------------------------------------------------
// This function load all the textures to the shader
// ------------------------------------------------------------------------------------------
void drawObject(GLuint g_simpleShader, GLuint texture_id, int multitexture) {
	//find the sample uniform in the shader
	GLuint u_texture = glGetUniformLocation(g_simpleShader, "u_texture");
	// bind the sampler to the texture unit 0
	glUniform1i(u_texture, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	// multitexture if
	GLuint u_multitexture = glGetUniformLocation(g_simpleShader, "multitext");
	glUniform1i(u_multitexture, multitexture);
}

// ------------------------------------------------------------------------------------------
// This function load the textures of the objects
// ------------------------------------------------------------------------------------------
GLuint textureLoad(char* path) {
	GLuint textureid;
	stbi_set_flip_vertically_on_load(true); // Remove if texture is flipped.
	unsigned char* pixels = stbi_load(path, &width, &height, &numChannels, 0);
	glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_2D, textureid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, // target
		0, // level = 0 base, no mipmap
		GL_RGB, // how the data will be stored(Grayscale, RGB, RGBA)
		width, // width of the image
		height, // height of the image
		0, //border
		GL_RGB, // format of original data
		GL_UNSIGNED_BYTE,// type of data
		pixels);
	stbi_image_free(pixels);
	return textureid;
}

// ------------------------------------------------------------------------------------------
// This function loads the multitextures of the objects
// ------------------------------------------------------------------------------------------
GLuint multitextureLoad(char* path) {
	int widthNormal, heightNormal, numChannelsNormal;
	GLuint texture_id_multitexture;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixelsNormal = stbi_load(path, &widthNormal, &heightNormal, &numChannelsNormal, 0); // Load image data
	// Depending on the number of channels of the image, we need to tell OpenGL if it is grayscale, RGB or RGBA (RGB + transparent channel)
	GLenum channelsNormal = GL_RGB;
	switch (numChannelsNormal) {
	case 1:
		channelsNormal = GL_RED;
		break;
	case 3:
		channelsNormal = GL_RGB;
		break;
	case 4:
		channelsNormal = GL_RGBA;
		break;
	}
	glGenTextures(1, &texture_id_multitexture);
	glBindTexture(GL_TEXTURE_2D, texture_id_multitexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, channelsNormal, widthNormal, heightNormal, 0, channelsNormal, GL_UNSIGNED_BYTE,
		pixelsNormal);
	return texture_id_multitexture;
}

// ------------------------------------------------------------------------------------------
// This function binds the objects
// ------------------------------------------------------------------------------------------
void bindObject(const std::vector<float>& positions, const std::vector<float>& texcoords, const std::vector<float>& normals, const std::vector<unsigned int>& indices, GLuint shaderProgram, GLuint& numTriangles) {
	gl_createAndBindAttribute(&(positions[0]), sizeof(float) * positions.size(), shaderProgram, "a_vertex", 3);
	gl_createAndBindAttribute(&(texcoords[0]), sizeof(float) * texcoords.size(), shaderProgram, "a_uv", 2);
	gl_createAndBindAttribute(&(normals[0]), sizeof(float) * normals.size(), shaderProgram, "a_normal", 3);
	gl_createIndexBuffer(&(indices[0]), sizeof(unsigned int) * indices.size());
	// Unbind VAO
	gl_unbindVAO();
	// Store number of triangles
	numTriangles = indices.size() / 3;
}


// ------------------------------------------------------------------------------------------
// This function manually creates a square geometry (defined in the array vertices[])
// ------------------------------------------------------------------------------------------
void load()
{
	//**********************
	// CODE TO SET GEOMETRY
	//**********************

	bool ret = tinyobj::LoadObj(shapes_earth, filename_earth);

	if (ret)
		cout << "OBJ File: " << filename_earth << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << filename_earth << " cannot be found or is not a valid OBJ\n";

	ret = tinyobj::LoadObj(shapes_moon, filename_moon);

	if (ret)
		cout << "OBJ File: " << filename_moon << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << filename_moon << " cannot be found or is not a valid OBJ\n";

	ret = tinyobj::LoadObj(shapes_plane, "assets/plane.obj");

	if (ret)
		cout << "OBJ File: " << "assets/plane.obj" << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << "assets / plane.obj" << " cannot be found or is not a valid OBJ\n";

	ret = tinyobj::LoadObj(shapes_tree, "assets/christmasTree.obj");

	if (ret)
		cout << "OBJ File: " << "assets/christmasTree.obj" << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << "assets/christmasTree.obj" << " cannot be found or is not a valid OBJ\n";

	ret = tinyobj::LoadObj(shapes_taylor, "assets/taylorswift.obj");

	if (ret)
		cout << "OBJ File: " << "assets/taylorswift.obj" << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << "assets/taylorswift.obj" << " cannot be found or is not a valid OBJ\n";

	ret = tinyobj::LoadObj(shapes_barbie, filename_barbie);

	if (ret)
		cout << "OBJ File: " << filename_barbie << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << filename_barbie << " cannot be found or is not a valid OBJ\n";

	ret = tinyobj::LoadObj(shapes_cars, filename_cars);

	if (ret)
		cout << "OBJ File: " << filename_cars << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << filename_cars << " cannot be found or is not a valid OBJ\n";

	ret = tinyobj::LoadObj(shapes_goomba, filename_goomba);

	if (ret)
		cout << "OBJ File: " << filename_goomba << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << filename_goomba << " cannot be found or is not a valid OBJ\n";

	ret = tinyobj::LoadObj(shapes_droid, filename_droid);

	if (ret)
		cout << "OBJ File: " << filename_droid << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << filename_droid << " cannot be found or is not a valid OBJ\n";

	ret = tinyobj::LoadObj(shapes_pokeball, filename_pokeball);

	if (ret)
		cout << "OBJ File: " << filename_pokeball << " succesfuly loaded\n";
	else
		cout << "OBJ File: " << filename_pokeball << " cannot be found or is not a valid OBJ\n";

	bool ret_sky = tinyobj::LoadObj(shapes_sky, filename_sky);

 	//**********************
	// CODE TO LOAD EVERYTHING INTO MEMORY
	//**********************

	//load the shader
	Shader simpleShader("src/shader.vert", "src/shader.frag");
	g_simpleShader = simpleShader.program;

	// load the shader for the skybox
	Shader simpleShader_sky("src/shader_sky.vert", "src/shader_sky.frag");
	g_simpleShader_sky = simpleShader_sky.program;

	//Create the bind of the SkyBox
	g_Vao_sky = gl_createAndBindVAO();
	bindObject(shapes_sky[0].mesh.positions, shapes_sky[0].mesh.texcoords, shapes_sky[0].mesh.normals, shapes_sky[0].mesh.indices, g_simpleShader_sky, g_NumTriangles_sky);

	//1er objeto con un VAO
	g_Vao_moon = gl_createAndBindVAO();
	bindObject(shapes_moon[0].mesh.positions, shapes_moon[0].mesh.texcoords, shapes_moon[0].mesh.normals, shapes_moon[0].mesh.indices, g_simpleShader, g_NumTriangles_moon);

	//2do objeto con otro VAO
	g_Vao_earth = gl_createAndBindVAO();
	bindObject(shapes_earth[0].mesh.positions, shapes_earth[0].mesh.texcoords, shapes_earth[0].mesh.normals, shapes_earth[0].mesh.indices, g_simpleShader, g_NumTriangles_earth);
	
	//3er objeto con otro VAO
	g_Vao_pokeball = gl_createAndBindVAO();
	bindObject(shapes_pokeball[0].mesh.positions, shapes_pokeball[0].mesh.texcoords, shapes_pokeball[0].mesh.normals, shapes_pokeball[0].mesh.indices, g_simpleShader, g_NumTriangles_pokeball);

	//4to objeto con otro VAO
	g_Vao_plane = gl_createAndBindVAO();
	bindObject(shapes_plane[0].mesh.positions, shapes_plane[0].mesh.texcoords, shapes_plane[0].mesh.normals, shapes_plane[0].mesh.indices, g_simpleShader_sky, g_NumTriangles_plane);

	//5to objeto con otro VAO
	g_Vao_tree = gl_createAndBindVAO();
	bindObject(shapes_tree[0].mesh.positions, shapes_tree[0].mesh.texcoords, shapes_tree[0].mesh.normals, shapes_tree[0].mesh.indices, g_simpleShader, g_NumTriangles_tree);

	//6to objeto con otro VAO
	g_Vao_taylor = gl_createAndBindVAO();
	bindObject(shapes_taylor[0].mesh.positions, shapes_taylor[0].mesh.texcoords, shapes_taylor[0].mesh.normals, shapes_taylor[0].mesh.indices, g_simpleShader, g_NumTriangles_taylor);

	//7mo objeto con otro VAO
	g_Vao_barbie = gl_createAndBindVAO();
	bindObject(shapes_barbie[0].mesh.positions, shapes_barbie[0].mesh.texcoords, shapes_barbie[0].mesh.normals, shapes_barbie[0].mesh.indices, g_simpleShader, g_NumTriangles_barbie);

	//8vo objeto con otro VAO
	g_Vao_cars = gl_createAndBindVAO();
	bindObject(shapes_cars[0].mesh.positions, shapes_cars[0].mesh.texcoords, shapes_cars[0].mesh.normals, shapes_cars[0].mesh.indices, g_simpleShader, g_NumTriangles_cars);

	//9no objeto con otro VAO
	g_Vao_goomba = gl_createAndBindVAO();
	bindObject(shapes_goomba[0].mesh.positions, shapes_goomba[0].mesh.texcoords, shapes_goomba[0].mesh.normals, shapes_goomba[0].mesh.indices, g_simpleShader, g_NumTriangles_goomba);

	//10mo objeto con otro VAO
	g_Vao_droid = gl_createAndBindVAO();
	bindObject(shapes_droid[0].mesh.positions, shapes_droid[0].mesh.texcoords, shapes_droid[0].mesh.normals, shapes_droid[0].mesh.indices, g_simpleShader, g_NumTriangles_droid);

	//Texture 1 load
	texture_id_moon = textureLoad(path_moon);

	//Texture 2 load
	texture_id_earth = textureLoad(path_earth);

	//Texture 3 load
	texture_id_pokeball = textureLoad(path_pokeball);

	//Texture 4 load (Alpha blending texture)
	char path_plane[] = "textures/rings.png";
	stbi_set_flip_vertically_on_load(true); // Remove if texture is flipped.
	unsigned char* pixels_plane = stbi_load(path_plane, &width, &height, &numChannels, 0);
	glGenTextures(1, &texture_id_plane);
	glBindTexture(GL_TEXTURE_2D, texture_id_plane);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, // target
		0, // level = 0 base, no mipmap
		GL_RGBA, // how the data will be stored(Grayscale, RGB, RGBA)
		width, // width of the image
		height, // height of the image
		0, //border
		GL_RGBA, // format of original data
		GL_UNSIGNED_BYTE,// type of data
		pixels_plane);

	//Texture 5 load
	texture_id_tree = textureLoad(path_tree);

	//Texture 6 load
	texture_id_taylor = textureLoad(path_taylor);

	//Texture 7 load
	texture_id_barbie = textureLoad(path_barbie);

	//Texture 8 load
	texture_id_cars = textureLoad(path_cars);

	//Texture 9 load
	texture_id_goomba = textureLoad(path_goomba);

	//Texture 10 load
	texture_id_droid = textureLoad(path_droid);

	//SkyBox Texture load
	texture_id_sky = textureLoad(path_sky);

	//Multitexture - Earth Normal
	char* pathN = "textures/earthnormal.bmp"; // Path to normal image
	texture_id_earth_normal = multitextureLoad(pathN);

	//Multitexture 2 - Earth map
	char* path = "textures/earthmap1k.bmp"; // Path to normal image
	texture_id_earth_1k = multitextureLoad(path);

	//Multitexture 3 - Earth Specular
	char* pathSpec = "textures/earthspec.bmp"; // Path to specular image
	texture_id_earth_spec = multitextureLoad(pathSpec);

	//Multitexture 4 - Earth Nigth
	char* pathNight = "textures/earthnight.bmp"; // Path to night image
	texture_id_earth_night = multitextureLoad(pathNight);
}

// ------------------------------------------------------------------------------------------
// This function actually draws to screen and called non-stop, in a loop
// ------------------------------------------------------------------------------------------
void draw()
{
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	// activate shader
	glUseProgram(g_simpleShader);

	GLuint model_loc = glGetUniformLocation(g_simpleShader, "u_model");
	GLuint colorLoc = glGetUniformLocation(g_simpleShader, "u_color");
	GLuint projection_loc = glGetUniformLocation(g_simpleShader, "u_projection");
	
	//--------
	// Camera
	//--------

	//Camera
	mat4 projection_matrix = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // Near plane (distance from camera)
		100.0f // Far plane (distance from camera)
	);
	mat4 ortho_matrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	if (view_type) {
		glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	}
	else {
		glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(ortho_matrix));
	}
	
	//-------
	// Light
	//-------

	//Light
	GLuint light_loc = glGetUniformLocation(g_simpleShader, "u_light_dir");
	glUniform3f(light_loc, g_light_dir.x, g_light_dir.y, g_light_dir.z);
	GLuint cam_pos_loc = glGetUniformLocation(g_simpleShader, "u_cam_pos");

	//-----------------
	// Camera Position
	//-----------------

	// this is the camera position, eye/cameraPos
	glUniform3f(cam_pos_loc, cameraPos.x, cameraPos.y, cameraPos.z);
	GLuint ambient_loc = glGetUniformLocation(g_simpleShader, "u_ambient");
	glUniform3f(ambient_loc, 0.1, 0.1, 0.1); // grey shadows
	GLuint diffuse_loc = glGetUniformLocation(g_simpleShader, "u_diffuse");
	glUniform3f(diffuse_loc, 1.0, 1.0, 1.0); // white light
	GLuint specular_loc = glGetUniformLocation(g_simpleShader, "u_specular");
	glUniform3f(specular_loc, 1.0, 1.0, 1.0);
	GLuint shininess_loc = glGetUniformLocation(g_simpleShader, "u_shininess");
	glUniform1f(shininess_loc, 20.0);

	//--------
	// SkyBox
	//--------

	//Settings for drawing the SkyBox
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glUseProgram(g_simpleShader_sky);

	//Draw the SkyBox
	GLuint model_loc_sky = glGetUniformLocation(g_simpleShader_sky, "u_model");
	GLuint view_loc_sky = glGetUniformLocation(g_simpleShader_sky, "u_view");
	GLuint projection_loc_sky = glGetUniformLocation(g_simpleShader_sky, "u_projection");
	//set MVP
	mat4 model_matrix_sky = translate(mat4(1.0f), cameraPos); // where the camera is
	mat4 view_matrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection_matrix = perspective(90.0f, 1.0f, 0.1f, 50.0f);
	//send all values to shader
	glUniformMatrix4fv(model_loc_sky, 1, GL_FALSE, glm::value_ptr(model_matrix_sky));
	glUniformMatrix4fv(view_loc_sky, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(projection_loc_sky, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	//Bind the texture
	GLuint u_texture_sky = glGetUniformLocation(g_simpleShader_sky, "u_texture");
	glUniform1i(u_texture_sky, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_sky);

	gl_bindVAO(g_Vao_sky);
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_sky, GL_UNSIGNED_INT, 0);

	//--------------------
	// Drawing of objects
	//--------------------

	//Settings reset for the other objects
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glUseProgram(g_simpleShader);

	//-----------------
	// Rotation matrix
	//-----------------

	// Eje de rotación (en este caso, rotamos alrededor del eje Y)
	glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);

	// Crear la matriz de rotación
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle1, rotationAxis);

	GLuint view_loc = glGetUniformLocation(g_simpleShader, "u_view");
	view_matrix = glm::lookAt(
		cameraPos, // the position of your camera, in world space
		cameraPos + cameraFront, // where you want to look at, in world space
		cameraUp // probably glm::vec3(0,1,0)
	);
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view_matrix));

	//--------------
	// Multitexture
	//--------------

	//Multitexture
	GLuint u_texture_normal = glGetUniformLocation(g_simpleShader, "u_texture_normal");
	glUniform1i(u_texture_normal, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_normal);

	//Multitexture 2
	GLuint u_texture_spec = glGetUniformLocation(g_simpleShader, "u_texture_spec");
	glUniform1i(u_texture_spec, 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_spec);

	//Multitexture 3
	GLuint u_texture_night = glGetUniformLocation(g_simpleShader, "u_texture_night");
	glUniform1i(u_texture_night, 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_night);
	
	//--------------------
	// Drawing of objects
	//--------------------

	//Texture 1
	drawObject(g_simpleShader, texture_id_moon, 0);

	//bind the geometry
	gl_bindVAO(g_Vao_moon);

	//Posicion y color objeto 1
	mat4 model_moon = translate(mat4(1.0f), vec3(moon_x, 0.0, moon_z));
	model_moon = glm::scale(model_moon, vec3(0.5, 0.5, 0.5));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_moon));
	glUniform3f(colorLoc, color1, 0.0, 0.0);

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_moon, GL_UNSIGNED_INT, 0);

	//Texture 3
	drawObject(g_simpleShader, texture_id_pokeball, 0);

	//bind the geometry
	gl_bindVAO(g_Vao_pokeball);

	//Posicion y color objeto 3
	mat4 model_pokeball = translate(mat4(1.0f), vec3(-2.0, -1.0, -4.0));
	model_pokeball = glm::scale(model_pokeball, vec3(0.25, 0.25, 0.25));
	model_pokeball = glm::rotate(model_pokeball, angle2, vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_pokeball));
	glUniform3f(colorLoc, color1, 0.0, 0.0);

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_pokeball, GL_UNSIGNED_INT, 0);

	//Texture 5
	drawObject(g_simpleShader, texture_id_tree, 0);

	//bind the geometry
	gl_bindVAO(g_Vao_tree);

	//Posición y color objeto 5
	mat4 model_tree = translate(mat4(1.0f), vec3(-4.0, -2.0, -3.5));
	model_tree = glm::scale(model_tree, vec3(1.0, 1.0, 1.0));
	model_tree = glm::rotate(model_tree, angle2, vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_tree));

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_tree, GL_UNSIGNED_INT, 0);

	//Texture 6
	drawObject(g_simpleShader, texture_id_taylor, 0);

	//bind the geometry
	gl_bindVAO(g_Vao_taylor);

	//Posición y color objeto 6
	mat4 model_taylor = translate(mat4(1.0f), objectPosition);
	model_taylor = glm::scale(model_taylor, vec3(1.0, 1.0, 1.0));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_taylor));

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_taylor, GL_UNSIGNED_INT, 0);

	//Texture 7
	drawObject(g_simpleShader, texture_id_barbie, 0);

	//bind the geometry
	gl_bindVAO(g_Vao_barbie);

	//Posición y color objeto 7
	mat4 model_barbie = translate(mat4(1.0f), barbiePosition);
	model_barbie = glm::scale(model_barbie, vec3(0.25, 0.25, 0.25));
	model_barbie = glm::rotate(model_barbie, angle_barbie, vec3(0.0, 0.0, 1.0));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_barbie));

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_barbie, GL_UNSIGNED_INT, 0);

	//Texture 8
	drawObject(g_simpleShader, texture_id_cars, 0);

	//bind the geometry
	gl_bindVAO(g_Vao_cars);

	//Posición y color objeto 8
	mat4 model_cars = translate(mat4(1.0f), vec3(carPosition.x, -1.0, carPosition.z));
	model_cars = glm::scale(model_cars, vec3(0.1, 0.1, 0.1));
	model_cars = glm::rotate(model_cars, carRotation, vec3(0.0, -1.0, 0.0));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_cars));

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_cars, GL_UNSIGNED_INT, 0);

	//Texture 9
	drawObject(g_simpleShader, texture_id_goomba, 0);

	//bind the geometry
	gl_bindVAO(g_Vao_goomba);

	//Posición y color objeto 9
	mat4 model_goomba = translate(mat4(1.0f), vec3(-1.0, currentY, -3.0));
	model_goomba = glm::scale(model_goomba, vec3(0.25, 0.25, 0.25));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_goomba));

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_goomba, GL_UNSIGNED_INT, 0);

	//Texture 10
	drawObject(g_simpleShader, texture_id_droid, 0);

	//bind the geometry
	gl_bindVAO(g_Vao_droid);

	//Posición y color objeto 10
	mat4 model_droid = translate(mat4(1.0f), droidPosition);
	model_droid = glm::scale(model_droid, vec3(0.5, 0.5, 0.5));
	model_droid = glm::rotate(model_droid, angle_droid, vec3(1.0, 0.0, 0.0));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_droid));

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_droid, GL_UNSIGNED_INT, 0);

	//Texture 2
	drawObject(g_simpleShader, texture_id_earth, 1);

	//bind the geometry
	gl_bindVAO(g_Vao_earth);

	//Posición y color objeto 2
	mat4 model_earth = translate(mat4(1.0f), vec3(0.0, 0.0, -3.5));
	model_earth = glm::scale(model_earth, vec3(1.0, 1.0, 1.0));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_earth));

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_earth, GL_UNSIGNED_INT, 0);

	// activate shader
	glUseProgram(g_simpleShader_sky);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	
	//Textura 4
	gl_bindVAO(g_Vao_plane);
	u_texture_sky = glGetUniformLocation(g_simpleShader_sky, "u_texture");
	glUniform1i(u_texture_sky, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_plane);

	//Posicion y color objeto 4
	mat4 model_plane = translate(mat4(1.0f), vec3(0.0, 0.0, -3.5));
	model_plane = glm::scale(model_plane, vec3(3.5, 3.5, 3.5));
	model_plane = glm::rotate(model_plane, 90.0f, vec3(1.0, 0.0, 0.0));
	glUniformMatrix4fv(model_loc_sky, 1, GL_FALSE, glm::value_ptr(model_plane));

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_plane, GL_UNSIGNED_INT, 0);

	//desactivate shader
	glUseProgram(g_simpleShader);
	glEnable(GL_CULL_FACE);

	//Animations of all the objects
	animaciones();
}

// ------------------------------------------------------------------------------------------
// This function is called every time you press a screen
// ------------------------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //quit
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
	//reload
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
		cameraPos = cameraPos + normalize(cameraFront) * 0.1f;
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
		cameraPos = cameraPos - normalize(cameraFront) * 0.1f;
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		cameraSide = normalize(cross(cameraFront, cameraUp));
		cameraPos = cameraPos + cameraSide * 0.1f;
	}
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		cameraSide = normalize(cross(cameraFront, cameraUp));
		cameraPos = cameraPos - cameraSide * 0.1f;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (!isMoving) {
			isMoving = true;
			moveTime = 0.0f;
			maxOffsetY = 1.0f;
		}
		else {
			maxOffsetY = 2.0;
		}
	}
}

// ------------------------------------------------------------------------------------------
// This function is called every time you click the mouse
// ------------------------------------------------------------------------------------------
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		cout << "Left mouse down at" << mouse_x << ", " << mouse_y << endl;
	}
	if (mouseClick) {
		mouseClick = 0;
	}
	else {
		mouseClick = 1;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaww += xoffset;
	pitchh += yoffset;

	if (pitchh > 89.0f)
		pitchh = 89.0f;
	if (pitchh < -89.0f)
		pitchh = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaww)) * cos(glm::radians(pitchh));
	direction.y = sin(glm::radians(pitchh));
	direction.z = sin(glm::radians(yaww)) * cos(glm::radians(pitchh));
	if (mouseClick) {
		cameraFront = glm::normalize(direction);
	}
}

int main(void)
{
	//setup window and boring stuff, defined in glfunctions.cpp
	GLFWwindow* window;
	if (!glfwInit())return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 10);
	window = glfwCreateWindow(g_ViewportWidth, g_ViewportHeight, "Hello OpenGL!", NULL, NULL);
	if (!window) {glfwTerminate();	return -1;}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	//input callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	glClearColor(g_backgroundColor.x, g_backgroundColor.y, g_backgroundColor.z, 1.0f);

	GLint samples = 0;
	glGetIntegerv(GL_SAMPLES, &samples);
	std::cout << "Número de muestras activadas: " << samples << std::endl;

	GLint multisampleEnabled = 0;
	glGetIntegerv(GL_MULTISAMPLE, &multisampleEnabled);
	if (multisampleEnabled)
		std::cout << "Multisample esta habilitado." << std::endl;
	else
		std::cout << "Multisample NO está habilitado." << std::endl;

	//load all the resources
	load();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
		draw();

        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
        
        //mouse position must be tracked constantly (callbacks do not give accurate delta)
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
    }

    //terminate glfw and exit
    glfwTerminate();
    return 0;
}


