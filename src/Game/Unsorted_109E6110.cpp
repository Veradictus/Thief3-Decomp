// Game/Unsorted_109E6110.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

class Class_10E5B2C0
{
public:
    virtual void FUN_109e66e0(const Class_109081E0& Value);

    char Unknown04[0xD4];
    Class_109081E0 UnknownD8;
};

// FUNCTION: 0x109E66E0 ?FUN_109e66e0@Class_10E5B2C0@@UAEXABVClass_109081E0@@@Z
void Class_10E5B2C0::FUN_109e66e0(const Class_109081E0& Value)
{
    UnknownD8 = Value;
}
