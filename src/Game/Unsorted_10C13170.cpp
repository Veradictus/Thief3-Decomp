// Game/Unsorted_10C13170.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

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

class Class_10E8C4A4_Member
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
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual Class_109081E0 Virtual25();
};

struct Struct_10C131D0
{
    char Unknown00[8];
    Class_10E8C4A4_Member* Unknown08;
};

class Class_1096C8D0
{
public:
    char Unknown00[4];
    int Unknown04;
    int Unknown08;
    char Unknown0C[4];
    Struct_10C131D0* Unknown10;
};

class Class_10E8C4A4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual Class_109081E0 FUN_10c12cc0();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual Class_109081E0 FUN_10c131d0();
    virtual bool FUN_10c129b0();

    Class_1096C8D0* Unknown04;
    Class_10E8C4A4_Member* Unknown08;
};

// FUNCTION: 0x10C131D0 ?FUN_10c131d0@Class_10E8C4A4@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E8C4A4::FUN_10c131d0()
{
    Class_1096C8D0* Holder = Unknown04;
    Class_10E8C4A4_Member* Obj;
    if (Holder->Unknown04 == 0)
        Obj = (Class_10E8C4A4_Member*)UObject::GObjObjects(Holder->Unknown08);
    else
        Obj = Holder->Unknown10->Unknown08;
    return Obj->Virtual25();
}
