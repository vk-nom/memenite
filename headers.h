#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <iostream>
#include "MemoryHelper.h"
#include "no_spoofcall.h"
#include "siggies.h"
#include <algorithm>
#define RVA(addr, size) ((uintptr_t)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))