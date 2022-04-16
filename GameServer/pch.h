#pragma once

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#pragma comment(lib, "Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "Debug\\ServerCore.lib")
#pragma comment(lib, "Release\\libprotobuf.lib")
#endif

#include "CorePch.h"