// Game/Class_10C9DFC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern char DAT_10ea0908[];

extern char DAT_10e475dc[];

int FUN_10aeb200(const char* In);

void FUN_10af37a0(int Param, const char* Format, int Value);

class Class_10C9DFC0
{
public:
    void FUN_10c9dfc0(int Param);
};

// FUNCTION: 0x10C9DFC0 ?FUN_10c9dfc0@Class_10C9DFC0@@QAEXH@Z
void Class_10C9DFC0::FUN_10c9dfc0(int Param)
{
    FUN_10af37a0(Param, DAT_10e475dc, FUN_10aeb200(DAT_10ea0908));
}
