// Game/Unsorted_10B2F6C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

class Class_10B2F6A0
{
public:
    void FUN_10b2f590();
    void FUN_10b2f6c0(const Class_109081E0& Name);

    char Unknown00[0x120];
    void* Unknown120;
    char Unknown124[0x18];
    Class_109081E0 Unknown13C;
};

// FUNCTION: 0x10B2F6C0 ?FUN_10b2f6c0@Class_10B2F6A0@@QAEXABVClass_109081E0@@@Z
void Class_10B2F6A0::FUN_10b2f6c0(const Class_109081E0& Name)
{
    if (Unknown120)
    {
        Unknown13C = Name;
        FUN_10b2f590();
    }
}
