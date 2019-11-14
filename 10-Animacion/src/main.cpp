#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;

GLFWwindow *window;

Shader shader;
//Shader de texturizado
Shader shaderTexture;
//Shader con iluminacion solo color
Shader shaderColorLighting;
//Shader con iluminacion y textura
Shader shaderTextureLighting;
// Descomentar
//Shader con materiales
Shader shaderMaterialLighting;
// Descomentar
//Shader con skybox
Shader shaderSkybox;
// Shader con multiples luces
Shader shaderMulLighting;

std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());

Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Sphere sphere3(20, 20);
///Esfera Negra
Sphere sphere4(20, 20);
Sphere sphereLamp(20, 20);
// Descomentar
Sphere skyboxSphere(20, 20);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Cylinder cylinder2(20, 20, 0.5, 0.5);
Cylinder cylinderMaterials(20, 20, 0.5, 0.5);
Cylinder cylinder12(20, 20, 0.5, 0.5);
Box boxMaterials;
Box box1;
Box box2;
Box box3;
Box boxCesped;
Box boxWall;
// Models complex instances
Model modelRock;
Model modelRailRoad;
Model modelAircraft;
Model modelCarro;
Model modelchasis;
Model modelheli;
Model modelMi_24;
Model tabla;
Model sofa;
Model modelCalabaza;
////
Model modelApple, modelBanana, modelCouch, modelLamp, modelMandarine, modelOrange, modelPM, modelTable, modelChimney;
GLuint textureID1, textureID2, textureID3, textureID4, textureID5, textureID6, textureID7, textureID8, textureID9, textureID17, textureID18, textureID20, textureID20P, textureIDM, textureIDV;
GLuint textureIDR;
GLuint skyboxTextureID;
///Brazo 1 (izquierdo)
float rot1 = 0.0, rot2 = 0.0, rot3 = 0.0, rot4 = 0.0;
///Brazo 2 (Derecho)
float rot1d = 0.0, rot2d = 0.0, rot3d = 0.0, rot4d = 0.0;
///Pierna 1 (Derecho)
float rot1pd = 0.0, rot2pd = 0.0, rot3pd = 0.0, rot4pd = 0.0;
///Pierna 2 (Izquierdo)
float rot1pi = 0.0, rot2pi = 0.0, rot3pi = 0.0, rot4pi = 0.0;

///Cabeza 
float cb = 0.0;
///Brazo 1 (Izquierdo)
float rot1_2 = 0.0, rot2_2 = 0.0, rot3_2 = 0.0, rot4_2 = 0.0;
///Brazo 2 (Derecho)
float rot1_2d = 0.0, rot2_2d = 0.0, rot3_2d = 0.0, rot4_2d = 0.0;
////////////Giro general
float rot0 = 0.0, dz = 0.0;
bool sentido = true;

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Textures/mp_bloodvalley/blood-valley_ft.tga",
		"../Textures/mp_bloodvalley/blood-valley_bk.tga",
		"../Textures/mp_bloodvalley/blood-valley_up.tga",
		"../Textures/mp_bloodvalley/blood-valley_dn.tga",
		"../Textures/mp_bloodvalley/blood-valley_rt.tga",
		"../Textures/mp_bloodvalley/blood-valley_lf.tga" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

//float rot0 = 0.0, dz = 0.0;

//float rot1 = 0.0, rot2 = 0.0, rot3 = 0.0, rot4 = 0.0;
//bool sentido = true;

double deltaTime;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
	int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
			nullptr);

	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderTexture.initialize("../Shaders/texturizado_res.vs",
		"../Shaders/texturizado_res.fs");
	shaderColorLighting.initialize("../Shaders/iluminacion_color_res.vs",
		"../Shaders/iluminacion_color_res.fs");
	shaderTextureLighting.initialize("../Shaders/iluminacion_texture_res.vs",
		"../Shaders/iluminacion_texture_res.fs");
	shaderMaterialLighting.initialize("../Shaders/iluminacion_material.vs",
		"../Shaders/iluminacion_material_res.fs");
	shaderSkybox.initialize("../Shaders/cubeTexture.vs",
		"../Shaders/cubeTexture.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_texture_res.vs",
		"../Shaders/multipleLights.fs");

	// Inicializar los buffers VAO, VBO, EBO
	sphere1.init();
	// Método setter que colocar el apuntador al shader
	sphere1.setShader(&shaderColorLighting);
	//Setter para poner el color de la geometria
	sphere1.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));

	// Inicializar los buffers VAO, VBO, EBO
	sphere2.init();
	// Método setter que colocar el apuntador al shader
	sphere2.setShader(&shaderColorLighting);
	//Setter para poner el color de la geometria
	sphere2.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	// Inicializar los buffers VAO, VBO, EBO
	sphereLamp.init();
	// Método setter que colocar el apuntador al shader
	sphereLamp.setShader(&shader);
	//Setter para poner el color de la geometria
	sphereLamp.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	cylinder1.init();
	cylinder1.setShader(&shaderColorLighting);
	cylinder1.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));

	cylinder2.init();
	cylinder2.setShader(&shaderMulLighting);

	cylinderMaterials.init();
	cylinderMaterials.setShader(&shaderMaterialLighting);
	cylinderMaterials.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));
	////Segundo cilindro
	cylinder12.init();
	cylinder12.setShader(&shader);
	cylinder12.setColor(glm::vec4(255.0, 255.0, 255.0, 1.0));
	/////////////////
	boxMaterials.init();
	boxMaterials.setShader(&shaderMaterialLighting);

	// Inicializacion de la esfera del skybox
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));

	box1.init();
	// Settea el shader a utilizar
	box1.setShader(&shaderMulLighting);
	box1.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));

	box2.init();
	box2.setShader(&shaderMulLighting);

	sphere3.init();
	sphere3.setShader(&shaderMulLighting);
	///Esfera Negra
	sphere4.init();
	sphere4.setShader(&shader);
	sphere4.setColor(glm::vec4(0.0, 0.0, 0.0, 0.0));
	///////
	box3.init();
	box3.setShader(&shaderMulLighting);

	boxCesped.init();
	boxCesped.setShader(&shaderMulLighting);

	boxWall.init();
	boxWall.setShader(&shaderMulLighting);

	modelRock.loadModel("../models/nubes/nube.obj");
	modelRock.setShader(&shaderMulLighting);

	modelRailRoad.loadModel("../models/railroad/railroad_track.obj");
	modelRailRoad.setShader(&shaderMulLighting);

	modelAircraft.loadModel("../models/Aircraft_obj/E 45 Aircraft_obj.obj");
	modelAircraft.setShader(&shaderMulLighting);

	modelCarro.loadModel("../models/Eclipse/2003eclipse.obj");
	modelCarro.setShader(&shaderMulLighting);

	modelchasis.loadModel("../models/Helicopter/Mi_24_chasis.obj");
	modelchasis.setShader(&shaderMulLighting);

	modelheli.loadModel("../models/Helicopter/Mi_24_heli.obj");
	modelheli.setShader(&shaderMulLighting);

	modelMi_24.loadModel("../models/Helicopter/Mi_24.obj");
	modelMi_24.setShader(&shaderMulLighting);
	///Modelo de la tabla
	tabla.loadModel("../models/Wood_Table/Wood_Table.obj");
	tabla.setShader(&shaderMulLighting);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	modelApple.loadModel("../models/Apple/manzana.obj");
	modelApple.setShader(&shaderMulLighting);
	modelBanana.loadModel("../models/Banana/banana.obj");
	modelBanana.setShader(&shaderMulLighting);
	modelCouch.loadModel("../models/Couch/Sofa.obj");
	modelCouch.setShader(&shaderMulLighting);
	modelLamp.loadModel("../models/Lamp/Lamp.obj");
	modelLamp.setShader(&shaderMulLighting);
	//modelMandarine.loadModel("../models/Mandarine/mandarina.obj");
	//modelMandarine.setShader(&shaderMulLighting);
	modelOrange.loadModel("../models/Orange/orange.obj");
	modelOrange.setShader(&shaderMulLighting);
	modelPM.loadModel("../models/PanMuerto/morido.obj");
	modelPM.setShader(&shaderMulLighting);
	modelTable.loadModel("../models/Table_2/Mesa.obj");
	modelTable.setShader(&shaderMulLighting);
	modelChimney.loadModel("../models/Chimney/Chimenea.obj");
	modelChimney.setShader(&shaderMulLighting);
	/**/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///Modelo Pupitre
	sofa.loadModel("../models/chairSchool/chairSchool.obj");
	sofa.setShader(&shaderMulLighting);
	///modelo Escritorio
	modelCalabaza.loadModel("../models/Desk/Desk.obj");
	modelCalabaza.setShader(&shaderMulLighting);
	camera->setPosition(glm::vec3(0.0, 3.0, 4.0));

	// Descomentar
	// Definimos el tamanio de la imagen
	int imageWidth, imageHeight;
	// Definiendo la textura a utilizar
	Texture texture1("../Textures/sponge.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	FIBITMAP *bitmap = texture1.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	unsigned char *data = texture1.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID1);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture1.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture2("../Textures/pavimento.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = texture2.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture2.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID2);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture2.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture3("../Textures/goku.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture3.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture3.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID3);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID3);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture3.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture4("../Textures/texturaLadrillos.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture4.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture4.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID4);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID4);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture4.freeImage(bitmap);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definiendo la textura a utilizar
	Texture texture5("../Textures/piedra.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture5.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture5.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID5);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID5);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture5.freeImage(bitmap);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definiendo la textura a utilizar
	Texture texture6("../Textures/cesped.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture6.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture6.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID6);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID6);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture6.freeImage(bitmap);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definiendo la textura a utilizar
	Texture texture7("../Textures/window2.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture7.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture7.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID7);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID7);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture7.freeImage(bitmap);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definiendo la textura a utilizar
	Texture texture8("../Textures/door2.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture8.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture8.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID8);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID8);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture8.freeImage(bitmap);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definiendo la textura a utilizar
	Texture texture9("../Textures/door2.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture9.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture9.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID9);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID9);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture9.freeImage(bitmap);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////Textura pantalones//////////////////////////////////////////////
	Texture texture18("../Textures/pantalon.jpg");
	//Carga el mapa de bits(Es el tipo de dato de la libreria)
	///Esto para voltear mi imagen
	bitmap = texture18.loadImage(true);
	//convertimos el mapa de bits en un arreglo unidimensional de tipo unseigned char
	data = texture18.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 5
	glGenTextures(1, &textureID18);
	//enlazar ese ID o textura a un tipo de textura de 2D
	glBindTexture(GL_TEXTURE_2D, textureID18);
	// set the texture wrapping parameters coloca los parametros del wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Aqui simplemente verifica si se pudo abrir la textura
	if (data) {
		//tranformar los datos de la imagen a memoria
		//Tipo de textura, formato interno OpenGL, ancho, alto, Mimaps
		//formato inter de la libreria, el tipo de dato y el papuntador a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		//generan los nuveles del mipmap(OpenGl es el encargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture18.freeImage(bitmap);


	////////////////////////////////////////////////////Textura Ojos//////////////////////////////////////////////
	Texture texture17("../Textures/ojobob.png");
	//Carga el mapa de bits(Es el tipo de dato de la libreria)
	///Esto para voltear mi imagen
	bitmap = texture17.loadImage(true);
	//convertimos el mapa de bits en un arreglo unidimensional de tipo unseigned char
	data = texture17.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 5
	glGenTextures(1, &textureID17);
	//enlazar ese ID o textura a un tipo de textura de 2D
	glBindTexture(GL_TEXTURE_2D, textureID17);
	// set the texture wrapping parameters coloca los parametros del wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Aqui simplemente verifica si se pudo abrir la textura
	if (data) {
		//tranformar los datos de la imagen a memoria
		//Tipo de textura, formato interno OpenGL, ancho, alto, Mimaps
		//formato inter de la libreria, el tipo de dato y el papuntador a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		//generan los nuveles del mipmap(OpenGl es el encargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture17.freeImage(bitmap);

	////////////////////////////////////////////////////Textura Vela//////////////////////////////////////////////
	Texture texture20("../Textures/marco.jpg");
	//Carga el mapa de bits(Es el tipo de dato de la libreria)
	///Esto para voltear mi imagen
	bitmap = texture20.loadImage(true);
	//convertimos el mapa de bits en un arreglo unidimensional de tipo unseigned char
	data = texture20.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 5
	glGenTextures(1, &textureID20);
	//enlazar ese ID o textura a un tipo de textura de 2D
	glBindTexture(GL_TEXTURE_2D, textureID20);
	// set the texture wrapping parameters coloca los parametros del wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Aqui simplemente verifica si se pudo abrir la textura
	if (data) {
		//tranformar los datos de la imagen a memoria
		//Tipo de textura, formato interno OpenGL, ancho, alto, Mimaps
		//formato inter de la libreria, el tipo de dato y el papuntador a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		//generan los nuveles del mipmap(OpenGl es el encargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture17.freeImage(bitmap);
	////////////////////////////////////////////////////Textura Papel Picado//////////////////////////////////////////////
	Texture texturePicado("../Textures/ladrillos_picado.png");
	//Carga el mapa de bits(Es el tipo de dato de la libreria)
	///Esto para voltear mi imagen
	bitmap = texturePicado.loadImage(true);
	//convertimos el mapa de bits en un arreglo unidimensional de tipo unseigned char
	data = texturePicado.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 20
	glGenTextures(1, &textureID20P);
	//enlazar ese ID o textura a un tipo de textura de 2D
	glBindTexture(GL_TEXTURE_2D, textureID20P);
	// set the texture wrapping parameters coloca los parametros del wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Aqui simplemente verifica si se pudo abrir la textura
	if (data) {
		//tranformar los datos de la imagen a memoria
		//Tipo de textura, formato interno OpenGL, ancho, alto, Mimaps
		//formato inter de la libreria, el tipo de dato y el papuntador a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		//generan los nuveles del mipmap(OpenGl es el encargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture17.freeImage(bitmap);
	////////////////////////////////////////////////////Textura Vela//////////////////////////////////////////////
	Texture texturePicadoM("../Textures/ladrillos_picado_morado.png");
	//Carga el mapa de bits(Es el tipo de dato de la libreria)
	///Esto para voltear mi imagen
	bitmap = texturePicadoM.loadImage(true);
	//convertimos el mapa de bits en un arreglo unidimensional de tipo unseigned char
	data = texturePicadoM.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 5
	glGenTextures(1, &textureIDM);
	//enlazar ese ID o textura a un tipo de textura de 2D
	glBindTexture(GL_TEXTURE_2D, textureIDM);
	// set the texture wrapping parameters coloca los parametros del wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Aqui simplemente verifica si se pudo abrir la textura
	if (data) {
		//tranformar los datos de la imagen a memoria
		//Tipo de textura, formato interno OpenGL, ancho, alto, Mimaps
		//formato inter de la libreria, el tipo de dato y el papuntador a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		//generan los nuveles del mipmap(OpenGl es el encargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture17.freeImage(bitmap);
	////////////////////////////////////////////////////Picado Verde//////////////////////////////////////////////
	Texture texturePicadoV("../Textures/ladrillos_picado_verde.png");
	//Carga el mapa de bits(Es el tipo de dato de la libreria)
	///Esto para voltear mi imagen
	bitmap = texturePicadoV.loadImage(true);
	//convertimos el mapa de bits en un arreglo unidimensional de tipo unseigned char
	data = texturePicadoV.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 5
	glGenTextures(1, &textureIDV);
	//enlazar ese ID o textura a un tipo de textura de 2D
	glBindTexture(GL_TEXTURE_2D, textureIDV);
	// set the texture wrapping parameters coloca los parametros del wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Aqui simplemente verifica si se pudo abrir la textura
	if (data) {
		//tranformar los datos de la imagen a memoria
		//Tipo de textura, formato interno OpenGL, ancho, alto, Mimaps
		//formato inter de la libreria, el tipo de dato y el papuntador a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		//generan los nuveles del mipmap(OpenGl es el encargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture17.freeImage(bitmap);

	////////////////////////////////////////////////////Textura Rosa//////////////////////////////////////////////
	Texture texturePicadoR("../Textures/ladrillos_picado_rosa.png");
	//Carga el mapa de bits(Es el tipo de dato de la libreria)
	///Esto para voltear mi imagen
	bitmap = texturePicadoR.loadImage(true);
	//convertimos el mapa de bits en un arreglo unidimensional de tipo unseigned char
	data = texturePicadoR.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 5
	glGenTextures(1, &textureIDR);
	//enlazar ese ID o textura a un tipo de textura de 2D
	glBindTexture(GL_TEXTURE_2D, textureIDR);
	// set the texture wrapping parameters coloca los parametros del wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Aqui simplemente verifica si se pudo abrir la textura
	if (data) {
		//tranformar los datos de la imagen a memoria
		//Tipo de textura, formato interno OpenGL, ancho, alto, Mimaps
		//formato inter de la libreria, el tipo de dato y el papuntador a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		//generan los nuveles del mipmap(OpenGl es el encargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture17.freeImage(bitmap);
	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		skyboxTexture = Texture(fileNames[i]);
		FIBITMAP *bitmap = skyboxTexture.loadImage(true);
		unsigned char *data = skyboxTexture.convertToData(bitmap, imageWidth,
			imageHeight);
		if (data) {
			glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0,
				GL_BGRA, GL_UNSIGNED_BYTE, data);
		}
		else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage(bitmap);
	}

}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Destrucción de los VAO, EBO, VBO
	sphere1.destroy();
	cylinder1.destroy();
	box1.destroy();

	shader.destroy();
}

void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
	int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}

	TimeManager::Instance().CalculateFrameRate(false);
	deltaTime = TimeManager::Instance().DeltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFrontCamera(true, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveFrontCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRightCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRightCamera(true, deltaTime);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, offsetY, 0.01);
	offsetX = 0;
	offsetY = 0;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//se agregan estas dos lineas para mover la camara, hacia enfrente
		camera->moveFrontCamera(true, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//se agregan estas dos lineas para mover la camara, hacia atras
		camera->moveFrontCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//se agregan estas dos lineas para mover la camara, hacia la derecha
		camera->moveRightCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//se agregan estas dos lineas para mover la camara, hacia la izquierda
		camera->moveRightCamera(true, deltaTime);
	sentido = true;
	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;

	///Figura 1
	glm::mat4 model = glm::mat4(1.0f);
	/// Figura 2
	glm::mat4 model2 = glm::mat4(1.0f);

	//model = glm::translate(model, glm::vec3(0.0, 1.5, 0.0));
	float offX = 0.0;
	float angle = 0.0;
	float ratio = 30.0;
	////NAve
	//glm::mat4 matrixModelAircraft = glm::mat4(1.0);
	//matrixModelAircraft = glm::translate(matrixModelAircraft, glm::vec3(8.0, 2.0, -10.0));
	//Carro
	glm::mat4 matrixModelCarro = glm::mat4(1.0);
	matrixModelCarro = glm::translate(matrixModelCarro, glm::vec3(-20.0, 1.0, -10.0));
	///Helicoptero
	glm::mat4 matrixModelMi_24 = glm::mat4(1.0);
	matrixModelMi_24 = glm::translate(matrixModelMi_24, glm::vec3(0.0, 5.0, 5.0));
	int state = 0;
	float offsetAircraftAdvance = 0.0;
	float offsetCarAdvance = 0.0;
	float offsetairfart = 0.0;
	float offsetCarfart = 0.0;
	float offsetNaveArriba = 0.0;
	float offsetNaveAbajo = 0.0;
	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.01f, 100.0f);
		glm::mat4 view = camera->getViewMatrix();

		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		model = glm::translate(model, glm::vec3(0, 0, dz));
		model = glm::rotate(model, rot0, glm::vec3(0, 1, 0));

		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) screenWidth / (float) screenHeight, 0.01f, 100.0f);
		//glm::mat4 view = camera->getViewMatrix();

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));
		// Settea la matriz de vista y projection al shader con solo textura
		shaderTexture.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con iluminacion solo color
		shaderColorLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderColorLighting.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con iluminacion con textura
		shaderTextureLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTextureLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con iluminacion con material
		shaderMaterialLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderMaterialLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
			glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		// Propiedades de la luz para objetos con color
		shaderColorLighting.setVectorFloat3("viewPos",
			glm::value_ptr(camera->getPosition()));
		shaderColorLighting.setVectorFloat3("light.ambient",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderColorLighting.setVectorFloat3("light.diffuse",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderColorLighting.setVectorFloat3("light.specular",
			glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

		// Propiedades de la luz para objetos con textura
		shaderTextureLighting.setVectorFloat3("viewPos",
			glm::value_ptr(camera->getPosition()));
		shaderTextureLighting.setVectorFloat3("light.ambient",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTextureLighting.setVectorFloat3("light.diffuse",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTextureLighting.setVectorFloat3("light.specular",
			glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

		// Propiedades de la luz para objetos con textura
		shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMaterialLighting.setVectorFloat3("light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMaterialLighting.setVectorFloat3("light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMaterialLighting.setVectorFloat3("light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));

		// Propiedades de la luz para objetos con multiples luces
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));
		// Esto es para la luz spotlight
		shaderMulLighting.setInt("spotLightCount", 1);
		shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(camera->getFront()));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.01, 0.01, 0.01)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.1);
		shaderMulLighting.setFloat("spotLights[0].quadratic", 0.001);

		// Esto es para la luces pointlights(Actuan como si fueran un foco)
		// Numero de luces a utiliozar de tipo pointLights  = 3
		shaderMulLighting.setInt("pointLightCount", 4);
		// Posicion de la luz indice [0]
		shaderMulLighting.setVectorFloat3("pointLights[0].position", glm::value_ptr((glm::vec3(-5.1, 4.5, -3.5))));
		// Utiliza lo mismo para la luz Roja
		shaderMulLighting.setVectorFloat3("pointLights[0].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[0].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[0].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[0].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[0].quadratic", 0.004);

		// Utiliza lo mismo para la luz Roja
		shaderMulLighting.setVectorFloat3("pointLights[1].position", glm::value_ptr((glm::vec3(9.1, 1.1, 10.1))));
		shaderMulLighting.setVectorFloat3("pointLights[1].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[1].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.00, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[1].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
		shaderMulLighting.setFloat("pointLights[1].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[1].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[1].quadratic", 0.004);

		// Utiliza lo mismo para la luz Azul
		shaderMulLighting.setVectorFloat3("pointLights[2].position", glm::value_ptr((glm::vec3(2.1, 1.1, 10.1))));
		shaderMulLighting.setVectorFloat3("pointLights[2].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[2].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[2].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
		shaderMulLighting.setFloat("pointLights[2].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[2].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[2].quadratic", 0.004);
		////////////////////////////////////////////////////Amarillo///////////////////////////////////////////////////////////////////////
		shaderMulLighting.setVectorFloat3("pointLights[3].position", glm::value_ptr((glm::vec3(9.1, 1.1, 1.1))));
		shaderMulLighting.setVectorFloat3("pointLights[3].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[3].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[3].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[3].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[3].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[3].quadratic", 0.004);

		////////////////////////////////////////////////////Amarillo 2///////////////////////////////////////////////////////////////////////
		shaderMulLighting.setVectorFloat3("pointLights[4].position", glm::value_ptr((glm::vec3(2.1, 1.1, 6.1))));
		shaderMulLighting.setVectorFloat3("pointLights[4].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[4].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[4].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[4].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[4].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[4].quadratic", 0.004);

		//Esto es oara colocar las esferas de las luces
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(-5.1, 4.5, -3.5));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(-5.1, 4.8, -5.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		////////////////////////////////////////////////////////////////////////////Luces dentro de la casa//////////////////////////////////
		///Amarillo
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(9.0, 2.0, 1.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		///Amarillo 2
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(2.0, 2.0, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		///Amarillo 3
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(2.0, 2.0, 10.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		///Amarillo 4
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(9.0, 2.0, 10.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		////////////////////////////////////////////////////////////Luces dentro de la casa/////////////////////////////////////////////////////
		glm::mat4 lightModelmatrix = glm::rotate(glm::mat4(1.0f), angle,
			glm::vec3(-14.9, 4.8, 0.0f));
		lightModelmatrix = glm::translate(lightModelmatrix,
			glm::vec3(0.0f, 0.0f, -ratio));
		// Posicion luz para objetos con color
		shaderColorLighting.setVectorFloat3("light.position",
			glm::value_ptr(
				glm::vec4(
					lightModelmatrix
					* glm::vec4(0.0, 0.0, 0.0, 1.0))));

		// Posicion luz para objetos con textura
		shaderTextureLighting.setVectorFloat3("light.position",
			glm::value_ptr(
				glm::vec4(
					lightModelmatrix
					* glm::vec4(0.0, 0.0, 0.0, 1.0))));

		// Posicion luz para objetos con materiales
		shaderMaterialLighting.setVectorFloat3("light.position",
			glm::value_ptr(
				glm::vec4(
					lightModelmatrix
					* glm::vec4(0.0, 0.0, 0.0, 1.0))));
		sphereLamp.setScale(glm::vec3(1, 1, 1));
		sphereLamp.setPosition(glm::vec3(0, 0, 0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
		sphereLamp.render(lightModelmatrix);

		model = glm::translate(model, glm::vec3(0, 0, dz));
		model = glm::rotate(model, rot0, glm::vec3(0, 1, 0));
		//box1.enableWireMode();
		/*
		// Usamos la textura ID 1
		glBindTexture(GL_TEXTURE_2D, textureID1);
		box1.render(glm::scale(model, glm::vec3(1.0, 1.0, 0.1)));
		// No utilizar ninguna textura
		glBindTexture(GL_TEXTURE_2D, 0);
		// Articulacion 1
		glm::mat4 j1 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		j1 = glm::rotate(j1, rot1, glm::vec3(0, 0, 1));
		j1 = glm::rotate(j1, rot2, glm::vec3(0, 1, 0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j1, glm::vec3(0.1, 0.1, 0.1)));
		// Hueso 1
		glm::mat4 l1 = glm::translate(j1, glm::vec3(0.25f, 0.0, 0.0));
		l1 = glm::rotate(l1, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l1, glm::vec3(0.1, 0.5, 0.1)));
		// Articulacion 2
		glm::mat4 j2 = glm::translate(j1, glm::vec3(0.5, 0.0f, 0.0f));
		j2 = glm::rotate(j2, rot3, glm::vec3(0.0, 0.0, 1.0));
		j2 = glm::rotate(j2, rot4, glm::vec3(1.0, 0.0, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j2, glm::vec3(0.1, 0.1, 0.1)));
		// Hueso 2
		glm::mat4 l2 = glm::translate(j2, glm::vec3(0.25, 0.0, 0.0));
		l2 = glm::rotate(l2, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l2, glm::vec3(0.1, 0.5, 0.1)));
		// Ojo
		glm::mat4 ojo = glm::translate(model, glm::vec3(0.25, 0.25, 0.05));
		//sphere1.enableWireMode();
		sphere1.render(glm::scale(ojo, glm::vec3(0.2, 0.2, 0.1)));
		glm::mat4 ojo2 = glm::translate(model, glm::vec3(-0.25, 0.25, 0.05));
		//sphere2.enableWireMode();
		sphere2.render(glm::scale(ojo2, glm::vec3(0.2, 0.2, 0.1)));
		glm::mat4 modelAgua = glm::mat4(1.0);
		modelAgua = glm::translate(modelAgua, glm::vec3(5.0, 0.01, 5.0));
		modelAgua = glm::scale(modelAgua, glm::vec3(5.0, 0.01, 5.0));
		// Se activa la textura del agua
		glBindTexture(GL_TEXTURE_2D, textureID2);
		// Le cambiamos el shader con multiples luces NO OLVIDAR
		shaderMulLighting.setFloat("offsetX", offX);
		box2.render(modelAgua);
		glBindTexture(GL_TEXTURE_2D, 0);
		shaderMulLighting.setFloat("offsetX", 0);
		glm::mat4 modelCesped = glm::mat4(1.0);
		modelCesped = glm::translate(modelCesped, glm::vec3(0.0, 0.0, 0.0));
		modelCesped = glm::scale(modelCesped, glm::vec3(40.0, 0.001, 40.0));
		// Se activa la textura del agua
		glBindTexture(GL_TEXTURE_2D, textureID5);
		boxCesped.render(modelCesped);
		glBindTexture(GL_TEXTURE_2D, 0);
		glm::mat4 modelSphere = glm::mat4(1.0);
		modelSphere = glm::translate(modelSphere, glm::vec3(10.0, 0.5, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID3);
		sphere3.render(modelSphere);
		glBindTexture(GL_TEXTURE_2D, 0);
		glm::mat4 modelCylinder = glm::mat4(1.0);
		modelCylinder = glm::translate(modelCylinder,
				glm::vec3(-3.0, 0.5, 0.0));
		// Envolvente desde el indice 0, el tamanio es 20 * 20 * 6
		// Se usa la textura 1 ( Bon sponja)
		glBindTexture(GL_TEXTURE_2D, textureID1);
		cylinder2.render(0, cylinder2.getSlices() * cylinder2.getStacks() * 6,
				modelCylinder);
		// Tapa Superior desde el indice : 20 * 20 * 6, el tamanio de indices es 20 * 3
		// Se usa la textura 2 ( Agua )
		glBindTexture(GL_TEXTURE_2D, textureID2);
		cylinder2.render(cylinder2.getSlices() * cylinder2.getStacks() * 6,
				cylinder2.getSlices() * 3, modelCylinder);
		// Tapa inferior desde el indice : 20 * 20 * 6 + 20 * 3, el tamanio de indices es 20 * 3
		// Se usa la textura 3 ( Goku )
		glBindTexture(GL_TEXTURE_2D, textureID3);
		cylinder2.render(
				cylinder2.getSlices() * cylinder2.getStacks() * 6
						+ cylinder2.getSlices() * 3, cylinder2.getSlices() * 3,
				modelCylinder);
		glBindTexture(GL_TEXTURE_2D, 0);
		// Render del cubo con textura de ladrillos y con repeticion en x
		glm::mat4 cubeTextureModel = glm::mat4(1.0);
		cubeTextureModel = glm::translate(cubeTextureModel,
				glm::vec3(-5.0, 0.5, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderMulLighting.setVectorFloat2("scaleUV",
				glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(cubeTextureModel);
		shaderMulLighting.setVectorFloat2("scaleUV",
				glm::value_ptr(glm::vec2(0.0, 0.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		*/

		//Models complex render
		glm::mat4 matrixModelRock = glm::mat4(1.0);
		matrixModelRock = glm::translate(matrixModelRock, glm::vec3(-8.0, 5.0, 6.0));
		modelRock.render(glm::scale(matrixModelRock, glm::vec3(0.3, 0.3, 0.3)));
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 matrixModelChimney = glm::mat4(1.0);
		matrixModelChimney = glm::translate(matrixModelChimney, glm::vec3(6.0, 1.0, 10.5));
		modelChimney.render(glm::scale(matrixModelChimney, glm::vec3(0.3, 0.3, 0.3)));

		///////////Modelo Tabla
		//glm::mat4 matrixModelTabla = glm::mat4(1.0);
		//matrixModelTabla = glm::translate(matrixModelTabla, glm::vec3(-8.0, 6.0, 6.0));
		//tabla.render(matrixModelTabla);
		///Modelo Pupitre
		glm::mat4 matrixModelpupitre = glm::mat4(1.0);
		matrixModelpupitre = glm::translate(matrixModelpupitre, glm::vec3(9.0, 1.0, 4.0));
		sofa.render(glm::scale(matrixModelpupitre, glm::vec3(0.2, 0.2, 0.2)));
		//// Modelo Sofa
		glm::mat4 matrixModelCouch = glm::mat4(1.0);
		matrixModelCouch = glm::translate(matrixModelCouch, glm::vec3(8.0, 1.0, 7.0));
		modelCouch.render(glm::scale(matrixModelCouch, glm::vec3(0.6, 0.6, 0.6)));
		////Modelo Lampara
		glm::mat4 matrixModelLamp = glm::mat4(1.0);
		matrixModelLamp = glm::translate(matrixModelLamp, glm::vec3(9.0, 1.0, 1.0));
		modelLamp.render(glm::scale(matrixModelLamp, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Lampara 2
		glm::mat4 matrixModelLamp2 = glm::mat4(1.0);
		matrixModelLamp2 = glm::translate(matrixModelLamp2, glm::vec3(2.0, 1.0, 6.0));
		modelLamp.render(glm::scale(matrixModelLamp2, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Lampara 3
		glm::mat4 matrixModelLamp3 = glm::mat4(1.0);
		matrixModelLamp3 = glm::translate(matrixModelLamp3, glm::vec3(2.0, 1.0, 10.0));
		modelLamp.render(glm::scale(matrixModelLamp3, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Lampara 4
		glm::mat4 matrixModelLamp4 = glm::mat4(1.0);
		matrixModelLamp4 = glm::translate(matrixModelLamp4, glm::vec3(9.0, 1.0, 10.0));
		modelLamp.render(glm::scale(matrixModelLamp4, glm::vec3(0.2, 0.2, 0.2)));
		///Escritorio
		glm::mat4 matrixModelEscritorio = glm::mat4(1.0);
		matrixModelEscritorio = glm::translate(matrixModelEscritorio, glm::vec3(3.0, 1.5, 2.0));
		modelCalabaza.render(glm::scale(matrixModelEscritorio, glm::vec3(1.6, 1.6, 1.6)));
		//////////////////////////////////////////////////////////////////////////////////////////////
		//// Modelo Sofa
		glm::mat4 matrixModelCouch2 = glm::mat4(1.0);
		matrixModelCouch2 = glm::translate(matrixModelCouch2, glm::vec3(6.0, 3.0, 10.0));
		modelCouch.render(glm::scale(matrixModelCouch2, glm::vec3(0.6, 0.6, 0.6)));
		////Modelo Lampara 5
		glm::mat4 matrixModelLamp5 = glm::mat4(1.0);
		matrixModelLamp5 = glm::translate(matrixModelLamp5, glm::vec3(9.0, 3.0, 10.0));
		modelLamp.render(glm::scale(matrixModelLamp5, glm::vec3(0.2, 0.2, 0.2)));
		/*																			Decoracion												*/
		///////////////////////////////////////////////////////////////////////////////Panes///////////////////////////////////////////////////////////////////////////77
		////Modelo Pan Muerto	
		glm::mat4 matrixModelPM2 = glm::mat4(1.0);
		matrixModelPM2 = glm::translate(matrixModelPM2, glm::vec3(2.0, 3.5, 2.7));
		modelPM.render(glm::scale(matrixModelPM2, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 2
		glm::mat4 matrixModelPM = glm::mat4(1.0);
		matrixModelPM = glm::translate(matrixModelPM, glm::vec3(2.5, 3.5, 2.7));
		modelPM.render(glm::scale(matrixModelPM, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 3
		glm::mat4 matrixModelPM3 = glm::mat4(1.0);
		matrixModelPM3 = glm::translate(matrixModelPM3, glm::vec3(3.0, 3.5, 2.7));
		modelPM.render(glm::scale(matrixModelPM3, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 4
		glm::mat4 matrixModelPM4 = glm::mat4(1.0);
		matrixModelPM4 = glm::translate(matrixModelPM4, glm::vec3(3.5, 3.5, 2.7));
		modelPM.render(glm::scale(matrixModelPM4, glm::vec3(0.2, 0.2, 0.2)));
		///
				////Modelo Pan Muerto 21
		glm::mat4 matrixModelPM21 = glm::mat4(1.0);
		matrixModelPM21 = glm::translate(matrixModelPM21, glm::vec3(2.3, 3.5, 3.3));
		modelPM.render(glm::scale(matrixModelPM21, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 31
		glm::mat4 matrixModelPM31 = glm::mat4(1.0);
		matrixModelPM31 = glm::translate(matrixModelPM31, glm::vec3(2.8, 3.5, 3.3));
		modelPM.render(glm::scale(matrixModelPM31, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 41
		glm::mat4 matrixModelPM41 = glm::mat4(1.0);
		matrixModelPM41 = glm::translate(matrixModelPM41, glm::vec3(3.3, 3.5, 3.3));
		modelPM.render(glm::scale(matrixModelPM41, glm::vec3(0.2, 0.2, 0.2)));
		///
				////Modelo Pan Muerto 22
		glm::mat4 matrixModelPM22 = glm::mat4(1.0);
		matrixModelPM22 = glm::translate(matrixModelPM22, glm::vec3(2.5, 3.5, 3.9));
		modelPM.render(glm::scale(matrixModelPM22, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 32
		glm::mat4 matrixModelPM32 = glm::mat4(1.0);
		matrixModelPM32 = glm::translate(matrixModelPM32, glm::vec3(3.0, 3.5, 3.9));
		modelPM.render(glm::scale(matrixModelPM32, glm::vec3(0.2, 0.2, 0.2)));
		///
				////Modelo Pan Muerto 23
		glm::mat4 matrixModelPM23 = glm::mat4(1.0);
		matrixModelPM23 = glm::translate(matrixModelPM23, glm::vec3(2.8, 3.5, 4.5));
		modelPM.render(glm::scale(matrixModelPM23, glm::vec3(0.2, 0.2, 0.2)));

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
		////Modelo apple
		glm::mat4 matrixModelApple = glm::mat4(1.0);
		matrixModelApple = glm::translate(matrixModelApple, glm::vec3(4.6, 3.63, 2.7));
		modelApple.render(glm::scale(matrixModelApple, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 2
		glm::mat4 matrixModelApple1 = glm::mat4(1.0);
		matrixModelApple1 = glm::translate(matrixModelApple1, glm::vec3(5.0, 3.63, 2.7));
		modelApple.render(glm::scale(matrixModelApple1, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 3
		glm::mat4 matrixModelApple3 = glm::mat4(1.0);
		matrixModelApple3 = glm::translate(matrixModelApple3, glm::vec3(5.4, 3.63, 2.7));
		modelApple.render(glm::scale(matrixModelApple3, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 4
		glm::mat4 matrixModelApple4 = glm::mat4(1.0);
		matrixModelApple4 = glm::translate(matrixModelApple4, glm::vec3(5.8, 3.63, 2.7));
		modelApple.render(glm::scale(matrixModelApple4, glm::vec3(0.13, 0.13, 0.13)));
		///
				////Modelo apple
		glm::mat4 matrixModelApple11 = glm::mat4(1.0);
		matrixModelApple11 = glm::translate(matrixModelApple11, glm::vec3(4.8, 3.63, 3.1));
		modelApple.render(glm::scale(matrixModelApple11, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 21
		glm::mat4 matrixModelApple21 = glm::mat4(1.0);
		matrixModelApple21 = glm::translate(matrixModelApple21, glm::vec3(5.2, 3.63, 3.1));
		modelApple.render(glm::scale(matrixModelApple21, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 3
		glm::mat4 matrixModelApple31 = glm::mat4(1.0);
		matrixModelApple31 = glm::translate(matrixModelApple31, glm::vec3(5.6, 3.63, 3.1));
		modelApple.render(glm::scale(matrixModelApple31, glm::vec3(0.13, 0.13, 0.13)));
		///
				////Modelo apple
		glm::mat4 matrixModelApple12 = glm::mat4(1.0);
		matrixModelApple12 = glm::translate(matrixModelApple12, glm::vec3(5.0, 3.63, 3.4));
		modelApple.render(glm::scale(matrixModelApple12, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 21
		glm::mat4 matrixModelApple22 = glm::mat4(1.0);
		matrixModelApple22 = glm::translate(matrixModelApple22, glm::vec3(5.4, 3.63, 3.4));
		modelApple.render(glm::scale(matrixModelApple22, glm::vec3(0.13, 0.13, 0.13)));
		///
				////Modelo apple
		glm::mat4 matrixModelApple13 = glm::mat4(1.0);
		matrixModelApple13 = glm::translate(matrixModelApple13, glm::vec3(5.2, 3.63, 3.7));
		modelApple.render(glm::scale(matrixModelApple13, glm::vec3(0.13, 0.13, 0.13)));
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
		////Modelo Naranja
		glm::mat4 matrixModelOrange = glm::mat4(1.0);
		matrixModelOrange = glm::translate(matrixModelOrange, glm::vec3(6.5, 3.6, 2.7));
		modelOrange.render(glm::scale(matrixModelOrange, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 2
		glm::mat4 matrixModelOrange2 = glm::mat4(1.0);
		matrixModelOrange2 = glm::translate(matrixModelOrange2, glm::vec3(6.8, 3.6, 2.7));
		modelOrange.render(glm::scale(matrixModelOrange2, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 3
		glm::mat4 matrixModelOrange3 = glm::mat4(1.0);
		matrixModelOrange3 = glm::translate(matrixModelOrange3, glm::vec3(7.1, 3.6, 2.7));
		modelOrange.render(glm::scale(matrixModelOrange3, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 4
		glm::mat4 matrixModelOrange4 = glm::mat4(1.0);
		matrixModelOrange4 = glm::translate(matrixModelOrange4, glm::vec3(7.4, 3.6, 2.7));
		modelOrange.render(glm::scale(matrixModelOrange4, glm::vec3(0.1, 0.1, 0.1)));
		///
				////Modelo Naranja
		glm::mat4 matrixModelOrange1 = glm::mat4(1.0);
		matrixModelOrange1 = glm::translate(matrixModelOrange1, glm::vec3(6.65, 3.6, 3.1));
		modelOrange.render(glm::scale(matrixModelOrange1, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 2
		glm::mat4 matrixModelOrange21 = glm::mat4(1.0);
		matrixModelOrange21 = glm::translate(matrixModelOrange21, glm::vec3(6.95, 3.6, 3.1));
		modelOrange.render(glm::scale(matrixModelOrange21, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 3
		glm::mat4 matrixModelOrange31 = glm::mat4(1.0);
		matrixModelOrange31 = glm::translate(matrixModelOrange31, glm::vec3(7.25, 3.6, 3.1));
		modelOrange.render(glm::scale(matrixModelOrange31, glm::vec3(0.1, 0.1, 0.1)));
		///
				////Modelo Naranja
		glm::mat4 matrixModelOrange12 = glm::mat4(1.0);
		matrixModelOrange12 = glm::translate(matrixModelOrange12, glm::vec3(6.8, 3.6, 3.5));
		modelOrange.render(glm::scale(matrixModelOrange12, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 2
		glm::mat4 matrixModelOrange22 = glm::mat4(1.0);
		matrixModelOrange22 = glm::translate(matrixModelOrange22, glm::vec3(7.1, 3.6, 3.5));
		modelOrange.render(glm::scale(matrixModelOrange22, glm::vec3(0.1, 0.1, 0.1)));
		///
				////Modelo Naranja
		glm::mat4 matrixModelOrange13 = glm::mat4(1.0);
		matrixModelOrange13 = glm::translate(matrixModelOrange13, glm::vec3(6.95, 3.6, 3.9));
		modelOrange.render(glm::scale(matrixModelOrange13, glm::vec3(0.1, 0.1, 0.1)));
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
		////Modelo Banana
		//glm::mat4 matrixModelBanana = glm::mat4(1.0);
		//matrixModelBanana = glm::translate(matrixModelBanana, glm::vec3(2.0, 3.6, 5.5));
		//modelBanana.render(glm::scale(matrixModelBanana, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 1
		glm::mat4 matrixModelBanana1 = glm::mat4(1.0);
		matrixModelBanana1 = glm::translate(matrixModelBanana1, glm::vec3(2.5, 3.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana1, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 2
		glm::mat4 matrixModelBanana2 = glm::mat4(1.0);
		matrixModelBanana2 = glm::translate(matrixModelBanana2, glm::vec3(3.0, 3.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana2, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 3
		glm::mat4 matrixModelBanana3 = glm::mat4(1.0);
		matrixModelBanana3 = glm::translate(matrixModelBanana3, glm::vec3(3.5, 3.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana3, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 4
		glm::mat4 matrixModelBanana4 = glm::mat4(1.0);
		matrixModelBanana4 = glm::translate(matrixModelBanana4, glm::vec3(4.0, 3.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana4, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 5
		glm::mat4 matrixModelBanana5 = glm::mat4(1.0);
		matrixModelBanana5 = glm::translate(matrixModelBanana5, glm::vec3(4.5, 3.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana5, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 6
		glm::mat4 matrixModelBanana6 = glm::mat4(1.0);
		matrixModelBanana6 = glm::translate(matrixModelBanana6, glm::vec3(5.0, 3.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana6, glm::vec3(0.070, 0.07, 0.07)));

		/*											Decoracion								*/
		////Modelo Table
		glm::mat4 matrixModelTabla2 = glm::mat4(1.0);
		matrixModelTabla2 = glm::translate(matrixModelTabla2, glm::vec3(5.0, 3.0, 4.0));
		modelTable.render(glm::scale(matrixModelTabla2, glm::vec3(3.5, 0.8, 4.0)));
		//////// Stpehen
		glm::mat4 retrato = glm::mat4(3.0);
		retrato = glm::translate(retrato, glm::vec3(5.0, 4.0, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureID20);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(retrato, glm::vec3(1.5, 1.5, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////Papel picado (Azul)
		glm::mat4 ppicadoazul = glm::mat4(3.0);
		ppicadoazul = glm::translate(ppicadoazul, glm::vec3(6.5, 4.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoazul, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado 2 (Azul)
		glm::mat4 ppicadoazul2 = glm::mat4(3.0);
		ppicadoazul2 = glm::translate(ppicadoazul2, glm::vec3(3.5, 4.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoazul2, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado  (Morado)
		glm::mat4 ppicadomorado = glm::mat4(3.0);
		ppicadomorado = glm::translate(ppicadomorado, glm::vec3(2.2, 4.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureIDM);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadomorado, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////Papel picado (Verde)
		glm::mat4 ppicadoVerde2 = glm::mat4(3.0);
		ppicadoVerde2 = glm::translate(ppicadoVerde2, glm::vec3(7.8, 4.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureIDV);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoVerde2, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado (Rosa)
		glm::mat4 ppicadoRosa = glm::mat4(3.0);
		ppicadoRosa = glm::translate(ppicadoRosa, glm::vec3(9.0, 4.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureIDR);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoRosa, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////Papel picado (Azul)
		glm::mat4 ppicadoAazul = glm::mat4(3.0);
		ppicadoAazul = glm::translate(ppicadoAazul, glm::vec3(6.5, 4.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoAazul, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado 2 (Azul)
		glm::mat4 ppicadoAazul2 = glm::mat4(3.0);
		ppicadoAazul2 = glm::translate(ppicadoAazul2, glm::vec3(3.5, 4.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoAazul2, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado  (Morado)
		glm::mat4 ppicadoAmorado = glm::mat4(3.0);
		ppicadoAmorado = glm::translate(ppicadoAmorado, glm::vec3(2.2, 4.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureIDM);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoAmorado, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////Papel picado (Verde)
		glm::mat4 ppicadoAVerde2 = glm::mat4(3.0);
		ppicadoAVerde2 = glm::translate(ppicadoAVerde2, glm::vec3(7.8, 4.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureIDV);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoAVerde2, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado (Rosa)
		glm::mat4 ppicadoARosa = glm::mat4(3.0);
		ppicadoARosa = glm::translate(ppicadoARosa, glm::vec3(9.0, 4.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureIDR);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoARosa, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////Papel picado (Verde)
		glm::mat4 ppicadoDVerde2 = glm::mat4(3.0);
		ppicadoDVerde2 = glm::translate(ppicadoDVerde2, glm::vec3(10.0, 4.3, 1.7));
		glBindTexture(GL_TEXTURE_2D, textureIDV);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDVerde2, glm::vec3(0.001, 1.0, 1.0)));
		/////////////Papel picado (Azul)
		glm::mat4 ppicadoDAazul = glm::mat4(3.0);
		ppicadoDAazul = glm::translate(ppicadoDAazul, glm::vec3(10.0, 4.3, 4.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDAazul, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado 2 (Azul)
		glm::mat4 ppicadoDAazul2 = glm::mat4(3.0);
		ppicadoDAazul2 = glm::translate(ppicadoDAazul2, glm::vec3(10.0, 4.3, 5.7));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDAazul2, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado  (Morado)
		glm::mat4 ppicadoDAmorado = glm::mat4(3.0);
		ppicadoDAmorado = glm::translate(ppicadoDAmorado, glm::vec3(10.0, 4.3, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureIDM);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDAmorado, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////Papel picado (Rosa)
		glm::mat4 ppicadoDARosa = glm::mat4(3.0);
		ppicadoDARosa = glm::translate(ppicadoDARosa, glm::vec3(10.0, 4.3, 8.5));
		glBindTexture(GL_TEXTURE_2D, textureIDR);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDARosa, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////Papel picado (Verde)
		glm::mat4 pppicadoIVerde2 = glm::mat4(3.0);
		pppicadoIVerde2 = glm::translate(pppicadoIVerde2, glm::vec3(1.2, 4.3, 1.1));
		glBindTexture(GL_TEXTURE_2D, textureIDV);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIVerde2, glm::vec3(0.001, 1.0, 1.0)));
		/////////////Papel picado (Azul)
		glm::mat4 pppicadoIAazul = glm::mat4(3.0);
		pppicadoIAazul = glm::translate(pppicadoIAazul, glm::vec3(1.2, 4.3, 3.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIAazul, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado 2 (Azul)
		glm::mat4 pppicadoIAazul2 = glm::mat4(3.0);
		pppicadoIAazul2 = glm::translate(pppicadoIAazul2, glm::vec3(1.2, 4.3, 4.7));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIAazul2, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado  (Morado)
		glm::mat4 pppicadoIAmorado = glm::mat4(3.0);
		pppicadoIAmorado = glm::translate(pppicadoIAmorado, glm::vec3(1.2, 4.3, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureIDM);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIAmorado, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////Papel picado (Rosa)
		glm::mat4 pppicadoIARosa = glm::mat4(3.0);
		pppicadoIARosa = glm::translate(pppicadoIARosa, glm::vec3(1.2, 4.3, 7.5));
		glBindTexture(GL_TEXTURE_2D, textureIDR);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIARosa, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////Modelo Mandarina
		//glm::mat4 matrixModelMandarine = glm::mat4(1.0);
		//matrixModelMandarine = glm::translate(matrixModelMandarine, glm::vec3(-8.0, 11.0, 6.0));
		//modelMandarine.render(matrixModelMandarine);

		////Modelo Table 3
		glm::mat4 matrixModelTabla3 = glm::mat4(1.0);
		matrixModelTabla3 = glm::translate(matrixModelTabla3, glm::vec3(9.0, 1.0, 2.0));
		modelTable.render(glm::scale(matrixModelTabla3, glm::vec3(0.5, 0.5, 0.5)));
		glActiveTexture(GL_TEXTURE0);
		/**/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
		modelchasis.render(matrixModelMi_24_chasis);
		glActiveTexture(GL_TEXTURE0);
		modelheli.render(matrixModelMi_24_heli);
		glActiveTexture(GL_TEXTURE0);
		modelMi_24.render(matrixModelMi_24);
		glActiveTexture(GL_TEXTURE0);
		*/
		modelCarro.render(matrixModelCarro);
		glActiveTexture(GL_TEXTURE0);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Esto es para la pista

		glm::mat4 modelPista = glm::mat4(1.0);
		modelPista = glm::translate(modelPista, glm::vec3(5.0, 1.0, 18.0));
		modelPista = glm::scale(modelPista, glm::vec3(50.0, 0.01, 20.0));
		//// Se activa la textura
		glBindTexture(GL_TEXTURE_2D, textureID2);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(modelPista);
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
		glm::mat4 modelPistaT = glm::mat4(1.0);
		modelPistaT = glm::translate(modelPistaT, glm::vec3(5.0, 1.0, -18.0));
		modelPistaT = glm::scale(modelPistaT, glm::vec3(50.0, 0.01, 20.0));
		//// Se activa la textura
		glBindTexture(GL_TEXTURE_2D, textureID2);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(modelPistaT);
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
		glm::mat4 modelPistaI = glm::mat4(1.0);
		modelPistaI = glm::translate(modelPistaI, glm::vec3(-20.0, 1.0, 0.0));
		modelPistaI = glm::scale(modelPistaI, glm::vec3(20.0, 0.01, 40.0));
		//// Se activa la textura
		glBindTexture(GL_TEXTURE_2D, textureID2);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(modelPistaI);
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
		glm::mat4 modelPistaD = glm::mat4(1.0);
		modelPistaD = glm::translate(modelPistaD, glm::vec3(20.0, 1.0, 0.0));
		modelPistaD = glm::scale(modelPistaD, glm::vec3(20.0, 0.01, 40.0));
		//// Se activa la textura
		glBindTexture(GL_TEXTURE_2D, textureID2);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(modelPistaD);
		glBindTexture(GL_TEXTURE_2D, 0);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////PArte Trasera 0//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						// Render del cubo con textura de ladrillos y con repeticion en x
		glm::mat4 cubeTextureModel0 = glm::mat4(3.0);
		cubeTextureModel0 = glm::translate(cubeTextureModel0, glm::vec3(0.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel0, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel2 = glm::mat4(3.0);
		cubeTextureModel2 = glm::translate(cubeTextureModel2, glm::vec3(1.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel2, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel3 = glm::mat4(1.0);
		cubeTextureModel3 = glm::translate(cubeTextureModel3, glm::vec3(2.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel3, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel4 = glm::mat4(1.0);
		cubeTextureModel4 = glm::translate(cubeTextureModel4, glm::vec3(3.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel4, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel5 = glm::mat4(1.0);
		cubeTextureModel5 = glm::translate(cubeTextureModel5, glm::vec3(4.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel5, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel6 = glm::mat4(1.0);
		cubeTextureModel6 = glm::translate(cubeTextureModel6, glm::vec3(5.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel6, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel7 = glm::mat4(1.0);
		cubeTextureModel7 = glm::translate(cubeTextureModel7, glm::vec3(6.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel7, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel8 = glm::mat4(1.0);
		cubeTextureModel8 = glm::translate(cubeTextureModel8, glm::vec3(7.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel8, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel9 = glm::mat4(1.0);
		cubeTextureModel9 = glm::translate(cubeTextureModel9, glm::vec3(8.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel9, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel10 = glm::mat4(1.0);
		cubeTextureModel10 = glm::translate(cubeTextureModel10, glm::vec3(9.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel10, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel11 = glm::mat4(1.0);
		cubeTextureModel11 = glm::translate(cubeTextureModel11, glm::vec3(10.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel11, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel12 = glm::mat4(1.0);
		cubeTextureModel12 = glm::translate(cubeTextureModel12, glm::vec3(11.0, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel12, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////Paredes Internas Bajas/////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				////////////////////////////////////////////////////////////
		glm::mat4 pared10 = glm::mat4(1.0);
		pared10 = glm::translate(pared10, glm::vec3(9.0, 2.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared10, glm::vec3(4.0, 2.0, 0.1)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared20 = glm::mat4(1.0);
		pared20 = glm::translate(pared20, glm::vec3(9.0, 2.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared20, glm::vec3(4.0, 2.0, 0.1)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared30 = glm::mat4(1.0);
		pared30 = glm::translate(pared30, glm::vec3(3.0, 2.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared30, glm::vec3(4.0, 2.0, 0.1)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared301 = glm::mat4(1.0);
		pared301 = glm::translate(pared301, glm::vec3(5.0, 2.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared301, glm::vec3(0.1, 2.0, 5.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared302 = glm::mat4(1.0);
		pared302 = glm::translate(pared302, glm::vec3(5.0, 2.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared302, glm::vec3(0.1, 2.0, 2.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared40 = glm::mat4(1.0);
		pared40 = glm::translate(pared40, glm::vec3(7.0, 2.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared40, glm::vec3(0.1, 2.0, 3.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////Puertas//////////////////////////////////////////////////////////
		glm::mat4 puerta1 = glm::mat4(1.0);
		puerta1 = glm::translate(puerta1, glm::vec3(7.0, 2.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID9);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(puerta1, glm::vec3(0.1, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		glm::mat4 puerta12 = glm::mat4(1.0);
		puerta12 = glm::translate(puerta12, glm::vec3(7.0, 2.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID9);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(puerta12, glm::vec3(0.1, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		glm::mat4 puerta13 = glm::mat4(1.0);
		puerta13 = glm::translate(puerta13, glm::vec3(5.0, 2.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID9);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(puerta13, glm::vec3(0.1, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////Fin Puertas//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////Parte Trasera 1//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModell13 = glm::mat4(3.0);
		cubeTextureModell13 = glm::translate(cubeTextureModell13,
			glm::vec3(0.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModell13, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel13 = glm::mat4(3.0);
		cubeTextureModel13 = glm::translate(cubeTextureModel13,
			glm::vec3(1.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel13, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel14 = glm::mat4(1.0);
		cubeTextureModel14 = glm::translate(cubeTextureModel14,
			glm::vec3(2.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel14, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel15 = glm::mat4(1.0);
		cubeTextureModel15 = glm::translate(cubeTextureModel15,
			glm::vec3(3.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel15, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 ccubeTextureModel16 = glm::mat4(1.0);
		ccubeTextureModel16 = glm::translate(ccubeTextureModel16,
			glm::vec3(4.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ccubeTextureModel16, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel17 = glm::mat4(1.0);
		cubeTextureModel17 = glm::translate(cubeTextureModel17,
			glm::vec3(5.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel17, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 ccubeTextureModel18 = glm::mat4(1.0);
		ccubeTextureModel18 = glm::translate(ccubeTextureModel18,
			glm::vec3(6.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ccubeTextureModel18, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cucubeTextureModel19 = glm::mat4(1.0);
		cucubeTextureModel19 = glm::translate(cucubeTextureModel19,
			glm::vec3(7.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cucubeTextureModel19, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cucubeTextureModel20 = glm::mat4(1.0);
		cucubeTextureModel20 = glm::translate(cucubeTextureModel20,
			glm::vec3(8.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cucubeTextureModel20, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel21 = glm::mat4(1.0);
		cubeTextureModel21 = glm::translate(cubeTextureModel21, glm::vec3(9.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel21, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel22 = glm::mat4(1.0);
		cubeTextureModel22 = glm::translate(cubeTextureModel22, glm::vec3(10.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel22, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel23 = glm::mat4(1.0);
		cubeTextureModel23 = glm::translate(cubeTextureModel23, glm::vec3(11.0, 3.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel23, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////Parte Trasera 2//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTAl13 = glm::mat4(3.0);
		cubeTextureModelTAl13 = glm::translate(cubeTextureModelTAl13,
			glm::vec3(0.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTAl13, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA13 = glm::mat4(3.0);
		cubeTextureModelTA13 = glm::translate(cubeTextureModelTA13,
			glm::vec3(1.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA13, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA14 = glm::mat4(1.0);
		cubeTextureModelTA14 = glm::translate(cubeTextureModelTA14,
			glm::vec3(2.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA14, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA15 = glm::mat4(1.0);
		cubeTextureModelTA15 = glm::translate(cubeTextureModelTA15,
			glm::vec3(3.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA15, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 ccubeTextureModelTA16 = glm::mat4(1.0);
		ccubeTextureModelTA16 = glm::translate(ccubeTextureModelTA16,
			glm::vec3(4.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ccubeTextureModelTA16, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA17 = glm::mat4(1.0);
		cubeTextureModelTA17 = glm::translate(cubeTextureModelTA17,
			glm::vec3(5.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA17, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 ccubeTextureModelTA18 = glm::mat4(1.0);
		ccubeTextureModelTA18 = glm::translate(ccubeTextureModelTA18,
			glm::vec3(6.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ccubeTextureModelTA18, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cucubeTextureModelTA19 = glm::mat4(1.0);
		cucubeTextureModelTA19 = glm::translate(cucubeTextureModelTA19,
			glm::vec3(7.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cucubeTextureModelTA19, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cucubeTextureModelTA20 = glm::mat4(1.0);
		cucubeTextureModelTA20 = glm::translate(cucubeTextureModelTA20,
			glm::vec3(8.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cucubeTextureModelTA20, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA21 = glm::mat4(1.0);
		cubeTextureModelTA21 = glm::translate(cubeTextureModelTA21, glm::vec3(9.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA21, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA22 = glm::mat4(1.0);
		cubeTextureModelTA22 = glm::translate(cubeTextureModelTA22, glm::vec3(10.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA22, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA23 = glm::mat4(1.0);
		cubeTextureModelTA23 = glm::translate(cubeTextureModelTA23, glm::vec3(11.0, 4.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA23, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////PAredes Izquierdas 0////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel24 = glm::mat4(1.0);
		cubeTextureModel24 = glm::translate(cubeTextureModel24, glm::vec3(0.0, 2.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel24, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel25 = glm::mat4(1.0);
		cubeTextureModel25 = glm::translate(cubeTextureModel25, glm::vec3(0.0, 2.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel25, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel26 = glm::mat4(1.0);
		cubeTextureModel26 = glm::translate(cubeTextureModel26, glm::vec3(0.0, 2.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel26, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel27 = glm::mat4(1.0);
		cubeTextureModel27 = glm::translate(cubeTextureModel27, glm::vec3(0.0, 2.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel27, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel28 = glm::mat4(1.0);
		cubeTextureModel28 = glm::translate(cubeTextureModel28, glm::vec3(0.0, 2.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel28, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel34 = glm::mat4(1.0);
		cubeTextureModel34 = glm::translate(cubeTextureModel34, glm::vec3(0.0, 2.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel34, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel29 = glm::mat4(1.0);
		cubeTextureModel29 = glm::translate(cubeTextureModel29, glm::vec3(0.0, 2.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel29, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel30 = glm::mat4(1.0);
		cubeTextureModel30 = glm::translate(cubeTextureModel30, glm::vec3(0.0, 2.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel30, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel31 = glm::mat4(1.0);
		cubeTextureModel31 = glm::translate(cubeTextureModel31, glm::vec3(0.0, 2.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel31, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel32 = glm::mat4(1.0);
		cubeTextureModel32 = glm::translate(cubeTextureModel32, glm::vec3(0.0, 2.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel32, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel33 = glm::mat4(1.0);
		cubeTextureModel33 = glm::translate(cubeTextureModel33, glm::vec3(0.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel33, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Izqueirda 1/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI24 = glm::mat4(1.0);
		cubeTextureModelAI24 = glm::translate(cubeTextureModelAI24, glm::vec3(0.0, 3.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI24, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI25 = glm::mat4(1.0);
		cubeTextureModelAI25 = glm::translate(cubeTextureModelAI25, glm::vec3(0.0, 3.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI25, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI26 = glm::mat4(1.0);
		cubeTextureModelAI26 = glm::translate(cubeTextureModelAI26, glm::vec3(0.0, 3.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI26, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI27 = glm::mat4(1.0);
		cubeTextureModelAI27 = glm::translate(cubeTextureModelAI27, glm::vec3(0.0, 3.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI27, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI28 = glm::mat4(1.0);
		cubeTextureModelAI28 = glm::translate(cubeTextureModelAI28, glm::vec3(0.0, 3.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI28, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI34 = glm::mat4(1.0);
		cubeTextureModelAI34 = glm::translate(cubeTextureModelAI34, glm::vec3(0.0, 3.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI34, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI29 = glm::mat4(1.0);
		cubeTextureModelAI29 = glm::translate(cubeTextureModelAI29, glm::vec3(0.0, 3.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI29, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI30 = glm::mat4(1.0);
		cubeTextureModelAI30 = glm::translate(cubeTextureModelAI30, glm::vec3(0.0, 3.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI30, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI31 = glm::mat4(1.0);
		cubeTextureModelAI31 = glm::translate(cubeTextureModelAI31, glm::vec3(0.0, 3.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI31, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI32 = glm::mat4(1.0);
		cubeTextureModelAI32 = glm::translate(cubeTextureModelAI32, glm::vec3(0.0, 3.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI32, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelAI33 = glm::mat4(1.0);
		//cubeTextureModelAI33 = glm::translate(cubeTextureModelAI33, glm::vec3(0.0, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelAI33, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Izqueirda 2/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI124 = glm::mat4(1.0);
		cubeTextureModelAI124 = glm::translate(cubeTextureModelAI124, glm::vec3(0.0, 4.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI124, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI125 = glm::mat4(1.0);
		cubeTextureModelAI125 = glm::translate(cubeTextureModelAI125, glm::vec3(0.0, 4.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI125, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI126 = glm::mat4(1.0);
		cubeTextureModelAI126 = glm::translate(cubeTextureModelAI126, glm::vec3(-0.1, 4.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID7);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI126, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI127 = glm::mat4(1.0);
		cubeTextureModelAI127 = glm::translate(cubeTextureModelAI127, glm::vec3(0.0, 4.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI127, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI128 = glm::mat4(1.0);
		cubeTextureModelAI128 = glm::translate(cubeTextureModelAI128, glm::vec3(0.0, 4.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI128, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI134 = glm::mat4(1.0);
		cubeTextureModelAI134 = glm::translate(cubeTextureModelAI134, glm::vec3(0.0, 4.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI134, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI1129 = glm::mat4(1.0);
		cubeTextureModelAI1129 = glm::translate(cubeTextureModelAI1129, glm::vec3(0.0, 4.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI1129, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI1130 = glm::mat4(1.0);
		cubeTextureModelAI1130 = glm::translate(cubeTextureModelAI1130, glm::vec3(0.0, 4.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI1130, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI131 = glm::mat4(1.0);
		cubeTextureModelAI131 = glm::translate(cubeTextureModelAI131, glm::vec3(-0.1, 4.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID7);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI131, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI132 = glm::mat4(1.0);
		cubeTextureModelAI132 = glm::translate(cubeTextureModelAI132, glm::vec3(0.0, 4.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI132, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI133 = glm::mat4(1.0);
		cubeTextureModelAI133 = glm::translate(cubeTextureModelAI133, glm::vec3(0.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI133, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Derecha 0/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD024 = glm::mat4(1.0);
		cubeTextureModelD024 = glm::translate(cubeTextureModelD024, glm::vec3(11.0, 2.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD024, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD025 = glm::mat4(1.0);
		cubeTextureModelD025 = glm::translate(cubeTextureModelD025, glm::vec3(11.0, 2.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD025, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD026 = glm::mat4(1.0);
		cubeTextureModelD026 = glm::translate(cubeTextureModelD026, glm::vec3(11.0, 2.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD026, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD027 = glm::mat4(1.0);
		cubeTextureModelD027 = glm::translate(cubeTextureModelD027, glm::vec3(11.0, 2.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD027, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD028 = glm::mat4(1.0);
		cubeTextureModelD028 = glm::translate(cubeTextureModelD028, glm::vec3(11.0, 2.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD028, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD034 = glm::mat4(1.0);
		cubeTextureModelD034 = glm::translate(cubeTextureModelD034, glm::vec3(11.0, 2.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD034, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD029 = glm::mat4(1.0);
		cubeTextureModelD029 = glm::translate(cubeTextureModelD029, glm::vec3(11.0, 2.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD029, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD030 = glm::mat4(1.0);
		cubeTextureModelD030 = glm::translate(cubeTextureModelD030, glm::vec3(11.0, 2.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD030, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD031 = glm::mat4(1.0);
		cubeTextureModelD031 = glm::translate(cubeTextureModelD031, glm::vec3(11.0, 2.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD031, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD032 = glm::mat4(1.0);
		cubeTextureModelD032 = glm::translate(cubeTextureModelD032, glm::vec3(11.0, 2.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD032, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD033 = glm::mat4(1.0);
		cubeTextureModelD033 = glm::translate(cubeTextureModelD033, glm::vec3(11.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD033, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Derecha 1/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD124 = glm::mat4(1.0);
		cubeTextureModelD124 = glm::translate(cubeTextureModelD124, glm::vec3(11.0, 3.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD124, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD125 = glm::mat4(1.0);
		cubeTextureModelD125 = glm::translate(cubeTextureModelD125, glm::vec3(11.0, 3.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD125, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD126 = glm::mat4(1.0);
		cubeTextureModelD126 = glm::translate(cubeTextureModelD126, glm::vec3(11.0, 3.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD126, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD127 = glm::mat4(1.0);
		cubeTextureModelD127 = glm::translate(cubeTextureModelD127, glm::vec3(11.0, 3.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD127, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD128 = glm::mat4(1.0);
		cubeTextureModelD128 = glm::translate(cubeTextureModelD128, glm::vec3(11.0, 3.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD128, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD134 = glm::mat4(1.0);
		cubeTextureModelD134 = glm::translate(cubeTextureModelD134, glm::vec3(11.0, 3.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD134, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD129 = glm::mat4(1.0);
		cubeTextureModelD129 = glm::translate(cubeTextureModelD129, glm::vec3(11.0, 3.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD129, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD130 = glm::mat4(1.0);
		cubeTextureModelD130 = glm::translate(cubeTextureModelD130, glm::vec3(11.0, 3.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD130, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD131 = glm::mat4(1.0);
		cubeTextureModelD131 = glm::translate(cubeTextureModelD131, glm::vec3(11.0, 3.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD131, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD132 = glm::mat4(1.0);
		cubeTextureModelD132 = glm::translate(cubeTextureModelD132, glm::vec3(11.0, 3.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD132, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD133 = glm::mat4(1.0);
		cubeTextureModelD133 = glm::translate(cubeTextureModelD133, glm::vec3(11.0, 3.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD133, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Derecha 2/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD224 = glm::mat4(1.0);
		cubeTextureModelD224 = glm::translate(cubeTextureModelD224, glm::vec3(11.0, 4.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD224, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD225 = glm::mat4(1.0);
		cubeTextureModelD225 = glm::translate(cubeTextureModelD225, glm::vec3(11.1, 4.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID7);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD225, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD226 = glm::mat4(1.0);
		cubeTextureModelD226 = glm::translate(cubeTextureModelD226, glm::vec3(11.0, 4.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD226, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD227 = glm::mat4(1.0);
		cubeTextureModelD227 = glm::translate(cubeTextureModelD227, glm::vec3(11.0, 4.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD227, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD228 = glm::mat4(1.0);
		cubeTextureModelD228 = glm::translate(cubeTextureModelD228, glm::vec3(11.0, 4.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD228, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD234 = glm::mat4(1.0);
		cubeTextureModelD234 = glm::translate(cubeTextureModelD234, glm::vec3(11.0, 4.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD234, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD229 = glm::mat4(1.0);
		cubeTextureModelD229 = glm::translate(cubeTextureModelD229, glm::vec3(11.0, 4.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD229, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD230 = glm::mat4(1.0);
		cubeTextureModelD230 = glm::translate(cubeTextureModelD230, glm::vec3(11.0, 4.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD230, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD231 = glm::mat4(1.0);
		cubeTextureModelD231 = glm::translate(cubeTextureModelD231, glm::vec3(11.0, 4.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD231, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD232 = glm::mat4(1.0);
		cubeTextureModelD232 = glm::translate(cubeTextureModelD232, glm::vec3(11.1, 4.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID7);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD232, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelD233 = glm::mat4(1.0);
		//cubeTextureModelD233 = glm::translate(cubeTextureModelD233, glm::vec3(11.0, 4.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelD233, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Frontales 0/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF0 = glm::mat4(3.0);
		cubeTextureModelF0 = glm::translate(cubeTextureModelF0,
			glm::vec3(0.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF0, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF02 = glm::mat4(3.0);
		cubeTextureModelF02 = glm::translate(cubeTextureModelF02, glm::vec3(1.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF02, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF03 = glm::mat4(1.0);
		cubeTextureModelF03 = glm::translate(cubeTextureModelF03,
			glm::vec3(2.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF03, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF04 = glm::mat4(1.0);
		//cubeTextureModelF04 = glm::translate(cubeTextureModelF04, glm::vec3(3.0, 2.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF04, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF05 = glm::mat4(1.0);
		cubeTextureModelF05 = glm::translate(cubeTextureModelF05, glm::vec3(4.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF05, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF06 = glm::mat4(1.0);
		cubeTextureModelF06 = glm::translate(cubeTextureModelF06, glm::vec3(4.6, 2.0, 11.1));
		glBindTexture(GL_TEXTURE_2D, textureID8);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF06, glm::vec3(3.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF07 = glm::mat4(1.0);
		cubeTextureModelF07 = glm::translate(cubeTextureModelF07, glm::vec3(6.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF07, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF08 = glm::mat4(1.0);
		cubeTextureModelF08 = glm::translate(cubeTextureModelF08, glm::vec3(7.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF08, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF09 = glm::mat4(1.0);
		cubeTextureModelF09 = glm::translate(cubeTextureModelF09,
			glm::vec3(8.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF09, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF010 = glm::mat4(1.0);
		cubeTextureModelF010 = glm::translate(cubeTextureModelF010, glm::vec3(9.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF010, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF011 = glm::mat4(1.0);
		cubeTextureModelF011 = glm::translate(cubeTextureModelF011, glm::vec3(10.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF011, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF012 = glm::mat4(1.0);
		cubeTextureModelF012 = glm::translate(cubeTextureModelF012, glm::vec3(11.0, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF012, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Frontales 1/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF1 = glm::mat4(3.0);
		cubeTextureModelF1 = glm::translate(cubeTextureModelF1, glm::vec3(0.0, 3.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF1, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF12 = glm::mat4(3.0);
		cubeTextureModelF12 = glm::translate(cubeTextureModelF12,glm::vec3(1.0, 3.0, 11.1));
		glBindTexture(GL_TEXTURE_2D, textureID7);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF12, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/

		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF13 = glm::mat4(1.0);
		//cubeTextureModelF13 = glm::translate(cubeTextureModelF13,glm::vec3(2.0, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV",glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF13, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF14 = glm::mat4(1.0);
		//cubeTextureModelF14 = glm::translate(cubeTextureModelF14,glm::vec3(3.0, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF14, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF15 = glm::mat4(1.0);
		cubeTextureModelF15 = glm::translate(cubeTextureModelF15, glm::vec3(4.0, 3.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF15, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF16 = glm::mat4(1.0);
		cubeTextureModelF16 = glm::translate(cubeTextureModelF16, glm::vec3(5.0, 3.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF16, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF17 = glm::mat4(1.0);
		//cubeTextureModelF17 = glm::translate(cubeTextureModelF17, glm::vec3(6.0, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF17, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF18 = glm::mat4(1.0);
		cubeTextureModelF18 = glm::translate(cubeTextureModelF18,
			glm::vec3(7.0, 3.0, 11.1));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF18, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF19 = glm::mat4(1.0);
		cubeTextureModelF19 = glm::translate(cubeTextureModelF19,
			glm::vec3(8.0, 3.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF19, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF110 = glm::mat4(1.0);
		//cubeTextureModelF110 = glm::translate(cubeTextureModelF110, glm::vec3(9.0, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF110, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF111 = glm::mat4(1.0);
		//cubeTextureModelF111 = glm::translate(cubeTextureModelF111, glm::vec3(10.0, 3.0, 11.1));
		//glBindTexture(GL_TEXTURE_2D, textureID7);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF111, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF112 = glm::mat4(1.0);
		//cubeTextureModelF112 = glm::translate(cubeTextureModelF112, glm::vec3(11.0, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF112, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Frontales 2/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF2 = glm::mat4(3.0);
		cubeTextureModelF2 = glm::translate(cubeTextureModelF2,
			glm::vec3(0.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF2, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF22 = glm::mat4(3.0);
		cubeTextureModelF22 = glm::translate(cubeTextureModelF22,
			glm::vec3(1.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF22, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF23 = glm::mat4(1.0);
		cubeTextureModelF23 = glm::translate(cubeTextureModelF23,
			glm::vec3(2.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF23, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF24 = glm::mat4(1.0);
		cubeTextureModelF24 = glm::translate(cubeTextureModelF24,
			glm::vec3(3.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF24, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF25 = glm::mat4(1.0);
		cubeTextureModelF25 = glm::translate(cubeTextureModelF25,
			glm::vec3(4.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF25, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF26 = glm::mat4(1.0);
		cubeTextureModelF26 = glm::translate(cubeTextureModelF26,
			glm::vec3(5.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF26, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF27 = glm::mat4(1.0);
		cubeTextureModelF27 = glm::translate(cubeTextureModelF27,
			glm::vec3(6.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF27, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF28 = glm::mat4(1.0);
		cubeTextureModelF28 = glm::translate(cubeTextureModelF28, glm::vec3(7.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF28, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF29 = glm::mat4(1.0);
		cubeTextureModelF29 = glm::translate(cubeTextureModelF29, glm::vec3(8.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF29, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF210 = glm::mat4(1.0);
		cubeTextureModelF210 = glm::translate(cubeTextureModelF210, glm::vec3(9.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF210, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF211 = glm::mat4(1.0);
		cubeTextureModelF211 = glm::translate(cubeTextureModelF211, glm::vec3(10.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF211, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF212 = glm::mat4(1.0);
		cubeTextureModelF212 = glm::translate(cubeTextureModelF212, glm::vec3(11.0, 4.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF212, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*															Tapa de la casa (Arriba)														*/

		glm::mat4 modelPiedra4 = glm::mat4(1.0);
		modelPiedra4 = glm::translate(modelPiedra4, glm::vec3(5.5, 5.0, 5.5));
		glBindTexture(GL_TEXTURE_2D, textureID5);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(glm::scale(modelPiedra4, glm::vec3(11.0, 0.01, 11.0)));
		shaderTexture.setFloat("offsetX", 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		/*															Tapa de la casa (Planta Baja)														*/
		glm::mat4 modelPiedra2 = glm::mat4(1.0);
		modelPiedra2 = glm::translate(modelPiedra2, glm::vec3(5.5, 1.0, 5.5));
		glBindTexture(GL_TEXTURE_2D, textureID5);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(glm::scale(modelPiedra2, glm::vec3(11.0, 0.01, 11.0)));
		shaderTexture.setFloat("offsetX", 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		/*															Tapa de la casa (Piso 1)														*/
		glm::mat4 modelPiedra3 = glm::mat4(1.0);
		modelPiedra3 = glm::translate(modelPiedra3, glm::vec3(5.5, 3.0, 5.5));
		glBindTexture(GL_TEXTURE_2D, textureID5);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(glm::scale(modelPiedra3, glm::vec3(11.0, 0.01, 11.0)));
		shaderTexture.setFloat("offsetX", 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		/*															Tapa de la casa (Cesped)														*/
		glm::mat4 modelPasto2 = glm::mat4(1.0);
		modelPasto2 = glm::translate(modelPasto2, glm::vec3(5.5, 0.8, 5.5));
		glBindTexture(GL_TEXTURE_2D, textureID6);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(glm::scale(modelPasto2, glm::vec3(22.0, 0.01, 22.0)));
		shaderTexture.setFloat("offsetX", 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (angle > 2 * M_PI)
			angle = 0.0;
		else
			angle += 0.0001;

		// Se Dibuja el Skybox
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);

		dz = 0;
		rot0 = 0;
		offX += 0.001;
		switch (state) {
		case 0:
			//std::cout << "Advance Aircraft: " << std::endl;
			//-0.01 debe se rigual
			//matrixModelAircraft = glm::translate(matrixModelAircraft, glm::vec3(0.0, 0.0, -0.1));
			//offsetAircraftAdvance += 0.01;
			//if (offsetAircraftAdvance > 5.0) {
			//	offsetAircraftAdvance = 0.0;
			//	state = 1;
			//}
			////////////////////////////////////////////////////////////////////////////////////////
			std::cout << "Advance Car: " << std::endl;
			std::cout << "Helicopter Up: " << std::endl;
			matrixModelCarro = glm::translate(matrixModelCarro, glm::vec3(0.0, 0.0, 0.1));
			matrixModelMi_24 = glm::translate(matrixModelMi_24, glm::vec3(0.0, 0.1, 0.0));
			offsetCarAdvance += 0.1;
			offsetNaveArriba += 0.1;
			if (offsetCarAdvance > 40.0) {
				offsetCarAdvance = 0.0;
				offsetNaveArriba = 0.0;
				state = 1;
			}
			break;
		case 1:
			//			std::cout << "Turn: " << std::endl;
			//			matrixModelAircraft = glm::translate(matrixModelAircraft, glm::vec3(0,0,-0.001));
			//			matrixModelAircraft = glm::rotate(matrixModelAircraft, glm::radians(0.05f), glm::vec3(0, 1, 0));
			//			offsetairfart += 0.05;
			//			if (offsetairfart > 90.0) {
			//				offsetairfart = 0.0;
			//				state = 0;
			//			}
			//			break;
						//////////////////////////////////////////////////////////////////////////7
			std::cout << "Turn: Car " << std::endl;
			matrixModelCarro = glm::translate(matrixModelCarro, glm::vec3(0, 0, -0.001));
			matrixModelCarro = glm::rotate(matrixModelCarro, glm::radians(0.05f), glm::vec3(0, 1, 0));
			matrixModelMi_24 = glm::translate(matrixModelMi_24, glm::vec3(0.0, -0.1, 0.0));
			offsetCarfart += 0.05;
			offsetNaveAbajo += 0.5;
			if (offsetCarfart > 90.0) {
				offsetCarfart = 0.0;
				offsetNaveAbajo = 0.0;
				state = 0;
			}
			break;

		}

		glfwSwapBuffers(window);
	}
}

int main(int argc, char **argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}