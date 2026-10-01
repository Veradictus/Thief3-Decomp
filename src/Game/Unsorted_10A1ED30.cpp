// Game/Unsorted_10A1ED30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10D382EB {
public:
    void FUN_10d382eb();
};

struct Struct_10A1EDC0_Streambuf {
    int Unknown00;
    Class_10D382EB Unknown04;
};

struct Struct_10A1EDC0_Ios {
    char Unknown00[0x28];
    Struct_10A1EDC0_Streambuf* Unknown28;
};

struct Struct_10A1EDC0_Ostream : virtual Struct_10A1EDC0_Ios {
};

class Class_10A1EDC0 {
public:
    Struct_10A1EDC0_Ostream* Unknown00;

    void FUN_10a1edc0();
};

class Class_10A1F880
{
public:
    int FUN_10a1f880(int Index);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    int* Unknown0C;
};

// FUNCTION: 0x10A1EDC0 ?FUN_10a1edc0@Class_10A1EDC0@@QAEXXZ
void Class_10A1EDC0::FUN_10a1edc0()
{
    Struct_10A1EDC0_Streambuf* Buf = Unknown00->Unknown28;
    if (Buf)
        Buf->Unknown04.FUN_10d382eb();
}

// FUNCTION: 0x10A1F880 ?FUN_10a1f880@Class_10A1F880@@QAEHH@Z
int Class_10A1F880::FUN_10a1f880(int Index)
{
    if (Index >= 0 && Index < Unknown04)
        return Unknown0C[Index];
    return 0;
}
