/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "myTeapot.h"
#include <vector>
#include <unordered_map>
#include <utility>
#include <Windows.h>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>

#pragma comment(lib, "Winmm.lib")
using namespace std;

float speed_x=0;
float speed_y=0;
float aspectRatio=1;

ShaderProgram *sp;
GLuint mytex;

FMOD::System* fmodsystem;
FMOD_RESULT result = FMOD::System_Create(&fmodsystem);



float* vertices = myCubeVertices;
float* normals = myCubeNormals;
float* texCoords = myCubeTexCoords;
float* colors = myCubeColors;
int vertexCount = myCubeVertexCount;

pair<glm::mat4, bool> klawiszebiale[15];
pair<glm::mat4, bool> klawiszeczarne[10];
pair<glm::mat4, bool> klawiszeperkusyjne[8];
bool drugirzad = false;

FMOD::Sound* dzwieki[33] = { nullptr };
FMOD::Channel* kanaly[33] = { nullptr };
const char* nazwadzwieku[33];


//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {

	

    if (action==GLFW_PRESS) {
        if (key==GLFW_KEY_LEFT) speed_x=-PI/2;
        if (key==GLFW_KEY_RIGHT) speed_x=PI/2;
        if (key==GLFW_KEY_UP) speed_y=PI/2;
        if (key==GLFW_KEY_DOWN) speed_y=-PI/2;

		if (key == GLFW_KEY_Q) {
			klawiszebiale[0].second = true;

			fmodsystem->playSound(dzwieki[0], nullptr, false, &kanaly[0]);
		}
			
		if (key == GLFW_KEY_W) {
			klawiszebiale[1].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[1], nullptr, false, &kanaly[1]);

		}
		if (key == GLFW_KEY_E) {
			klawiszebiale[2].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[2], nullptr, false, &kanaly[2]);
		}
		if (key == GLFW_KEY_R) {
			klawiszebiale[3].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[3], nullptr, false, &kanaly[3]);
		}
		if (key == GLFW_KEY_T) {
			klawiszebiale[4].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[4], nullptr, false, &kanaly[4]);
		}
		if (key == GLFW_KEY_Y) {
			klawiszebiale[5].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[5], nullptr, false, &kanaly[5]);
		}
		if (key == GLFW_KEY_U) {
			klawiszebiale[6].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[6], nullptr, false, &kanaly[6]);
		}
		if (key == GLFW_KEY_I) {
			klawiszebiale[7].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[7], nullptr, false, &kanaly[7]);
		}
		if (key == GLFW_KEY_O) {
			klawiszebiale[8].second = true;
			
			

			fmodsystem->playSound(dzwieki[8], nullptr, false, &kanaly[8]);
		}
		if (key == GLFW_KEY_P) {
			klawiszebiale[9].second = true;
			
			

		
			fmodsystem->playSound(dzwieki[9], nullptr, false, &kanaly[9]);
		}
		if (key == GLFW_KEY_A) {
			klawiszebiale[10].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[10], nullptr, false, &kanaly[10]);
		}
		if (key == GLFW_KEY_S) {
			klawiszebiale[11].second = true;
			
			

			fmodsystem->playSound(dzwieki[11], nullptr, false, &kanaly[11]);
		}
		if (key == GLFW_KEY_D) {
			klawiszebiale[12].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[12], nullptr, false, &kanaly[12]);
		}
		if (key == GLFW_KEY_F) {
			klawiszebiale[13].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[13], nullptr, false, &kanaly[13]);
		}
		if (key == GLFW_KEY_G) {
			klawiszebiale[14].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[14], nullptr, false, &kanaly[14]);
		}

		if (key == GLFW_KEY_H) {
			klawiszeczarne[0].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[15], nullptr, false, &kanaly[15]);
		}
		if (key == GLFW_KEY_J) {
			klawiszeczarne[1].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[16], nullptr, false, &kanaly[16]);
		}
		if (key == GLFW_KEY_K) {
			klawiszeczarne[2].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[17], nullptr, false, &kanaly[17]);
		}
		if (key == GLFW_KEY_L) {
			klawiszeczarne[3].second = true;
			
			

			
			fmodsystem->playSound(dzwieki[18], nullptr, false, &kanaly[18]);
		}
		if (key == GLFW_KEY_Z) {
			klawiszeczarne[4].second = true;
			
			
		
			fmodsystem->playSound(dzwieki[19], nullptr, false, &kanaly[19]);
		}
		if (key == GLFW_KEY_X) {
			klawiszeczarne[5].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[20], nullptr, false, &kanaly[20]);
		}
		if (key == GLFW_KEY_C) {
			klawiszeczarne[6].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[21], nullptr, false, &kanaly[21]);
		}
		if (key == GLFW_KEY_V) {
			klawiszeczarne[7].second = true;
			
			

		
			fmodsystem->playSound(dzwieki[22], nullptr, false, &kanaly[22]);
		}
		if (key == GLFW_KEY_B) {
			klawiszeczarne[8].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[23], nullptr, false, &kanaly[23]);
		}
		if (key == GLFW_KEY_N) {
			klawiszeczarne[9].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[24], nullptr, false, &kanaly[24]);
		}

		if (key == GLFW_KEY_1) {
			klawiszeperkusyjne[0].second = true;
			
			
		
			fmodsystem->playSound(dzwieki[25], nullptr, false, &kanaly[25]);
		}

		if (key == GLFW_KEY_2) {
			klawiszeperkusyjne[1].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[26], nullptr, false, &kanaly[26]);
		}

		if (key == GLFW_KEY_3) {
			klawiszeperkusyjne[2].second = true;
		
			
			
			fmodsystem->playSound(dzwieki[27], nullptr, false, &kanaly[27]);
		}
		if (key == GLFW_KEY_4) {
			klawiszeperkusyjne[3].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[28], nullptr, false, &kanaly[28]);
		}
		if (key == GLFW_KEY_5) {
			klawiszeperkusyjne[4].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[29], nullptr, false, &kanaly[29]);
		}
		if (key == GLFW_KEY_6) {
			klawiszeperkusyjne[5].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[30], nullptr, false, &kanaly[30]);
		}
		if (key == GLFW_KEY_7) {
			klawiszeperkusyjne[6].second = true;
			
			
			
			fmodsystem->playSound(dzwieki[31], nullptr, false, &kanaly[31]);
		}
		if (key == GLFW_KEY_8) {
			klawiszeperkusyjne[7].second = true;
			
			
			fmodsystem->playSound(dzwieki[32], nullptr, false, &kanaly[32]);
		}

		
		
		
    }
    if (action==GLFW_RELEASE) {
        if (key==GLFW_KEY_LEFT) speed_x=0;
        if (key==GLFW_KEY_RIGHT) speed_x=0;
        if (key==GLFW_KEY_UP) speed_y=0;
        if (key==GLFW_KEY_DOWN) speed_y=0;
		

		if (key == GLFW_KEY_Q) {
			klawiszebiale[0].second = false;
			

		}
		if (key == GLFW_KEY_W) {
			klawiszebiale[1].second = false;
			
		}
		if (key == GLFW_KEY_E) {
			klawiszebiale[2].second = false;
			
		}
		if (key == GLFW_KEY_R) {
			klawiszebiale[3].second = false;
			
		}
		if (key == GLFW_KEY_T) {
			klawiszebiale[4].second = false;
			
		}
		if (key == GLFW_KEY_Y) {
			klawiszebiale[5].second = false;
			
		}
		if (key == GLFW_KEY_U) {
			klawiszebiale[6].second = false;
		}
		if (key == GLFW_KEY_I) {
			klawiszebiale[7].second = false;
		}
		if (key == GLFW_KEY_O) {
			klawiszebiale[8].second = false;
		}
		if (key == GLFW_KEY_P) {
			klawiszebiale[9].second = false;
		}
		if (key == GLFW_KEY_A) {
			klawiszebiale[10].second = false;
		}
		if (key == GLFW_KEY_S) {
			klawiszebiale[11].second = false;
		}
		if (key == GLFW_KEY_D) {
			klawiszebiale[12].second = false;
		}
		if (key == GLFW_KEY_F) {
			klawiszebiale[13].second = false;
		}
		if (key == GLFW_KEY_G) {
			klawiszebiale[14].second = false;
		}

		if (key == GLFW_KEY_H) {
			klawiszeczarne[0].second = false;
		}
		if (key == GLFW_KEY_J) {
			klawiszeczarne[1].second = false;
		}
		if (key == GLFW_KEY_K) {
			klawiszeczarne[2].second = false;
		}
		if (key == GLFW_KEY_L) {
			klawiszeczarne[3].second = false;
		}
		if (key == GLFW_KEY_Z) {
			klawiszeczarne[4].second = false;
		}
		if (key == GLFW_KEY_X) {
			klawiszeczarne[5].second = false;
		}
		if (key == GLFW_KEY_C) {
			klawiszeczarne[6].second = false;
		}
		if (key == GLFW_KEY_V) {
			klawiszeczarne[7].second = false;
		}
		if (key == GLFW_KEY_B) {
			klawiszeczarne[8].second = false;
		}
		if (key == GLFW_KEY_N) {
			klawiszeczarne[9].second = false;
		}

		if (key == GLFW_KEY_1) {
			klawiszeperkusyjne[0].second = false;
		}

		if (key == GLFW_KEY_2) {
			klawiszeperkusyjne[1].second = false;
		}

		if (key == GLFW_KEY_3) {
			klawiszeperkusyjne[2].second = false;
		}
		if (key == GLFW_KEY_4) {
			klawiszeperkusyjne[3].second = false;
		}
		if (key == GLFW_KEY_5) {
			klawiszeperkusyjne[4].second = false;
		}
		if (key == GLFW_KEY_6) {
			klawiszeperkusyjne[5].second = false;
		}
		if (key == GLFW_KEY_7) {
			klawiszeperkusyjne[6].second = false;
		}
		if (key == GLFW_KEY_8) {
			klawiszeperkusyjne[7].second = false;
		}
    }

	

}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}



GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filename);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return tex;
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetKeyCallback(window,keyCallback);

	
	for (int i = 0; i < 15; i++) {
		klawiszebiale[i] = make_pair(glm::mat4(1.0f), false);
	}

	for (int i = 0; i < 10; i++) {
		klawiszeczarne[i] = make_pair(glm::mat4(1.0f), false);
	}

	for (int i = 0; i < 8; i++) {
		klawiszeperkusyjne[i] = make_pair(glm::mat4(1.0f), false);
	}

	mytex = readTexture("metal_klawisz.png");
	sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
	
	FMOD::Sound* c4s = nullptr;
	FMOD::Channel* c4c = nullptr;
	FMOD::Sound* d4s = nullptr;
	FMOD::Channel* d4c = nullptr;
	FMOD::Sound* e4s = nullptr;
	FMOD::Channel* e4c = nullptr;
	FMOD::Sound* f4s = nullptr;
	FMOD::Channel* f4c = nullptr;
	FMOD::Sound* g4s = nullptr;
	FMOD::Channel* g4c = nullptr;
	FMOD::Sound* a4s = nullptr;
	FMOD::Channel* a4c = nullptr;
	FMOD::Sound* b4s = nullptr;
	FMOD::Channel* b4c = nullptr;
	FMOD::Sound* c5s = nullptr;
	FMOD::Channel* c5c = nullptr;
	FMOD::Sound* d5s = nullptr;
	FMOD::Channel* d5c = nullptr;
	FMOD::Sound* e5s = nullptr;
	FMOD::Channel* e5c = nullptr;
	FMOD::Sound* f5s = nullptr;
	FMOD::Channel* f5c = nullptr;
	FMOD::Sound* g5s = nullptr;
	FMOD::Channel* g5c = nullptr;
	FMOD::Sound* a5s = nullptr;
	FMOD::Channel* a5c = nullptr;
	FMOD::Sound* b5s = nullptr;
	FMOD::Channel* b5c = nullptr;
	FMOD::Sound* c6s = nullptr;
	FMOD::Channel* c6c = nullptr;
	FMOD::Sound* c4ms = nullptr;
	FMOD::Channel* c4mc = nullptr;
	FMOD::Sound* d4ms = nullptr;
	FMOD::Channel* d4mc = nullptr;
	FMOD::Sound* f4ms = nullptr;
	FMOD::Channel* f4mc = nullptr;
	FMOD::Sound* g4ms = nullptr;
	FMOD::Channel* g4mc = nullptr;
	FMOD::Sound* a4ms = nullptr;
	FMOD::Channel* a4mc = nullptr;
	FMOD::Sound* c5ms = nullptr;
	FMOD::Channel* c5mc = nullptr;
	FMOD::Sound* d5ms = nullptr;
	FMOD::Channel* d5mc = nullptr;
	FMOD::Sound* f5ms = nullptr;
	FMOD::Channel* f5mc = nullptr;
	FMOD::Sound* g5ms = nullptr;
	FMOD::Channel* g5mc = nullptr;
	FMOD::Sound* a5ms = nullptr;
	FMOD::Channel* a5mc = nullptr;
	FMOD::Sound* drums8s = nullptr;
	FMOD::Channel* drums8c = nullptr;
	FMOD::Sound* drums1s = nullptr;
	FMOD::Channel* drums1c = nullptr;
	FMOD::Sound* drums2s = nullptr;
	FMOD::Channel* drums2c = nullptr;
	FMOD::Sound* drums3s = nullptr;
	FMOD::Channel* drums3c = nullptr;
	FMOD::Sound* drums4s = nullptr;
	FMOD::Channel* drums4c = nullptr;
	FMOD::Sound* drums5s = nullptr;
	FMOD::Channel* drums5c = nullptr;
	FMOD::Sound* drums6s = nullptr;
	FMOD::Channel* drums6c = nullptr;
	FMOD::Sound* drums7s = nullptr;
	FMOD::Channel* drums7c = nullptr;

	FMOD::Sound* tempSounds[] = {
		c4s, d4s, e4s, f4s, g4s, a4s, b4s, c5s, d5s, e5s,
		f5s, g5s, a5s, b5s, c6s, c4ms, d4ms, f4ms, g4ms, a4ms,
		c5ms, d5ms, f5ms, g5ms, a5ms, drums8s, drums1s, drums2s, drums3s, drums4s,
		drums5s, drums6s, drums7s
	};

	FMOD::Channel* tempChannels[] = {
		c4c, d4c, e4c, f4c, g4c, a4c, b4c, c5c, d5c, e5c,
		f5c, g5c, a5c, b5c, c6c, c4mc, d4mc, f4mc, g4mc, a4mc,
		c5mc, d5mc, f5mc, g5mc, a5mc, drums8c, drums1c, drums2c, drums3c, drums4c,
		drums5c, drums6c, drums7c
	};

	
	for (int i = 0; i < 33; ++i) {
		dzwieki[i] = tempSounds[i];
		kanaly[i] = tempChannels[i];
	}

	const char* fileNames[33] = {
		"c4.mp3", "d4.mp3", "e4.mp3", "f4.mp3", "g4.mp3", "a4.mp3", "b4.mp3", "c5.mp3", "d5.mp3", "e5.mp3",
		"f5.mp3", "g5.mp3", "a5.mp3", "b5.mp3", "c6.mp3", "c4m.mp3", "d4m.mp3", "f4m.mp3", "g4m.mp3", "a4m.mp3",
		"c5m.mp3", "d5m.mp3", "f5m.mp3", "g5m.mp3", "a5m.mp3", "drums8.mp3", "drums1.mp3", "drums2.mp3", "drums3.mp3", "drums4.mp3",
		"drums5.mp3", "drums6.mp3", "drums7.mp3"
	};

	for (int i = 0; i < 33; ++i) {
		result = fmodsystem->createSound(fileNames[i], FMOD_DEFAULT, nullptr, &dzwieki[i]);
	}

	
}

void stopAllSounds(FMOD::Channel* channels[], int numChannels) {
	for (int i = 0; i < numChannels; ++i) {
		if (channels[i] != nullptr) {
			bool isPlaying = false;
			channels[i]->isPlaying(&isPlaying);
			if (isPlaying) {
				channels[i]->stop();
			}
		}
	}
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

	glDeleteTextures(1, &mytex);
    delete sp;
}


void klawisz_bialy(pair<glm::mat4, bool> M, glm::mat4 podstawa, float temp) {
	
	M.first = podstawa * glm::translate(M.first, glm::vec3(3.5-temp, 0.15f, -1.1f));

	if (M.second) {
		M.first = glm::rotate(M.first, 2 * (PI / 180), glm::vec3(-1.0f, 0.0f, 0.0f));
	}
	

	glm::mat4 Mp = glm::scale(M.first, glm::vec3(3.2f/15, 0.15f, 1.0f));

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mp));

	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt
}

void klawisz_czarny(pair<glm::mat4, bool> M, glm::mat4 podstawa, float temp) {

	M.first = podstawa * glm::translate(M.first, glm::vec3(3.5f-3.2f/15-temp, 0.2f, -0.90f));

	if (M.second) {
		M.first = glm::rotate(M.first, 2 * (PI / 180), glm::vec3(-1.0f, 0.0f, 0.0f));
	}


	glm::mat4 Mp = glm::scale(M.first, glm::vec3(2.5f / 15, 0.15f, 0.8f));

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mp));

	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt


}

void klawisz_perkusyjny(pair<glm::mat4, bool> M, glm::mat4 podstawa, float temp, bool drugirzad) {

	if (drugirzad == false) M.first = podstawa * glm::translate(M.first, glm::vec3(3.3f - temp, 0.2f, 1.4f));
	
	if (drugirzad == true) M.first = podstawa * glm::translate(M.first, glm::vec3(3.3f - temp, 0.2f, 0.5f));
		

	//if (M.second) M.first = glm::rotate(M.first, 2 * (PI / 180), glm::vec3(0.0f, 0.0f, 1.0f));

	if (M.second) M.first = glm::translate(M.first, glm::vec3(0.0f, -0.06f, 0.0f));


	glm::mat4 Mp = glm::scale(M.first, glm::vec3(0.4f, 0.20f, 0.4f));

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mp));

	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt

}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window,float angle_x,float angle_y) {

	

	sp->use();

	glm::vec4 czerwony = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); //red color
	glUniform4fv(sp->u("objectColor"), 1, glm::value_ptr(czerwony));


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V=glm::lookAt(glm::vec3(0, 0, -10),glm::vec3(0,0,0),glm::vec3(0.0f,1.0f,0.0f)); //Wylicz macierz widoku

    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));


	//podstawa konsoli

    glm::mat4 podstawa=glm::mat4(1.0f);

	podstawa = glm::rotate(podstawa, angle_y, glm::vec3(1.0f, 0.0f, 0.0f));
	podstawa = glm::rotate(podstawa, angle_x, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 Mp = glm::scale(podstawa, glm::vec3(4.0f, 0.25f, 2.0f));

    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(Mp));

	

    glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0,vertices); //Wskaż tablicę z danymi dla atrybutu vertex


	
    glDrawArrays(GL_TRIANGLES,0,vertexCount); //Narysuj obiekt

	glm::vec4 zielony = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); //red color
	glUniform4fv(sp->u("objectColor"), 1, glm::value_ptr(zielony));



	//glBindTexture(GL_TEXTURE_2D, mytex);

	float licznik = 0;
	for (int i = 0; i < 15; i++) {
		
		klawisz_bialy(klawiszebiale[i], podstawa, licznik);
		licznik += 0.5;
	}


	glm::vec4 niebieski = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); //red color
	glUniform4fv(sp->u("objectColor"), 1, glm::value_ptr(niebieski));

	float licznikc = 0;
	//bool temp=false;
	for (int i = 0; i < 10; i++) {

		if (i == 2) licznikc += 0.5;
		if (i == 5) licznikc += 0.5;
		if (i == 7) licznikc += 0.5;

		klawisz_czarny(klawiszeczarne[i], podstawa, licznikc);
		licznikc += 0.5;
	}

	//glm::vec4 zielony = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); //red color
	glUniform4fv(sp->u("objectColor"), 1, glm::value_ptr(zielony));

	float licznikp = 0;
	bool drugirzad;
	for (int i = 0; i < 4; i++) {
		drugirzad = false;
		klawisz_perkusyjny(klawiszeperkusyjne[i], podstawa, licznikp, drugirzad);
		
		licznikp += 1;
	}
	licznikp = 0;
	for (int i = 4; i < 8; i++) {
		drugirzad = true;
		klawisz_perkusyjny(klawiszeperkusyjne[i], podstawa, licznikp, drugirzad);

		licznikp += 1;
	}

    glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("texCoord"));

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


int main(void)

{
	
	if (result != FMOD_OK) {
		std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
		// Handle initialization error
		return -1;
	}

	result = fmodsystem->init(512, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK) {
		std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
		// Handle initialization error
		return -1;
	}

	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	float angle_x=0; //Aktualny kąt obrotu obiektu
	float angle_y=0; //Aktualny kąt obrotu obiektu
	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        angle_x+=speed_x*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki
        angle_y+=speed_y*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki
        glfwSetTime(0); //Zeruj timer
		drawScene(window,angle_x,angle_y); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	fmodsystem->release();
	exit(EXIT_SUCCESS);
}
