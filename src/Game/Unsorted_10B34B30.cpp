// Game/Unsorted_10B34B30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7C268_Primary
{
public:
    virtual void Virtual0();
    virtual void Virtual1();

    char Unknown04[8];
};

class Class_10E7C268_Secondary
{
public:
    char Unknown00[4];
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E7C268_Secondary* A, int B, int C, int D);
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    int Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E7C268 : public Class_10E7C268_Primary, public Class_10E7C268_Secondary
{
public:
    virtual void FUN_10b35120();
};

// FUNCTION: 0x10B35120 ?FUN_10b35120@Class_10E7C268@@UAEXXZ
void Class_10E7C268::FUN_10b35120()
{
    DAT_10f46da0->Virtual1(this, 0x3E, DAT_10f35dec->Unknown08, -1);
}
