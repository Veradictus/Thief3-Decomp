// Game/Class_10CA3290.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern char DAT_10ea0760[];

extern char DAT_10e475dc[];

int FUN_10aeb200(const char* In);

void FUN_10af37a0(int Param, const char* Format, int Value);

class Class_10CA3290
{
public:
    void FUN_10ca3290(int Param);
};

// FUNCTION: 0x10CA3290 ?FUN_10ca3290@Class_10CA3290@@QAEXH@Z
void Class_10CA3290::FUN_10ca3290(int Param)
{
    FUN_10af37a0(Param, DAT_10e475dc, FUN_10aeb200(DAT_10ea0760));
}
