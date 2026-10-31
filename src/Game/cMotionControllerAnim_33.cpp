// Game/cMotionControllerAnim_33.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.
#include "Game/cIntArray.h"
#include "Game/Class_109A62E0.h"
#include "Game/Class_10C356D0_Element.h"
class Class_10E9AAD0
{
public:
    virtual ~Class_10E9AAD0();
};

void ReleaseHashTable();

class Class_10E7C584
{
public:
    virtual void Virtual0();

    int Unknown04;
};

class Class_10C356D0_Node
{
public:
    char Pad00[0x8];
    Class_10C356D0_Element* Unknown08;
};

class Class_10C356D0_Unknown0A4
{
public:
    ~Class_10C356D0_Unknown0A4();

    Class_10C356D0_Element* FirstElement()
    {
        return Head ? Head->Unknown08 : 0;
    }
    Class_10C356D0_Element* FUN_10c32ba0(Class_10C356D0_Element* Element);

    int Count;
    Class_10C356D0_Node* Head;
    char Pad08[0x8C];
};

class cMotionControllerAnim : public Class_10E9AAD0, public Class_10E7C584
{
public:
    virtual ~cMotionControllerAnim();
    virtual void FUN_10c357d0(float Delta);

    Class_109A62E0* Unknown0C;
    char Pad10[0x94];
    Class_10C356D0_Unknown0A4 Unknown0A4;
    cIntArray Unknown138;
};

// FUNCTION: 0x10C356D0 ??1cMotionControllerAnim@@UAE@XZ
cMotionControllerAnim::~cMotionControllerAnim()
{
    while (Unknown0A4.Count > 0)
    {
        Class_10C356D0_Element* Element = Unknown0A4.FirstElement();
        Element->Virtual9();
        Class_10C356D0_Element* Removed = Unknown0A4.FUN_10c32ba0(Element);
        if (Removed)
        {
            delete Removed;
        }
    }
    ReleaseHashTable();
    if (Unknown0C && (Unknown0C->Unknown1C & 0x800000) == 0)
    {
        Unknown0C->FUN_109a62e0(this);
    }
}
