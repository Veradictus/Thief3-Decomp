// Game/Unsorted_10C02010.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090AFD0
{
public:
    void FUN_1090afd0(const Class_1090AFD0& Other);

    void* Unknown00;
};

class Class_10C02010
{
public:
    Class_10C02010* FUN_10c02010(Class_10C02010* Other);

    int Unknown00;
    Class_1090AFD0 Unknown04;
};

// FUNCTION: 0x10C02010 ?FUN_10c02010@Class_10C02010@@QAEPAV1@PAV1@@Z
Class_10C02010* Class_10C02010::FUN_10c02010(Class_10C02010* Other)
{
    Unknown04.FUN_1090afd0(Other->Unknown04);
    return this;
}
