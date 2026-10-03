// Game/Unsorted_10B3ACD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A37C60
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual bool Virtual2();

    void FUN_10a37c60(float A, float B);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x10];
    Class_10A37C60* Unknown10;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

struct Struct_10B3ACE0
{
    char Unknown00[0x40C];
    float Unknown40C;
    float Unknown410;
};

class Class_10B22020;

class Object_10B4BC30;

class Class_10AA82D0
{
public:
    virtual void Virtual0();
};

class Class_10E7E538 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10b483c0(Class_10B22020* A);
    virtual int Virtual4();
    virtual int FUN_10b48400(Object_10B4BC30* A, int B);
    virtual void FUN_10b3ace0(Struct_10B3ACE0* A, float B, float C);
};

// FUNCTION: 0x10B3ACE0 ?FUN_10b3ace0@Class_10E7E538@@UAEXPAUStruct_10B3ACE0@@MM@Z
void Class_10E7E538::FUN_10b3ace0(Struct_10B3ACE0* A, float B, float C)
{
    Class_10A37C60* Item = DAT_10f3a3d8->Unknown10;
    if (Item->Virtual2())
    {
        A->Unknown410 = B;
        A->Unknown40C = C;
    }
    else
    {
        A->Unknown410 = 0;
        A->Unknown40C = 0;
    }
    Item->FUN_10a37c60(B, C);
}
