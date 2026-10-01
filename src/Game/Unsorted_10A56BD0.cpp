// Game/Unsorted_10A56BD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A56BD0 {
public:
    char Unknown00[0x164];
    int Unknown164;
    int* FUN_10a56bd0(int* out);
};

class Class_10A56BE0 {
public:
    char Unknown00[0x168];
    int Unknown168;
    int* FUN_10a56be0(int* out);
};

class Class_10A56BF0
{
public:
    char Unknown00[0x184];
    int Unknown184;
    int Unknown188;
    void FUN_10a56bf0(int* OutA, int* OutB);
};

class Class_10A56C10 {
public:
    char Unknown00[0x184];
    int Unknown184;
    int Unknown188;

    void FUN_10a56c10(int p1, int p2);
};

// FUNCTION: 0x10A56BD0 ?FUN_10a56bd0@Class_10A56BD0@@QAEPAHPAH@Z
int* Class_10A56BD0::FUN_10a56bd0(int* out)
{
    *out = Unknown164;
    return out;
}

// FUNCTION: 0x10A56BE0 ?FUN_10a56be0@Class_10A56BE0@@QAEPAHPAH@Z
int* Class_10A56BE0::FUN_10a56be0(int* out)
{
    *out = Unknown168;
    return out;
}

// FUNCTION: 0x10A56BF0 ?FUN_10a56bf0@Class_10A56BF0@@QAEXPAH0@Z
void Class_10A56BF0::FUN_10a56bf0(int* OutA, int* OutB)
{
    *OutA = Unknown184;
    *OutB = Unknown188;
}

// FUNCTION: 0x10A56C10 ?FUN_10a56c10@Class_10A56C10@@QAEXHH@Z
void Class_10A56C10::FUN_10a56c10(int p1, int p2)
{
    Unknown184 = p1;
    Unknown188 = p2;
}
