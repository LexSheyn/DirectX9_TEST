#pragma once

// Custom types
typedef          char      char8;

typedef signed   char      int8;
typedef signed   short     int16;
typedef signed   int       int32;
typedef signed   long long int64;

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef float              float32;
typedef double             float64;

// Constants
#define Pi_float32 3.141592f
#define Pi_float64 3.14159265358979323846

// Windows 10 x32
#include <windows.h>

// C++ core
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <math.h>

// DirectX 9
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib" )
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxerr.lib")

// Custom
#include "../Templates/Templates.h"