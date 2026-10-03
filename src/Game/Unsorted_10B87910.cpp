// Game/Unsorted_10B87910.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B8D520
{
public:
    ~Class_10B8D520();
};

class Class_10B87910
{
public:
    void FUN_10b87910(Class_10B8D520* A);

    char Unknown00[0x78];
    Class_10B8D520* Unknown78;
};

// FUNCTION: 0x10B87910 ?FUN_10b87910@Class_10B87910@@QAEXPAVClass_10B8D520@@@Z
void Class_10B87910::FUN_10b87910(Class_10B8D520* A)
{
    if (Unknown78)
    {
        delete Unknown78;
        Unknown78 = 0;
    }
    Unknown78 = A;
}
