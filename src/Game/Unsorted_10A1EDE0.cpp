// Game/Unsorted_10A1EDE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

extern const char DAT_10e47660[];

class Class_10A1F4D0
{
public:
    void FUN_10a1f4d0(int A);
    void FUN_109f36e0();
};

Class_10A1F4D0* FUN_109f5f80(void* A, const char* S);

class Class_10E65574
{
public:
    virtual void Virtual0();
    virtual Class_1090A780 FUN_10b34b10();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10a1f840(void* A);

    Class_1090A780 Unknown04;
};

// FUNCTION: 0x10A1F840 ?FUN_10a1f840@Class_10E65574@@UAEXPAX@Z
void Class_10E65574::FUN_10a1f840(void* A)
{
    const char* S = Unknown04.Unknown00;
    if (!S)
        S = DAT_10e47660;
    Class_10A1F4D0* Obj = FUN_109f5f80(A, S);
    Obj->FUN_10a1f4d0(10);
    Obj->FUN_109f36e0();
}
