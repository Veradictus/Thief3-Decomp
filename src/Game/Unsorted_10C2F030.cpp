// Game/Unsorted_10C2F030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BA9F50
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Object_10C2F030
{
public:
    char Unknown00[0x38];
    Struct_10BA9F50 Unknown38;
};

class Class_10BA9F50
{
public:
    bool FUN_10ba9f50(Struct_10BA9F50* Out);
};

class Class_10E9AC80
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
    virtual Struct_10BA9F50 FUN_10c2f030();

    char Unknown04[4];
    Class_10BA9F50* Unknown08;
    char Unknown0C[4];
    Object_10C2F030* Unknown10;
    char Unknown14[0x20];
    Struct_10BA9F50 Unknown34;
};

// FUNCTION: 0x10C2F030 ?FUN_10c2f030@Class_10E9AC80@@UAE?AUStruct_10BA9F50@@XZ
Struct_10BA9F50 Class_10E9AC80::FUN_10c2f030()
{
    Struct_10BA9F50 Value = Unknown10->Unknown38;
    Unknown08->FUN_10ba9f50(&Value);
    Value.Unknown00 = Unknown34.Unknown00;
    Value.Unknown04 += Unknown34.Unknown04;
    Value.Unknown08 = Unknown34.Unknown08;
    return Value;
}
