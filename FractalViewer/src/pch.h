#pragma once

#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include <memory>
#include <thread>

#include <functional>
#include <algorithm>

#include <typeinfo>
#include <type_traits>


#define GL_CALL(gl) \
gl; \
(glGetError() != GL_NO_ERROR ? DebugBreak() : 0)
