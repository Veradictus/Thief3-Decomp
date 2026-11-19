// Game/UniqueObjectWrapperAppend.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cIntArray.h"
#include "Game/Class_10978090.h"

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

class Class_10E98C8C {
public:
    virtual void FUN_10c162e0(int A);
    Class_10E98C8C(int A);
    int Unknown04;
};

class Class_10BABF80 {
public:
    void FUN_10babf80(int Object);
    char Unknown00[0x74];
    cIntArray Objects;
};

// FUNCTION: 0x10BABF80 ?FUN_10babf80@Class_10BABF80@@QAEXH@Z
void Class_10BABF80::FUN_10babf80(int Object)
{
    cIntArray* Array = &Objects;
    for (int i = 0; i < Array->Count; ++i) {
        Class_10978090* Entry = (Class_10978090*)Objects.Data[i];
        if (Entry && (int)Entry->FUN_10978090() == Object)
            return;
    }
    GetAllocator()->Virtual8(0, 0);
    Class_10E98C8C* Entry = new(0, 0, 0, 0, 0) Class_10E98C8C(Object);
    int Index = Array->Count;
    Array->SetCount(Index + 1);
    Array->Data[Index] = (int)Entry;
    GetAllocator()->Virtual9();
}
