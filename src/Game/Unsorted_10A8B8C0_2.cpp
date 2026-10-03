// Game/Unsorted_10A8B8C0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

template <class T> class TArray
{
public:
    T& operator()(int i) { return Data[i]; }

    T* Data;
    int ArrayNum;
    int ArrayMax;
};

class UObject
{
public:
    static TArray<UObject*> GObjObjects;
};

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_1096A960
{
public:
    Class_109081E0 FUN_1096a960();
};

struct Struct_10A8BBC0
{
    char Unknown00[8];
    Class_1096A960* Unknown08;
};

class Class_1096C8D0
{
public:
    void FUN_1096c8d0();

    char Unknown00[4];
    int Unknown04;
    int Unknown08;
    char Unknown0C[4];
    Struct_10A8BBC0* Unknown10;
};

class Class_10F3A1EC : public Class_1096C8D0
{
};

extern Class_10F3A1EC* DAT_10f3a1ec;

class Class_10E6C68C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10a8bf80();
    virtual int FUN_10a8b860();
    virtual Class_109081E0 FUN_10a8bbc0();

    int FUN_10a8bac0();
};

// FUNCTION: 0x10A8BBC0 ?FUN_10a8bbc0@Class_10E6C68C@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E6C68C::FUN_10a8bbc0()
{
    Class_1096C8D0* Holder = DAT_10f3a1ec;
    Class_1096A960* Obj;
    if (Holder->Unknown04 == 0)
        Obj = (Class_1096A960*)UObject::GObjObjects(Holder->Unknown08);
    else
        Obj = Holder->Unknown10->Unknown08;
    return Obj->FUN_1096a960();
}
