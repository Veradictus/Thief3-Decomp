// Game/Unsorted_10AB3800_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);
};

bool FUN_1094c430(const Class_109081E0& A, const Class_109081E0& B);

class Class_10AB3C20
{
public:
    void FUN_10ab3ab0();
    void FUN_10ab3c20(const Class_109081E0& Value);

    char Unknown00[4];
    Class_109081E0 Unknown04;
};

// FUNCTION: 0x10AB3C20 ?FUN_10ab3c20@Class_10AB3C20@@QAEXABVClass_109081E0@@@Z
void Class_10AB3C20::FUN_10ab3c20(const Class_109081E0& Value)
{
    if (FUN_1094c430(Unknown04, Value))
    {
        Unknown04 = Value;
        FUN_10ab3ab0();
    }
}
