// Game/Unsorted_10C1AF00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C1AF00
{
    char Unknown00[0x2C];
    int Unknown2C;
    int Unknown30;
    char Unknown34[0x28];
    float Unknown5C;
};

class Class_10E98D50
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10c1af00(Class_10E98D50* Other);

    char Unknown04[0x44];
    Struct_10C1AF00* Unknown48;
};

// FUNCTION: 0x10C1AF00 ?FUN_10c1af00@Class_10E98D50@@UAEHPAV1@@Z
int Class_10E98D50::FUN_10c1af00(Class_10E98D50* Other)
{
    if (Unknown48->Unknown2C == Other->Unknown48->Unknown2C && Unknown48->Unknown30 == Other->Unknown48->Unknown30 &&
        Unknown48->Unknown5C == Other->Unknown48->Unknown5C)
        return 1;
    return 0;
}
