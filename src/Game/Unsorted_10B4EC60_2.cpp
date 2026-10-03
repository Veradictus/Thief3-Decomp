// Game/Unsorted_10B4EC60_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AGarrett
{
public:
    char Unknown00[0x450];
    unsigned bInBowDraw : 1;
    unsigned isCrouching : 1;
};

class Class_10B39530
{
public:
    void FUN_10b39530(int A, float B, float C, int D, int E, int F, float G);
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10B3AE70 : public Class_10AA82D0
{
public:
    virtual void Virtual1();

    void FUN_10b3ae70(AGarrett* Garrett);

    char Unknown04[0xC];
};

class Class_10E7EB20 : public Class_10B3AE70
{
public:
    virtual void FUN_10b4f430(AGarrett* Garrett);

    void FUN_10b3b400(AGarrett* Garrett);
};

// FUNCTION: 0x10B4F430 ?FUN_10b4f430@Class_10E7EB20@@UAEXPAVAGarrett@@@Z
void Class_10E7EB20::FUN_10b4f430(AGarrett* Garrett)
{
    if (Garrett->isCrouching)
        ((Class_10B39530*)FUN_10aa82d0())->FUN_10b39530(0xaf, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    else
        ((Class_10B39530*)FUN_10aa82d0())->FUN_10b39530(0xa9, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    FUN_10b3ae70(Garrett);
    FUN_10b3b400(Garrett);
}
