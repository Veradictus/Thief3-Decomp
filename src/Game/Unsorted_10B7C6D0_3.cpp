// Game/Unsorted_10B7C6D0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B8AC90;

class Class_10D9B090;

Class_10D9B090* __stdcall FUN_10d9dcb0(Class_10B8AC90* Obj, int A);

class Class_10E4B180_Unknown70
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6(Class_10D9B090* A);
    virtual void Virtual7(Class_10D9B090* A);
};

class Class_10E4B180
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
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void FUN_10b7c6d0(int A, Class_10B8AC90* B, int C);
    virtual void FUN_10b7c720(Class_10B8AC90* A, int B);

    char Unknown04[0x7C];
    int Unknown80;
    char Unknown84[4];
    Class_10E4B180_Unknown70** Unknown88;
    int Unknown8C;
    char Unknown90[4];
    Class_10E4B180_Unknown70** Unknown94;
};

// FUNCTION: 0x10B7C720 ?FUN_10b7c720@Class_10E4B180@@UAEXPAVClass_10B8AC90@@H@Z
void Class_10E4B180::FUN_10b7c720(Class_10B8AC90* A, int B)
{
    for (int i = 0; i < Unknown8C; i++)
    {
        Class_10E4B180_Unknown70* Item = Unknown94[i];
        Item->Virtual7(FUN_10d9dcb0(A, B));
    }
}
