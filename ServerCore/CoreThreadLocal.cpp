#include "pch.h"
#include "CoreThreadLocal.h"
#include "Timer.h"

thread_local uint16 LThreadId = 0;
thread_local int64 LTickCount = 0;
thread_local Timer* LTimer = nullptr;