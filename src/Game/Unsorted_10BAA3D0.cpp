// Game/Unsorted_10BAA3D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    void FUN_1098e330(int A, int* B);
};

class Class_10BAA3D0
{
public:
    bool FUN_10baa3d0();

    char Unknown00[0x34];
    Class_1098E330* Unknown34;
    char Unknown38[0x130];
    int Unknown168;
};

// FUNCTION: 0x10BAA3D0 ?FUN_10baa3d0@Class_10BAA3D0@@QAE_NXZ
bool Class_10BAA3D0::FUN_10baa3d0()
{
    if (Unknown168 == -1)
    {
        int Value = 0;
        Unknown34->FUN_1098e330(0x8003e8, &Value);
        Unknown168 = Value;
    }
    return Unknown168 != 0;
}
