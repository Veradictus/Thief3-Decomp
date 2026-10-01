// Game/Unsorted_10905F40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10906070
{
    char Unknown00[4];
    int Unknown04;
    char Unknown08[0x101];
    char Unknown109;
};

void FUN_1090dcb0(int p1, char* p2);

// FUNCTION: 0x10906070 ?FUN_10906070@@YAXPAUInfo_10906070@@@Z
void FUN_10906070(Info_10906070* Info)
{
    FUN_1090dcb0(Info->Unknown04, &Info->Unknown109);
}
