// Game/Class_10943970.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10943970
{
public:
    int FUN_10943970();

    char Unknown00[0xE4];
    int UnknownE4;
    char UnknownE8[0x4];
    int UnknownEC;
    char UnknownF0[0xC];
    int UnknownFC;
    char Unknown100[0x4];
    int Unknown104;
};

// FUNCTION: 0x10943970 ?FUN_10943970@Class_10943970@@QAEHXZ
int Class_10943970::FUN_10943970()
{
    return (UnknownFC + (Unknown104 + UnknownE4 * 2) * 8 + UnknownEC) * 2 + 0x1ac;
}
