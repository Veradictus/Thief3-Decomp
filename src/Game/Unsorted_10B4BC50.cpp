// Game/Unsorted_10B4BC50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10B4BC30
{
public:
    char Unknown00[0x344];
    int Unknown344;
};

class Class_10B39670
{
public:
    bool FUN_10b39670(int A);
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

class Class_10E7E7C0 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual int FUN_10b4bc30(Object_10B4BC30* A, int B);
    virtual void Virtual6();
    virtual void FUN_10b4bc50(Object_10B4BC30* A);

    char Unknown04[0xC];
    int Unknown10;
};

// FUNCTION: 0x10B4BC50 ?FUN_10b4bc50@Class_10E7E7C0@@UAEXPAVObject_10B4BC30@@@Z
void Class_10E7E7C0::FUN_10b4bc50(Object_10B4BC30* A)
{
    if (!((Class_10B39670*)FUN_10aa82d0())->FUN_10b39670(A->Unknown344))
        ((Class_10B39530*)FUN_10aa82d0())->FUN_10b39530(A->Unknown344, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    Virtual4();
}
