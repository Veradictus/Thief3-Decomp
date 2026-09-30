// Game/Class_10C16220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C160D0
{
public:
    bool FUN_10c160d0(int Id, int* Out);
};

class Class_10C16220
{
public:
    int FUN_10c16220(int Id);

    char Unknown00[4];
    Class_10C160D0 Unknown04;
};

// FUNCTION: 0x10C16220 ?FUN_10c16220@Class_10C16220@@QAEHH@Z
int Class_10C16220::FUN_10c16220(int Id)
{
    int Value = 0;
    Unknown04.FUN_10c160d0(Id, &Value);
    return Value;
}
