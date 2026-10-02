// Game/Unsorted_10C16250.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10C15EF0
{
public:
    void FUN_10c16140();

    char Unknown00[0x4010];
};

struct Struct_10C16250
{
    char Unknown00[0xC000];
};

extern Struct_10C16250* DAT_10ff7070;

extern int DAT_10ff7074;

class Class_10C16250
{
public:
    void FUN_10c16250();

    char Unknown00[4];
    Class_10C15EF0 Unknown04;
    char Unknown4014[4];
    int Unknown4018;
    int Unknown401C;
};

// FUNCTION: 0x10C16250 ?FUN_10c16250@Class_10C16250@@QAEXXZ
void Class_10C16250::FUN_10c16250()
{
    Unknown04.FUN_10c16140();
    if (DAT_10ff7070 == 0)
        DAT_10ff7070 = new(0, 0, 0, 0, 0) Struct_10C16250;
    DAT_10ff7074 = 0;
    Unknown4018 = 0;
    Unknown401C = 0;
}
