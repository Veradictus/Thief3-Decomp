// Game/Class_10B66060.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10B66060
{
    char Unknown00[0x2C];
};

struct Data_10B66060
{
    char Unknown000[0x178];
    Info_10B66060 Unknown178;
};

class Class_10B66060
{
public:
    void FUN_10b66060(int A, Data_10B66060* B);

    char Unknown000[0x154];
    Data_10B66060* Unknown154;
    Info_10B66060 Unknown158;
    int Unknown184;
};

// FUNCTION: 0x10B66060 ?FUN_10b66060@Class_10B66060@@QAEXHPAUData_10B66060@@@Z
void Class_10B66060::FUN_10b66060(int A, Data_10B66060* B)
{
    Unknown184 = A;
    Unknown154 = B;
    Unknown158 = B->Unknown178;
}
