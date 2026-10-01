// Game/Unsorted_10A35640.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A35660
{
public:
    void FUN_10a35660(int p1, int p2);

    char Unknown00[0x70];
    int Unknown70;
    int Unknown74;
    int Unknown78;
    int Unknown7C;
};

struct Struct_10A35640 {
    char Unknown00[0x18];
    int Unknown18;
    int Unknown1C;
};

class Class_10A35640 {
public:
    char Unknown00[0x24];
    int Unknown24;
    int Unknown28;
    char Unknown2C[0x44];
    Struct_10A35640* Unknown70;

    void FUN_10a35640(Struct_10A35640* P);
};

// FUNCTION: 0x10A35640 ?FUN_10a35640@Class_10A35640@@QAEXPAUStruct_10A35640@@@Z
void Class_10A35640::FUN_10a35640(Struct_10A35640* P)
{
    Unknown70 = P;
    if (P)
    {
        Unknown24 = P->Unknown18;
        Unknown28 = P->Unknown1C;
    }
}

// FUNCTION: 0x10A35660 ?FUN_10a35660@Class_10A35660@@QAEXHH@Z
void Class_10A35660::FUN_10a35660(int p1, int p2)
{
    Unknown78 = p1;
    Unknown7C = p2;
    Unknown70 = 0;
    Unknown74 = 0;
}
