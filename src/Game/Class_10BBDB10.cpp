// Game/Class_10BBDB10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

class Class_10BBDB10
{
public:
    int FUN_10bbdb10(int Id);

    int Unknown00;
    Class_1098E330* Unknown04;
};

// FUNCTION: 0x10BBDB10 ?FUN_10bbdb10@Class_10BBDB10@@QAEHH@Z
int Class_10BBDB10::FUN_10bbdb10(int Id)
{
    int Value = 0;
    Unknown04->FUN_1098e330(Id, &Value);
    return Value;
}
