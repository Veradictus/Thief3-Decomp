// Game/Unsorted_10A59350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

class Class_10A59370
{
public:
    void FUN_10a59370(int Index, const Class_109081E0& Value);

    char Unknown00[0x1BC];
    Class_109081E0 Unknown1BC[4];
};

// FUNCTION: 0x10A59370 ?FUN_10a59370@Class_10A59370@@QAEXHABVClass_109081E0@@@Z
void Class_10A59370::FUN_10a59370(int Index, const Class_109081E0& Value)
{
    if (Index > -1 && Index < 4)
        Unknown1BC[Index] = Value;
}
