// Game/Unsorted_10C15D60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

struct Struct_10C16250
{
    char Unknown00[0xC000];
};

extern void* DAT_10e98c84[];

extern Struct_10C16250* DAT_10ff7070;

extern int DAT_10ff7074;

class Class_10C15DB0
{
public:
    Class_10C15DB0();

    void* Field00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10C15D60 ??0Class_10C15DB0@@QAE@XZ
Class_10C15DB0::Class_10C15DB0()
{
    Field00 = DAT_10e98c84;
    Unknown04 = 0;
    Unknown08 = 0;
    if (DAT_10ff7070 == 0)
        DAT_10ff7070 = new(0, 0, 0, 0, 0) Struct_10C16250;
    DAT_10ff7074 = 0;
}
