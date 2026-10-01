// Game/Unsorted_10C26A60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e99298[];

class Class_10C26980
{
public:
    Class_10C26980(int A, int B, int C, int D, float E, float F);

    void** Unknown00;
};

class Class_10E99298 : public Class_10C26980
{
public:
    Class_10E99298* FUN_10c27010(int A, int B, int C, int D);
};

extern void* DAT_10e992d4[];

class Class_10E992D4 : public Class_10C26980
{
public:
    Class_10E992D4* FUN_10c27050(int A, int B, int C, int D);
};

class Class_10C39220
{
public:
    bool FUN_10c39220(int A);
};

class Class_10E9AA7C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual bool FUN_10c27090(int A);

    char Unknown04[0x44];
    Class_10C39220* Unknown48;
};

// FUNCTION: 0x10C27010 ?FUN_10c27010@Class_10E99298@@QAEPAV1@HHHH@Z
Class_10E99298* Class_10E99298::FUN_10c27010(int A, int B, int C, int D)
{
    this->Class_10C26980::Class_10C26980(A, B, C, D, 90.0f, 90.0f);
    Unknown00 = DAT_10e99298;
    return this;
}

// FUNCTION: 0x10C27050 ?FUN_10c27050@Class_10E992D4@@QAEPAV1@HHHH@Z
Class_10E992D4* Class_10E992D4::FUN_10c27050(int A, int B, int C, int D)
{
    this->Class_10C26980::Class_10C26980(A, B, C, D, 180.0f, 0.0f);
    Unknown00 = DAT_10e992d4;
    return this;
}

// FUNCTION: 0x10C27090 ?FUN_10c27090@Class_10E9AA7C@@UAE_NH@Z
bool Class_10E9AA7C::FUN_10c27090(int A)
{
    if (!Unknown48)
        return false;
    return Unknown48->FUN_10c39220(A);
}
