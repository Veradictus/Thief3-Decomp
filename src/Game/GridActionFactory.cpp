// Game/GridActionFactory.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10905A90_Member.h"
#include "Game/Class_10C26A60.h"
#include "Game/Class_10E9AF80.h"

Class_10905A90_Member* GetAllocator();

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

// FUNCTION: 0x10C26AC0 ?FUN_10c26ac0@Class_10C26A60@@QAEXHHH@Z
void Class_10C26A60::FUN_10c26ac0(int A, int B, int C)
{
    GetAllocator()->Virtual8(0, 0);
    Class_10E9AF80* Action = new(0, 0, 0, 0, 0) Class_10E9AF80(A, B, C);
    GetAllocator()->Virtual9();
    Replace((Struct_10C26A60*)Action, C);
}
