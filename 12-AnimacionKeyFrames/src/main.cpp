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

#include <AL/alut.h>

#define NUM_BUFFERS 2
#define NUM_SOURCES 2
#define NUM_ENVRIONMENTS 1

// Config OpenAL
ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffers[NUM_BUFFERS];
ALuint sources[NUM_SOURCES];
ALuint enviornment[NUM_ENVRIONMENTS];
// variables para inicializar audios
ALsizei size, freq;
ALenum format;
ALvoid* data;
int ch;
ALboolean loop;

#include "Headers/AnimationUtils.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;

GLFWwindow* window;

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
std::shared_ptr<FirstPersonCamera> camera_halloween(new FirstPersonCamera());
std::shared_ptr<FirstPersonCamera> camara_ofrenda(new FirstPersonCamera());
std::shared_ptr<FirstPersonCamera> camara_nacimiento(new FirstPersonCamera());

Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Sphere sphere3(20, 20);
Sphere sphereLamp(20, 20);
// Descomentar
Sphere skyboxSphere(20, 20);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Cylinder cylinder2(20, 20, 0.5, 0.5);
Cylinder cylinderMaterials(20, 20, 0.5, 0.5);
Box boxMaterials;
Box box1;
Box box2;
Box box3;
Box boxCesped;
Box boxWall;
Box boxParedes;
Box boxCarretera;

// Models complex instances
Model modelRock;
Model tabla;
Model sofa;
Model modelCalabaza;
////
Model modelApple, modelBanana, modelCouch, modelLamp, modelMandarine, modelOrange, modelPM, modelTable, modelChimney, modelVela;
GLuint textureID1G, textureID2G, textureID7G, textureID8G, textureID9G, textureID20M, textureID20P, textureIDM, textureIDV;
GLuint textureIDR;
GLuint textureID1, textureID2, textureID3, textureID4, textureID5, textureID6, textureID7, textureID8, textureID9;
GLuint textureID10, textureID11, textureID12, textureID13, textureID14, textureID15, textureID16, textureID17, textureIDv2;
GLuint textureID18, textureID19, textureID20, textureID21, textureID22, textureID23, textureID24, textureID25;
GLuint textureID26, textureID27, textureflorID1;;//, textureID28, textureID29, textureID30, textureID31, textureID32, textureID33;

//Offsets luces navideñas
int offset1 = 1;
int offset2 = 4;
int offset3 = 7;
int offset4 = 7;
int offset5 = 4;

//On-off luces 
int lightState = 100;

float onOffSala = 7;
float onOffComedor = 7;
float onOffCocina = 7;
float onOffBanio = 7;
float onOffRecamara1 = 7;
float onOffRecamara2 = 7;
float onOffRecamara3 = 7;
float onOffHabitacionArbol = 7;
float onOffCochera = 7;

//on-off de las luces de la casa de halloween
float onOffLampara1 = 7;
float onOffLampara2 = 7;
float onOffLampara3 = 7;
//*******************************

float cam1posx = 0.0;
float cam1posy = 0.0;
float cam1posz = 0.0;
////////////////////
	
int numberCamera = 1;
float offsetState = 0.0;

GLuint skyboxTextureID;
// Dart lego
Model modelDartLegoBody;
Model modelDartLegoHead;
Model modelDartLegoMask;
Model modelDartLegoLeftArm;
Model modelDartLegoRightArm;
Model modelDartLegoLeftHand;
Model modelDartLegoRightHand;
Model modelDartLegoLeftLeg;
Model modelDartLegoRightLeg;

Model modelCar;
Model modelEclipseWheelsFrontal;
Model modelEclipseWheelsRear;


Model modelRosa;
Model modelMaceta;
Model modelJardinera;
Model modelMueble;
Model modelMueble2;
Model modelSala;
Model modelSalap;
Model modelToilet;
Model modelHandWash;
Model modelTable2;

Model modelLampara;
Model modelKitchen;
Model modelBed;
Model modelRefrigerator;


Model modelHeliChasis;
Model modelHeliHeliMeid;
Model modelHeliHeliCh;

Model modelLambo;
Model modelLamboLeftDor;
Model modelLamboRightDoor;

Model modelLamboFrontWheels;
Model modelLamboBackWheels;

Model modelTree;
Model modelStar;
Model modePiso;
Model modelChBall1;
Model modelChBall2;
Model modelChBall3;
Model modelChBall4;
Model modelChBall5;
Model modelRegalo1;
Model modelRegalo2;
Model modelRegalo3;
Model snowMan;
Model modelCoronaDecoracion;
Model modelNocheBuena;
Model modelBaston;
Model modelTrineo;
Model modelPinata;
Model modelPiso;
Model modelSantaHat;


Model modelCabine;
Model modelElefante;
Model modelCamello;
Model modelCow;
Model modelSheep;
Model modelDeer;
Model modelChicken;
Model modelMuebleTV;
Model modelTV;
Model modelCloset;


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

float rot0 = 0.0, dz = 0.0;

float rot1 = 0.0, rot2 = 0.0, rot3 = 0.0, rot4 = 0.0;
float rotDartHead = 0.0, rotDartBody = 0.0, advanceDartBody = 0.0, rotDartLeftArm = 0.0,
rotDartLeftHand = 0.0, rotDartRightArm = 0.0, rotDartRightHand = 0.0, rotDartLeftLeg = 0.0, rotDartRightLeg = 0.0;
int modelSelected = 0;
bool enableCountSelected = true;

// Variables to animations keyframes
bool saveFrame = false, availableSave = true;
std::ofstream myfile;
std::string fileName = "";
bool record = false;

// Joints interpolations Dart Lego
std::vector<std::vector<float>> keyFramesJoints;
std::vector<std::vector<glm::mat4>> keyFramesDart;
int indexFrameJoints = 0;
int indexFrameJointsNext = 1;
float interpolationJoints = 0.0;
int maxNumPasosJoints = 20;
int numPasosJoints = 0;

int indexFrameDart = 0;
int indexFrameDartNext = 1;
float interpolationDart = 0.0;
int maxNumPasosDart = 200;
int numPasosDart = 0;

double deltaTime;
double currTime, lastTime;

bool muestraPosicion = false;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action,
	int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
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


	boxParedes.init();
	boxParedes.setShader(&shaderMulLighting);


	boxParedes.init();
	boxParedes.setShader(&shaderMulLighting);

	boxCesped.init();
	boxCesped.setShader(&shaderMulLighting);

	boxCarretera.init();
	boxCarretera.setShader(&shaderMulLighting);

	sphere3.init();
	sphere3.setShader(&shaderMulLighting);

	box3.init();
	box3.setShader(&shaderMulLighting);

	boxCesped.init();
	boxCesped.setShader(&shaderMulLighting);

	boxWall.init();
	boxWall.setShader(&shaderMulLighting);

	modelRock.loadModel("../models/nubes/nube.obj");
	modelRock.setShader(&shaderMulLighting);


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

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///Modelo Pupitre
	sofa.loadModel("../models/chairSchool/chairSchool.obj");
	sofa.setShader(&shaderMulLighting);
	///modelo Escritorio
	modelCalabaza.loadModel("../models/Desk/Desk.obj");
	modelCalabaza.setShader(&shaderMulLighting);
	///Model Vela
	//modelVela.loadModel("../models/vela/velas.obj");
	//modelVela.setShader(&shaderMulLighting);
	////////

	// Dart Lego
	modelDartLegoBody.loadModel("../models/LegoDart/LeoDart_body.obj");
	modelDartLegoBody.setShader(&shaderMulLighting);
	modelDartLegoMask.loadModel("../models/LegoDart/LeoDart_mask.obj");
	modelDartLegoMask.setShader(&shaderMulLighting);
	modelDartLegoHead.loadModel("../models/LegoDart/LeoDart_head.obj");
	modelDartLegoHead.setShader(&shaderMulLighting);
	modelDartLegoLeftArm.loadModel("../models/LegoDart/LeoDart_left_arm.obj");
	modelDartLegoLeftArm.setShader(&shaderMulLighting);
	modelDartLegoRightArm.loadModel("../models/LegoDart/LeoDart_right_arm.obj");
	modelDartLegoRightArm.setShader(&shaderMulLighting);
	modelDartLegoLeftHand.loadModel("../models/LegoDart/LeoDart_left_hand.obj");
	modelDartLegoLeftHand.setShader(&shaderMulLighting);
	modelDartLegoRightHand.loadModel("../models/LegoDart/LeoDart_right_hand.obj");
	modelDartLegoRightHand.setShader(&shaderMulLighting);
	modelDartLegoLeftLeg.loadModel("../models/LegoDart/LeoDart_left_leg.obj");
	modelDartLegoLeftLeg.setShader(&shaderMulLighting);
	modelDartLegoRightLeg.loadModel("../models/LegoDart/LeoDart_right_leg.obj");
	modelDartLegoRightLeg.setShader(&shaderMulLighting);
	////////////////////////////////////////////////////////////////
	/////////////////////Modelos navidad y animaciones//////////////
	////////////////////////////////////////////////////////////////
	/////////////////////
	/////eclipse car/////
	/////////////////////
	modelCar.loadModel("../models/Eclipse/2003eclipse_chasis.obj");
	modelCar.setShader(&shaderMulLighting);

	modelEclipseWheelsFrontal.loadModel("../models/Eclipse/2003eclipse_frontal_wheels.obj");
	modelEclipseWheelsFrontal.setShader(&shaderMulLighting);

	modelEclipseWheelsRear.loadModel("../models/Eclipse/2003eclipse_rear_wheels.obj");
	modelEclipseWheelsRear.setShader(&shaderMulLighting);

	/////////////////////
	/////Helicoptero/////
	/////////////////////
	modelHeliChasis.loadModel("../models/Helicopter/Mi_24_chasis.obj");
	modelHeliChasis.setShader(&shaderMulLighting);

	modelHeliHeliMeid.loadModel("../models/Helicopter/Mi_24_heli.obj");
	modelHeliHeliMeid.setShader(&shaderMulLighting);

	modelHeliHeliCh.loadModel("../models/Helicopter/Mi_24_heli2.obj");
	modelHeliHeliCh.setShader(&shaderMulLighting);
	/////////////////////
	/////Lambo car/////
	/////////////////////
	modelLambo.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_chasis.obj");
	modelLambo.setShader(&shaderMulLighting);
	modelLamboLeftDor.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_left_dor.obj");
	modelLamboLeftDor.setShader(&shaderMulLighting);
	modelLamboRightDoor.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborginhi_Aventador_door2.obj");
	modelLamboRightDoor.setShader(&shaderMulLighting);
	modelLamboFrontWheels.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborginhi_Aventador_wheels.obj");
	modelLamboFrontWheels.setShader(&shaderMulLighting);
	modelLamboBackWheels.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborginhi_Aventador_wheels2.obj");
	modelLamboBackWheels.setShader(&shaderMulLighting);


	/////////////////////
	/////Muebles/////////
	/////////////////////
	modelMueble.loadModel("../models/Wood_Table/\Wood_Table.obj");
	modelMueble.setShader(&shaderMulLighting);
	modelTable2.loadModel("../models/table/table.obj");
	modelTable2.setShader(&shaderMulLighting);
	modelSala.loadModel("../models/sofa/sofa.obj");
	modelSala.setShader(&shaderMulLighting);
	modelRosa.loadModel("../models/rosa/rosa.obj");
	modelRosa.setShader(&shaderMulLighting);
	modelMaceta.loadModel("../models/plantamaceta/plantamaceta.obj");
	modelMaceta.setShader(&shaderMulLighting);
	modelJardinera.loadModel("../models/jardinera/jardinera.obj");
	modelJardinera.setShader(&shaderMulLighting);
	modelSalap.loadModel("../models/sofap/sofap.obj");
	modelSalap.setShader(&shaderMulLighting);
	modelToilet.loadModel("../models/toilet/toilet.obj");
	modelToilet.setShader(&shaderMulLighting);
	modelHandWash.loadModel("../models/lavamanos/bathroom_vanity.obj");
	modelHandWash.setShader(&shaderMulLighting);
	modelLampara.loadModel("../models/lampara1/lampara.obj");
	modelLampara.setShader(&shaderMulLighting);
	modelBed.loadModel("../models/bed/bed2.obj");
	modelBed.setShader(&shaderMulLighting);
	modelMueble2.loadModel("../models/mesasala/Mesa.obj");
	modelMueble2.setShader(&shaderMulLighting);
	modelMuebleTV.loadModel("../models/pooltv/Pooltv.obj");
	modelMuebleTV.setShader(&shaderMulLighting);
	modelCloset.loadModel("../models/closet/closet.obj");
	modelCloset.setShader(&shaderMulLighting);
	modelKitchen.loadModel("../models/panelkonha/panelkonha1.obj");
	modelKitchen.setShader(&shaderMulLighting);
	modelRefrigerator.loadModel("../models/refrigerator/refrigerator.obj");
	modelRefrigerator.setShader(&shaderMulLighting);
	////////////////////////
	/////Decoración/////////
	////////////////////////
	modelCabine.loadModel("../models/cabine/cabine2.obj");
	modelCabine.setShader(&shaderMulLighting);
	modelTree.loadModel("../models/christmas_tree/Christmas+tree.obj");
	modelTree.setShader(&shaderMulLighting);
	modelStar.loadModel("../models/star_obj/gold_star.obj");
	modelStar.setShader(&shaderMulLighting);
	modelPiso.loadModel("../models/cabine/piso.obj");
	modelPiso.setShader(&shaderMulLighting);
	modelChBall1.loadModel("../models/Christmas_Bells_obj/ball1.obj");
	modelChBall1.setShader(&shaderMulLighting);
	modelChBall2.loadModel("../models/Christmas_Bells_obj/ball2.obj");
	modelChBall2.setShader(&shaderMulLighting);
	modelChBall3.loadModel("../models/Christmas_Bells_obj/ball3.obj");
	modelChBall3.setShader(&shaderMulLighting);
	modelChBall4.loadModel("../models/Christmas_Bells_obj/ball4.obj");
	modelChBall4.setShader(&shaderMulLighting);
	modelChBall5.loadModel("../models/Christmas_Bells_obj/ball5.obj");
	modelChBall5.setShader(&shaderMulLighting);
	modelRegalo1.loadModel("../models/regalos/regalo1.obj");
	modelRegalo1.setShader(&shaderMulLighting);
	modelRegalo2.loadModel("../models/regalos/regalo2.obj");
	modelRegalo2.setShader(&shaderMulLighting);
	modelRegalo3.loadModel("../models/regalos/regalo3.obj");
	modelRegalo3.setShader(&shaderMulLighting);
	modelCamello.loadModel("../models/jirafa/camel.obj");
	modelCamello.setShader(&shaderMulLighting);
	modelCow.loadModel("../models/cow/cow.obj");
	modelCow.setShader(&shaderMulLighting);
	modelDeer.loadModel("../models/deer/deer.obj");
	modelDeer.setShader(&shaderMulLighting);
	modelSheep.loadModel("../models/sheep2/sheep2.obj");
	modelSheep.setShader(&shaderMulLighting);
	modelChicken.loadModel("../models/chicken/chicken.obj");
	modelChicken.setShader(&shaderMulLighting);
	snowMan.loadModel("../models/SnowMan/SnowMan.obj");
	snowMan.setShader(&shaderMulLighting);
	modelTrineo.loadModel("../models/trineo/trineo.obj");
	modelTrineo.setShader(&shaderMulLighting);
	modelNocheBuena.loadModel("../models/nochebuena/nochebuena.obj");
	modelNocheBuena.setShader(&shaderMulLighting);
	modelBaston.loadModel("../models/baston/baston1.obj");
	modelBaston.setShader(&shaderMulLighting);
	modelCoronaDecoracion.loadModel("../models/wreath/wreath.obj");
	modelCoronaDecoracion.setShader(&shaderMulLighting);
	modelPinata.loadModel("../models/pinata/pinata.obj");
	modelPinata.setShader(&shaderMulLighting);

	camera->setPosition(glm::vec3(0.0, 2.8, 25.0));
	camera->setSensitivity(1);

	camera_halloween->setPosition(glm::vec3(-26, 2.8, 25.0));
	camera_halloween->setSensitivity(1);

	camara_nacimiento->setPosition(glm::vec3(2.0, 2.8, 0.0));
	camara_nacimiento->setFront(glm::vec3(0.0, 0.0, 1.0));


	camara_ofrenda->setPosition(glm::vec3(-25, 2.3, 9.0));


	// Descomentar
	// Definimos el tamanio de la imagen
	int imageWidth, imageHeight;
	// Definiendo la textura a utilizar
	Texture texture1("../Textures/sponge.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	FIBITMAP* bitmap = texture1.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	unsigned char* data = texture1.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID1G);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID1G);
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
	Texture texture2G("../Textures/pavimento.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = texture2G.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture2G.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID2G);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID2G);
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
	texture2G.freeImage(bitmap);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definiendo la textura a utilizar
	Texture texture2("../Textures/piedra.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture2.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture2.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID2G);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID2G);
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
	texture2.freeImage(bitmap);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definiendo la textura a utilizar
	Texture texture7G("../Textures/window2.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture7G.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture7G.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID7G);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID7G);
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
	texture7G.freeImage(bitmap);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definiendo la textura a utilizar
	Texture texture8G("../Textures/door2.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture8G.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture8G.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID8G);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID8G);
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
	texture8G.freeImage(bitmap);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definiendo la textura a utilizar
	Texture texture9G("../Textures/door2.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture9G.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture9G.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID9G);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID9G);
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
	texture9G.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureflor("../Textures/flor.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureflor.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureflor.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureflorID1);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureflorID1);
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
	texture9G.freeImage(bitmap);


	Texture texture20G("../Textures/marco.jpg");
	//Carga el mapa de bits(Es el tipo de dato de la libreria)
	///Esto para voltear mi imagen
	bitmap = texture20G.loadImage(true);
	//convertimos el mapa de bits en un arreglo unidimensional de tipo unseigned char
	data = texture20G.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 5
	glGenTextures(1, &textureID20M);
	//enlazar ese ID o textura a un tipo de textura de 2D
	glBindTexture(GL_TEXTURE_2D, textureID20M);
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
	texture20G.freeImage(bitmap);
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
	texturePicado.freeImage(bitmap);
	/////////Vela
	// Definiendo la textura a utilizar
	Texture texturev2("../Textures/vela.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = texturev2.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texturev2.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureIDv2);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureIDv2);
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
	texturePicadoM.freeImage(bitmap);
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
	texturePicadoV.freeImage(bitmap);

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
	texturePicadoR.freeImage(bitmap);

	////////////////////////////////////////////////
	////////////Texturas casa navidad///////////////
	////////////////////////////////////////////////



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
	Texture texture5("../Textures/duela.jpg");
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

	Texture texture6("../Textures/madera_cherry.jpg");
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

	Texture texture7("../Textures/cortina.jpg");
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
	Texture texture8("../Textures/Netflix.jpg");
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

	Texture texture9("../Textures/madera.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture9.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture6.convertToData(bitmap, imageWidth, imageHeight);
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

	Texture texture10("../Textures/pared1.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture10.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture6.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID10);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID10);
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
	texture10.freeImage(bitmap);

	Texture texture11("../Textures/colcha.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture11.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture6.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID11);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID11);
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
	texture11.freeImage(bitmap);

	Texture texture12("../Textures/almohada.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture12.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture12.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID12);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID12);
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
	texture12.freeImage(bitmap);

	Texture texture13("../Textures/zaguan.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture13.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture13.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID13);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID13);
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
	texture13.freeImage(bitmap);

	Texture texture14("../Textures/puerta_sala.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture14.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture14.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID14);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID14);
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
	texture14.freeImage(bitmap);

	Texture texture15("../Textures/probando.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture15.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture15.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID15);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID15);
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
	texture15.freeImage(bitmap);

	Texture texture16("../Textures/ventanal_arriba.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture16.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture16.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID16);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID16);
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
	texture16.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture17("../Textures/cesped.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture17.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture17.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID17);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID17);
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
	texture17.freeImage(bitmap);

	Texture texture18("../Textures/carretera.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture18.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture18.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID18);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID18);
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
	texture18.freeImage(bitmap);

	Texture texture19("../Textures/pared_naranja.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture19.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture19.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID19);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID19);
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
	texture19.freeImage(bitmap);

	Texture texture20("../Textures/pared_azul.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture20.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture20.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID20);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID20);
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
	texture20.freeImage(bitmap);

	Texture texture21("../Textures/piso_piedra.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture21.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture21.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID21);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID21);
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
	texture21.freeImage(bitmap);

	Texture texture22("../Textures/piso_gris.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture22.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture22.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID22);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID22);
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
	texture22.freeImage(bitmap);

	Texture texture23("../Textures/maria.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture23.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture23.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID23);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID23);
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
	texture23.freeImage(bitmap);

	Texture texture24("../Textures/jose.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture24.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture24.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID24);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID24);
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
	texture24.freeImage(bitmap);

	Texture texture25("../Textures/bebe.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture25.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture25.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID25);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID25);
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
	texture25.freeImage(bitmap);

	Texture texture26("../Textures/reyes.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture26.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture26.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID26);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID26);
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
	texture26.freeImage(bitmap);

	Texture texture27("../Textures/bebe.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture27.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture27.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID27);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID27);
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
	texture27.freeImage(bitmap);

	////////////////////////////////////////
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
		FIBITMAP* bitmap = skyboxTexture.loadImage(true);
		unsigned char* data = skyboxTexture.convertToData(bitmap, imageWidth,
			imageHeight);
		if (data) {
			glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0,
				GL_BGRA, GL_UNSIGNED_BYTE, data);
		}
		else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage(bitmap);
	}

	// OpenAL init
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // Limpiamos los errores previos de OpenAL
	if (alGetError() != AL_NO_ERROR) {
		printf("Error al crear los buffers");
		exit(1);
	}
	else
		printf("Se crearon los buffers");

	alGenBuffers(NUM_BUFFERS, buffers);
	buffers[0] = alutCreateBufferFromFile("../sounds/Summer_OvertureM.wav");
	buffers[1] = alutCreateBufferFromFile("../sounds/LesDeuxPianosM.wav");

	int errorAlut = alutGetError();

	if (errorAlut != ALUT_ERROR_NO_ERROR) {
		printf("Error al crear los buffers %d", errorAlut);
		exit(2);
	}
	else
		printf("Se crearon los buffers");

	glGetError();
	alGenSources(NUM_SOURCES, sources);

	if (alutGetError() != AL_NO_ERROR) {
		printf("Error al crear las fuentes de sonidos");
		exit(2);
	}
	else
		printf("Se crearon las fuentes de sonido");


	alSourcef(sources[0], AL_PITCH, 1.0f);
	alSourcef(sources[0], AL_GAIN, 2.0f);
	alSourcefv(sources[0], AL_VELOCITY, source0Vel);
	alSourcefv(sources[0], AL_POSITION, source0Pos);
	alSourcei(sources[0], AL_BUFFER, buffers[0]);
	alSourcei(sources[0], AL_LOOPING, AL_TRUE);
	alSourcei(sources[0], AL_MAX_DISTANCE, 10);

	alSourcef(sources[1], AL_PITCH, 1.0f);
	alSourcef(sources[1], AL_GAIN, 2.0f);
	alSourcefv(sources[1], AL_VELOCITY, source0Vel);
	alSourcefv(sources[1], AL_POSITION, source0Pos);
	alSourcei(sources[1], AL_BUFFER, buffers[0]);
	alSourcei(sources[1], AL_LOOPING, AL_TRUE);
	alSourcei(sources[1], AL_MAX_DISTANCE, 10);
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

	boxParedes.destroy();
	shader.destroy();
	shaderColorLighting.destroy();
	shaderMaterialLighting.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTexture.destroy();
	shaderTextureLighting.destroy();

	modelCar.destroy();
	modelEclipseWheelsFrontal.destroy();
	modelEclipseWheelsRear.destroy();

	modelHeliChasis.destroy();
	modelHeliHeliMeid.destroy();
	modelHeliHeliCh.destroy();

	modelLambo.destroy();
	modelLamboLeftDor.destroy();
	modelLamboRightDoor.destroy();
	modelLamboBackWheels.destroy();
	modelLamboFrontWheels.destroy();

	modelMueble.destroy();
	modelMueble2.destroy();
	modelSala.destroy();
	modelRosa.destroy();
	modelMaceta.destroy();
	modelJardinera.destroy();
	modelLampara.destroy();
	modelSalap.destroy();
	modelToilet.destroy();
	modelTable.destroy();
	modelTable2.destroy();
	modelHandWash.destroy();
	modelKitchen.destroy();
	modelBed.destroy();
	modelRefrigerator.destroy();
	modelMuebleTV.destroy();
	modelTV.destroy();
	modelCloset.destroy();

	modelTree.destroy();
	modelStar.destroy();
	modelCabine.destroy();
	modelElefante.destroy();
	modelCamello.destroy();
	modelCow.destroy();
	modelDeer.destroy();
	modelSheep.destroy();
	modelChicken.destroy();

	modelChBall1.destroy();
	modelChBall2.destroy();
	modelChBall3.destroy();
	modelChBall4.destroy();
	modelChBall5.destroy();

	modelCoronaDecoracion.destroy();
	modelNocheBuena.destroy();
	modelBaston.destroy();
	modelRegalo1.destroy();
	modelRegalo2.destroy();
	modelRegalo3.destroy();
	snowMan.destroy();
	modelTrineo.destroy();
	modelPinata.destroy();
	modelPiso.destroy();
	modelSantaHat.destroy();


	modelRock.destroy();
	modelApple.destroy();
	modelBanana.destroy();
	modelCouch.destroy();
	modelLamp.destroy();

	modelOrange.destroy();
	modelPM.destroy();
	modelTable.destroy();
	modelChimney.destroy();
	sofa.destroy();
	modelCalabaza.destroy();

	// Dart Lego
	modelDartLegoBody.destroy();
	modelDartLegoMask.destroy();
	modelDartLegoHead.destroy();
	modelDartLegoLeftArm.destroy();
	modelDartLegoRightArm.destroy();
	modelDartLegoLeftHand.destroy();
	modelDartLegoRightHand.destroy();
	modelDartLegoLeftLeg.destroy();
	modelDartLegoRightLeg.destroy();
}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
	int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
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
	if (numberCamera == 1) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->moveFrontCamera(true, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->moveFrontCamera(false, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->moveRightCamera(false, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->moveRightCamera(true, deltaTime);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			camera->mouseMoveCamera(offsetX, offsetY, deltaTime);
	}
	if (numberCamera == 2) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera_halloween->moveFrontCamera(true, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera_halloween->moveFrontCamera(false, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera_halloween->moveRightCamera(false, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera_halloween->moveRightCamera(true, deltaTime);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			camera_halloween->mouseMoveCamera(offsetX, offsetY, deltaTime);
	}
	offsetX = 0;
	offsetY = 0;

	// Seleccionar modelo
	if (enableCountSelected && glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
		enableCountSelected = false;
		modelSelected++;
		if (modelSelected > 2)
			modelSelected = 0;
		if (modelSelected == 1)
			fileName = "../animaciones/animation_rotation.txt";
		if (modelSelected == 2)
			fileName = "../animaciones/animation_dart.txt";
		std::cout << "modelSelected:" << modelSelected << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
		enableCountSelected = true;

	// Guardar key frames
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		record = true;
		if (myfile.is_open())
			myfile.close();
		myfile.open(fileName);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE
		&& glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		record = false;
		myfile.close();
		if (modelSelected == 1)
			keyFramesJoints = getKeyRotFrames(fileName);
		if (modelSelected == 2)
			keyFramesDart = getKeyFrames(fileName);
	}
	if (availableSave && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		saveFrame = true;
		availableSave = false;
	}if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE)
		availableSave = true;

	// Condiciones para Mover el modelo del bob sponja
	if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rot1 += 0.01;
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rot1 -= 0.01;
	if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rot2 += 0.01;
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rot2 -= 0.01;
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rot3 += 0.01;
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rot3 -= 0.01;
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rot4 += 0.01;
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rot4 -= 0.01;

	if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot0 = 0.1;
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot0 = -0.1;
	if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		dz = 0.1;
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		dz = -0.1;

	// Dart Lego model movements
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rotDartHead += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rotDartHead -= 0.02;

	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rotDartLeftArm += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rotDartLeftArm -= 0.02;

	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rotDartRightArm += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rotDartRightArm -= 0.02;

	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rotDartLeftHand += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rotDartLeftHand -= 0.02;

	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		rotDartRightHand += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		rotDartRightHand -= 0.02;

	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		rotDartLeftLeg += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		rotDartLeftLeg -= 0.02;

	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		rotDartRightLeg += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		rotDartRightLeg -= 0.02;

	if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotDartBody = 0.02;
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotDartBody = -0.02;
	if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		advanceDartBody = -0.02;
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		advanceDartBody = 0.02;

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		alSourcePlay(sources[0]);
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		alSourcePlay(sources[1]);

	//camara libre navidad
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		numberCamera = 1 ;
	//camara libre halloween
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		numberCamera = 2;
	//camara fija halloween
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		numberCamera = 4;
	//camara fija navidad
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		numberCamera = 3;
	
	//evento que me permite saber la posicion de la camara, para obtener las posiciones de las luces puntuales de la casa halloween
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && numberCamera == 2) {
		//std::cout << "(" << camera_halloween->getPosition().x << " , " << camera_halloween->getPosition().y << " , " << camera_halloween->getPosition().z << " )" << std::endl;
		muestraPosicion = true;
	}


	glfwPollEvents();
	return continueApplication;
}

bool camera_is_in(float x1, float x2, float y1, float y2, float z1, float z2) {
	float x, y, z;
	x = camera->getPosition().x;
	y = camera->getPosition().y;
	z = camera->getPosition().z;
	return x > x1 and x < x2 and y > y1 and y < y2 and z > z1 and z < z2;

}

void applicationLoop() {
	bool psi = true;

	glm::mat4 modelMatrixHeli = glm::mat4(1.0f);

	glm::mat4 modelMatrixDart = glm::mat4(1.0f);
	modelMatrixDart = glm::translate(modelMatrixDart, glm::vec3(-33, -2.5, 20.0));
	modelMatrixDart = glm::scale(modelMatrixDart, glm::vec3(0.5, 0.5, 0.5));

	// Variables to interpolation key frames
	fileName = "../animaciones/animation_dart_joints.txt";
	keyFramesJoints = getKeyRotFrames(fileName);
	keyFramesDart = getKeyFrames("../animaciones/animation_dart.txt");

	lastTime = TimeManager::Instance().GetTime();

	//*********** Varibles para calcular distancias entre objetos y la camara ***************************************************//
	float distanciaCamaraHalloweenFoco1 = 4.0, distanciaCamaraHalloweenFoco2 = 4.0, distanciaCamaraHalloweenFoco3 = 4.0;

	//////////////////aqui empieza lo mio////////////

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 model2 = glm::mat4(1.0f);
	float offX = 0.0;
	float angle = 0.0;
	float ratio = 30.0;
	float rotHeliHeliy = 0.0;
	float rotHeliHeliz = 0.0;
	float rotWheelx = 0.0;
	float rotWheely = 0.0;
	float rotWheelLamboX = 0.0;
	float rotWheelLamboY = 0.0;
	float dorRotCount = 0.0;
	int stateDoor = 0;

	glm::mat4 matrixModelAircraft = glm::mat4(1.0);
	matrixModelAircraft = glm::translate(matrixModelAircraft, glm::vec3(8.0, 2.0, -10.0));
	glm::mat4 matrixModelCar = glm::mat4(1.0);
	matrixModelCar = glm::translate(matrixModelCar, glm::vec3(-10, -1.6, -12.0));
	matrixModelCar = glm::scale(matrixModelCar, glm::vec3(0.65, 0.65, 0.65));

	glm::mat4 modelMatrixLambo = glm::mat4(1.0);
	modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(-15.0, -1.6, -15.0));
	modelMatrixLambo = glm::scale(modelMatrixLambo, glm::vec3(2.0, 2.0, 2.0));

	glm::mat4 modelMatrixHeliChasis = glm::mat4(1.0);
	modelMatrixHeliChasis = glm::translate(modelMatrixHeliChasis, glm::vec3(20, 20, 0));

	glm::mat4 matrixModelRegalo1 = glm::mat4(1.0);
	matrixModelRegalo1 = glm::translate(matrixModelRegalo1, glm::vec3(-4.5, 2.4, 3.5));

	glm::mat4 matrixModelRegalo2 = glm::mat4(1.0);
	matrixModelRegalo2 = glm::translate(matrixModelRegalo2, glm::vec3(-3.2, 2.4, 3.5));
	matrixModelRegalo2 = glm::rotate(matrixModelRegalo2, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 matrixModelRegalo3 = glm::mat4(1.0);
	matrixModelRegalo3 = glm::translate(matrixModelRegalo3, glm::vec3(-2.5, 2.6, 4.5));



	int state = 0;
	int stateheli = 0;

	float offsetAircraftAdvance = 0.0;
	float  offsetLamboAdvance = 0.0;
	float offsetLamboRot = 0.0;
	float offsetAircraftRot = 0.0;

	float offsetHeliAdvance = 0.0;

	float offsetRegalo1 = 0.0;

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if (currTime - lastTime < 0.00016666667) {
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		// Variables donde se guardan las matrices de cada articulacion por 1 frame
		std::vector<float> matrixJoints;
		std::vector<glm::mat4> matrixDart;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.01f, 100.0f);

		if (numberCamera == 1) {
			glm::mat4 view = camera->getViewMatrix();

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
			shaderMulLighting.setInt("spotLightCount", 2);
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
		}

		if (numberCamera == 2) {
			glm::mat4 view = camera_halloween->getViewMatrix();

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
				glm::value_ptr(camera_halloween->getPosition()));
			shaderColorLighting.setVectorFloat3("light.ambient",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderColorLighting.setVectorFloat3("light.diffuse",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderColorLighting.setVectorFloat3("light.specular",
				glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

			// Propiedades de la luz para objetos con textura
			shaderTextureLighting.setVectorFloat3("viewPos",
				glm::value_ptr(camera_halloween->getPosition()));
			shaderTextureLighting.setVectorFloat3("light.ambient",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderTextureLighting.setVectorFloat3("light.diffuse",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderTextureLighting.setVectorFloat3("light.specular",
				glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

			// Propiedades de la luz para objetos con textura
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(camera_halloween->getPosition()));
			shaderMaterialLighting.setVectorFloat3("light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderMaterialLighting.setVectorFloat3("light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
			shaderMaterialLighting.setVectorFloat3("light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));

			// Propiedades de la luz para objetos con multiples luces
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera_halloween->getPosition()));
			shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
			shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));
			// Esto es para la luz spotlight
			shaderMulLighting.setInt("spotLightCount", 2);
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(camera_halloween->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(camera_halloween->getFront()));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.01, 0.01, 0.01)));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
			shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5)));
			shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0)));
			shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
			shaderMulLighting.setFloat("spotLights[0].linear", 0.1);
			shaderMulLighting.setFloat("spotLights[0].quadratic", 0.001);
		}

		if (numberCamera == 3) {
			glm::mat4 view = camara_nacimiento->getViewMatrix();

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
				glm::value_ptr(camara_nacimiento->getPosition()));
			shaderColorLighting.setVectorFloat3("light.ambient",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderColorLighting.setVectorFloat3("light.diffuse",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderColorLighting.setVectorFloat3("light.specular",
				glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

			// Propiedades de la luz para objetos con textura
			shaderTextureLighting.setVectorFloat3("viewPos",
				glm::value_ptr(camara_nacimiento->getPosition()));
			shaderTextureLighting.setVectorFloat3("light.ambient",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderTextureLighting.setVectorFloat3("light.diffuse",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderTextureLighting.setVectorFloat3("light.specular",
				glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

			// Propiedades de la luz para objetos con textura
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(camara_nacimiento->getPosition()));
			shaderMaterialLighting.setVectorFloat3("light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderMaterialLighting.setVectorFloat3("light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
			shaderMaterialLighting.setVectorFloat3("light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));

			// Propiedades de la luz para objetos con multiples luces
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camara_nacimiento->getPosition()));
			shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
			shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));
			// Esto es para la luz spotlight
			shaderMulLighting.setInt("spotLightCount", 2);
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(camara_nacimiento->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(camara_nacimiento->getFront()));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.01, 0.01, 0.01)));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
			shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5)));
			shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0)));
			shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
			shaderMulLighting.setFloat("spotLights[0].linear", 0.1);
			shaderMulLighting.setFloat("spotLights[0].quadratic", 0.001);
		}

		if (numberCamera == 4) {
			glm::mat4 view = camara_ofrenda->getViewMatrix();

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
				glm::value_ptr(camara_ofrenda->getPosition()));
			shaderColorLighting.setVectorFloat3("light.ambient",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderColorLighting.setVectorFloat3("light.diffuse",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderColorLighting.setVectorFloat3("light.specular",
				glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

			// Propiedades de la luz para objetos con textura
			shaderTextureLighting.setVectorFloat3("viewPos",
				glm::value_ptr(camara_ofrenda->getPosition()));
			shaderTextureLighting.setVectorFloat3("light.ambient",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderTextureLighting.setVectorFloat3("light.diffuse",
				glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderTextureLighting.setVectorFloat3("light.specular",
				glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

			// Propiedades de la luz para objetos con textura
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(camara_ofrenda->getPosition()));
			shaderMaterialLighting.setVectorFloat3("light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderMaterialLighting.setVectorFloat3("light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
			shaderMaterialLighting.setVectorFloat3("light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));

			// Propiedades de la luz para objetos con multiples luces
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camara_ofrenda->getPosition()));
			shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
			shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
			shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));
			// Esto es para la luz spotlight
			shaderMulLighting.setInt("spotLightCount", 2);
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(camara_ofrenda->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(camara_ofrenda->getFront()));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.01, 0.01, 0.01)));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
			shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5)));
			shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0)));
			shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
			shaderMulLighting.setFloat("spotLights[0].linear", 0.1);
			shaderMulLighting.setFloat("spotLights[0].quadratic", 0.001);
		}

		shaderMulLighting.setVectorFloat3("spotLights[1].position", glm::value_ptr(glm::vec3(3.0, 8.0, 3.0)));
		shaderMulLighting.setVectorFloat3("spotLights[1].direction", glm::value_ptr(glm::vec3(0.0, -1.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[1].light.ambient", glm::value_ptr(glm::vec3(0.01, 0.01, 0.01)));
		shaderMulLighting.setVectorFloat3("spotLights[1].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("spotLights[1].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
		shaderMulLighting.setFloat("spotLights[1].cutOff", cos(glm::radians(12.5)));
		shaderMulLighting.setFloat("spotLights[1].outerCutOff", cos(glm::radians(15.0)));
		shaderMulLighting.setFloat("spotLights[1].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[1].linear", 0.1);
		shaderMulLighting.setFloat("spotLights[1].quadratic", 0.001);

		// Esto es para la luces pointlights(Actuan como si fueran un foco)
		// Numero de luces a utiliozar de tipo pointLights  = 3
		shaderMulLighting.setInt("pointLightCount", 25);//se agrego tres luces mas para la casa de halloween (antes 22)

		shaderMulLighting.setVectorFloat3("pointLights[0].position", glm::value_ptr((glm::vec3(-3.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[0].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[0].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[0].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[0].linear", offset1);
		shaderMulLighting.setFloat("pointLights[0].quadratic", 0.004);

		shaderMulLighting.setVectorFloat3("pointLights[1].position", glm::value_ptr((glm::vec3(-4.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[1].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[1].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));
		shaderMulLighting.setVectorFloat3("pointLights[1].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
		shaderMulLighting.setFloat("pointLights[1].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[1].linear", offset2);
		shaderMulLighting.setFloat("pointLights[1].quadratic", 0.004);

		//luz azul
		shaderMulLighting.setVectorFloat3("pointLights[2].position", glm::value_ptr((glm::vec3(-5.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[2].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[2].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[2].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
		shaderMulLighting.setFloat("pointLights[2].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[2].linear", offset3);
		shaderMulLighting.setFloat("pointLights[2].quadratic", 0.004);

		//luz extra amarilla
		shaderMulLighting.setVectorFloat3("pointLights[3].position", glm::value_ptr((glm::vec3(-2.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[3].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[3].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[3].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[3].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[3].linear", offset4);
		shaderMulLighting.setFloat("pointLights[3].quadratic", 0.004);

		shaderMulLighting.setVectorFloat3("pointLights[4].position", glm::value_ptr((glm::vec3(-1.1, 1.8, 7.0))));
		shaderMulLighting.setVectorFloat3("pointLights[4].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[4].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[4].light.specular", glm::value_ptr(glm::vec3(0.34, 0.13, 0.39)));
		shaderMulLighting.setFloat("pointLights[4].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[4].linear", offset5);
		shaderMulLighting.setFloat("pointLights[4].quadratic", 0.004);

		//luz del baño
		shaderMulLighting.setVectorFloat3("pointLights[5].position", glm::value_ptr((glm::vec3(-1.0, 1.3, -2.5))));
		shaderMulLighting.setVectorFloat3("pointLights[5].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[5].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[5].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[5].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[5].linear", onOffBanio);
		shaderMulLighting.setFloat("pointLights[5].quadratic", 0.004);

		//luz comedor
		shaderMulLighting.setVectorFloat3("pointLights[6].position", glm::value_ptr((glm::vec3(2.5, 1.12, -2.5))));
		shaderMulLighting.setVectorFloat3("pointLights[6].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[6].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[6].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[6].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[6].linear", onOffComedor);
		shaderMulLighting.setFloat("pointLights[6].quadratic", 0.004);


		//luz cocina
		shaderMulLighting.setVectorFloat3("pointLights[7].position", glm::value_ptr((glm::vec3(6.0, 1.12, -2.5))));
		shaderMulLighting.setVectorFloat3("pointLights[7].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[7].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[7].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[7].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[7].linear", onOffCocina);
		shaderMulLighting.setFloat("pointLights[7].quadratic", 0.004);

		//luces sala
		shaderMulLighting.setVectorFloat3("pointLights[8].position", glm::value_ptr((glm::vec3(0.0, 1.0, 3.0))));
		shaderMulLighting.setVectorFloat3("pointLights[8].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[8].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[8].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[8].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[8].linear", onOffSala);
		shaderMulLighting.setFloat("pointLights[8].quadratic", 0.004);

		shaderMulLighting.setVectorFloat3("pointLights[9].position", glm::value_ptr((glm::vec3(2.0, 1.0, 3.0))));
		shaderMulLighting.setVectorFloat3("pointLights[9].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[9].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[9].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[9].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[9].linear", onOffSala);
		shaderMulLighting.setFloat("pointLights[9].quadratic", 0.004);

		//luz recamara abajo
		shaderMulLighting.setVectorFloat3("pointLights[10].position", glm::value_ptr((glm::vec3(7.5, 1.0, 4.0))));
		shaderMulLighting.setVectorFloat3("pointLights[10].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[10].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[10].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[10].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[10].linear", onOffRecamara1);
		shaderMulLighting.setFloat("pointLights[10].quadratic", 0.004);

		//luz recamara 1
		shaderMulLighting.setVectorFloat3("pointLights[11].position", glm::value_ptr((glm::vec3(7.5, 4.65, 4.0))));
		shaderMulLighting.setVectorFloat3("pointLights[11].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[11].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[11].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[11].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[11].linear", onOffRecamara2);
		shaderMulLighting.setFloat("pointLights[11].quadratic", 0.004);

		//luz recamara 2
		shaderMulLighting.setVectorFloat3("pointLights[12].position", glm::value_ptr((glm::vec3(7.5, 4.65, -2.5))));
		shaderMulLighting.setVectorFloat3("pointLights[12].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[12].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[12].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[12].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[12].linear", onOffRecamara3);
		shaderMulLighting.setFloat("pointLights[12].quadratic", 0.004);

		//luz estrella
		shaderMulLighting.setVectorFloat3("pointLights[13].position", glm::value_ptr((glm::vec3(-4.1, 4.5, 5.0))));
		shaderMulLighting.setVectorFloat3("pointLights[13].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[13].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[13].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[13].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[13].linear", offset1);
		shaderMulLighting.setFloat("pointLights[13].quadratic", 0.004);

		shaderMulLighting.setVectorFloat3("pointLights[14].position", glm::value_ptr((glm::vec3(-4.1, 2.8, 5.0))));
		shaderMulLighting.setVectorFloat3("pointLights[14].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[14].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[14].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[14].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[14].linear", offset2);
		shaderMulLighting.setFloat("pointLights[14].quadratic", 0.004);

		// Posicion de la luz indice [15]
		shaderMulLighting.setVectorFloat3("pointLights[15].position", glm::value_ptr((glm::vec3(-5.1 - 30, 4.5, -3.5))));
		// Utiliza lo mismo para la luz Roja
		shaderMulLighting.setVectorFloat3("pointLights[15].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[15].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[15].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[15].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[15].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[15].quadratic", 0.004);

		// Utiliza lo mismo para la luz Roja
		shaderMulLighting.setVectorFloat3("pointLights[16].position", glm::value_ptr((glm::vec3(9.1 - 30, 1.1, 10.1))));
		shaderMulLighting.setVectorFloat3("pointLights[16].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[16].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.00, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[16].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
		shaderMulLighting.setFloat("pointLights[16].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[16].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[16].quadratic", 0.004);

		// Utiliza lo mismo para la luz Azul
		shaderMulLighting.setVectorFloat3("pointLights[17].position", glm::value_ptr((glm::vec3(2.1 - 30, 1.1, 10.1))));
		shaderMulLighting.setVectorFloat3("pointLights[17].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[17].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[17].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
		shaderMulLighting.setFloat("pointLights[17].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[17].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[17].quadratic", 0.004);
		////////////////////////////////////////////////////Amarillo///////////////////////////////////////////////////////////////////////
		shaderMulLighting.setVectorFloat3("pointLights[18].position", glm::value_ptr((glm::vec3(9.1 - 30, 1.1, 1.1))));
		shaderMulLighting.setVectorFloat3("pointLights[18].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[18].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[18].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[18].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[18].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[18].quadratic", 0.004);

		////////////////////////////////////////////////////Amarillo 2///////////////////////////////////////////////////////////////////////
		shaderMulLighting.setVectorFloat3("pointLights[19].position", glm::value_ptr((glm::vec3(2.1 - 30, 1.1, 6.1))));
		shaderMulLighting.setVectorFloat3("pointLights[19].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[19].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[19].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
		shaderMulLighting.setFloat("pointLights[19].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[19].linear", 0.04);
		shaderMulLighting.setFloat("pointLights[19].quadratic", 0.004);


		//luz habitacion arbol
		shaderMulLighting.setVectorFloat3("pointLights[20].position", glm::value_ptr((glm::vec3(-1.5, 4.65, 0.0))));
		shaderMulLighting.setVectorFloat3("pointLights[20].position", glm::value_ptr((glm::vec3(-1.5, 4.65, 0.0))));
		shaderMulLighting.setVectorFloat3("pointLights[20].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[20].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[20].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[20].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[20].linear", onOffHabitacionArbol);
		shaderMulLighting.setFloat("pointLights[20].quadratic", 0.004);

		//luz cochera
		shaderMulLighting.setVectorFloat3("pointLights[21].position", glm::value_ptr((glm::vec3(-4.15, 1.0, 0.0))));
		shaderMulLighting.setVectorFloat3("pointLights[21].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[21].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[21].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[21].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[21].linear", onOffCochera);
		shaderMulLighting.setFloat("pointLights[21].quadratic", 0.004);

		//luz de la lampara 1, casa halloween
		shaderMulLighting.setVectorFloat3("pointLights[22].position", glm::value_ptr((glm::vec3(-26.23, 0.854434, 9.32244))));
		shaderMulLighting.setVectorFloat3("pointLights[22].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[22].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[22].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[22].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[22].linear", onOffLampara1);
		shaderMulLighting.setFloat("pointLights[22].quadratic", 0.004);

		//luz de la lampara 2, casa halloween
		shaderMulLighting.setVectorFloat3("pointLights[23].position", glm::value_ptr((glm::vec3(-21.3986, 0.789432, 3.8218))));
		shaderMulLighting.setVectorFloat3("pointLights[23].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[23].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[23].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[23].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[23].linear", onOffLampara2);
		shaderMulLighting.setFloat("pointLights[23].quadratic", 0.004);

		//luz de la lampara 3, casa halloween
		shaderMulLighting.setVectorFloat3("pointLights[24].position", glm::value_ptr((glm::vec3(-26.3791, 0.970396, 3.8465))));
		shaderMulLighting.setVectorFloat3("pointLights[24].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
		shaderMulLighting.setVectorFloat3("pointLights[24].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
		shaderMulLighting.setVectorFloat3("pointLights[24].light.specular", glm::value_ptr(glm::vec3(0.91, 0.92, 0.85)));
		shaderMulLighting.setFloat("pointLights[24].constant", 1.0);
		shaderMulLighting.setFloat("pointLights[24].linear", onOffLampara3);
		shaderMulLighting.setFloat("pointLights[24].quadratic", 0.004);

		//Esto es oara colocar las esferas de las luces
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(-5.1 - 30, 2.5, -3.5));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(-5.1 - 30, 2.8, -5.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		////////////////////////////////////////////////////////////////////////////Luces dentro de la casa//////////////////////////////////
		///Amarillo
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(6.95 - 30, 1.7, 4.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		///Amarillo 2
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(6.95 - 29, 1.7, 4.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		///Amarillo 3
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(2.0 - 30, 0.0, 10.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		///Amarillo 4
		sphereLamp.setScale(glm::vec3(0.1, 0.1, 0.2));
		sphereLamp.setPosition(glm::vec3(9.0 - 30, 0.0, 10.0));
		sphereLamp.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-6.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(4.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(5.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(6.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(7.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(8.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(9.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.0, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.1, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.2, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.3, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.4, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.5, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.6, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.7, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.8, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(10.9, 1.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 6.5));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		/////////////////////////////////////////////////
		////////////////////Serie arriba izq/////////////////
		/////////////////////////////////////////////////

		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 6.5));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 6.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 6.3));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 6.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 6.1));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 6.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.9));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.8));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.6));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.5));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.3));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.2));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.1));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.9));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.6));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.5));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.3));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.1));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 4.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.9));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.8));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.6));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.5));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.3));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.2));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.1));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 3.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.9));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.6));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.5));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.3));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.1));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 2.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.9));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.8));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.6));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.5));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.3));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.2));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.1));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 1.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.9));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.6));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.5));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.3));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.1));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 0.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -0.1));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -0.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -0.3));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -0.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -0.5));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -0.6));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -0.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -0.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -0.9));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.1));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.2));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.3));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.5));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.6));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.8));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -1.9));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.1));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.3));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.5));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.6));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -2.9));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.1));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.2));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.3));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.5));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.6));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.8));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -3.9));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.1));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.3));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.5));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.6));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -4.9));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -5.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -5.1));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -5.2));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -5.3));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -5.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///////////////Luces arribab enfrente///////////////
		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-6.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.0, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.1, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.2, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.3, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.4, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.5, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.6, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.7, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.8, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.9, 4.8, 5.7));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		///Luces superiores traseras

		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-6.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-5.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-4.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-3.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-2.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-1.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(-0.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(0.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(1.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(2.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.0, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.1, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.2, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.3, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.4, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.5, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.6, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.7, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.8, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		sphereLamp.setScale(glm::vec3(0.05, 0.07, 0.05));
		sphereLamp.setPosition(glm::vec3(3.9, 4.8, -5.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
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

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 matrixModelChimney = glm::mat4(1.0);
		matrixModelChimney = glm::translate(matrixModelChimney, glm::vec3(6.0 - 30, -1.0, 10.5));
		modelChimney.render(glm::scale(matrixModelChimney, glm::vec3(0.3, 0.3, 0.3)));


		glm::mat4 matrixModelpupitre = glm::mat4(1.0);
		matrixModelpupitre = glm::translate(matrixModelpupitre, glm::vec3(9.0 - 30, -1.0, 4.0));
		sofa.render(glm::scale(matrixModelpupitre, glm::vec3(0.2, 0.2, 0.2)));
		//// Modelo Sofa
		glm::mat4 matrixModelCouch = glm::mat4(1.0);
		matrixModelCouch = glm::translate(matrixModelCouch, glm::vec3(8.0 - 30, -1.0, 7.0));
		modelCouch.render(glm::scale(matrixModelCouch, glm::vec3(0.6, 0.6, 0.6)));
		////Modelo Lampara
		glm::mat4 matrixModelLamp = glm::mat4(1.0);
		matrixModelLamp = glm::translate(matrixModelLamp, glm::vec3(9.0 - 30, -1.0, 1.0));
		modelLamp.render(glm::scale(matrixModelLamp, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Lampara 2
		glm::mat4 matrixModelLamp2 = glm::mat4(1.0);
		matrixModelLamp2 = glm::translate(matrixModelLamp2, glm::vec3(2.0 - 30, -1.0, 6.0));
		modelLamp.render(glm::scale(matrixModelLamp2, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Lampara 3
		glm::mat4 matrixModelLamp3 = glm::mat4(1.0);
		matrixModelLamp3 = glm::translate(matrixModelLamp3, glm::vec3(2.0 - 30, -1.0, 10.0));
		modelLamp.render(glm::scale(matrixModelLamp3, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Lampara 4
		glm::mat4 matrixModelLamp4 = glm::mat4(1.0);
		matrixModelLamp4 = glm::translate(matrixModelLamp4, glm::vec3(9.0 - 30, -1.0, 10.0));
		modelLamp.render(glm::scale(matrixModelLamp4, glm::vec3(0.2, 0.2, 0.2)));
		///Escritorio
		glm::mat4 matrixModelEscritorio = glm::mat4(1.0);
		matrixModelEscritorio = glm::translate(matrixModelEscritorio, glm::vec3(3.0 - 30, 0.5, 2.0));
		modelCalabaza.render(glm::scale(matrixModelEscritorio, glm::vec3(1.6, 1.6, 1.6)));
		//////////////////////////////////////////////////////////////////////////////////////////////
		//// Modelo Sofa
		glm::mat4 matrixModelCouch2 = glm::mat4(1.0);
		matrixModelCouch2 = glm::translate(matrixModelCouch2, glm::vec3(6.0 - 30, 2.0, 10.0));
		modelCouch.render(glm::scale(matrixModelCouch2, glm::vec3(0.6, 0.6, 0.6)));
		////Modelo Lampara 5
		glm::mat4 matrixModelLamp5 = glm::mat4(1.0);
		matrixModelLamp5 = glm::translate(matrixModelLamp5, glm::vec3(9.0 - 30, 1.0, 10.0));
		modelLamp.render(glm::scale(matrixModelLamp5, glm::vec3(0.2, 0.2, 0.2)));
		/*																			Decoracion												*/
		///////////////////////////////////////////////////////////////////////////////Panes///////////////////////////////////////////////////////////////////////////77
		////Modelo Pan Muerto	
		glm::mat4 matrixModelPM2 = glm::mat4(1.0);
		matrixModelPM2 = glm::translate(matrixModelPM2, glm::vec3(2.0 - 30, 1.5, 2.7));
		modelPM.render(glm::scale(matrixModelPM2, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 2
		glm::mat4 matrixModelPM = glm::mat4(1.0);
		matrixModelPM = glm::translate(matrixModelPM, glm::vec3(2.5 - 30, 1.5, 2.7));
		modelPM.render(glm::scale(matrixModelPM, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 3
		glm::mat4 matrixModelPM3 = glm::mat4(1.0);
		matrixModelPM3 = glm::translate(matrixModelPM3, glm::vec3(3.0 - 30, 1.5, 2.7));
		modelPM.render(glm::scale(matrixModelPM3, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 4
		glm::mat4 matrixModelPM4 = glm::mat4(1.0);
		matrixModelPM4 = glm::translate(matrixModelPM4, glm::vec3(3.5 - 30, 1.5, 2.7));
		modelPM.render(glm::scale(matrixModelPM4, glm::vec3(0.2, 0.2, 0.2)));
		///
		////Modelo Pan Muerto 21
		glm::mat4 matrixModelPM21 = glm::mat4(1.0);
		matrixModelPM21 = glm::translate(matrixModelPM21, glm::vec3(2.3 - 30, 1.5, 3.3));
		modelPM.render(glm::scale(matrixModelPM21, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 31
		glm::mat4 matrixModelPM31 = glm::mat4(1.0);
		matrixModelPM31 = glm::translate(matrixModelPM31, glm::vec3(2.8 - 30, 1.5, 3.3));
		modelPM.render(glm::scale(matrixModelPM31, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 41
		glm::mat4 matrixModelPM41 = glm::mat4(1.0);
		matrixModelPM41 = glm::translate(matrixModelPM41, glm::vec3(3.3 - 30, 1.5, 3.3));
		modelPM.render(glm::scale(matrixModelPM41, glm::vec3(0.2, 0.2, 0.2)));
		///
		////Modelo Pan Muerto 22
		glm::mat4 matrixModelPM22 = glm::mat4(1.0);
		matrixModelPM22 = glm::translate(matrixModelPM22, glm::vec3(2.5 - 30, 1.5, 3.9));
		modelPM.render(glm::scale(matrixModelPM22, glm::vec3(0.2, 0.2, 0.2)));
		////Modelo Pan Muerto 32
		glm::mat4 matrixModelPM32 = glm::mat4(1.0);
		matrixModelPM32 = glm::translate(matrixModelPM32, glm::vec3(3.0 - 30, 1.5, 3.9));
		modelPM.render(glm::scale(matrixModelPM32, glm::vec3(0.2, 0.2, 0.2)));
		///
		////Modelo Pan Muerto 23
		glm::mat4 matrixModelPM23 = glm::mat4(1.0);
		matrixModelPM23 = glm::translate(matrixModelPM23, glm::vec3(2.8 - 30, 1.5, 4.5));
		modelPM.render(glm::scale(matrixModelPM23, glm::vec3(0.2, 0.2, 0.2)));

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
		////Modelo apple
		glm::mat4 matrixModelApple = glm::mat4(1.0);
		matrixModelApple = glm::translate(matrixModelApple, glm::vec3(4.6 - 30, 1.63, 2.7));
		modelApple.render(glm::scale(matrixModelApple, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 2
		glm::mat4 matrixModelApple1 = glm::mat4(1.0);
		matrixModelApple1 = glm::translate(matrixModelApple1, glm::vec3(5.0 - 30, 1.63, 2.7));
		modelApple.render(glm::scale(matrixModelApple1, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 3
		glm::mat4 matrixModelApple3 = glm::mat4(1.0);
		matrixModelApple3 = glm::translate(matrixModelApple3, glm::vec3(5.4 - 30, 1.63, 2.7));
		modelApple.render(glm::scale(matrixModelApple3, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 4
		glm::mat4 matrixModelApple4 = glm::mat4(1.0);
		matrixModelApple4 = glm::translate(matrixModelApple4, glm::vec3(5.8 - 30, 1.63, 2.7));
		modelApple.render(glm::scale(matrixModelApple4, glm::vec3(0.13, 0.13, 0.13)));
		///
				////Modelo apple
		glm::mat4 matrixModelApple11 = glm::mat4(1.0);
		matrixModelApple11 = glm::translate(matrixModelApple11, glm::vec3(4.8 - 30, 1.63, 3.1));
		modelApple.render(glm::scale(matrixModelApple11, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 21
		glm::mat4 matrixModelApple21 = glm::mat4(1.0);
		matrixModelApple21 = glm::translate(matrixModelApple21, glm::vec3(5.2 - 30, 1.63, 3.1));
		modelApple.render(glm::scale(matrixModelApple21, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 3
		glm::mat4 matrixModelApple31 = glm::mat4(1.0);
		matrixModelApple31 = glm::translate(matrixModelApple31, glm::vec3(5.6 - 30, 1.63, 3.1));
		modelApple.render(glm::scale(matrixModelApple31, glm::vec3(0.13, 0.13, 0.13)));
		///
				////Modelo apple
		glm::mat4 matrixModelApple12 = glm::mat4(1.0);
		matrixModelApple12 = glm::translate(matrixModelApple12, glm::vec3(5.0 - 30, 1.63, 3.4));
		modelApple.render(glm::scale(matrixModelApple12, glm::vec3(0.13, 0.13, 0.13)));
		////Modelo Apple 21
		glm::mat4 matrixModelApple22 = glm::mat4(1.0);
		matrixModelApple22 = glm::translate(matrixModelApple22, glm::vec3(5.4 - 30, 1.63, 3.4));
		modelApple.render(glm::scale(matrixModelApple22, glm::vec3(0.13, 0.13, 0.13)));
		/////////////Vela
		glm::mat4 velamodel = glm::mat4(3.0);
		velamodel = glm::translate(velamodel, glm::vec3(6.95 - 30, 1.6, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureIDv2);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(velamodel, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Vela 2
		glm::mat4 velamodel2 = glm::mat4(3.0);
		velamodel2 = glm::translate(velamodel2, glm::vec3(6.95 - 29, 1.6, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureIDv2);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(velamodel2, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);

		///
				////Modelo apple
		glm::mat4 matrixModelApple13 = glm::mat4(1.0);
		matrixModelApple13 = glm::translate(matrixModelApple13, glm::vec3(5.2 - 30, 1.63, 3.7));
		modelApple.render(glm::scale(matrixModelApple13, glm::vec3(0.13, 0.13, 0.13)));
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
		////Modelo Naranja
		glm::mat4 matrixModelOrange = glm::mat4(1.0);
		matrixModelOrange = glm::translate(matrixModelOrange, glm::vec3(6.5 - 30, 1.6, 2.7));
		modelOrange.render(glm::scale(matrixModelOrange, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 2
		glm::mat4 matrixModelOrange2 = glm::mat4(1.0);
		matrixModelOrange2 = glm::translate(matrixModelOrange2, glm::vec3(6.8 - 30, 1.6, 2.7));
		modelOrange.render(glm::scale(matrixModelOrange2, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 3
		glm::mat4 matrixModelOrange3 = glm::mat4(1.0);
		matrixModelOrange3 = glm::translate(matrixModelOrange3, glm::vec3(7.1 - 30, 1.6, 2.7));
		modelOrange.render(glm::scale(matrixModelOrange3, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 4
		glm::mat4 matrixModelOrange4 = glm::mat4(1.0);
		matrixModelOrange4 = glm::translate(matrixModelOrange4, glm::vec3(7.4 - 30, 1.6, 2.7));
		modelOrange.render(glm::scale(matrixModelOrange4, glm::vec3(0.1, 0.1, 0.1)));
		///
				////Modelo Naranja
		glm::mat4 matrixModelOrange1 = glm::mat4(1.0);
		matrixModelOrange1 = glm::translate(matrixModelOrange1, glm::vec3(6.65 - 30, 1.6, 3.1));
		modelOrange.render(glm::scale(matrixModelOrange1, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 2
		glm::mat4 matrixModelOrange21 = glm::mat4(1.0);
		matrixModelOrange21 = glm::translate(matrixModelOrange21, glm::vec3(6.95 - 30, 1.6, 3.1));
		modelOrange.render(glm::scale(matrixModelOrange21, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 3
		glm::mat4 matrixModelOrange31 = glm::mat4(1.0);
		matrixModelOrange31 = glm::translate(matrixModelOrange31, glm::vec3(7.25 - 30, 1.6, 3.1));
		modelOrange.render(glm::scale(matrixModelOrange31, glm::vec3(0.1, 0.1, 0.1)));
		///
				////Modelo Naranja
		glm::mat4 matrixModelOrange12 = glm::mat4(1.0);
		matrixModelOrange12 = glm::translate(matrixModelOrange12, glm::vec3(6.8 - 30, 1.6, 3.5));
		modelOrange.render(glm::scale(matrixModelOrange12, glm::vec3(0.1, 0.1, 0.1)));
		////Modelo Naranja 2
		glm::mat4 matrixModelOrange22 = glm::mat4(1.0);
		matrixModelOrange22 = glm::translate(matrixModelOrange22, glm::vec3(7.1 - 30, 1.6, 3.5));
		modelOrange.render(glm::scale(matrixModelOrange22, glm::vec3(0.1, 0.1, 0.1)));
		///
				////Modelo Naranja
		glm::mat4 matrixModelOrange13 = glm::mat4(1.0);
		matrixModelOrange13 = glm::translate(matrixModelOrange13, glm::vec3(6.95 - 30, 1.6, 3.9));
		modelOrange.render(glm::scale(matrixModelOrange13, glm::vec3(0.1, 0.1, 0.1)));
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
		////Modelo Banana
		//glm::mat4 matrixModelBanana = glm::mat4(1.0);
		//matrixModelBanana = glm::translate(matrixModelBanana, glm::vec3(2.0-5, 3.6, 5.5));
		//modelBanana.render(glm::scale(matrixModelBanana, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 1
		glm::mat4 matrixModelBanana1 = glm::mat4(1.0);
		matrixModelBanana1 = glm::translate(matrixModelBanana1, glm::vec3(2.5 - 30, 1.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana1, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 2
		glm::mat4 matrixModelBanana2 = glm::mat4(1.0);
		matrixModelBanana2 = glm::translate(matrixModelBanana2, glm::vec3(3.0 - 30, 1.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana2, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 3
		glm::mat4 matrixModelBanana3 = glm::mat4(1.0);
		matrixModelBanana3 = glm::translate(matrixModelBanana3, glm::vec3(3.5 - 30, 1.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana3, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 4
		glm::mat4 matrixModelBanana4 = glm::mat4(1.0);
		matrixModelBanana4 = glm::translate(matrixModelBanana4, glm::vec3(4.0 - 30, 1.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana4, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 5
		glm::mat4 matrixModelBanana5 = glm::mat4(1.0);
		matrixModelBanana5 = glm::translate(matrixModelBanana5, glm::vec3(4.5 - 30, 1.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana5, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Banana 6
		glm::mat4 matrixModelBanana6 = glm::mat4(1.0);
		matrixModelBanana6 = glm::translate(matrixModelBanana6, glm::vec3(5.0 - 30, 1.6, 5.5));
		modelBanana.render(glm::scale(matrixModelBanana6, glm::vec3(0.070, 0.07, 0.07)));
		////Modelo Vela 1
		//glm::mat4 matrixModelVela = glm::mat4(1.0);
		//matrixModelVela = glm::translate(matrixModelVela, glm::vec3(5.0, 3.6, 6.5));
		//modelVela.render(glm::scale(matrixModelVela, glm::vec3(0.070, 0.07, 0.07)));


		/*											Decoracion								*/
		////Modelo Table
		glm::mat4 matrixModelTabla2 = glm::mat4(1.0);
		matrixModelTabla2 = glm::translate(matrixModelTabla2, glm::vec3(5.0 - 30, 1.0, 4.0));
		modelTable.render(glm::scale(matrixModelTabla2, glm::vec3(3.5, 0.8, 4.0)));
		//////// Stpehen
		glm::mat4 retrato = glm::mat4(3.0);
		retrato = glm::translate(retrato, glm::vec3(5.0 - 30, 2.0, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureID20M);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(retrato, glm::vec3(1.5, 1.5, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////////////////////////////////////

		glm::mat4 modelflor = glm::mat4(1.0);
		modelflor = glm::translate(modelflor, glm::vec3(5.5 - 30, 1.1, 5.5));
		glBindTexture(GL_TEXTURE_2D, textureflorID1);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(glm::scale(modelflor, glm::vec3(5.0, 0.01, 5.0)));
		shaderTexture.setFloat("offsetX", 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////Papel picado (Azul)
		glm::mat4 ppicadoazul = glm::mat4(3.0);
		ppicadoazul = glm::translate(ppicadoazul, glm::vec3(6.5 - 30, 2.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoazul, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado 2 (Azul)
		glm::mat4 ppicadoazul2 = glm::mat4(3.0);
		ppicadoazul2 = glm::translate(ppicadoazul2, glm::vec3(3.5 - 30, 2.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoazul2, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado  (Morado)
		glm::mat4 ppicadomorado = glm::mat4(3.0);
		ppicadomorado = glm::translate(ppicadomorado, glm::vec3(2.2 - 30, 2.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureIDM);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadomorado, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////Papel picado (Verde)
		glm::mat4 ppicadoVerde2 = glm::mat4(3.0);
		ppicadoVerde2 = glm::translate(ppicadoVerde2, glm::vec3(7.8 - 30, 2.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureIDV);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoVerde2, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado (Rosa)
		glm::mat4 ppicadoRosa = glm::mat4(3.0);
		ppicadoRosa = glm::translate(ppicadoRosa, glm::vec3(9.0 - 30, 2.3, 0.5));
		glBindTexture(GL_TEXTURE_2D, textureIDR);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoRosa, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////Papel picado (Azul)
		glm::mat4 ppicadoAazul = glm::mat4(3.0);
		ppicadoAazul = glm::translate(ppicadoAazul, glm::vec3(6.5 - 30, 2.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoAazul, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado 2 (Azul)
		glm::mat4 ppicadoAazul2 = glm::mat4(3.0);
		ppicadoAazul2 = glm::translate(ppicadoAazul2, glm::vec3(3.5 - 30, 2.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoAazul2, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado  (Morado)
		glm::mat4 ppicadoAmorado = glm::mat4(3.0);
		ppicadoAmorado = glm::translate(ppicadoAmorado, glm::vec3(2.2 - 30, 2.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureIDM);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoAmorado, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////Papel picado (Verde)
		glm::mat4 ppicadoAVerde2 = glm::mat4(3.0);
		ppicadoAVerde2 = glm::translate(ppicadoAVerde2, glm::vec3(7.8 - 30, 2.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureIDV);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoAVerde2, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado (Rosa)
		glm::mat4 ppicadoARosa = glm::mat4(3.0);
		ppicadoARosa = glm::translate(ppicadoARosa, glm::vec3(9.0 - 30, 2.3, 10.5));
		glBindTexture(GL_TEXTURE_2D, textureIDR);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoARosa, glm::vec3(1.0, 1.0, 0.001)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////Papel picado (Verde)
		glm::mat4 ppicadoDVerde2 = glm::mat4(3.0);
		ppicadoDVerde2 = glm::translate(ppicadoDVerde2, glm::vec3(10.0 - 30, 2.3, 1.7));
		glBindTexture(GL_TEXTURE_2D, textureIDV);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDVerde2, glm::vec3(0.001, 1.0, 1.0)));
		/////////////Papel picado (Azul)
		glm::mat4 ppicadoDAazul = glm::mat4(3.0);
		ppicadoDAazul = glm::translate(ppicadoDAazul, glm::vec3(10.0 - 30, 2.3, 4.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDAazul, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado 2 (Azul)
		glm::mat4 ppicadoDAazul2 = glm::mat4(3.0);
		ppicadoDAazul2 = glm::translate(ppicadoDAazul2, glm::vec3(10.0 - 30, 2.3, 5.7));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDAazul2, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado  (Morado)
		glm::mat4 ppicadoDAmorado = glm::mat4(3.0);
		ppicadoDAmorado = glm::translate(ppicadoDAmorado, glm::vec3(10.0 - 30, 2.3, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureIDM);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDAmorado, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////Papel picado (Rosa)
		glm::mat4 ppicadoDARosa = glm::mat4(3.0);
		ppicadoDARosa = glm::translate(ppicadoDARosa, glm::vec3(10.0 - 30, 2.3, 8.5));
		glBindTexture(GL_TEXTURE_2D, textureIDR);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ppicadoDARosa, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////Papel picado (Verde)
		glm::mat4 pppicadoIVerde2 = glm::mat4(3.0);
		pppicadoIVerde2 = glm::translate(pppicadoIVerde2, glm::vec3(1.2 - 30, 2.3, 1.1));
		glBindTexture(GL_TEXTURE_2D, textureIDV);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIVerde2, glm::vec3(0.001, 1.0, 1.0)));
		/////////////Papel picado (Azul)
		glm::mat4 pppicadoIAazul = glm::mat4(3.0);
		pppicadoIAazul = glm::translate(pppicadoIAazul, glm::vec3(1.2 - 30, 2.3, 3.5));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIAazul, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado 2 (Azul)
		glm::mat4 pppicadoIAazul2 = glm::mat4(3.0);
		pppicadoIAazul2 = glm::translate(pppicadoIAazul2, glm::vec3(1.2 - 30, 2.3, 4.7));
		glBindTexture(GL_TEXTURE_2D, textureID20P);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIAazul2, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////Papel picado  (Morado)
		glm::mat4 pppicadoIAmorado = glm::mat4(3.0);
		pppicadoIAmorado = glm::translate(pppicadoIAmorado, glm::vec3(1.2 - 30, 2.3, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureIDM);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIAmorado, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////Papel picado (Rosa)
		glm::mat4 pppicadoIARosa = glm::mat4(3.0);
		pppicadoIARosa = glm::translate(pppicadoIARosa, glm::vec3(1.2 - 30, 2.3, 7.5));
		glBindTexture(GL_TEXTURE_2D, textureIDR);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pppicadoIARosa, glm::vec3(0.001, 1.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////Modelo Mandarina
		//glm::mat4 matrixModelMandarine = glm::mat4(1.0);
		//matrixModelMandarine = glm::translate(matrixModelMandarine, glm::vec3(-8.0-5, 11.0, 6.0));
		//modelMandarine.render(matrixModelMandarine);

		////Modelo Table 3
		glm::mat4 matrixModelTabla3 = glm::mat4(1.0);
		matrixModelTabla3 = glm::translate(matrixModelTabla3, glm::vec3(9.0 - 30, -1.0, 2.0));
		modelTable.render(glm::scale(matrixModelTabla3, glm::vec3(0.5, 0.5, 0.5)));
		glActiveTexture(GL_TEXTURE0);


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////PArte Trasera 0//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						// Render del cubo con textura de ladrillos y con repeticion en x
		glm::mat4 cubeTextureModel0 = glm::mat4(3.0);
		cubeTextureModel0 = glm::translate(cubeTextureModel0, glm::vec3(0.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel0, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel2 = glm::mat4(3.0);
		cubeTextureModel2 = glm::translate(cubeTextureModel2, glm::vec3(1.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel2, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel3 = glm::mat4(1.0);
		cubeTextureModel3 = glm::translate(cubeTextureModel3, glm::vec3(2.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel3, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel4 = glm::mat4(1.0);
		cubeTextureModel4 = glm::translate(cubeTextureModel4, glm::vec3(3.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel4, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel5 = glm::mat4(1.0);
		cubeTextureModel5 = glm::translate(cubeTextureModel5, glm::vec3(4.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel5, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel6 = glm::mat4(1.0);
		cubeTextureModel6 = glm::translate(cubeTextureModel6, glm::vec3(5.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel6, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel7 = glm::mat4(1.0);
		cubeTextureModel7 = glm::translate(cubeTextureModel7, glm::vec3(6.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel7, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel8 = glm::mat4(1.0);
		cubeTextureModel8 = glm::translate(cubeTextureModel8, glm::vec3(7.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel8, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel9 = glm::mat4(1.0);
		cubeTextureModel9 = glm::translate(cubeTextureModel9, glm::vec3(8.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel9, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel10 = glm::mat4(1.0);
		cubeTextureModel10 = glm::translate(cubeTextureModel10, glm::vec3(9.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel10, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel11 = glm::mat4(1.0);
		cubeTextureModel11 = glm::translate(cubeTextureModel11, glm::vec3(10.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel11, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel12 = glm::mat4(1.0);
		cubeTextureModel12 = glm::translate(cubeTextureModel12, glm::vec3(11.0 - 30, 0.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel12, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////Paredes Internas Bajas/////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				////////////////////////////////////////////////////////////
		glm::mat4 pared10 = glm::mat4(1.0);
		pared10 = glm::translate(pared10, glm::vec3(9.0 - 30, 0.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared10, glm::vec3(4.0, 2.0, 0.1)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared20 = glm::mat4(1.0);
		pared20 = glm::translate(pared20, glm::vec3(9.0 - 30, 0.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared20, glm::vec3(4.0, 2.0, 0.1)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared30 = glm::mat4(1.0);
		pared30 = glm::translate(pared30, glm::vec3(3.0 - 30, 0.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared30, glm::vec3(4.0, 2.0, 0.1)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared301 = glm::mat4(1.0);
		pared301 = glm::translate(pared301, glm::vec3(5.0 - 30, 0.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared301, glm::vec3(0.1, 2.0, 5.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared302 = glm::mat4(1.0);
		pared302 = glm::translate(pared302, glm::vec3(5.0 - 30, 0.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared302, glm::vec3(0.1, 2.0, 2.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 pared40 = glm::mat4(1.0);
		pared40 = glm::translate(pared40, glm::vec3(7.0 - 30, 0.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(pared40, glm::vec3(0.1, 2.0, 3.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////Puertas//////////////////////////////////////////////////////////
		glm::mat4 puerta1 = glm::mat4(1.0);
		puerta1 = glm::translate(puerta1, glm::vec3(7.0 - 30, 0.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID9);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(puerta1, glm::vec3(0.1, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		glm::mat4 puerta12 = glm::mat4(1.0);
		puerta12 = glm::translate(puerta12, glm::vec3(7.0 - 30, 0.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID9);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(puerta12, glm::vec3(0.1, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		glm::mat4 puerta13 = glm::mat4(1.0);
		puerta13 = glm::translate(puerta13, glm::vec3(5.0 - 30, 0.0, 3.0));
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
		cubeTextureModell13 = glm::translate(cubeTextureModell13, glm::vec3(0.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModell13, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel13 = glm::mat4(3.0);
		cubeTextureModel13 = glm::translate(cubeTextureModel13, glm::vec3(1.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel13, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel14 = glm::mat4(1.0);
		cubeTextureModel14 = glm::translate(cubeTextureModel14, glm::vec3(2.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel14, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel15 = glm::mat4(1.0);
		cubeTextureModel15 = glm::translate(cubeTextureModel15, glm::vec3(3.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel15, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 ccubeTextureModel16 = glm::mat4(1.0);
		ccubeTextureModel16 = glm::translate(ccubeTextureModel16, glm::vec3(4.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ccubeTextureModel16, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel17 = glm::mat4(1.0);
		cubeTextureModel17 = glm::translate(cubeTextureModel17, glm::vec3(5.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel17, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 ccubeTextureModel18 = glm::mat4(1.0);
		ccubeTextureModel18 = glm::translate(ccubeTextureModel18, glm::vec3(6.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ccubeTextureModel18, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cucubeTextureModel19 = glm::mat4(1.0);
		cucubeTextureModel19 = glm::translate(cucubeTextureModel19, glm::vec3(7.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cucubeTextureModel19, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cucubeTextureModel20 = glm::mat4(1.0);
		cucubeTextureModel20 = glm::translate(cucubeTextureModel20, glm::vec3(8.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cucubeTextureModel20, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel21 = glm::mat4(1.0);
		cubeTextureModel21 = glm::translate(cubeTextureModel21, glm::vec3(9.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel21, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel22 = glm::mat4(1.0);
		cubeTextureModel22 = glm::translate(cubeTextureModel22, glm::vec3(10.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel22, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel23 = glm::mat4(1.0);
		cubeTextureModel23 = glm::translate(cubeTextureModel23, glm::vec3(11.0 - 30, 1.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel23, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////Parte Trasera 2//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTAl13 = glm::mat4(3.0);
		cubeTextureModelTAl13 = glm::translate(cubeTextureModelTAl13, glm::vec3(0.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTAl13, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA13 = glm::mat4(3.0);
		cubeTextureModelTA13 = glm::translate(cubeTextureModelTA13, glm::vec3(1.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA13, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA14 = glm::mat4(1.0);
		cubeTextureModelTA14 = glm::translate(cubeTextureModelTA14, glm::vec3(2.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA14, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA15 = glm::mat4(1.0);
		cubeTextureModelTA15 = glm::translate(cubeTextureModelTA15, glm::vec3(3.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA15, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 ccubeTextureModelTA16 = glm::mat4(1.0);
		ccubeTextureModelTA16 = glm::translate(ccubeTextureModelTA16, glm::vec3(4.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ccubeTextureModelTA16, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA17 = glm::mat4(1.0);
		cubeTextureModelTA17 = glm::translate(cubeTextureModelTA17, glm::vec3(5.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA17, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 ccubeTextureModelTA18 = glm::mat4(1.0);
		ccubeTextureModelTA18 = glm::translate(ccubeTextureModelTA18, glm::vec3(6.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(ccubeTextureModelTA18, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cucubeTextureModelTA19 = glm::mat4(1.0);
		cucubeTextureModelTA19 = glm::translate(cucubeTextureModelTA19, glm::vec3(7.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cucubeTextureModelTA19, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cucubeTextureModelTA20 = glm::mat4(1.0);
		cucubeTextureModelTA20 = glm::translate(cucubeTextureModelTA20, glm::vec3(8.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cucubeTextureModelTA20, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA21 = glm::mat4(1.0);
		cubeTextureModelTA21 = glm::translate(cubeTextureModelTA21, glm::vec3(9.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA21, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA22 = glm::mat4(1.0);
		cubeTextureModelTA22 = glm::translate(cubeTextureModelTA22, glm::vec3(10.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA22, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelTA23 = glm::mat4(1.0);
		cubeTextureModelTA23 = glm::translate(cubeTextureModelTA23, glm::vec3(11.0 - 30, 2.0, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelTA23, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////PAredes Izquierdas 0////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel24 = glm::mat4(1.0);
		cubeTextureModel24 = glm::translate(cubeTextureModel24, glm::vec3(0.0 - 30, 0.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel24, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel25 = glm::mat4(1.0);
		cubeTextureModel25 = glm::translate(cubeTextureModel25, glm::vec3(0.0 - 30, 0.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel25, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel26 = glm::mat4(1.0);
		cubeTextureModel26 = glm::translate(cubeTextureModel26, glm::vec3(0.0 - 30, 0.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel26, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel27 = glm::mat4(1.0);
		cubeTextureModel27 = glm::translate(cubeTextureModel27, glm::vec3(0.0 - 30, 0.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel27, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel28 = glm::mat4(1.0);
		cubeTextureModel28 = glm::translate(cubeTextureModel28, glm::vec3(0.0 - 30, 0.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel28, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel34 = glm::mat4(1.0);
		cubeTextureModel34 = glm::translate(cubeTextureModel34, glm::vec3(0.0 - 30, 0.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel34, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel29 = glm::mat4(1.0);
		cubeTextureModel29 = glm::translate(cubeTextureModel29, glm::vec3(0.0 - 30, 0.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel29, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel30 = glm::mat4(1.0);
		cubeTextureModel30 = glm::translate(cubeTextureModel30, glm::vec3(0.0 - 30, 0.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel30, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel31 = glm::mat4(1.0);
		cubeTextureModel31 = glm::translate(cubeTextureModel31, glm::vec3(0.0 - 30, 0.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel31, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel32 = glm::mat4(1.0);
		cubeTextureModel32 = glm::translate(cubeTextureModel32, glm::vec3(0.0 - 30, 0.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel32, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModel33 = glm::mat4(1.0);
		cubeTextureModel33 = glm::translate(cubeTextureModel33, glm::vec3(0.0 - 30, 0.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModel33, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Izqueirda 1/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI24 = glm::mat4(1.0);
		cubeTextureModelAI24 = glm::translate(cubeTextureModelAI24, glm::vec3(0.0 - 30, 1.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI24, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI25 = glm::mat4(1.0);
		cubeTextureModelAI25 = glm::translate(cubeTextureModelAI25, glm::vec3(0.0 - 30, 1.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI25, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI26 = glm::mat4(1.0);
		cubeTextureModelAI26 = glm::translate(cubeTextureModelAI26, glm::vec3(0.0 - 30, 1.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI26, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI27 = glm::mat4(1.0);
		cubeTextureModelAI27 = glm::translate(cubeTextureModelAI27, glm::vec3(0.0 - 30, 1.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI27, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI28 = glm::mat4(1.0);
		cubeTextureModelAI28 = glm::translate(cubeTextureModelAI28, glm::vec3(0.0 - 30, 1.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI28, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI34 = glm::mat4(1.0);
		cubeTextureModelAI34 = glm::translate(cubeTextureModelAI34, glm::vec3(0.0 - 30, 1.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI34, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI29 = glm::mat4(1.0);
		cubeTextureModelAI29 = glm::translate(cubeTextureModelAI29, glm::vec3(0.0 - 30, 1.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI29, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI30 = glm::mat4(1.0);
		cubeTextureModelAI30 = glm::translate(cubeTextureModelAI30, glm::vec3(0.0 - 30, 1.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI30, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI31 = glm::mat4(1.0);
		cubeTextureModelAI31 = glm::translate(cubeTextureModelAI31, glm::vec3(0.0 - 30, 1.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI31, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI32 = glm::mat4(1.0);
		cubeTextureModelAI32 = glm::translate(cubeTextureModelAI32, glm::vec3(0.0 - 30, 1.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI32, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelAI33 = glm::mat4(1.0);
		//cubeTextureModelAI33 = glm::translate(cubeTextureModelAI33, glm::vec3(0.0-5, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelAI33, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Izqueirda 2/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI124 = glm::mat4(1.0);
		cubeTextureModelAI124 = glm::translate(cubeTextureModelAI124, glm::vec3(0.0 - 30, 2.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI124, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI125 = glm::mat4(1.0);
		cubeTextureModelAI125 = glm::translate(cubeTextureModelAI125, glm::vec3(0.0 - 30, 2.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI125, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI126 = glm::mat4(1.0);
		cubeTextureModelAI126 = glm::translate(cubeTextureModelAI126, glm::vec3(-0.1 - 30, 2.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID7G);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI126, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI127 = glm::mat4(1.0);
		cubeTextureModelAI127 = glm::translate(cubeTextureModelAI127, glm::vec3(0.0 - 30, 2.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI127, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI128 = glm::mat4(1.0);
		cubeTextureModelAI128 = glm::translate(cubeTextureModelAI128, glm::vec3(0.0 - 30, 2.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI128, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI134 = glm::mat4(1.0);
		cubeTextureModelAI134 = glm::translate(cubeTextureModelAI134, glm::vec3(0.0 - 30, 2.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI134, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI1129 = glm::mat4(1.0);
		cubeTextureModelAI1129 = glm::translate(cubeTextureModelAI1129, glm::vec3(0.0 - 30, 2.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI1129, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI1130 = glm::mat4(1.0);
		cubeTextureModelAI1130 = glm::translate(cubeTextureModelAI1130, glm::vec3(0.0 - 30, 2.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI1130, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI131 = glm::mat4(1.0);
		cubeTextureModelAI131 = glm::translate(cubeTextureModelAI131, glm::vec3(-0.1 - 30, 2.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID7G);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI131, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI132 = glm::mat4(1.0);
		cubeTextureModelAI132 = glm::translate(cubeTextureModelAI132, glm::vec3(0.0 - 30, 2.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI132, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelAI133 = glm::mat4(1.0);
		cubeTextureModelAI133 = glm::translate(cubeTextureModelAI133, glm::vec3(0.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelAI133, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Derecha 0/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD024 = glm::mat4(1.0);
		cubeTextureModelD024 = glm::translate(cubeTextureModelD024, glm::vec3(11.0 - 30, 0.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD024, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD025 = glm::mat4(1.0);
		cubeTextureModelD025 = glm::translate(cubeTextureModelD025, glm::vec3(11.0 - 30, 0.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD025, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD026 = glm::mat4(1.0);
		cubeTextureModelD026 = glm::translate(cubeTextureModelD026, glm::vec3(11.0 - 30, 0.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD026, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD027 = glm::mat4(1.0);
		cubeTextureModelD027 = glm::translate(cubeTextureModelD027, glm::vec3(11.0 - 30, 0.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD027, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD028 = glm::mat4(1.0);
		cubeTextureModelD028 = glm::translate(cubeTextureModelD028, glm::vec3(11.0 - 30, 0.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD028, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD034 = glm::mat4(1.0);
		cubeTextureModelD034 = glm::translate(cubeTextureModelD034, glm::vec3(11.0 - 30, 0.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD034, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD029 = glm::mat4(1.0);
		cubeTextureModelD029 = glm::translate(cubeTextureModelD029, glm::vec3(11.0 - 30, 0.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD029, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD030 = glm::mat4(1.0);
		cubeTextureModelD030 = glm::translate(cubeTextureModelD030, glm::vec3(11.0 - 30, 0.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD030, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD031 = glm::mat4(1.0);
		cubeTextureModelD031 = glm::translate(cubeTextureModelD031, glm::vec3(11.0 - 30, 0.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD031, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD032 = glm::mat4(1.0);
		cubeTextureModelD032 = glm::translate(cubeTextureModelD032, glm::vec3(11.0 - 30, 0.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD032, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD033 = glm::mat4(1.0);
		cubeTextureModelD033 = glm::translate(cubeTextureModelD033, glm::vec3(11.0 - 30, 0.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD033, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Derecha 1/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD124 = glm::mat4(1.0);
		cubeTextureModelD124 = glm::translate(cubeTextureModelD124, glm::vec3(11.0 - 30, 1.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD124, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD125 = glm::mat4(1.0);
		cubeTextureModelD125 = glm::translate(cubeTextureModelD125, glm::vec3(11.0 - 30, 1.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD125, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD126 = glm::mat4(1.0);
		cubeTextureModelD126 = glm::translate(cubeTextureModelD126, glm::vec3(11.0 - 30, 1.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD126, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD127 = glm::mat4(1.0);
		cubeTextureModelD127 = glm::translate(cubeTextureModelD127, glm::vec3(11.0 - 30, 1.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD127, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD128 = glm::mat4(1.0);
		cubeTextureModelD128 = glm::translate(cubeTextureModelD128, glm::vec3(11.0 - 30, 1.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD128, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD134 = glm::mat4(1.0);
		cubeTextureModelD134 = glm::translate(cubeTextureModelD134, glm::vec3(11.0 - 30, 1.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD134, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD129 = glm::mat4(1.0);
		cubeTextureModelD129 = glm::translate(cubeTextureModelD129, glm::vec3(11.0 - 30, 1.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD129, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD130 = glm::mat4(1.0);
		cubeTextureModelD130 = glm::translate(cubeTextureModelD130, glm::vec3(11.0 - 30, 1.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD130, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD131 = glm::mat4(1.0);
		cubeTextureModelD131 = glm::translate(cubeTextureModelD131, glm::vec3(11.0 - 30, 1.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD131, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD132 = glm::mat4(1.0);
		cubeTextureModelD132 = glm::translate(cubeTextureModelD132, glm::vec3(11.0 - 30, 1.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD132, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD133 = glm::mat4(1.0);
		cubeTextureModelD133 = glm::translate(cubeTextureModelD133, glm::vec3(11.0 - 30, 1.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD133, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Derecha 2/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD224 = glm::mat4(1.0);
		cubeTextureModelD224 = glm::translate(cubeTextureModelD224, glm::vec3(11.0 - 30, 2.0, 4.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD224, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD225 = glm::mat4(1.0);
		cubeTextureModelD225 = glm::translate(cubeTextureModelD225, glm::vec3(11.1 - 30, 2.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID7G);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD225, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD226 = glm::mat4(1.0);
		cubeTextureModelD226 = glm::translate(cubeTextureModelD226, glm::vec3(11.0 - 30, 2.0, 2.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD226, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD227 = glm::mat4(1.0);
		cubeTextureModelD227 = glm::translate(cubeTextureModelD227, glm::vec3(11.0 - 30, 2.0, 1.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD227, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD228 = glm::mat4(1.0);
		cubeTextureModelD228 = glm::translate(cubeTextureModelD228, glm::vec3(11.0 - 30, 2.0, 5.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD228, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD234 = glm::mat4(1.0);
		cubeTextureModelD234 = glm::translate(cubeTextureModelD234, glm::vec3(11.0 - 30, 2.0, 6.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD234, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD229 = glm::mat4(1.0);
		cubeTextureModelD229 = glm::translate(cubeTextureModelD229, glm::vec3(11.0 - 30, 2.0, 7.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD229, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD230 = glm::mat4(1.0);
		cubeTextureModelD230 = glm::translate(cubeTextureModelD230, glm::vec3(11.0 - 30, 2.0, 8.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD230, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD231 = glm::mat4(1.0);
		cubeTextureModelD231 = glm::translate(cubeTextureModelD231, glm::vec3(11.0 - 30, 2.0, 9.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD231, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelD232 = glm::mat4(1.0);
		cubeTextureModelD232 = glm::translate(cubeTextureModelD232, glm::vec3(11.1 - 30, 2.0, 10.0));
		glBindTexture(GL_TEXTURE_2D, textureID7G);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelD232, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		/////////////////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelD233 = glm::mat4(1.0);
		//cubeTextureModelD233 = glm::translate(cubeTextureModelD233, glm::vec3(11.0-5, 4.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelD233, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Frontales 0/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF0 = glm::mat4(3.0);
		cubeTextureModelF0 = glm::translate(cubeTextureModelF0, glm::vec3(0.0 - 30, 0.0, 11.0));
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
		cubeTextureModelF03 = glm::translate(cubeTextureModelF03, glm::vec3(2.0 - 30, 0.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF03, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF04 = glm::mat4(1.0);
		//cubeTextureModelF04 = glm::translate(cubeTextureModelF04, glm::vec3(3.0-5, 2.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF04, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF05 = glm::mat4(1.0);
		cubeTextureModelF05 = glm::translate(cubeTextureModelF05, glm::vec3(4.0-5, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF05, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF06 = glm::mat4(1.0);
		cubeTextureModelF06 = glm::translate(cubeTextureModelF06, glm::vec3(4.6 - 30, 0.0, 11.1));
		glBindTexture(GL_TEXTURE_2D, textureID8G);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF06, glm::vec3(3.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF07 = glm::mat4(1.0);
		cubeTextureModelF07 = glm::translate(cubeTextureModelF07, glm::vec3(6.0-5, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF07, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF08 = glm::mat4(1.0);
		cubeTextureModelF08 = glm::translate(cubeTextureModelF08, glm::vec3(7.0 - 30, 0.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF08, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF09 = glm::mat4(1.0);
		cubeTextureModelF09 = glm::translate(cubeTextureModelF09, glm::vec3(8.0 - 30, 0.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF09, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF010 = glm::mat4(1.0);
		cubeTextureModelF010 = glm::translate(cubeTextureModelF010, glm::vec3(9.0 - 30, 0.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF010, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF011 = glm::mat4(1.0);
		cubeTextureModelF011 = glm::translate(cubeTextureModelF011, glm::vec3(10.0 - 30, 0.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF011, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF012 = glm::mat4(1.0);
		cubeTextureModelF012 = glm::translate(cubeTextureModelF012, glm::vec3(11.0 - 30, 0.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF012, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////Paredes Frontales 1/////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF1 = glm::mat4(3.0);
		cubeTextureModelF1 = glm::translate(cubeTextureModelF1, glm::vec3(0.0 - 30, 1.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF1, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF12 = glm::mat4(3.0);
		cubeTextureModelF12 = glm::translate(cubeTextureModelF12,glm::vec3(1.0 - 30, 3.0, 11.1));
		glBindTexture(GL_TEXTURE_2D, textureID7G);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF12, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/

		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF13 = glm::mat4(1.0);
		//cubeTextureModelF13 = glm::translate(cubeTextureModelF13,glm::vec3(2.0 - 30, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV",glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF13, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF14 = glm::mat4(1.0);
		//cubeTextureModelF14 = glm::translate(cubeTextureModelF14,glm::vec3(3.0 - 30, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF14, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF15 = glm::mat4(1.0);
		cubeTextureModelF15 = glm::translate(cubeTextureModelF15, glm::vec3(4.0 - 30, 3.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF15, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		/*glm::mat4 cubeTextureModelF16 = glm::mat4(1.0);
		cubeTextureModelF16 = glm::translate(cubeTextureModelF16, glm::vec3(5.0 - 30, 3.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF16, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);*/
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF17 = glm::mat4(1.0);
		//cubeTextureModelF17 = glm::translate(cubeTextureModelF17, glm::vec3(6.0 - 30, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF17, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF18 = glm::mat4(1.0);
		cubeTextureModelF18 = glm::translate(cubeTextureModelF18, glm::vec3(7.0 - 30, 1.0, 11.1));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF18, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF19 = glm::mat4(1.0);
		cubeTextureModelF19 = glm::translate(cubeTextureModelF19, glm::vec3(8.0 - 30, 1.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF19, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF110 = glm::mat4(1.0);
		//cubeTextureModelF110 = glm::translate(cubeTextureModelF110, glm::vec3(9.0 - 30, 3.0, 11.0));
		//glBindTexture(GL_TEXTURE_2D, textureID4);
		//shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		//box3.render(glm::scale(cubeTextureModelF110, glm::vec3(2.0, 2.0, 1.0)));
		//glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		//glm::mat4 cubeTextureModelF111 = glm::mat4(1.0);
		//cubeTextureModelF111 = glm::translate(cubeTextureModelF111, glm::vec3(10.0 - 30, 3.0, 11.1));
		//glBindTexture(GL_TEXTURE_2D, textureID7G);
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
		cubeTextureModelF2 = glm::translate(cubeTextureModelF2, glm::vec3(0.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF2, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF22 = glm::mat4(3.0);
		cubeTextureModelF22 = glm::translate(cubeTextureModelF22, glm::vec3(1.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF22, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF23 = glm::mat4(1.0);
		cubeTextureModelF23 = glm::translate(cubeTextureModelF23, glm::vec3(2.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF23, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF24 = glm::mat4(1.0);
		cubeTextureModelF24 = glm::translate(cubeTextureModelF24, glm::vec3(3.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF24, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF25 = glm::mat4(1.0);
		cubeTextureModelF25 = glm::translate(cubeTextureModelF25, glm::vec3(4.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF25, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF26 = glm::mat4(1.0);
		cubeTextureModelF26 = glm::translate(cubeTextureModelF26, glm::vec3(5.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF26, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF27 = glm::mat4(1.0);
		cubeTextureModelF27 = glm::translate(cubeTextureModelF27, glm::vec3(6.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
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
		cubeTextureModelF210 = glm::translate(cubeTextureModelF210, glm::vec3(9.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF210, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF211 = glm::mat4(1.0);
		cubeTextureModelF211 = glm::translate(cubeTextureModelF211, glm::vec3(10.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF211, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////////////////////////////////////////////////////
		glm::mat4 cubeTextureModelF212 = glm::mat4(1.0);
		cubeTextureModelF212 = glm::translate(cubeTextureModelF212, glm::vec3(11.0 - 30, 2.0, 11.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(glm::scale(cubeTextureModelF212, glm::vec3(2.0, 2.0, 1.0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*															Tapa de la casa (Arriba)														*/

		glm::mat4 modelPiedra4 = glm::mat4(1.0);
		modelPiedra4 = glm::translate(modelPiedra4, glm::vec3(5.5 - 30, 3.0, 5.5));
		glBindTexture(GL_TEXTURE_2D, textureID2G);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(glm::scale(modelPiedra4, glm::vec3(11.0, 0.01, 11.0)));
		shaderTexture.setFloat("offsetX", 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		/*															Tapa de la casa (Planta Baja)														*/
		glm::mat4 modelPiedra2 = glm::mat4(1.0);
		modelPiedra2 = glm::translate(modelPiedra2, glm::vec3(5.5 - 30, -1.0, 5.5));
		glBindTexture(GL_TEXTURE_2D, textureID2G);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(glm::scale(modelPiedra2, glm::vec3(11.0, 0.01, 11.0)));
		shaderTexture.setFloat("offsetX", 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		/*															Tapa de la casa (Piso 1)														*/
		glm::mat4 modelPiedra3 = glm::mat4(1.0);
		modelPiedra3 = glm::translate(modelPiedra3, glm::vec3(5.5 - 30, 1.0, 5.5));
		glBindTexture(GL_TEXTURE_2D, textureID2G);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(glm::scale(modelPiedra3, glm::vec3(11.0, 0.01, 11.0)));
		shaderTexture.setFloat("offsetX", 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		/*															Tapa de la casa (Cesped)														*/
		glm::mat4 modelPasto2 = glm::mat4(1.0);
		modelPasto2 = glm::translate(modelPasto2, glm::vec3(5.5 - 30, -1.8, 5.5));
		glBindTexture(GL_TEXTURE_2D, textureID17);
		shaderTexture.setFloat("offsetX", offX);
		box2.render(glm::scale(modelPasto2, glm::vec3(22.0, 0.01, 22.0)));
		shaderTexture.setFloat("offsetX", 0);
		glBindTexture(GL_TEXTURE_2D, 0);

	//********************Render de las camaras que se prenden en la casa de diad de muertos*****************************//
		glm::mat4 matrixModelLamp1H = glm::mat4(1.0);
		matrixModelLamp1H = glm::translate(matrixModelLamp1H, glm::vec3(-26.23, 0.854434, 9.32244));
		modelLampara.render(glm::scale(matrixModelLamp1H, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelLamp2H = glm::mat4(1.0);
		matrixModelLamp2H = glm::translate(matrixModelLamp2H, glm::vec3(-21.3986, 0.789432, 3.8218));
		modelLampara.render(glm::scale(matrixModelLamp2H, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelLamp3H = glm::mat4(1.0);
		matrixModelLamp3H = glm::translate(matrixModelLamp3H, glm::vec3(-26.3791, 0.970396, 3.8465));
		modelLampara.render(glm::scale(matrixModelLamp3H, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);
	//****************************
		///////////////////////////////////////////////////////////////////////
	/////////////////////////// FIN CASA MUERTOS ////////////////////////////
	///////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	//////////////////////RENDER CASA NAVIDAD ////////////////////////////
	//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////RENDER CASA ////////////////////////////
//////////////////////////////////////////////////////////////

///////////////////////PLANTA BAJA///////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID13);
		glm::mat4 zaguan = glm::mat4(1.0);
		zaguan = glm::translate(zaguan, glm::vec3(-4.1, 0.0, 5.8));
		boxParedes.render(glm::scale(zaguan, glm::vec3(3.4, 3.0, 0.2)));
		glBindTexture(GL_TEXTURE_2D, 0);
		////////////PAREDES COCHERA//////////////////////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredizquierdapb = glm::mat4(1.0);
		paredizquierdapb = glm::translate(paredizquierdapb, glm::vec3(-6.0, 0.0, 0.0));
		boxParedes.render(glm::scale(paredizquierdapb, glm::vec3(0.4, 3.0, 12.0)));

		glm::mat4 paredpuerta = glm::mat4(1.0);
		paredpuerta = glm::translate(paredpuerta, glm::vec3(-2.3, 0.0, 5.25));
		boxParedes.render(glm::scale(paredpuerta, glm::vec3(0.2, 3.0, 1.5)));

		glm::mat4 paredicochera = glm::mat4(1.0);
		paredicochera = glm::translate(paredicochera, glm::vec3(-2.3, 0.0, -3));
		boxParedes.render(glm::scale(paredicochera, glm::vec3(0.2, 3.0, 6.0)));

		glm::mat4 paredventana = glm::mat4(1.0);
		paredventana = glm::translate(paredventana, glm::vec3(-2.3, -1.0, 1.55));
		boxParedes.render(glm::scale(paredventana, glm::vec3(0.2, 1.0, 3.0)));
		//////////////////PUERTA SALA////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID14);
		glm::mat4 puertasala = glm::mat4(1.0);
		puertasala = glm::translate(puertasala, glm::vec3(-2.3, 0.0, 3.75));
		boxParedes.render(glm::scale(puertasala, glm::vec3(0.2, 3.0, 1.5)));
		////////////////VENATNA SALA COCHERA/////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanasala = glm::mat4(1.0);
		ventanasala = glm::translate(ventanasala, glm::vec3(-2.3, 0.5, 1.55));
		boxParedes.render(glm::scale(ventanasala, glm::vec3(0.2, 2.0, 3.0)));
		//////////////////BAÑO////////////////////////////////

		glBindTexture(GL_TEXTURE_2D, textureID9);
		glm::mat4 puertabanio = glm::mat4(1.0);
		puertabanio = glm::translate(puertabanio, glm::vec3(-1.8, -0.2, 0.0));
		boxParedes.render(glm::scale(puertabanio, glm::vec3(1.0, 2.6, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredbanio1 = glm::mat4(1.0);
		paredbanio1 = glm::translate(paredbanio1, glm::vec3(-1.8, 1.3, 0.0));
		boxParedes.render(glm::scale(paredbanio1, glm::vec3(1.0, 0.4, 0.2)));

		glm::mat4 paredbanio2 = glm::mat4(1.0);
		paredbanio2 = glm::translate(paredbanio2, glm::vec3(-0.75, 0, 0.0));
		boxParedes.render(glm::scale(paredbanio2, glm::vec3(2.5, 3.0, 0.2)));

		glm::mat4 paredbanio3 = glm::mat4(1.0);
		paredbanio3 = glm::translate(paredbanio3, glm::vec3(0.4, 0, -3.0));
		boxParedes.render(glm::scale(paredbanio3, glm::vec3(0.2, 3.0, 6.0)));


		glm::mat4 paredbanio4 = glm::mat4(1.0);
		paredbanio4 = glm::translate(paredbanio4, glm::vec3(-0.9, 0, -6.0));
		boxParedes.render(glm::scale(paredbanio4, glm::vec3(3, 3.0, 0.2)));

		///////////////////COMEDOR/////////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID14);
		glm::mat4 puertacomedor = glm::mat4(1.0);
		puertacomedor = glm::translate(puertacomedor, glm::vec3(1.1, 0.0, -6.0));
		boxParedes.render(glm::scale(puertacomedor, glm::vec3(1.0, 3.0, 0.2)));
		////////////////VENTANA COMEDOR/////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanacomedor = glm::mat4(1.0);
		ventanacomedor = glm::translate(ventanacomedor, glm::vec3(2.6, 0.5, -6.0));
		boxParedes.render(glm::scale(ventanacomedor, glm::vec3(2.0, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredcomedor = glm::mat4(1.0);
		paredcomedor = glm::translate(paredcomedor, glm::vec3(2.6, -1.0, -6.0));
		boxParedes.render(glm::scale(paredcomedor, glm::vec3(2, 1.0, 0.2)));

		glm::mat4 paredcomedor2 = glm::mat4(1.0);
		paredcomedor2 = glm::translate(paredcomedor2, glm::vec3(4, 0, -6.0));
		boxParedes.render(glm::scale(paredcomedor2, glm::vec3(1, 3.0, 0.2)));


		//////////////////COCINA/////////////////////
		glm::mat4 paredcocina1 = glm::mat4(1.0);
		paredcocina1 = glm::translate(paredcocina1, glm::vec3(5.25, 0, -6.0));
		boxParedes.render(glm::scale(paredcocina1, glm::vec3(1.5, 3.0, 0.2)));

		glm::mat4 paredcocina2 = glm::mat4(1.0);
		paredcocina2 = glm::translate(paredcocina2, glm::vec3(7.0, -1.0, -6.0));
		boxParedes.render(glm::scale(paredcocina2, glm::vec3(2, 1.0, 0.2)));

		glm::mat4 paredcocina3 = glm::mat4(1.0);
		paredcocina3 = glm::translate(paredcocina3, glm::vec3(9.25, 0.0, -6.0));
		boxParedes.render(glm::scale(paredcocina3, glm::vec3(2.5, 3.0, 0.2)));


		glm::mat4 paredcocina5 = glm::mat4(1.0);
		paredcocina5 = glm::translate(paredcocina5, glm::vec3(7.5, 0, 0.0));
		boxParedes.render(glm::scale(paredcocina5, glm::vec3(6, 3.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanacocina = glm::mat4(1.0);
		ventanacocina = glm::translate(ventanacocina, glm::vec3(7, 0.5, -6.0));
		boxParedes.render(glm::scale(ventanacocina, glm::vec3(2.0, 2.0, 0.2)));

		////////////////////////SALA///////////////
		glm::mat4 ventanasala2 = glm::mat4(1.0);
		ventanasala2 = glm::translate(ventanasala2, glm::vec3(.95, 0.5, 5.9));
		boxParedes.render(glm::scale(ventanasala2, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredsala1 = glm::mat4(1.0);
		paredsala1 = glm::translate(paredsala1, glm::vec3(-1.3, 0.0, 5.9));
		boxParedes.render(glm::scale(paredsala1, glm::vec3(2, 3.0, 0.2)));

		glm::mat4 paredsala2 = glm::mat4(1.0);
		paredsala2 = glm::translate(paredsala2, glm::vec3(0.95, -1.0, 5.9));
		boxParedes.render(glm::scale(paredsala2, glm::vec3(2.5, 1.0, 0.2)));

		glm::mat4 paredsala3 = glm::mat4(1.0);
		paredsala3 = glm::translate(paredsala3, glm::vec3(3.7, 0.0, 5.9));
		boxParedes.render(glm::scale(paredsala3, glm::vec3(3, 3.0, 0.2)));

		//////////////////RECAMARA INFERIOR///////////////////////////
		glm::mat4 paredrecamarai = glm::mat4(1.0);
		paredrecamarai = glm::translate(paredrecamarai, glm::vec3(6.4, -1.0, 5.9));
		boxParedes.render(glm::scale(paredrecamarai, glm::vec3(2.5, 1.0, 0.2)));

		glm::mat4 paredrecamarai2 = glm::mat4(1.0);
		paredrecamarai2 = glm::translate(paredrecamarai2, glm::vec3(9.15, 0.0, 5.9));
		boxParedes.render(glm::scale(paredrecamarai2, glm::vec3(3, 3.0, 0.2)));

		glm::mat4 paredrecamarai3 = glm::mat4(1.0);
		paredrecamarai3 = glm::translate(paredrecamarai3, glm::vec3(8, 0, 2.0));
		boxParedes.render(glm::scale(paredrecamarai3, glm::vec3(5, 3.0, 0.2)));

		glm::mat4 paredrecamarai4 = glm::mat4(1.0);
		paredrecamarai4 = glm::translate(paredrecamarai4, glm::vec3(4.5, 0, 3.9));
		boxParedes.render(glm::scale(paredrecamarai4, glm::vec3(0.2, 3.0, 3.9)));

		glm::mat4 paredrecamarai5 = glm::mat4(1.0);
		paredrecamarai5 = glm::translate(paredrecamarai5, glm::vec3(5, 1.3, 2.0));
		boxParedes.render(glm::scale(paredrecamarai5, glm::vec3(1.0, 0.4, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID9);
		glm::mat4 puertarecamarai = glm::mat4(1.0);
		puertarecamarai = glm::translate(puertarecamarai, glm::vec3(5, -0.2, 2.0));
		boxParedes.render(glm::scale(puertarecamarai, glm::vec3(1, 2.6, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanarecamarai = glm::mat4(1.0);
		ventanarecamarai = glm::translate(ventanarecamarai, glm::vec3(6.4, 0.5, 5.9));
		boxParedes.render(glm::scale(ventanarecamarai, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredderechapb = glm::mat4(1.0);
		paredderechapb = glm::translate(paredderechapb, glm::vec3(10.4, 0.0, 0.0));
		boxParedes.render(glm::scale(paredderechapb, glm::vec3(0.4, 3.0, 12.0)));

		////////PISOS PLANTA BAJA//////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID21);
		glm::mat4 pisocochera = glm::mat4(1.0);
		pisocochera = glm::translate(pisocochera, glm::vec3(-4.1, -1.5, -0.2));
		boxParedes.render(glm::scale(pisocochera, glm::vec3(3.4, 0.1, 12)));

		glBindTexture(GL_TEXTURE_2D, textureID22);

		glm::mat4 pisopb = glm::mat4(1.0);
		pisopb = glm::translate(pisopb, glm::vec3(4.0, -1.5, -0.2));
		shaderMaterialLighting.setVectorFloat3("material.ambient", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.diffuse", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.specular", glm::value_ptr(glm::vec3(0.727811f, 0.626959f, 0.626959f)));
		shaderMaterialLighting.setFloat("material.shininess", 76.8f);
		boxParedes.render(glm::scale(pisopb, glm::vec3(13, 0.1, 12)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		/////TECHO PLANTA BAJA
		glm::mat4 techopb = glm::mat4(1.0);
		techopb = glm::translate(techopb, glm::vec3(2.25, 1.8, 0.0));
		glBindTexture(GL_TEXTURE_2D, textureID5);
		boxParedes.render(24, 6, glm::scale(techopb, glm::vec3(16.85, 0.6, 12)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(0, 24, glm::scale(techopb, glm::vec3(16.85, 0.6, 12)));
		boxParedes.render(30, 6, glm::scale(techopb, glm::vec3(16.85, 0.6, 12)));

		//////////////////FIN PLANTA BAJA///////////////////////////////

		//////////////////////////////////////////////////////////////
		///////////////////PRIMER PISO/////////////////////
		//////////////////////////////////////////////////////////////

		////////////PAREDES RECAMARA 1///////////
		glm::mat4 paredrecamara1 = glm::mat4(1.0);
		paredrecamara1 = glm::translate(paredrecamara1, glm::vec3(6.4, 2.6, 5.9));
		boxParedes.render(glm::scale(paredrecamara1, glm::vec3(2.5, 1.0, 0.2)));

		glm::mat4 paredrecamara12 = glm::mat4(1.0);
		paredrecamara12 = glm::translate(paredrecamara12, glm::vec3(9.15, 3.6, 5.9));
		boxParedes.render(glm::scale(paredrecamara12, glm::vec3(3, 3.0, 0.2)));

		glm::mat4 paredrecamara13 = glm::mat4(1.0);
		paredrecamara13 = glm::translate(paredrecamara13, glm::vec3(8, 3.6, 2.0));
		boxParedes.render(glm::scale(paredrecamara13, glm::vec3(5, 3.0, 0.2)));

		glm::mat4 paredrecamara14 = glm::mat4(1.0);
		paredrecamara14 = glm::translate(paredrecamara14, glm::vec3(4.5, 3.6, 3.9));
		boxParedes.render(glm::scale(paredrecamara14, glm::vec3(0.2, 3.0, 3.9)));

		glm::mat4 paredrecamara15 = glm::mat4(1.0);
		paredrecamara15 = glm::translate(paredrecamara15, glm::vec3(5, 4.9, 2.0));
		boxParedes.render(glm::scale(paredrecamara15, glm::vec3(1.0, 0.4, 0.2)));

		glm::mat4 paredrecamara16 = glm::mat4(1.0);
		paredrecamara16 = glm::translate(paredrecamara16, glm::vec3(4.8, 3.6, 5.9));
		boxParedes.render(glm::scale(paredrecamara16, glm::vec3(0.8, 3.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID9);
		glm::mat4 puertarecamara1 = glm::mat4(1.0);
		puertarecamara1 = glm::translate(puertarecamara1, glm::vec3(5, 3.4, 2.0));
		boxParedes.render(glm::scale(puertarecamara1, glm::vec3(1, 2.6, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanarecamara1 = glm::mat4(1.0);
		ventanarecamara1 = glm::translate(ventanarecamara1, glm::vec3(6.4, 4.1, 5.9));
		boxParedes.render(glm::scale(ventanarecamara1, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredderechap1 = glm::mat4(1.0);
		paredderechap1 = glm::translate(paredderechap1, glm::vec3(10.4, 3.6, 0.0));
		//boxParedes.render(glm::scale(paredderechap1, glm::vec3(0.4, 3.0, 12.0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		/////////////////////RECAMARA DOSSS/////////////////
		glm::mat4 modelCasa = glm::mat4(1.0f);
		modelCasa = glm::translate(modelCasa, glm::vec3(4.5, 3.6, -3));
		modelCasa = glm::rotate(modelCasa, glm::radians(90.0f), glm::vec3(0, 1, 0.0));

		glm::mat4 paredFrontal = glm::scale(modelCasa, glm::vec3(6.0, 3.0, 0.3));
		glBindTexture(GL_TEXTURE_2D, textureID10);

		boxParedes.render(paredFrontal);

		glm::mat4 plafonf = glm::translate(modelCasa, glm::vec3(0, 1.2, 0.3));
		boxParedes.render(glm::scale(plafonf, glm::vec3(6.0, 0.1, 0.3)));
		glBindTexture(GL_TEXTURE_2D, textureID10);

		glBindTexture(GL_TEXTURE_2D, textureID8);
		glm::mat4 pantalla = glm::translate(plafonf, glm::vec3(0.35, -1.0, 0.0));
		boxParedes.render(glm::scale(pantalla, glm::vec3(1.5, 1.0, 0.3)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 repisaVertical1 = glm::translate(modelCasa, glm::vec3(-1.5, -0.2, 0.3));
		boxParedes.render(glm::scale(repisaVertical1, glm::vec3(0.05, 2.65, 0.3)));

		glm::mat4 repisaHorizontal1 = glm::translate(repisaVertical1, glm::vec3(0.4, 0.45, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal1, glm::vec3(0.75, 0.05, 0.3)));


		glm::mat4 repisaHorizontal2 = glm::translate(repisaHorizontal1, glm::vec3(0.0, -0.75, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal2, glm::vec3(0.75, 0.05, 0.3)));

		glm::mat4 repisaVertical2 = glm::translate(repisaVertical1, glm::vec3(0.8, 0.0, 0.0));
		boxParedes.render(glm::scale(repisaVertical2, glm::vec3(0.05, 2.65, 0.3)));


		////////////repisas tele/////////////
		glm::mat4 repisaHorizontal3 = glm::translate(repisaVertical2, glm::vec3(1, -0.5, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal3, glm::vec3(2, 0.05, 0.3)));
		glm::mat4 repisaHorizontal4 = glm::translate(repisaHorizontal3, glm::vec3(0.0, -0.4, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal4, glm::vec3(2, 0.05, 0.3)));

		glm::mat4 repisaVertical3 = glm::translate(repisaVertical2, glm::vec3(2.0, 0.0, 0.0));
		boxParedes.render(glm::scale(repisaVertical3, glm::vec3(0.05, 2.65, 0.3)));

		glm::mat4 repisaHorizontal5 = glm::translate(repisaVertical3, glm::vec3(0.8, -.7, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal5, glm::vec3(1.6, 0.05, 0.3)));

		glm::mat4 repisaHorizontal6 = glm::translate(repisaHorizontal5, glm::vec3(0.0, 0.66, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal6, glm::vec3(1.6, 0.05, 0.3)));

		glm::mat4 repisaHorizontal7 = glm::translate(repisaHorizontal6, glm::vec3(0.0, 0.66, 0.0));
		boxParedes.render(glm::scale(repisaHorizontal7, glm::vec3(1.6, 0.05, 0.3)));


		//////////////////Pared closet/////////////////////
		glm::mat4 paredCloset = glm::translate(modelCasa, glm::vec3(-3, 0.0, 3.5));
		boxParedes.render(glm::scale(paredCloset, glm::vec3(0.2, 3.0, 5.0)));

		glm::mat4 paredCloset2 = glm::translate(modelCasa, glm::vec3(-3, 1.25, 0.6));
		boxParedes.render(glm::scale(paredCloset2, glm::vec3(0.2, 0.4, 1)));

		glBindTexture(GL_TEXTURE_2D, textureID9);
		glm::mat4 puerta = glm::translate(paredCloset, glm::vec3(0.0, -0.25, -3.0));
		boxParedes.render(glm::scale(puerta, glm::vec3(0.2, 2.6, 1)));

		glBindTexture(GL_TEXTURE_2D, textureID6);
		glm::mat4 closetArriba = glm::translate(paredCloset, glm::vec3(0.3, 1.5, 0.0));
		boxParedes.render(glm::scale(closetArriba, glm::vec3(0.8, 0.2, 5.0)));

		glm::mat4 closetAbajo11 = glm::translate(paredCloset, glm::vec3(0.3, 0.0, 0.0));
		boxParedes.render(glm::scale(closetAbajo11, glm::vec3(0.6, 3.0, 5.0)));


		////////////Pared ventana/////////////////
		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanarecamara2 = glm::mat4(1.0);
		ventanarecamara2 = glm::translate(ventanarecamara2, glm::vec3(6.4, 4.1, -6.0));
		boxParedes.render(glm::scale(ventanarecamara2, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredventana1 = glm::mat4(1.0);
		paredventana1 = glm::translate(paredventana1, glm::vec3(4.8, 3.6, -6));
		boxParedes.render(glm::scale(paredventana1, glm::vec3(0.8, 3.0, 0.2)));

		glm::mat4 paredventana2 = glm::mat4(1.0);
		paredventana2 = glm::translate(paredventana2, glm::vec3(6.4, 2.6, -6));
		boxParedes.render(glm::scale(paredventana2, glm::vec3(2.5, 1.0, 0.2)));

		glm::mat4 paredventana3 = glm::mat4(1.0);
		paredventana3 = glm::translate(paredventana3, glm::vec3(9.15, 3.6, -6));
		boxParedes.render(glm::scale(paredventana3, glm::vec3(3, 3.0, 0.2)));

		////////pared superior derecha/////////
		glm::mat4 paredderechas = glm::mat4(1.0);
		paredderechas = glm::translate(paredderechas, glm::vec3(10.4, 3.6, 0.0));
		boxParedes.render(glm::scale(paredderechas, glm::vec3(0.4, 3.0, 12.0)));

		////////////Pared superior trasera  ////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredSuperior = glm::mat4(1.0);
		paredSuperior = glm::translate(paredSuperior, glm::vec3(-0.9, 3.6, -6.0));
		boxParedes.render(glm::scale(paredSuperior, glm::vec3(10.4, 3.0, 0.2)));

		////////////Pared superior trasera  ////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID10);
		glm::mat4 paredCocheraTrasera = glm::mat4(1.0);
		paredCocheraTrasera = glm::translate(paredCocheraTrasera, glm::vec3(-4.1, 0.0, -6.0));
		boxParedes.render(glm::scale(paredCocheraTrasera, glm::vec3(3.4, 3.0, 0.2)));


		////////////////Fachada parte 1 ///////////////

		glBindTexture(GL_TEXTURE_2D, textureID19);
		glm::mat4 paredizquierdap1 = glm::mat4(1.0);
		paredizquierdap1 = glm::translate(paredizquierdap1, glm::vec3(-6.0, 3.6, 0.3));
		boxParedes.render(0, 6, glm::scale(paredizquierdap1, glm::vec3(0.4, 3.0, 12.6)));
		boxParedes.render(30, 6, glm::scale(paredizquierdap1, glm::vec3(0.4, 3.0, 12.6)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(paredizquierdap1, glm::vec3(0.4, 3.0, 12.6)));

		glBindTexture(GL_TEXTURE_2D, textureID19);
		glm::mat4 fachada1 = glm::mat4(1.0);
		fachada1 = glm::translate(fachada1, glm::vec3(-4.1, 2.4, 6.25));
		//boxParedes.render(12, 12, glm::scale(fachada1, glm::vec3(3.4, 0.6, 1.2)));
		boxParedes.render(0, 6, glm::scale(fachada1, glm::vec3(3.4, 0.6, 0.7)));
		boxParedes.render(30, 6, glm::scale(fachada1, glm::vec3(3.4, 0.6, 0.7)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(fachada1, glm::vec3(3.4, 0.6, 0.7)));

		glm::mat4 fachada2 = glm::mat4(1.0);
		glBindTexture(GL_TEXTURE_2D, textureID19);
		fachada2 = glm::translate(fachada2, glm::vec3(-2.3, 3.6, 6.25));
		boxParedes.render(0, 12, glm::scale(fachada2, glm::vec3(0.4, 3.0, 0.7)));
		boxParedes.render(30, 6, glm::scale(fachada2, glm::vec3(0.4, 3.0, 0.7)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(12, 18, glm::scale(fachada2, glm::vec3(0.4, 3.0, 0.7)));



		glBindTexture(GL_TEXTURE_2D, textureID16);
		glm::mat4 fachada4 = glm::mat4(1.0);
		fachada4 = glm::translate(fachada4, glm::vec3(-4.1, 3.9, 6.25));
		boxParedes.render(glm::scale(fachada4, glm::vec3(3.4, 2.4, 0.7)));
		///////////////fachada en medio arriba///////////////
		glBindTexture(GL_TEXTURE_2D, textureID15);
		glm::mat4 ventanafachada = glm::mat4(1.0);
		ventanafachada = glm::translate(ventanafachada, glm::vec3(.95, 4.1, 6.1));
		boxParedes.render(glm::scale(ventanafachada, glm::vec3(2.5, 2.0, 0.2)));

		glBindTexture(GL_TEXTURE_2D, textureID20);
		glm::mat4 paredfachada1 = glm::mat4(1.0);
		paredfachada1 = glm::translate(paredfachada1, glm::vec3(-1.3, 3.6, 6.1));
		boxParedes.render(0, 12, glm::scale(paredfachada1, glm::vec3(2, 3.0, 0.3)));
		boxParedes.render(30, 6, glm::scale(paredfachada1, glm::vec3(2, 3.0, 0.3)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(paredfachada1, glm::vec3(2, 3.0, 0.3)));


		glm::mat4 paredfachada2 = glm::mat4(1.0);
		paredfachada2 = glm::translate(paredfachada2, glm::vec3(0.95, 2.6, 6.1));
		glBindTexture(GL_TEXTURE_2D, textureID20);
		boxParedes.render(0, 12, glm::scale(paredfachada2, glm::vec3(2.5, 1.0, 0.3)));
		boxParedes.render(30, 6, glm::scale(paredfachada2, glm::vec3(2.5, 1.0, 0.3)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(paredfachada2, glm::vec3(2.5, 1.0, 0.3)));

		glBindTexture(GL_TEXTURE_2D, textureID19);
		glm::mat4 paredfachada3 = glm::mat4(1.0);
		paredfachada3 = glm::translate(paredfachada3, glm::vec3(3.3, 3.6, 6.1));
		glBindTexture(GL_TEXTURE_2D, textureID20);
		boxParedes.render(0, 12, glm::scale(paredfachada3, glm::vec3(2.25, 3.0, 0.3)));
		boxParedes.render(30, 6, glm::scale(paredfachada3, glm::vec3(2.25, 3.0, 0.3)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(6, 24, glm::scale(paredfachada3, glm::vec3(2.25, 3.0, 0.3))); //vemos

		glBindTexture(GL_TEXTURE_2D, textureID20);
		glm::mat4 paredfachada4 = glm::mat4(1.0);
		paredfachada4 = glm::translate(paredfachada4, glm::vec3(1.1, 5.2, 6.1));
		boxParedes.render(glm::scale(paredfachada4, glm::vec3(6.75, 0.4, 0.4)));

		////////////////////////Techo segundo piso////////////////////////////
		glBindTexture(GL_TEXTURE_2D, textureID19);

		glm::mat4 techo1 = glm::mat4(1.0);
		techo1 = glm::translate(techo1, glm::vec3(-4.1, 5.2, 0.3));
		boxParedes.render(0, 12, glm::scale(techo1, glm::vec3(4.2, 0.4, 12.6)));
		glBindTexture(GL_TEXTURE_2D, textureID10);
		boxParedes.render(12, 24, glm::scale(techo1, glm::vec3(4.2, 0.4, 12.6)));


		glm::mat4 techo2 = glm::mat4(1.0);
		techo2 = glm::translate(techo2, glm::vec3(4.2, 5.2, 0.0));
		boxParedes.render(glm::scale(techo2, glm::vec3(13, 0.4, 12)));
		///////////////////////////////////////////
		/////////////Carretera/////////////////////
		///////////////////////////////////////////

		glBindTexture(GL_TEXTURE_2D, textureID18);
		glm::mat4 carretera1 = glm::mat4(1.0);
		carretera1 = glm::translate(carretera1, glm::vec3(-15, -1.6, 14.5));
		boxCarretera.render(glm::scale(carretera1, glm::vec3(50, 0.0, 10)));

		glm::mat4 carretera2 = glm::mat4(1.0);
		carretera2 = glm::translate(carretera2, glm::vec3(-12.7, -1.6, 4.4));
		boxCarretera.render(glm::scale(carretera2, glm::vec3(10, 0.0, 30)));

		glm::mat4 carretera3 = glm::mat4(1.0);
		carretera3 = glm::translate(carretera3, glm::vec3(15.0, -1.6, 4.4));
		boxCarretera.render(glm::scale(carretera3, glm::vec3(10, 0.0, 30)));

		glm::mat4 modelCesped = glm::mat4(1.0);
		modelCesped = glm::translate(modelCesped, glm::vec3(2.25, -1.6, 0.0));
		modelCesped = glm::scale(modelCesped, glm::vec3(20.0, 0.001, 20.0));
		// Se activa la textura del agua
		glBindTexture(GL_TEXTURE_2D, textureID17);
		boxCesped.render(modelCesped);
		glBindTexture(GL_TEXTURE_2D, 0);

		//////////////////////////////////////
		/////////////////Pesebre//////////////
		/////////////////////////////////////

		glBindTexture(GL_TEXTURE_2D, textureID26);
		glm::mat4 reyes = glm::mat4(1.0);
		reyes = glm::translate(reyes, glm::vec3(1.5, 2.6, 4.2));
		reyes = glm::rotate(reyes, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
		boxParedes.render(glm::scale(reyes, glm::vec3(0.7, 1, 0.0)));

		glBindTexture(GL_TEXTURE_2D, textureID23);
		glm::mat4 maria = glm::mat4(1.0);
		maria = glm::translate(maria, glm::vec3(2.4, 2.7, 5.0));
		maria = glm::rotate(maria, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
		boxParedes.render(glm::scale(maria, glm::vec3(0.5, 1, 0.0)));

		glBindTexture(GL_TEXTURE_2D, textureID24);
		glm::mat4 jose = glm::mat4(1.0);
		jose = glm::translate(jose, glm::vec3(1.9, 2.7, 5.0));
		jose = glm::rotate(jose, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
		boxParedes.render(glm::scale(jose, glm::vec3(0.5, 1, 0.0)));

		glBindTexture(GL_TEXTURE_2D, textureID25);
		glm::mat4 bebe = glm::mat4(1.0);
		bebe = glm::translate(bebe, glm::vec3(2.1, 2.3, 4.5));
		bebe = glm::rotate(bebe, glm::radians(-40.0f), glm::vec3(1.0, 0.0, 0.0));
		boxParedes.render(glm::scale(bebe, glm::vec3(0.25, 0.0, 0.5)));
		glBindTexture(GL_TEXTURE_2D, 0);

		///////////////////////////////////////////
/////////////MUEBLES/////////////////////
///////////////////////////////////////////

		glm::mat4 matrixModelMueble = glm::mat4(1.0);
		matrixModelMueble = glm::translate(matrixModelMueble, glm::vec3(1.0, -1.6, 3.0));
		matrixModelMueble = glm::scale(matrixModelMueble, glm::vec3(1.5, 1.5, 1.5));
		modelMueble.render(matrixModelMueble);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelTable = glm::mat4(1.0);
		matrixModelTable = glm::translate(matrixModelTable, glm::vec3(2.5, -1.6, -2.5));
		matrixModelTable = glm::scale(matrixModelTable, glm::vec3(2, 2, 2));
		modelTable2.render(matrixModelTable);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelRosa = glm::mat4(1.0);
		matrixModelRosa = glm::translate(matrixModelRosa, glm::vec3(1.0, -1.0, 3.0));
		matrixModelRosa = glm::scale(matrixModelRosa, glm::vec3(0.3, 0.3, 0.3));
		modelRosa.render(matrixModelRosa);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelMaceta = glm::mat4(1.0);
		matrixModelMaceta = glm::translate(matrixModelMaceta, glm::vec3(1.0, -1.6, 6.8));
		matrixModelMaceta = glm::rotate(matrixModelMaceta, glm::radians(90.0f), glm::vec3(0, 1, 0));
		matrixModelMaceta = glm::scale(matrixModelMaceta, glm::vec3(0.2, 0.2, 0.2));
		modelMaceta.render(matrixModelMaceta);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelJardinera = glm::mat4(1.0);
		matrixModelJardinera = glm::translate(matrixModelJardinera, glm::vec3(10.0, -1.6, 8));
		matrixModelJardinera = glm::rotate(matrixModelJardinera, glm::radians(90.0f), glm::vec3(0, 1, 0));
		matrixModelJardinera = glm::scale(matrixModelJardinera, glm::vec3(0.3, 0.3, 0.3));
		modelJardinera.render(matrixModelJardinera);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelSala = glm::mat4(1.0);
		matrixModelSala = glm::translate(matrixModelSala, glm::vec3(1.0, -1.0, 5.0));
		matrixModelSala = glm::rotate(matrixModelSala, glm::radians(180.0f), glm::vec3(0, 1, 0));
		matrixModelSala = glm::scale(matrixModelSala, glm::vec3(0.5, 0.5, 0.5));
		modelSala.render(matrixModelSala);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelSalap = glm::mat4(1.0);
		matrixModelSalap = glm::translate(matrixModelSalap, glm::vec3(-1.0, -1.5, 3.5));
		matrixModelSalap = glm::rotate(matrixModelSalap, glm::radians(90.0f), glm::vec3(0, 1, 0));
		matrixModelSalap = glm::scale(matrixModelSalap, glm::vec3(0.3, 0.3, 0.3));
		modelSalap.render(matrixModelSalap);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelMuebleTV = glm::mat4(1.0);
		matrixModelMuebleTV = glm::translate(matrixModelMuebleTV, glm::vec3(3.8, -1.5, 3.8));
		matrixModelMuebleTV = glm::rotate(matrixModelMuebleTV, glm::radians(180.0f), glm::vec3(0, 1, 0));
		modelMuebleTV.render(matrixModelMuebleTV);
		glActiveTexture(GL_TEXTURE0);


		///////////////////////////
		/////Muebles baño////////
		//////////////////////////
		glm::mat4 matrixModelToilet = glm::mat4(1.0);
		matrixModelToilet = glm::translate(matrixModelToilet, glm::vec3(-0.2, -1.6, -1.0));
		matrixModelToilet = glm::rotate(matrixModelToilet, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		matrixModelToilet = glm::scale(matrixModelToilet, glm::vec3(0.3, 0.3, 0.3));
		modelToilet.render(matrixModelToilet);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelHandWash = glm::mat4(1.0);
		matrixModelHandWash = glm::translate(matrixModelHandWash, glm::vec3(-0.2, -1.6, -2.5));
		matrixModelHandWash = glm::rotate(matrixModelHandWash, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelHandWash.render(matrixModelHandWash);
		glActiveTexture(GL_TEXTURE0);

		///////////////////////////
		/////Muebles cocina////////
		///////////////////////////

		glm::mat4 matrixModelKitchen = glm::mat4(1.0);
		matrixModelKitchen = glm::translate(matrixModelKitchen, glm::vec3(9.0, -0.4, -2.2));
		matrixModelKitchen = glm::rotate(matrixModelKitchen, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		matrixModelKitchen = glm::scale(matrixModelKitchen, glm::vec3(1.4, 1.2, 1.2));
		modelKitchen.render(matrixModelKitchen);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelRefrigerator = glm::mat4(1.0);
		matrixModelRefrigerator = glm::translate(matrixModelRefrigerator, glm::vec3(9.4, -0.05, -5.05));
		matrixModelRefrigerator = glm::rotate(matrixModelRefrigerator, glm::radians(180.0f), glm::vec3(0, 1, 0));
		modelRefrigerator.render(glm::scale(matrixModelRefrigerator, glm::vec3(1.0, 1.4, 1.3)));
		glActiveTexture(GL_TEXTURE0);

		///////////////////////////
		/////Muebles arriba////////
		///////////////////////////
		glm::mat4 matrixModelMueble1 = glm::mat4(1.0);
		matrixModelMueble1 = glm::translate(matrixModelMueble1, glm::vec3(-5.3, 2.1, 0.0));
		matrixModelMueble1 = glm::rotate(matrixModelMueble1, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
		modelMueble2.render(matrixModelMueble1);


		///////////////////////////
		/////Muebles recamaras////////
		///////////////////////////

		//recamara abajo
		glm::mat4 matrixModelBed1 = glm::mat4(1.0);
		matrixModelBed1 = glm::translate(matrixModelBed1, glm::vec3(9.3, -0.8, 4.4));
		matrixModelBed1 = glm::rotate(matrixModelBed1, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		matrixModelBed1 = glm::scale(matrixModelBed1, glm::vec3(1.55, 1.6, 1.6));
		modelBed.render(matrixModelBed1);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelCloset1 = glm::mat4(1.0);
		matrixModelCloset1 = glm::translate(matrixModelCloset1, glm::vec3(7.2, -1.3, 3.4));
		matrixModelCloset1 = glm::scale(matrixModelCloset1, glm::vec3(0.9, 0.65, 0.6));
		modelCloset.render(matrixModelCloset1);
		glActiveTexture(GL_TEXTURE0);

		//recamara arriba1
		glm::mat4 matrixModelBed2 = glm::mat4(1.0);
		matrixModelBed2 = glm::translate(matrixModelBed2, glm::vec3(9.3, 2.85, 4.4));
		matrixModelBed2 = glm::rotate(matrixModelBed2, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		matrixModelBed2 = glm::scale(matrixModelBed2, glm::vec3(1.55, 1.6, 1.6));
		modelBed.render(matrixModelBed2);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 matrixModelCloset2 = glm::mat4(1.0);
		matrixModelCloset2 = glm::translate(matrixModelCloset2, glm::vec3(7.2, 2.35, 3.4));
		matrixModelCloset2 = glm::scale(matrixModelCloset2, glm::vec3(0.9, 0.65, 0.6));
		modelCloset.render(matrixModelCloset2);
		glActiveTexture(GL_TEXTURE0);

		//recamara arriba 2
		glm::mat4 matrixModelBed3 = glm::mat4(1.0);
		matrixModelBed3 = glm::translate(matrixModelBed3, glm::vec3(9.3, 2.85, -3.0));
		matrixModelBed3 = glm::rotate(matrixModelBed3, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		matrixModelBed3 = glm::scale(matrixModelBed3, glm::vec3(1.55, 1.6, 1.6));
		modelBed.render(matrixModelBed3);
		glActiveTexture(GL_TEXTURE0);

		//////////////////////////////
		////////////lamparas//////////
		//////////////////////////////

		//lampara del baño
		glm::mat4 matrixModelLamp1B = glm::mat4(1.0);
		matrixModelLamp1B = glm::translate(matrixModelLamp1B, glm::vec3(-1.0, 1.12, -2.5));
		modelLampara.render(glm::scale(matrixModelLamp1B, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara comedor
		glm::mat4 matrixModelLamp2B = glm::mat4(1.0);
		matrixModelLamp2B = glm::translate(matrixModelLamp2B, glm::vec3(2.5, 1.12, -2.5));
		modelLampara.render(glm::scale(matrixModelLamp2B, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara cocina
		glm::mat4 matrixModelLamp3B = glm::mat4(1.0);
		matrixModelLamp3B = glm::translate(matrixModelLamp3B, glm::vec3(6.0, 1.12, -2.5));
		modelLampara.render(glm::scale(matrixModelLamp3B, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);


		//lampara sala 1
		glm::mat4 matrixModelLamp4B = glm::mat4(1.0);
		matrixModelLamp4B = glm::translate(matrixModelLamp4B, glm::vec3(0.0, 1.0, 3.0));
		modelLampara.render(glm::scale(matrixModelLamp4B, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara sala 2
		glm::mat4 matrixModelLamp5B = glm::mat4(1.0);
		matrixModelLamp5B = glm::translate(matrixModelLamp5B, glm::vec3(2.0, 1.0, 3.0));
		modelLampara.render(glm::scale(matrixModelLamp5B, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara recamara abajo
		glm::mat4 matrixModelLamp6 = glm::mat4(1.0);
		matrixModelLamp6 = glm::translate(matrixModelLamp6, glm::vec3(7.5, 1.0, 4.0));
		modelLampara.render(glm::scale(matrixModelLamp6, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara recamara arriba
		glm::mat4 matrixModelLamp7 = glm::mat4(1.0);
		matrixModelLamp7 = glm::translate(matrixModelLamp7, glm::vec3(7.5, 4.65, 4.0));
		modelLampara.render(glm::scale(matrixModelLamp7, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//recamara arriba2
		glm::mat4 matrixModelLamp8 = glm::mat4(1.0);
		matrixModelLamp8 = glm::translate(matrixModelLamp8, glm::vec3(7.5, 4.65, -2.5));
		modelLampara.render(glm::scale(matrixModelLamp8, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara cochera
		glm::mat4 matrixModelLamp9 = glm::mat4(1.0);
		matrixModelLamp9 = glm::translate(matrixModelLamp9, glm::vec3(-4.15, 1.0, 0.0));
		modelLampara.render(glm::scale(matrixModelLamp9, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);

		//lampara recamara arbol
		glm::mat4 matrixModelLamp10 = glm::mat4(1.0);
		matrixModelLamp10 = glm::translate(matrixModelLamp10, glm::vec3(-1.5, 4.65, 0.0));
		modelLampara.render(glm::scale(matrixModelLamp10, glm::vec3(0.2, 0.2, 0.2)));
		glActiveTexture(GL_TEXTURE0);





		/////////////////////////////////////////
		/////////////Decoraciones////////////////
		/////////////////////////////////////////
		glm::mat4 matrixModelTree = glm::mat4(1.0);
		matrixModelTree = glm::translate(matrixModelTree, glm::vec3(-4.1, 2.1, 5.0));
		matrixModelTree = glm::scale(matrixModelTree, glm::vec3(0.7, 0.6, 0.7));
		modelTree.render(matrixModelTree);

		glm::mat4 matrixModelStar = glm::mat4(1.0);
		matrixModelStar = glm::translate(matrixModelStar, glm::vec3(-4.1, 4.8, 5.0));
		matrixModelStar = glm::scale(matrixModelStar, glm::vec3(0.15, 0.15, 0.15));
		modelStar.render(matrixModelStar);

		glm::mat4 matrixModelSnowman = glm::mat4(1.0);
		matrixModelSnowman = glm::translate(matrixModelSnowman, glm::vec3(-4.5, 5.8, 6.1));
		matrixModelSnowman = glm::rotate(matrixModelSnowman, glm::radians(-135.0f), glm::vec3(0.0, 1.0, 0.0));
		matrixModelSnowman = glm::scale(matrixModelSnowman, glm::vec3(2.5, 2.5, 2.5));
		snowMan.render(matrixModelSnowman);

		glm::mat4 matrixModelTrineo = glm::mat4(1.0);
		matrixModelTrineo = glm::translate(matrixModelTrineo, glm::vec3(0.0, 6.6, 5.0));
		matrixModelTrineo = glm::rotate(matrixModelTrineo, glm::radians(-135.0f), glm::vec3(0.0, 1.0, 0.0));
		matrixModelTrineo = glm::scale(matrixModelTrineo, glm::vec3(0.8, 0.8, 0.8));
		modelTrineo.render(matrixModelTrineo);

		glm::mat4 matrixModelCorona = glm::mat4(1.0);
		matrixModelCorona = glm::translate(matrixModelCorona, glm::vec3(-2.5, 0.5, 3.75));
		matrixModelCorona = glm::rotate(matrixModelCorona, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
		modelCoronaDecoracion.render(matrixModelCorona);

		glm::mat4 matrixModelCorona2 = glm::mat4(1.0);
		matrixModelCorona2 = glm::translate(matrixModelCorona2, glm::vec3(-5.3, 3.6, 0.0));
		matrixModelCorona2 = glm::rotate(matrixModelCorona2, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
		modelCoronaDecoracion.render(matrixModelCorona2);

		/*glm::mat4 matrixSantaHatModel = glm::mat4(1.0);
		matrixSantaHatModel = glm::translate(matrixSantaHatModel, glm::vec3(-5.3, 2.6, -1.5));
		matrixSantaHatModel = glm::rotate(matrixSantaHatModel, glm::radians(90.0f), glm::vec3(0, 1, 0));
		modelSantaHat.render(matrixSantaHatModel);*/

		////////////////////////
		//////Nochebuenas///////
		////////////////////////

		glm::mat4 matrixModelNocheBuena1 = glm::mat4(1.0);
		matrixModelNocheBuena1 = glm::translate(matrixModelNocheBuena1, glm::vec3(-3.0, -1.5, 3.0));
		modelNocheBuena.render(glm::scale(matrixModelNocheBuena1, glm::vec3(0.8, 0.8, 0.8)));

		glm::mat4 matrixModelNocheBuena2 = glm::mat4(1.0);
		matrixModelNocheBuena2 = glm::translate(matrixModelNocheBuena2, glm::vec3(-3.0, -1.5, 0.0));
		modelNocheBuena.render(glm::scale(matrixModelNocheBuena2, glm::vec3(0.8, 0.8, 0.8)));

		glm::mat4 matrixModelNocheBuena3 = glm::mat4(1.0);
		matrixModelNocheBuena3 = glm::translate(matrixModelNocheBuena3, glm::vec3(-3.0, -1.5, -3.0));
		modelNocheBuena.render(glm::scale(matrixModelNocheBuena3, glm::vec3(0.8, 0.8, 0.8)));

		glm::mat4 matrixModelNocheBuena4 = glm::mat4(1.0);
		matrixModelNocheBuena4 = glm::translate(matrixModelNocheBuena4, glm::vec3(-5.5, -1.5, 3.0));
		modelNocheBuena.render(glm::scale(matrixModelNocheBuena4, glm::vec3(0.8, 0.8, 0.8)));

		glm::mat4 matrixModelNocheBuena5 = glm::mat4(1.0);
		matrixModelNocheBuena5 = glm::translate(matrixModelNocheBuena5, glm::vec3(-5.5, -1.5, 0.0));
		modelNocheBuena.render(glm::scale(matrixModelNocheBuena5, glm::vec3(0.8, 0.8, 0.8)));

		glm::mat4 matrixModelNocheBuena6 = glm::mat4(1.0);
		matrixModelNocheBuena6 = glm::translate(matrixModelNocheBuena6, glm::vec3(-5.5, -1.5, -3.0));
		modelNocheBuena.render(glm::scale(matrixModelNocheBuena6, glm::vec3(0.8, 0.8, 0.8)));

		glm::mat4 matrixModelNocheBuena7 = glm::mat4(1.0);
		matrixModelNocheBuena7 = glm::translate(matrixModelNocheBuena7, glm::vec3(-5.3, 2.1, -1.5));
		modelNocheBuena.render(glm::scale(matrixModelNocheBuena7, glm::vec3(0.8, 0.8, 0.8)));

		glm::mat4 matrixModelNocheBuena8 = glm::mat4(1.0);
		matrixModelNocheBuena8 = glm::translate(matrixModelNocheBuena8, glm::vec3(-5.3, 2.1, 1.5));
		modelNocheBuena.render(glm::scale(matrixModelNocheBuena8, glm::vec3(0.8, 0.8, 0.8)));

		////////////////////////
		///////Pinatas//////////
		////////////////////////

		glm::mat4 matrixModelPinata1 = glm::mat4(1.0);
		matrixModelPinata1 = glm::translate(matrixModelPinata1, glm::vec3(-4.5, 1.0, 3.75));
		modelPinata.render(glm::scale(matrixModelPinata1, glm::vec3(0.15, 0.15, 0.15)));

		glm::mat4 matrixModelPinata2 = glm::mat4(1.0);
		matrixModelPinata2 = glm::translate(matrixModelPinata2, glm::vec3(-4.5, 1.0, 0.75));
		modelPinata.render(glm::scale(matrixModelPinata2, glm::vec3(0.15, 0.15, 0.15)));

		///////////////////////
		/////Esferas///////////
		/////////////////////

		glm::mat4 matrixModelChBall1 = glm::mat4(1.0);
		matrixModelChBall1 = glm::translate(matrixModelChBall1, glm::vec3(-4.0, 4.4, 4.8));
		modelChBall1.render(glm::scale(matrixModelChBall1, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall2 = glm::mat4(1.0);
		matrixModelChBall2 = glm::translate(matrixModelChBall2, glm::vec3(-4.3, 4.4, 4.9));
		modelChBall2.render(glm::scale(matrixModelChBall2, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall3 = glm::mat4(1.0);
		matrixModelChBall3 = glm::translate(matrixModelChBall3, glm::vec3(-4.3, 4.0, 4.8));
		modelChBall3.render(glm::scale(matrixModelChBall3, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall4 = glm::mat4(1.0);
		matrixModelChBall4 = glm::translate(matrixModelChBall4, glm::vec3(-4.0, 4.0, 4.7));
		modelChBall5.render(glm::scale(matrixModelChBall4, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall5 = glm::mat4(1.0);
		matrixModelChBall5 = glm::translate(matrixModelChBall5, glm::vec3(-3.8, 4.0, 5.0));
		modelChBall4.render(glm::scale(matrixModelChBall5, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall6 = glm::mat4(1.0);
		matrixModelChBall6 = glm::translate(matrixModelChBall6, glm::vec3(-4.3, 4.0, 5.1));
		modelChBall1.render(glm::scale(matrixModelChBall6, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall7 = glm::mat4(1.0);
		matrixModelChBall7 = glm::translate(matrixModelChBall7, glm::vec3(-4.0, 4.0, 5.1));
		modelChBall2.render(glm::scale(matrixModelChBall7, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall8 = glm::mat4(1.0);
		matrixModelChBall8 = glm::translate(matrixModelChBall8, glm::vec3(-3.8, 3.6, 5.1));
		modelChBall3.render(glm::scale(matrixModelChBall8, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall9 = glm::mat4(1.0);
		matrixModelChBall9 = glm::translate(matrixModelChBall9, glm::vec3(-4.1, 3.6, 5.2));
		modelChBall1.render(glm::scale(matrixModelChBall9, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall10 = glm::mat4(1.0);
		matrixModelChBall10 = glm::translate(matrixModelChBall10, glm::vec3(-4.4, 3.6, 5.3));
		modelChBall4.render(glm::scale(matrixModelChBall10, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall11 = glm::mat4(1.0);
		matrixModelChBall11 = glm::translate(matrixModelChBall11, glm::vec3(-3.8, 3.6, 4.7));
		modelChBall2.render(glm::scale(matrixModelChBall11, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall12 = glm::mat4(1.0);
		matrixModelChBall12 = glm::translate(matrixModelChBall12, glm::vec3(-4.1, 3.6, 4.6));
		modelChBall4.render(glm::scale(matrixModelChBall12, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall13 = glm::mat4(1.0);
		matrixModelChBall13 = glm::translate(matrixModelChBall13, glm::vec3(-4.4, 3.6, 4.7));
		modelChBall5.render(glm::scale(matrixModelChBall13, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall14 = glm::mat4(1.0);
		matrixModelChBall14 = glm::translate(matrixModelChBall14, glm::vec3(-3.7, 3.2, 5.3));
		modelChBall2.render(glm::scale(matrixModelChBall14, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall15 = glm::mat4(1.0);
		matrixModelChBall15 = glm::translate(matrixModelChBall15, glm::vec3(-4.1, 3.2, 5.4));
		modelChBall1.render(glm::scale(matrixModelChBall15, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall16 = glm::mat4(1.0);
		matrixModelChBall16 = glm::translate(matrixModelChBall16, glm::vec3(-4.5, 3.2, 5.4));
		modelChBall5.render(glm::scale(matrixModelChBall16, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall17 = glm::mat4(1.0);
		matrixModelChBall17 = glm::translate(matrixModelChBall17, glm::vec3(-3.7, 3.2, 4.5));
		modelChBall4.render(glm::scale(matrixModelChBall17, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall18 = glm::mat4(1.0);
		matrixModelChBall18 = glm::translate(matrixModelChBall18, glm::vec3(-4.1, 3.2, 4.4));
		modelChBall3.render(glm::scale(matrixModelChBall18, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall19 = glm::mat4(1.0);
		matrixModelChBall19 = glm::translate(matrixModelChBall19, glm::vec3(-4.5, 3.2, 4.5));
		modelChBall2.render(glm::scale(matrixModelChBall19, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall20 = glm::mat4(1.0);
		matrixModelChBall20 = glm::translate(matrixModelChBall20, glm::vec3(-3.7, 2.8, 5.4));
		modelChBall4.render(glm::scale(matrixModelChBall20, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall26 = glm::mat4(1.0);
		matrixModelChBall26 = glm::translate(matrixModelChBall26, glm::vec3(-3.5, 2.8, 5.0));
		modelChBall3.render(glm::scale(matrixModelChBall26, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall27 = glm::mat4(1.0);
		matrixModelChBall27 = glm::translate(matrixModelChBall27, glm::vec3(-3.6, 3.2, 4.8));
		modelChBall5.render(glm::scale(matrixModelChBall27, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall28 = glm::mat4(1.0);
		matrixModelChBall28 = glm::translate(matrixModelChBall28, glm::vec3(-3.5, 2.4, 5.0));
		modelChBall1.render(glm::scale(matrixModelChBall28, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall21 = glm::mat4(1.0);
		matrixModelChBall21 = glm::translate(matrixModelChBall21, glm::vec3(-4.1, 2.8, 5.6));
		modelChBall2.render(glm::scale(matrixModelChBall21, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall22 = glm::mat4(1.0);
		matrixModelChBall22 = glm::translate(matrixModelChBall22, glm::vec3(-4.5, 2.8, 5.4));
		modelChBall1.render(glm::scale(matrixModelChBall22, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall23 = glm::mat4(1.0);
		matrixModelChBall23 = glm::translate(matrixModelChBall23, glm::vec3(-3.7, 2.8, 4.5));
		modelChBall1.render(glm::scale(matrixModelChBall23, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall24 = glm::mat4(1.0);
		matrixModelChBall24 = glm::translate(matrixModelChBall24, glm::vec3(-4.1, 2.8, 4.4));
		modelChBall5.render(glm::scale(matrixModelChBall24, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall25 = glm::mat4(1.0);
		matrixModelChBall25 = glm::translate(matrixModelChBall25, glm::vec3(-4.5, 2.8, 4.5));
		modelChBall3.render(glm::scale(matrixModelChBall25, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall29 = glm::mat4(1.0);
		matrixModelChBall29 = glm::translate(matrixModelChBall29, glm::vec3(-3.7, 2.4, 5.3));
		modelChBall2.render(glm::scale(matrixModelChBall29, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall30 = glm::mat4(1.0);
		matrixModelChBall30 = glm::translate(matrixModelChBall30, glm::vec3(-4.1, 2.4, 5.4));
		modelChBall1.render(glm::scale(matrixModelChBall30, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall31 = glm::mat4(1.0);
		matrixModelChBall31 = glm::translate(matrixModelChBall31, glm::vec3(-4.5, 2.4, 5.4));
		modelChBall5.render(glm::scale(matrixModelChBall31, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall32 = glm::mat4(1.0);
		matrixModelChBall32 = glm::translate(matrixModelChBall32, glm::vec3(-3.7, 2.4, 4.5));
		modelChBall4.render(glm::scale(matrixModelChBall32, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall33 = glm::mat4(1.0);
		matrixModelChBall33 = glm::translate(matrixModelChBall33, glm::vec3(-4.1, 2.4, 4.4));
		modelChBall3.render(glm::scale(matrixModelChBall33, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelChBall34 = glm::mat4(1.0);
		matrixModelChBall34 = glm::translate(matrixModelChBall34, glm::vec3(-4.5, 2.4, 4.5));
		modelChBall2.render(glm::scale(matrixModelChBall34, glm::vec3(0.5, 0.5, 0.5)));
		///////////////////////
		/////Regalos///////////
		/////////////////////

		modelRegalo1.render(matrixModelRegalo1);

		modelRegalo2.render(matrixModelRegalo2);

		modelRegalo3.render(matrixModelRegalo3);

		///////////////////////
		/////Objetos pesebre///////////
		/////////////////////
		glm::mat4 pesebre3 = glm::mat4(1.0);
		pesebre3 = glm::translate(pesebre3, glm::vec3(3.0, 2.2, 4.0));
		pesebre3 = glm::rotate(pesebre3, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
		modelCabine.render(glm::scale(pesebre3, glm::vec3(0.8, 0.7, 0.5)));

		glm::mat4 pisoPesebre = glm::mat4(1.0);
		pisoPesebre = glm::translate(pisoPesebre, glm::vec3(2.5, 2.2, 4.0));
		modelPiso.render(pisoPesebre);

		glm::mat4 camello = glm::mat4(1.0);
		camello = glm::translate(camello, glm::vec3(1.0, 2.3, 3.0));
		camello = glm::rotate(camello, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
		modelCamello.render(glm::scale(camello, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 Cow = glm::mat4(1.0);
		Cow = glm::translate(Cow, glm::vec3(3.5, 2.3, 3.5));
		modelCow.render(glm::scale(Cow, glm::vec3(0.3, 0.3, 0.3)));

		glm::mat4 matrixModelDeer = glm::mat4(1.0);
		matrixModelDeer = glm::translate(matrixModelDeer, glm::vec3(2.5, 2.2, 2.5));
		matrixModelDeer = glm::rotate(matrixModelDeer, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
		modelDeer.render(glm::scale(matrixModelDeer, glm::vec3(0.5, 0.5, 0.5)));

		glm::mat4 matrixModelSheep1 = glm::mat4(1.0);
		matrixModelSheep1 = glm::translate(matrixModelSheep1, glm::vec3(3.0, 2.2, 3.5));
		matrixModelSheep1 = glm::rotate(matrixModelSheep1, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
		modelSheep.render(glm::scale(matrixModelSheep1, glm::vec3(0.2, 0.2, 0.2)));

		glm::mat4 matrixModelSheep2 = glm::mat4(1.0);
		matrixModelSheep2 = glm::translate(matrixModelSheep2, glm::vec3(2.0, 2.2, 3.5));
		matrixModelSheep2 = glm::rotate(matrixModelSheep2, glm::radians(-45.0f), glm::vec3(0.0, 1.0, 0.0));
		modelSheep.render(glm::scale(matrixModelSheep2, glm::vec3(0.2, 0.2, 0.2)));


		glm::mat4 matrixModelSheep3 = glm::mat4(1.0);
		matrixModelSheep3 = glm::translate(matrixModelSheep3, glm::vec3(2.0, 2.2, 2.5));
		modelSheep.render(glm::scale(matrixModelSheep3, glm::vec3(0.2, 0.2, 0.2)));

		glm::mat4 matrixModelSheep4 = glm::mat4(1.0);
		matrixModelSheep4 = glm::translate(matrixModelSheep4, glm::vec3(1.2, 2.2, 2));
		matrixModelSheep4 = glm::rotate(matrixModelSheep4, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
		modelSheep.render(glm::scale(matrixModelSheep4, glm::vec3(0.2, 0.2, 0.2)));

		glm::mat4 matrixModelSheep5 = glm::mat4(1.0);
		matrixModelSheep5 = glm::translate(matrixModelSheep5, glm::vec3(3.2, 2.2, 2));
		matrixModelSheep5 = glm::rotate(matrixModelSheep5, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
		modelSheep.render(glm::scale(matrixModelSheep5, glm::vec3(0.2, 0.2, 0.2)));

		glm::mat4 matrixModelChicken1 = glm::mat4(1.0);
		matrixModelChicken1 = glm::translate(matrixModelChicken1, glm::vec3(1.6, 2.2, 2.7));
		matrixModelChicken1 = glm::rotate(matrixModelChicken1, glm::radians(135.0f), glm::vec3(0.0, 1.0, 0.0));
		modelChicken.render(glm::scale(matrixModelChicken1, glm::vec3(0.2, 0.2, 0.2)));

		glm::mat4 matrixModelChicken2 = glm::mat4(1.0);
		matrixModelChicken2 = glm::translate(matrixModelChicken2, glm::vec3(3.0, 2.2, 2.7));
		matrixModelChicken2 = glm::rotate(matrixModelChicken2, glm::radians(135.0f), glm::vec3(0.0, 1.0, 0.0));
		modelChicken.render(glm::scale(matrixModelChicken2, glm::vec3(0.2, 0.2, 0.2)));

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////RENDER ANIMACIONES/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////
		/////Render eclipse//////////////////////
		/////////////////////////////////////////
		//Chasis
		modelCar.render(matrixModelCar);
		glActiveTexture(GL_TEXTURE0);
		//Llantas delanteras
		// Render for the eclipse car llantas delanteras
		glm::mat4 modelMatrixEclipseFrontalWheels = glm::mat4(matrixModelCar);
		modelMatrixEclipseFrontalWheels = glm::translate(modelMatrixEclipseFrontalWheels, glm::vec3(0.0, 1.06285, 4.11795));
		//Rotacion de llanata cuando da vuelta
		modelMatrixEclipseFrontalWheels = glm::rotate(modelMatrixEclipseFrontalWheels, rotWheely, glm::vec3(0, 1, 0));
		modelMatrixEclipseFrontalWheels = glm::rotate(modelMatrixEclipseFrontalWheels, rotWheelx, glm::vec3(1, 0, 0));
		modelMatrixEclipseFrontalWheels = glm::translate(modelMatrixEclipseFrontalWheels, glm::vec3(0.0, -1.06285, -4.11795));
		modelEclipseWheelsFrontal.render(modelMatrixEclipseFrontalWheels);
		glActiveTexture(GL_TEXTURE0);

		// Render for the eclipse car llantas atras
		glm::mat4 modelMatrixEclipseRealWheels = glm::mat4(matrixModelCar);
		modelMatrixEclipseRealWheels = glm::translate(modelMatrixEclipseRealWheels, glm::vec3(0.0, 1.05128, -4.34651));
		modelMatrixEclipseRealWheels = glm::rotate(modelMatrixEclipseRealWheels, rotWheelx, glm::vec3(1, 0, 0));
		modelMatrixEclipseRealWheels = glm::translate(modelMatrixEclipseRealWheels, glm::vec3(0.0, -1.05128, 4.34651));
		modelEclipseWheelsRear.render(modelMatrixEclipseRealWheels);
		glActiveTexture(GL_TEXTURE0);


		/////////////////////////////////////////
		//////////RENDER HELICOPTERO/////////////
		/////////////////////////////////////////
		modelHeliChasis.render(modelMatrixHeliChasis);
		glActiveTexture(GL_TEXTURE0);

		// Helices Helicoptero
		glm::mat4 modelMatrixHeliHeli = glm::mat4(modelMatrixHeliChasis);
		modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(-0.003344, 1.88318, -0.254566));
		modelMatrixHeliHeli = glm::rotate(modelMatrixHeliHeli, rotHeliHeliy, glm::vec3(0, 1, 0));
		modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.003344, -1.88318, 0.254566));
		modelHeliHeliMeid.render(modelMatrixHeliHeli);
		glActiveTexture(GL_TEXTURE0);
		//Helice chica
		glm::mat4 modelMatrixHeliHeli2 = glm::mat4(modelMatrixHeliChasis);
		modelMatrixHeliHeli2 = glm::translate(modelMatrixHeliHeli2, glm::vec3(0.4685, 2.099, -5.645));
		modelMatrixHeliHeli2 = glm::rotate(modelMatrixHeliHeli2, rotHeliHeliz, glm::vec3(1, 0, 0));
		modelMatrixHeliHeli2 = glm::translate(modelMatrixHeliHeli2, glm::vec3(-0.4685, -2.099, 5.645));
		modelHeliHeliCh.render(modelMatrixHeliHeli2);
		glActiveTexture(GL_TEXTURE0);

		/////////////////////////////////////////
		//////////RENDER Lambo/////////////
		/////////////////////////////////////////

		//chasis
		modelLambo.render(modelMatrixLambo);
		glActiveTexture(GL_TEXTURE0);

		//puertas
		glm::mat4 modelMatrixLamboLeftDor = glm::mat4(modelMatrixLambo);
		modelMatrixLamboLeftDor = glm::translate(modelMatrixLamboLeftDor, glm::vec3(1.08676, 0.707316, 0.982601));
		modelMatrixLamboLeftDor = glm::rotate(modelMatrixLamboLeftDor, glm::radians(dorRotCount), glm::vec3(1.0, 0, 0));
		modelMatrixLamboLeftDor = glm::translate(modelMatrixLamboLeftDor, glm::vec3(-1.08676, -0.707316, -0.982601));
		modelLamboLeftDor.render(modelMatrixLamboLeftDor);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 modelMatrixLamboLeftDoor2 = glm::mat4(modelMatrixLambo);
		modelMatrixLamboLeftDoor2 = glm::translate(modelMatrixLamboLeftDoor2, glm::vec3(-1.113, 0.707316, 0.982601));
		modelMatrixLamboLeftDoor2 = glm::rotate(modelMatrixLamboLeftDoor2, glm::radians(dorRotCount), glm::vec3(1.0, 0, 0));
		modelMatrixLamboLeftDoor2 = glm::translate(modelMatrixLamboLeftDoor2, glm::vec3(1.113, -0.707316, -0.982601));
		modelLamboRightDoor.render(modelMatrixLamboLeftDoor2);
		glActiveTexture(GL_TEXTURE0);

		//llantas enfrente
		glm::mat4 modelMatrixLamboFrontalWheels = glm::mat4(modelMatrixLambo);
		modelMatrixLamboFrontalWheels = glm::translate(modelMatrixLamboFrontalWheels, glm::vec3(0.0, 0.3722, 1.409));
		//Rotacion de llanata cuando da vuelta
		//modelMatrixLamboFrontalWheels = glm::rotate(modelMatrixLamboFrontalWheels, rotWheelLamboY, glm::vec3(0, 1, 0));
		modelMatrixLamboFrontalWheels = glm::rotate(modelMatrixLamboFrontalWheels, rotWheelLamboX, glm::vec3(1, 0, 0));
		modelMatrixLamboFrontalWheels = glm::translate(modelMatrixLamboFrontalWheels, glm::vec3(0.0, -0.3722, -1.409));
		modelLamboFrontWheels.render(modelMatrixLamboFrontalWheels);
		glActiveTexture(GL_TEXTURE0);


		//llantas atras
		glm::mat4 modelMatrixLamboRealWheels = glm::mat4(modelMatrixLambo);
		modelMatrixLamboRealWheels = glm::translate(modelMatrixLamboRealWheels, glm::vec3(0.0, 0.3722, -1.609));
		modelMatrixLamboRealWheels = glm::rotate(modelMatrixLamboRealWheels, rotWheelLamboX, glm::vec3(1, 0, 0));
		modelMatrixLamboRealWheels = glm::translate(modelMatrixLamboRealWheels, glm::vec3(0.0, -0.3722, 1.609));
		modelLamboBackWheels.render(modelMatrixLamboRealWheels);
		glActiveTexture(GL_TEXTURE0);


		///////////////////////////////////////////////////////////////////////
		//////////////////////////FIN CASA NAVIDAD////////////////////////////
		///////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////MAQUINAS DE ESTADOS/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////
		/////////////////STATE MACHINE Eclipse car/////////////////////////
		///////////////////////////////////////////////////////////////////
		switch (state)
		{
		case 0:
			matrixModelCar = glm::translate(matrixModelCar, glm::vec3(0.0, 0.0, 0.1));
			offsetAircraftAdvance += 0.1;
			rotWheely -= 0.01;
			if (rotWheely < 0)
				rotWheely = 0;
			if (offsetAircraftAdvance > 30.0) {
				offsetAircraftAdvance = 0.0;
				state = 1;
			}
			break;
		case 1:
			matrixModelCar = glm::translate(matrixModelCar, glm::vec3(0.0, 0.0, 0.01));
			matrixModelCar = glm::rotate(matrixModelCar, glm::radians(0.05f), glm::vec3(0.0, 1.0, 0.0));
			offsetAircraftRot += 0.05;
			rotWheely += 0.0001;
			if (rotWheely < glm::radians(15.0))
				rotWheely = glm::radians(15.0);
			if (offsetAircraftRot > 90) {
				offsetAircraftRot = 0.0;
				state = 0;
			}
			break;
		default:
			break;
		}

		///////////////////////////////////////////////////////////////////
		/////////////////STATE MACHINE HELICOPTERO/////////////////////
		///////////////////////////////////////////////////////////////////
		switch (stateheli) {
		case 0:
			modelMatrixHeliChasis = glm::translate(modelMatrixHeliChasis, glm::vec3(-0.1, -0.1, 0.0));
			offsetHeliAdvance += 0.1;
			if (offsetHeliAdvance > 14.7) {
				offsetHeliAdvance = 0.0;
				stateheli = 2;
			}
			break;
		case 1:
			modelMatrixHeliChasis = glm::translate(modelMatrixHeliChasis, glm::vec3(0.1, 0.1, 0));
			offsetHeliAdvance += 0.1;
			if (offsetHeliAdvance > 14.7) {
				offsetHeliAdvance = 0.0;
				stateheli = 0;
			}

			break;
		case 2:
			offsetState += 0.2;
			if (offsetState > 18.0) {
				offsetState = 0;
				stateheli = 1;
			}
			break;
		default:
			break;
		}

		/////////////////////////////////////////////////////
		/////////////////State machine lambo/////////////////////
		/////////////////////////////////////////////////////
		switch (stateDoor) {
		case 0:
			modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(0.0, 0.0, 0.1));
			offsetLamboAdvance += 0.1;
			rotWheelLamboX += 0.1;

			if (offsetLamboAdvance > 10.0) {
				offsetLamboAdvance = 0.0;
				stateDoor = 1;
			}

			break;
		case 1:
			modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(0.0, 0.0, 0.1));
			modelMatrixLambo = glm::rotate(modelMatrixLambo, glm::radians(0.4f), glm::vec3(0.0, 1.0, 0.0));
			rotWheelLamboX += 0.1;
			offsetLamboRot += 0.4;
			if (offsetLamboRot > 25) {
				offsetLamboRot = 0.0;
				stateDoor = 2;
			}
			break;
		case 2:
			dorRotCount += 0.5;
			if (dorRotCount > 75)
				stateDoor = 3;
			break;
		case 3:
			dorRotCount -= 0.5;
			if (dorRotCount < 0) {
				dorRotCount = 0.0;
				stateDoor = 4;
			}
			break;
		case 4:
			modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(0.0, 0.0, -0.1));
			modelMatrixLambo = glm::rotate(modelMatrixLambo, glm::radians(-0.4f), glm::vec3(0.0, 1.0, 0.0));
			rotWheelLamboX -= 0.1;
			offsetLamboRot += 0.4;
			if (offsetLamboRot > 25) {
				offsetLamboRot = 0.0;
				stateDoor = 5;
			}
			break;
		case 5:
			modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(0.0, 0.0, -0.1));
			offsetLamboAdvance += 0.1;
			rotWheelLamboX -= 0.1;
			if (offsetLamboAdvance > 10.0) {
				offsetLamboAdvance = 0.0;
				stateDoor = 0;
			}
			break;
		}

		///////////////////////////////////////////////////////////////////
		/////////////////STATE MACHINE Regalos/////////////////////////
		///////////////////////////////////////////////////////////////////
		switch (state)
		{
		case 0:
			matrixModelRegalo1 = glm::translate(matrixModelRegalo1, glm::vec3(0.0, 0.01, 0.0));
			matrixModelRegalo3 = glm::translate(matrixModelRegalo3, glm::vec3(0.0, -0.01, 0.0));
			matrixModelRegalo1 = glm::rotate(matrixModelRegalo1, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));
			matrixModelRegalo3 = glm::rotate(matrixModelRegalo3, glm::radians(-0.5f), glm::vec3(0.0, 1.0, 0.0));
			matrixModelRegalo2 = glm::rotate(matrixModelRegalo2, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));

			offsetRegalo1 += 0.1;

			if (offsetRegalo1 > 1.0) {
				offsetRegalo1 = 0.0;
				state = 1;
			}
			break;
		case 1:
			matrixModelRegalo1 = glm::translate(matrixModelRegalo1, glm::vec3(0.0, -0.01, -0.0));
			matrixModelRegalo3 = glm::translate(matrixModelRegalo3, glm::vec3(0.0, 0.01, 0.0));
			matrixModelRegalo1 = glm::rotate(matrixModelRegalo1, glm::radians(-0.5f), glm::vec3(0.0, 1.0, 0.0));
			matrixModelRegalo3 = glm::rotate(matrixModelRegalo3, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));
			matrixModelRegalo2 = glm::rotate(matrixModelRegalo2, glm::radians(-0.5f), glm::vec3(0.0, 1.0, 0.0));

			offsetRegalo1 += 0.1;

			if (offsetRegalo1 > 1.0) {
				offsetRegalo1 = 0.0;
				state = 0;
			}
			break;
		default:
			break;
		}

		// Dart lego
		// Se deshabilita el cull faces IMPORTANTE para la capa
		glDisable(GL_CULL_FACE);
		modelDartLegoBody.render(modelMatrixDart);
		glm::mat4 modelMatrixDartHead = glm::mat4(modelMatrixDart);
		modelMatrixDartHead = glm::rotate(modelMatrixDartHead, rotDartHead, glm::vec3(0, 1, 0));
		modelDartLegoHead.render(modelMatrixDartHead);
		modelDartLegoMask.render(modelMatrixDartHead);
		glm::mat4 modelMatrixDartLeftArm = glm::mat4(modelMatrixDart);
		modelMatrixDartLeftArm = glm::translate(modelMatrixDartLeftArm, glm::vec3(-0.023515, 2.43607, 0.446066));
		modelMatrixDartLeftArm = glm::rotate(modelMatrixDartLeftArm, glm::radians(-10.0f), glm::vec3(1, 0, 0));
		modelMatrixDartLeftArm = glm::rotate(modelMatrixDartLeftArm, rotDartLeftArm, glm::vec3(0, 0, 1));
		modelMatrixDartLeftArm = glm::rotate(modelMatrixDartLeftArm, glm::radians(10.0f), glm::vec3(1, 0, 0));
		modelMatrixDartLeftArm = glm::translate(modelMatrixDartLeftArm, glm::vec3(0.023515, -2.43607, -0.446066));
		modelDartLegoLeftArm.render(modelMatrixDartLeftArm);
		glm::mat4 modelMatrixDartLeftHand = glm::mat4(modelMatrixDartLeftArm);
		modelMatrixDartLeftHand = glm::translate(modelMatrixDartLeftHand, glm::vec3(0.201343, 1.68317, 0.99774));
		modelMatrixDartLeftHand = glm::rotate(modelMatrixDartLeftHand, glm::radians(-10.0f), glm::vec3(1, 0, 0));
		modelMatrixDartLeftHand = glm::rotate(modelMatrixDartLeftHand, rotDartLeftHand, glm::vec3(0, 1, 0));
		modelMatrixDartLeftHand = glm::rotate(modelMatrixDartLeftHand, glm::radians(10.0f), glm::vec3(1, 0, 0));
		modelMatrixDartLeftHand = glm::translate(modelMatrixDartLeftHand, glm::vec3(-0.201343, -1.68317, -0.99774));
		modelDartLegoLeftHand.render(modelMatrixDartLeftHand);
		glm::mat4 modelMatrixDartRightArm = glm::mat4(modelMatrixDart);
		modelMatrixDartRightArm = glm::translate(modelMatrixDartRightArm, glm::vec3(-0.023515, 2.43607, -0.446066));
		modelMatrixDartRightArm = glm::rotate(modelMatrixDartRightArm, glm::radians(10.0f), glm::vec3(1, 0, 0));
		modelMatrixDartRightArm = glm::rotate(modelMatrixDartRightArm, rotDartRightArm, glm::vec3(0, 0, 1));
		modelMatrixDartRightArm = glm::rotate(modelMatrixDartRightArm, glm::radians(-10.0f), glm::vec3(1, 0, 0));
		modelMatrixDartRightArm = glm::translate(modelMatrixDartRightArm, glm::vec3(0.023515, -2.43607, 0.446066));
		modelDartLegoRightArm.render(modelMatrixDartRightArm);
		glm::mat4 modelMatrixDartRightHand = glm::mat4(modelMatrixDartRightArm);
		modelMatrixDartRightHand = glm::translate(modelMatrixDartRightHand, glm::vec3(0.201343, 1.68317, -0.99774));
		modelMatrixDartRightHand = glm::rotate(modelMatrixDartRightHand, glm::radians(10.0f), glm::vec3(1, 0, 0));
		modelMatrixDartRightHand = glm::rotate(modelMatrixDartRightHand, rotDartRightHand, glm::vec3(0, 1, 0));
		modelMatrixDartRightHand = glm::rotate(modelMatrixDartRightHand, glm::radians(-10.0f), glm::vec3(1, 0, 0));
		modelMatrixDartRightHand = glm::translate(modelMatrixDartRightHand, glm::vec3(-0.201343, -1.68317, 0.99774));
		modelDartLegoRightHand.render(modelMatrixDartRightHand);
		glm::mat4 modelMatrixDartLeftLeg = glm::mat4(modelMatrixDart);
		modelMatrixDartLeftLeg = glm::translate(modelMatrixDartLeftLeg, glm::vec3(0, 1.12632, 0.423349));
		modelMatrixDartLeftLeg = glm::rotate(modelMatrixDartLeftLeg, rotDartLeftLeg, glm::vec3(0, 0, 1));
		modelMatrixDartLeftLeg = glm::translate(modelMatrixDartLeftLeg, glm::vec3(0, -1.12632, -0.423349));
		modelDartLegoLeftLeg.render(modelMatrixDartLeftLeg);
		glm::mat4 modelMatrixDartRightLeg = glm::mat4(modelMatrixDart);
		modelMatrixDartRightLeg = glm::translate(modelMatrixDartRightLeg, glm::vec3(0, 1.12632, -0.423349));
		modelMatrixDartRightLeg = glm::rotate(modelMatrixDartRightLeg, rotDartRightLeg, glm::vec3(0, 0, 1));
		modelMatrixDartRightLeg = glm::translate(modelMatrixDartRightLeg, glm::vec3(0, -1.12632, 0.423349));
		modelDartLegoRightLeg.render(modelMatrixDartRightLeg);
		glActiveTexture(GL_TEXTURE0); // IMPORTANTE regresar a la textura 0
		// Se regresa el cull faces IMPORTANTE para la capa
		glEnable(GL_CULL_FACE);

		// Para salvar el frame
		if (record && modelSelected == 1) {
			matrixJoints.push_back(rotDartHead);
			matrixJoints.push_back(rotDartLeftArm);
			matrixJoints.push_back(rotDartLeftHand);
			matrixJoints.push_back(rotDartRightArm);
			matrixJoints.push_back(rotDartRightHand);
			matrixJoints.push_back(rotDartLeftLeg);
			matrixJoints.push_back(rotDartRightLeg);
			if (saveFrame) {
				appendFrame(myfile, matrixJoints);
				saveFrame = false;
			}
		}
		else if (keyFramesJoints.size() > 0) {
			// Para reproducir el frame
			interpolationJoints = numPasosJoints / (float)maxNumPasosJoints;
			numPasosJoints++;
			if (interpolationJoints > 1.0) {
				numPasosJoints = 0;
				interpolationJoints = 0;
				indexFrameJoints = indexFrameJointsNext;
				indexFrameJointsNext++;
			}
			if (indexFrameJointsNext > keyFramesJoints.size() - 1)
				indexFrameJointsNext = 0;

			rotDartHead = interpolate(keyFramesJoints, indexFrameJoints, indexFrameJointsNext, 0, interpolationJoints);
			rotDartLeftArm = interpolate(keyFramesJoints, indexFrameJoints, indexFrameJointsNext, 1, interpolationJoints);
			rotDartLeftHand = interpolate(keyFramesJoints, indexFrameJoints, indexFrameJointsNext, 2, interpolationJoints);
			rotDartRightArm = interpolate(keyFramesJoints, indexFrameJoints, indexFrameJointsNext, 3, interpolationJoints);
			rotDartRightHand = interpolate(keyFramesJoints, indexFrameJoints, indexFrameJointsNext, 4, interpolationJoints);
			rotDartLeftLeg = interpolate(keyFramesJoints, indexFrameJoints, indexFrameJointsNext, 5, interpolationJoints);
			rotDartRightLeg = interpolate(keyFramesJoints, indexFrameJoints, indexFrameJointsNext, 6, interpolationJoints);
		}

		if (record && modelSelected == 2) {
			modelMatrixDart = glm::translate(modelMatrixDart, glm::vec3(advanceDartBody, 0.0, 0.0));
			modelMatrixDart = glm::rotate(modelMatrixDart, rotDartBody, glm::vec3(0, 1, 0));
			matrixDart.push_back(modelMatrixDart);
			if (saveFrame) {
				appendFrame(myfile, matrixDart);
				saveFrame = false;
			}
		}
		else if (keyFramesDart.size() > 0) {
			// Para reproducir el frame
			interpolationDart = numPasosDart / (float)maxNumPasosDart;
			numPasosDart++;
			if (interpolationDart > 1.0) {
				numPasosDart = 0;
				interpolationDart = 0;
				indexFrameDart = indexFrameDartNext;
				indexFrameDartNext++;
			}
			if (indexFrameDartNext > keyFramesDart.size() - 1)
				indexFrameDartNext = 0;

			modelMatrixDart = interpolate(keyFramesDart, indexFrameDart, indexFrameDartNext, 0, interpolationDart);
		}

		//////////////////////////////////////////////////////////////////////
		////////////Condicionales para encender luces casa navidad/////////////////////////
		//////////////////////////////////////////////////////////////////////
		
		//sala
		if (numberCamera == 1) {		
			if (camera_is_in(-2.3, 4.5, -1.5, 1.8, 0.0, 5.9)) {
				onOffSala = 0.01;
				onOffComedor = 7;
				onOffCocina = 7;
				onOffBanio = 7;
				onOffRecamara1 = 7;
				onOffRecamara2 = 7;
				onOffRecamara3 = 7;
				onOffHabitacionArbol = 7;
				onOffCochera = 7;
			}
			//recamara1
			else if (camera_is_in(4.5, 10.4, -1.5, 1.8, 2.0, 5.9)){
				onOffSala = 7;
				onOffComedor = 7;
				onOffCocina = 7;
				onOffBanio = 7;
				onOffRecamara1 = 0.01;
				onOffRecamara2 = 7;
				onOffRecamara3 = 7;
				onOffHabitacionArbol = 7;
				onOffCochera = 7;
			}
			//baño
			else if (camera_is_in(-2.3, 0.4, -1.5, 1.8, -6.0, 0.0)){
				onOffSala = 7;
				onOffComedor = 7;
				onOffCocina = 7;
				onOffBanio = 0.01;
				onOffRecamara1 = 7;
				onOffRecamara2 = 7;
				onOffRecamara3 = 7;
				onOffHabitacionArbol = 7;
				onOffCochera = 7;
			}
			//comedor
			else if (camera_is_in(0.4, 4.5, -1.5, 1.8, -6.0, 0.0)) {
				onOffSala = 7;
				onOffComedor = 0.01;
				onOffCocina = 7;
				onOffBanio = 7;
				onOffRecamara1 = 7;
				onOffRecamara2 = 7;
				onOffRecamara3 = 7;
				onOffHabitacionArbol = 7;
				onOffCochera = 7;
			}
			//cocina
			else if (camera_is_in(4.5, 10.4, -1.5, 1.8, -6.0, 0.0)) {
				onOffSala = 7;
				onOffComedor = 7;
				onOffCocina = 0.01;
				onOffBanio = 7;
				onOffRecamara1 = 7;
				onOffRecamara2 = 7;
				onOffRecamara3 = 7;
				onOffHabitacionArbol = 7;
				onOffCochera = 7;
			}
			//recamara 2
			else if (camera_is_in(4.5, 10.4, 1.8, 5.9, 2.0, 5.9)) {
				onOffSala = 7;
				onOffComedor = 7;
				onOffCocina = 7;
				onOffBanio = 7;
				onOffRecamara1 = 7;
				onOffRecamara2 = 0.01;
				onOffRecamara3 = 7;
				onOffHabitacionArbol = 7;
				onOffCochera = 7;

			}
			//recamara 3
			else if (camera_is_in(4.5, 10.4, 1.8, 5.9, -6.0, 0.0)) {
				onOffSala = 7;
				onOffComedor = 7;
				onOffCocina = 7;
				onOffBanio = 7;
				onOffRecamara1 = 7;
				onOffRecamara2 = 7;
				onOffRecamara3 = 0.01;
				onOffHabitacionArbol = 7;
				onOffCochera = 7;
			}
			//habitacion arbol
			else if (camera_is_in(-6, 4.5, 1.8, 5.9, -6, 5.9)) {
				onOffSala = 7;
				onOffComedor = 7;
				onOffCocina = 7;
				onOffBanio = 7;
				onOffRecamara1 = 7;
				onOffRecamara2 = 7;
				onOffRecamara3 = 7;
				onOffHabitacionArbol = 0.01;
				onOffCochera = 7;
			}
			//cochera
			else if (camera_is_in(-6, -2.3, -1.5, 1.8, -6, 5.9)) {
				onOffSala = 7;
				onOffComedor = 7;
				onOffCocina = 7;
				onOffBanio = 7;
				onOffRecamara1 = 7;
				onOffRecamara2 = 7;
				onOffRecamara3 = 7;
				onOffHabitacionArbol = 7;
				onOffCochera = 0.01;
			}//cualquier otro lugar, todo apagado
			else {
				onOffSala = 7;
				onOffComedor = 7;
				onOffCocina = 7;
				onOffBanio = 7;
				onOffRecamara1 = 7;
				onOffRecamara2 = 7;
				onOffRecamara3 = 7;
				onOffHabitacionArbol = 7;
				onOffCochera = 7;
			}
		}

		//******************** Calculo de la distancia entre los objetos y la camara ***************************************//
		if (numberCamera == 2) {
			float distanciaLampara1x = matrixModelLamp1H[3].x - camera_halloween->getPosition().x;
			float distanciaLampara1y = matrixModelLamp1H[3].y - camera_halloween->getPosition().y;
			float distanciaLampara1z = matrixModelLamp1H[3].z - camera_halloween->getPosition().z;
			float sumaDistanciaLampara1 = glm::pow(distanciaLampara1x, 2) + glm::pow(distanciaLampara1y, 2) + glm::pow(distanciaLampara1z, 2);
			distanciaCamaraHalloweenFoco1 = glm::sqrt(sumaDistanciaLampara1);

			float distanciaLampara2x = matrixModelLamp2H[3].x - camera_halloween->getPosition().x;
			float distanciaLampara2y = matrixModelLamp2H[3].y - camera_halloween->getPosition().y;
			float distanciaLampara2z = matrixModelLamp2H[3].z - camera_halloween->getPosition().z;
			float sumaDistanciaLampara2 = glm::pow(distanciaLampara2x, 2) + glm::pow(distanciaLampara2y, 2) + glm::pow(distanciaLampara2z, 2);
			distanciaCamaraHalloweenFoco2 = glm::sqrt(sumaDistanciaLampara2);

			float distanciaLampara3x = matrixModelLamp3H[3].x - camera_halloween->getPosition().x;
			float distanciaLampara3y = matrixModelLamp3H[3].y - camera_halloween->getPosition().y;
			float distanciaLampara3z = matrixModelLamp3H[3].z - camera_halloween->getPosition().z;
			float sumaDistanciaLampara3 = glm::pow(distanciaLampara3x, 2) + glm::pow(distanciaLampara3y, 2) + glm::pow(distanciaLampara3z, 2);
			distanciaCamaraHalloweenFoco3 = glm::sqrt(sumaDistanciaLampara3);
			
			//casa de halloween, luces
			if (distanciaCamaraHalloweenFoco1 < 3.0) {
				onOffLampara1 = 0.01;
				onOffLampara2 = 7;
				onOffLampara3 = 7;
				std::cout << "Foco 1 prendido" << std::endl;
			}
			else if (distanciaCamaraHalloweenFoco2 < 3.0) {
				onOffLampara1 = 7;
				onOffLampara2 = 0.01;
				onOffLampara3 = 7;
				std::cout << "Foco 2 prendido" << std::endl;
			}
			else if (distanciaCamaraHalloweenFoco3 < 3.0) {
				onOffLampara1 = 7;
				onOffLampara2 = 7;
				onOffLampara3 = 0.01;
				std::cout << "Foco 3 prendido" << std::endl;
			}
			else {
				onOffLampara1 = 7;
				onOffLampara2 = 7;
				onOffLampara3 = 7;
			}

			if (muestraPosicion) {
				std::cout << "Distancia foco 1 " << distanciaCamaraHalloweenFoco1 << std::endl;
				std::cout << "Distancia foco 2 " << distanciaCamaraHalloweenFoco2 << std::endl;
				std::cout << "Distancia foco 3 " << distanciaCamaraHalloweenFoco3 << std::endl;
				muestraPosicion = false;
			}
			
		}



		/*******************************************
		 * Skybox
		 *******************************************/
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

		// Constantes de animaciones
		if (angle > 2 * M_PI)
			angle = 0.0;
		else
			angle += 0.01;

		offset1 += 1;
		offset2 += 1;
		offset3 += 1;
		offset4 += 1;
		offset5 += 1;
		rotHeliHeliy += 0.1;
		rotHeliHeliz += 0.1;
		rotWheelx += 0.1;

		if (offset1 > 7) { offset1 = 0.0; }
		if (offset2 > 7) { offset2 = 0.0; }
		if (offset3 > 7) { offset3 = 0.0; }
		if (offset4 > 7) { offset4 = 0.0; }
		if (offset5 > 7) { offset5 = 0.0; }

		advanceDartBody = 0.0;
		rotDartBody = 0.0;

		glfwSwapBuffers(window);

		// Libreria de audio
		// openal sound data
		source0Pos[0] = cubeTextureModelF06[3].x;
		source0Pos[1] = cubeTextureModelF06[3].y;
		source0Pos[2] = cubeTextureModelF06[3].z;
		alSourcefv(sources[0], AL_POSITION, source0Pos);
		source1Pos[0] = modelMatrixHeli[3].x;
		source1Pos[1] = modelMatrixHeli[3].y;
		source1Pos[2] = modelMatrixHeli[3].z;
		alSourcefv(sources[1], AL_POSITION, source1Pos);


		// Position listener
		listenerPos[0] = camera->getPosition().x;
		listenerPos[1] = camera->getPosition().y;
		listenerPos[2] = camera->getPosition().z;
		alListenerfv(AL_POSITION, listenerPos);
		// Orientation listener
		listenerOri[0] = camera->getFront().x;
		listenerOri[1] = camera->getFront().y;
		listenerOri[2] = camera->getFront().z;
		listenerOri[3] = camera->getUp().x;
		listenerOri[4] = camera->getUp().y;
		listenerOri[5] = camera->getUp().z;
		alListenerfv(AL_ORIENTATION, listenerOri);
	}
}

int main(int argc, char** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
