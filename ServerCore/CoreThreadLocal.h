#pragma once
#include "CoreTypeDefine.h"

class Timer;

thread_local extern uint16 LThreadId;
thread_local extern int64 LTickCount;
thread_local extern Timer* LTimer;