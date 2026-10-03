// Game/Unsorted_10BAE100.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" int __cdecl sprintf(char* Out, const char* Format, ...);

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern const char DAT_10e8d7d0[];

extern const char DAT_10e48c2c[];

// FUNCTION: 0x10BAE330 ?FUN_10bae330@@YA?AVClass_109081E0@@H@Z
Class_109081E0 FUN_10bae330(int Value)
{
    char Buffer[8];
    if (Value < 10)
        sprintf(Buffer, DAT_10e8d7d0, Value);
    else
    {
        if (Value > 99)
            Value = 99;
        sprintf(Buffer, DAT_10e48c2c, Value);
    }
    return Class_109081E0(Buffer);
}
