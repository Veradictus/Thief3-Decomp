// Game/Unsorted_10C547F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C41420
{
public:
    void FUN_10c41490(int p1);
};

Class_10C41420* FUN_10c47d90();

class Class_10E9C330
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void FUN_10c547f0(int p1);
};

class Object_10AB5B20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
};

class Class_10AB5B20
{
public:
    Class_10AB5B20()
    {
        Unknown00 = 0;
    }
    Class_10AB5B20(Object_10AB5B20* P)
    {
        Unknown00 = P;
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10AB5B20();

    Object_10AB5B20* Unknown00;
};

class Class_10C54970
{
public:
    Class_10AB5B20 FUN_10c54970();

    char Unknown00[0x28];
    Object_10AB5B20* Unknown28;
};

struct Struct_10C55800
{
};

class Class_10C55800
{
public:
    void FUN_10c55800();
    void FUN_10c553a0();

    char Unknown00[0x18];
    Struct_10C55800* Unknown18;
};

// FUNCTION: 0x10C547F0 ?FUN_10c547f0@Class_10E9C330@@UAEXH@Z
void Class_10E9C330::FUN_10c547f0(int p1)
{
    FUN_10c47d90()->FUN_10c41490(p1);
}

// FUNCTION: 0x10C54970 ?FUN_10c54970@Class_10C54970@@QAE?AVClass_10AB5B20@@XZ
Class_10AB5B20 Class_10C54970::FUN_10c54970()
{
    if (Unknown28)
        return Class_10AB5B20(Unknown28);
    return Class_10AB5B20();
}
