#ifndef _COMMON_H
#define _COMMON_H

// OpenGL Libraries
#include <GL\glew.h>
#include <GL\glfw.h>

// Core Libraries
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include <io.h>


// C++ 11 Libraries
#include <memory>
#include <exception>
#include <thread>
#include <chrono>
#include <functional>
#include <algorithm>

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>          
#include <assimp/postprocess.h> 

// Manager Classes
#include "ThreadManager.h"
#include "GLWindow.h"
#include "InputManager.h"
#include "GameEngine.h"




// Shader Classes
#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderManager.h"

#endif