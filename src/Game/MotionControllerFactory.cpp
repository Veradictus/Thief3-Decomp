// Game/MotionControllerFactory.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cIntArray.h"
#include "Game/Class_10EBFF38.h"
#include "Game/Class_10C7D570.h"
#include "Game/Class_109A62E0.h"
#include "Game/Class_1098E330.h"
#include "Game/Info_10C2F870.h"
// Exact independently reviewed physical known-base prefix.
class Class_10E9AAD0 { public: virtual ~Class_10E9AAD0(); };
#include "Game/Class_10C30D10.h"

struct ControllerDelta643 { float X,Y,Z; };

class Class_10EC0080
{
public:
    virtual void OnSignal(int Code) = 0;
    virtual bool GetDelta(int Key,const ControllerDelta643* Delta,unsigned char* Out) = 0;
};

struct ControllerNode643;

class Class_10C352D0
{
public:
    Class_10C352D0();
    ~Class_10C352D0();
    int Count;
    ControllerNode643* Head;
    ControllerNode643* Tail;
    Class_10C30D10 Hash;
};

class cMotionControllerAnim : public Class_10E9AAD0, public Class_10EC0080
{
public:
    cMotionControllerAnim(Class_10C7D570* InOwner);
    virtual ~cMotionControllerAnim();
    virtual void FUN_10c357d0(float Delta);
    virtual void OnSignal(int Code);
    virtual bool GetDelta(int Key,const ControllerDelta643* Delta,unsigned char* Out);

    Class_10C7D570* Owner;
    // Unaccessed tail: only total native allocation extent is asserted here.
    char Opaque0C[0x15C];
};

// Existing Ion Storm allocation and matching construction-failure cleanup ABI.
void* operator new(unsigned int Size,const int& Tag,int A,int B,int C,int D);

void operator delete(void* Memory,const int& Tag,int A,int B,int C,int D);

// FUNCTION: 0x10C38460 ?FUN_10c38460@@YAPAVcMotionControllerAnim@@HPAVClass_10C7D570@@@Z
cMotionControllerAnim* FUN_10c38460(int Kind,Class_10C7D570* Owner)
{
    switch (Kind)
    {
    case 0:
        return new(0,0,0,0,0) cMotionControllerAnim(Owner);
    case 1:
        return 0;
    }
    return 0;
}
