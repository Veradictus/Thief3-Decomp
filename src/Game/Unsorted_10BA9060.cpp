// Game/Unsorted_10BA9060.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10C16250
{
public:
    void FUN_10c16250();

    char Unknown00[0x4020];
};

class Class_10E8D65C
{
public:
    virtual ~Class_10E8D65C();
    virtual bool Virtual1();
    virtual void FUN_10ba9060(Class_10c7d570* Obj);
    virtual void FUN_10ba9030(int Value);
    virtual void FUN_10ba9010(bool p1);

    void FUN_10c15bc0();

    char Unknown04;
    bool Unknown05;
    char Unknown06[2];
    int Unknown08;
    void* Unknown0C;
    Class_10C16250 Unknown10;
    Class_10C16250 Unknown4030;
};

// FUNCTION: 0x10BA9060 ?FUN_10ba9060@Class_10E8D65C@@UAEXPAVClass_10c7d570@@@Z
void Class_10E8D65C::FUN_10ba9060(Class_10c7d570* Obj)
{
    FUN_10c15bc0();
    Unknown10.FUN_10c16250();
    Unknown4030.FUN_10c16250();
    Unknown08 = 0;
    Unknown0C = Obj ? Obj->FUN_10c7d570() : 0;
}
