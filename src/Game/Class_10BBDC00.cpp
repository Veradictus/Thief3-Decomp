// Game/Class_10BBDC00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

class Class_10BBDC00
{
public:
    int FUN_10bbdc00(int Id);

    char Unknown00[0xC];
    Class_1098E330* Unknown0C;
};

// FUNCTION: 0x10BBDC00 ?FUN_10bbdc00@Class_10BBDC00@@QAEHH@Z
int Class_10BBDC00::FUN_10bbdc00(int Id)
{
    int Value = 0;
    Unknown0C->FUN_1098e330(Id, &Value);
    return Value;
}
