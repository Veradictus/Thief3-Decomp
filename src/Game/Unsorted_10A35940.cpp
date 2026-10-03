// Game/Unsorted_10A35940.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A359D0
{
public:
    int FUN_10a358b0();
    void FUN_10a359d0();
    void FUN_10a35a20();

    char Unknown00[0xD];
    bool Unknown0D;
    char Unknown0E[0xE];
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    char Unknown28[8];
    int Unknown30;
    int Unknown34;
    int Unknown38;
    int Unknown3C;
    int Unknown40;
    char Unknown44[8];
    int Unknown4C;
    int Unknown50;
    int Unknown54;
    int Unknown58;
    int Unknown5C;
    int Unknown60;
    int Unknown64;
    int Unknown68;
    char Unknown6C[0xC];
    int Unknown78;
    int Unknown7C;
};

// FUNCTION: 0x10A359D0 ?FUN_10a359d0@Class_10A359D0@@QAEXXZ
void Class_10A359D0::FUN_10a359d0()
{
    Unknown1C = Unknown60 + Unknown78;
    Unknown20 = Unknown24 - Unknown64 + Unknown78;
    Unknown30 = Unknown68 + Unknown7C;
    Unknown40 = Unknown30;
    Unknown4C = 0;
    Unknown38 = Unknown3C = FUN_10a358b0();
    Unknown58 = -1;
    Unknown5C = -1;
    Unknown50 = -1;
    Unknown54 = -1;
}

// FUNCTION: 0x10A35A20 ?FUN_10a35a20@Class_10A359D0@@QAEXXZ
void Class_10A359D0::FUN_10a35a20()
{
    Unknown34 = 0;
    Unknown3C = FUN_10a358b0();
    Unknown0D = true;
    if (Unknown30 >= Unknown50 && Unknown30 <= Unknown54)
    {
        Unknown1C = Unknown78 + Unknown60;
    }
    else
    {
        Unknown1C = Unknown60 + Unknown78;
        Unknown20 = Unknown24 - Unknown64 + Unknown78;
    }
}
