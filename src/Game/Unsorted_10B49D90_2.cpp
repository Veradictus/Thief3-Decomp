// Game/Unsorted_10B49D90_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AGarrett;

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

class Class_10E7E730 : public Class_10B3AE70
{
public:
    void FUN_10b3b0b0(AGarrett* Garrett);
};

class Class_10E7E6E8 : public Class_10E7E730
{
public:
    virtual void FUN_10b4a0d0(AGarrett* Garrett);

    bool Unknown10;
    float Unknown14;
};

// FUNCTION: 0x10B4A0D0 ?FUN_10b4a0d0@Class_10E7E6E8@@UAEXPAVAGarrett@@@Z
void Class_10E7E6E8::FUN_10b4a0d0(AGarrett* Garrett)
{
    ((Class_10B39530*)FUN_10aa82d0())->FUN_10b39530(0xa3, 0.0f, 1.0f, 0x101, 0, 0, -1.0f);
    FUN_10b3b0b0(Garrett);
    FUN_10b3ae70(Garrett);
    Unknown10 = false;
    Unknown14 = 1.5f;
}
