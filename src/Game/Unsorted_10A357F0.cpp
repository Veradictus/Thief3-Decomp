// Game/Unsorted_10A357F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Static_10A35EA0
{
    char Unknown00[0xC];
    bool Unknown0C;

    Static_10A35EA0() { Unknown0C = false; }
    ~Static_10A35EA0() {}
};

class Class_10A35EE0
{
public:
    void FUN_10a35ee0(int p1, int p2);
    void FUN_10a35940();

    char Unknown00[0x80];
    int Unknown80;
};

class Class_10A35870
{
public:
    void FUN_10a35870(const int* p1);

    int Unknown00;
    char Unknown04[9];
    bool Unknown0D;
};

class Class_10A35890
{
public:
    void FUN_10a35890(const int* p1);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[5];
    bool Unknown0D;
};

class Class_10A35920
{
public:
    void FUN_10a35920(bool Value);

    char Unknown00[0xE];
    bool Unknown0E;
    int Unknown10;
};

// FUNCTION: 0x10A35870 ?FUN_10a35870@Class_10A35870@@QAEXPBH@Z
void Class_10A35870::FUN_10a35870(const int* p1)
{
    if (!Unknown0D)
        Unknown00 = *p1;
}

// FUNCTION: 0x10A35890 ?FUN_10a35890@Class_10A35890@@QAEXPBH@Z
void Class_10A35890::FUN_10a35890(const int* p1)
{
    if (!Unknown0D)
        Unknown04 = *p1;
}

// FUNCTION: 0x10A35920 ?FUN_10a35920@Class_10A35920@@QAEX_N@Z
void Class_10A35920::FUN_10a35920(bool Value)
{
    Unknown0E = Value;
    Unknown10 = Value ? 0 : 8;
}

// FUNCTION: 0x10A35EA0 ?FUN_10a35ea0@@YAPAUStatic_10A35EA0@@XZ
Static_10A35EA0* FUN_10a35ea0()
{
    static Static_10A35EA0 Instance;
    return &Instance;
}

// FUNCTION: 0x10A35EE0 ?FUN_10a35ee0@Class_10A35EE0@@QAEXHH@Z
void Class_10A35EE0::FUN_10a35ee0(int p1, int p2)
{
    Unknown80 = p1;
    FUN_10a35940();
}
