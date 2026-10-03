// Game/Unsorted_10A130D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A80E60;

struct Struct_10A13110
{
    int Unknown00;
    char Unknown04[0xC];
};

class Class_10E5D548
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
    virtual void FUN_10a12fd0(int Param);
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14(int A, int* B);
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual Struct_10A13110* FUN_10a13110(int Key);
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void FUN_10a13480(int Param);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[4];
    Class_10A80E60** Unknown10;
    int Unknown14;
    char Unknown18[4];
    int* Unknown1C;
    int Unknown20;
    char Unknown24[4];
    Struct_10A13110* Unknown28;
};

// FUNCTION: 0x10A13110 ?FUN_10a13110@Class_10E5D548@@UAEPAUStruct_10A13110@@H@Z
Struct_10A13110* Class_10E5D548::FUN_10a13110(int Key)
{
    for (int i = 0; i < Unknown20; i++)
    {
        if (Unknown28[i].Unknown00 == Key)
            return &Unknown28[i];
    }
    return 0;
}
