// Game/Unsorted_10B9BC80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9D940
{
public:
    bool FUN_10b9d940(int p1, int p2);
};

class Class_10B9BC80_Member
{
public:
    char Unknown00[8];
    Class_10B9D940* Unknown08;
};

class Class_10B9BC80
{
public:
    bool FUN_10b9bc80(int p1, int p2);

    char Unknown00[0x118];
    Class_10B9BC80_Member* Unknown118;
};

// FUNCTION: 0x10B9BC80 ?FUN_10b9bc80@Class_10B9BC80@@QAE_NHH@Z
bool Class_10B9BC80::FUN_10b9bc80(int p1, int p2)
{
    if (!Unknown118)
        return false;
    return Unknown118->Unknown08->FUN_10b9d940(p1, p2);
}
