// Game/Unsorted_1095BF80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1095BF80;

struct Arg_1095BF20
{
    char Unknown00;
};

void FUN_1095bf20(short* Dest, int Count, const short* Value, Class_1095BF80* Owner, Arg_1095BF20 Flags);

class Class_1095BF80
{
public:
    short* FUN_1095bf80(short* Dest, int Count, const short* Value);
};

// FUNCTION: 0x1095BF80 ?FUN_1095bf80@Class_1095BF80@@QAEPAFPAFHPBF@Z
short* Class_1095BF80::FUN_1095bf80(short* Dest, int Count, const short* Value)
{
    Arg_1095BF20 Flags;
    Flags.Unknown00 = 0;
    FUN_1095bf20(Dest, Count, Value, this, Flags);
    return Dest + Count;
}
