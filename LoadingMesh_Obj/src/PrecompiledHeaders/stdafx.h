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

// Windows 10 x32
#include <windows.h>

// C++ core
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>

// DirectX 9
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib" )
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxerr.lib")