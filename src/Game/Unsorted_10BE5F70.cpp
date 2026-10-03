// Game/Unsorted_10BE5F70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10BE58C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(void* Data, int Size);

    char Unknown04[8];
    int Unknown0C;
};

class Class_10BFF280
{
public:
    int FUN_10bff280();
};

class Class_10BFF460 : public Class_10BFF280
{
public:
    bool FUN_10bff330();
};

class Class_10BBB410
{
public:
    Class_10BFF460* FUN_10bbb410();
    void FUN_10bb9f60(int A, int B);
};

class Class_10E960D8
{
public:
    virtual void Virtual0();

    void FUN_10be4ef0(Object_10BE58C0* Ar);

    Class_10BBB410* Unknown04;
    char Unknown08[0x60];
    int Unknown68;
};

class Class_10E96810 : public Class_10E960D8
{
public:
    virtual void FUN_10be4a20();
    virtual void FUN_10be69a0(Object_10BE58C0* Ar);

    bool Unknown6C;
};

// FUNCTION: 0x10BE69A0 ?FUN_10be69a0@Class_10E96810@@UAEXPAVObject_10BE58C0@@@Z
void Class_10E96810::FUN_10be69a0(Object_10BE58C0* Ar)
{
    FUN_10be4ef0(Ar);
    if (Ar->Unknown0C >= 0x45)
    {
        Ar->Virtual1(&Unknown6C, 1);
        Ar->Virtual1(&Unknown68, 4);
    }
}
