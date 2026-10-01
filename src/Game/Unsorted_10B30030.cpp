// Game/Unsorted_10B30030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10B30190
{
public:
    Class_1090A780 FUN_10b30190(int Index);

    char Unknown00[0x30];
    Class_1090A780* Unknown30;
};

class Class_10b31460
{
public:
    char Unknown00[0x130];
    unsigned char Unknown130;

    void FUN_10b31460(unsigned char param);
};

class Class_10B31470
{
public:
    void FUN_10b31470(int p1, int p2);

    char Unknown00[0x124];
    int Unknown124;
    int Unknown128;
};

class Class_10b314e0
{
public:
    char Unknown00[0x132];
    unsigned char Unknown132;

    void FUN_10b314e0(unsigned char param);
};

class Struct_10B314F0
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
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void Virtual51();
    virtual void Virtual52();
    virtual void Virtual53();
    virtual void Virtual54();
    virtual void Virtual55();
    virtual void Virtual56(int A);
};

class Class_10B314F0
{
public:
    void FUN_10b314f0(bool A);

    char Unknown00[0x134];
    Struct_10B314F0* Unknown134;
    bool Unknown138;
};

class Class_10b31570
{
public:
    char Unknown00[0x144];
    unsigned char Unknown144;

    void FUN_10b31570(unsigned char param);
};

class Class_10E7BB2C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10b30030(const float* p1);

    char Unknown04[0x10];
    float Unknown14;
    float Unknown18;
    float Unknown1C;
};

// FUNCTION: 0x10B30030 ?FUN_10b30030@Class_10E7BB2C@@UAEXPBM@Z
void Class_10E7BB2C::FUN_10b30030(const float* p1)
{
    Unknown18 = *p1;
    Unknown1C = Unknown18 - Unknown14;
}

// FUNCTION: 0x10B30190 ?FUN_10b30190@Class_10B30190@@QAE?AVClass_1090A780@@H@Z
Class_1090A780 Class_10B30190::FUN_10b30190(int Index)
{
    return Unknown30[Index];
}

// FUNCTION: 0x10B31460 ?FUN_10b31460@Class_10b31460@@QAEXE@Z
void Class_10b31460::FUN_10b31460(unsigned char param)
{
    Unknown130 = param;
}

// FUNCTION: 0x10B31470 ?FUN_10b31470@Class_10B31470@@QAEXHH@Z
void Class_10B31470::FUN_10b31470(int p1, int p2)
{
    Unknown124 = p1;
    Unknown128 = p2;
}

// FUNCTION: 0x10B314E0 ?FUN_10b314e0@Class_10b314e0@@QAEXE@Z
void Class_10b314e0::FUN_10b314e0(unsigned char param)
{
    Unknown132 = param;
}

// FUNCTION: 0x10B314F0 ?FUN_10b314f0@Class_10B314F0@@QAEX_N@Z
void Class_10B314F0::FUN_10b314f0(bool A)
{
    Unknown138 = A;
    if (Unknown134)
        Unknown134->Virtual56(A ? 2 : 0);
}

// FUNCTION: 0x10B31570 ?FUN_10b31570@Class_10b31570@@QAEXE@Z
void Class_10b31570::FUN_10b31570(unsigned char param)
{
    Unknown144 = param;
}
