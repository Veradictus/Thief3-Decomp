// Game/Unsorted_10B10250.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string>

class Class_10B10C30 {
public:
    void FUN_10b10ab0(int p1, int p2);
    void FUN_10b10c30(int p1);
};

extern "C" void* memset(void*, int, unsigned);

extern bool DAT_10ff35ce;

extern int DAT_10f7b5c8[0x1e000];

class Class_10B10A70
{
public:
    Class_10B10A70* FUN_10b10a70();

    int Unknown00[4];
};

class Class_10B10B80
{
public:
    unsigned short FUN_10ad24b0(int p1);

    bool FUN_10b10b80(int p1);
};

class Class_10E6D4F0
{
public:
    virtual ~Class_10E6D4F0() = 0;
};

inline Class_10E6D4F0::~Class_10E6D4F0() {}

// A string holder: FUN_10aaf830 stores this vtable and copies its argument to +0x04.
class Class_10E77978 : public Class_10E6D4F0
{
public:
    Class_10E77978(std::string A);
    virtual ~Class_10E77978();

    std::string Unknown04;
};

// The object FUN_10b101b0 constructs: a Class_10E77978 whose own vtable folded into its base's.
class Class_10B101B0 : public Class_10E77978
{
public:
    Class_10B101B0(std::string A);
};

class Class_10E779F0 : public Class_10E77978
{
public:
    Class_10E779F0(std::string A, int B);
    virtual ~Class_10E779F0();

    int Unknown20;
    Class_10B101B0* Unknown24;
};

// FUNCTION: 0x10B10790 ??0Class_10E779F0@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
Class_10E779F0::Class_10E779F0(std::string A, int B) : Class_10E77978(A), Unknown20(B)
{
    Unknown24 = new Class_10B101B0(A);
}

// FUNCTION: 0x10B10870 ??_GClass_10E779F0@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B10790's definition in this unit.

// FUNCTION: 0x10B10A70 ?FUN_10b10a70@Class_10B10A70@@QAEPAV1@XZ
Class_10B10A70* Class_10B10A70::FUN_10b10a70()
{
    memset(Unknown00, 0, sizeof(Unknown00));
    if (!DAT_10ff35ce)
    {
        memset(DAT_10f7b5c8, 0, sizeof(DAT_10f7b5c8));
        DAT_10ff35ce = true;
    }
    return this;
}

// FUNCTION: 0x10B10B80 ?FUN_10b10b80@Class_10B10B80@@QAE_NH@Z
bool Class_10B10B80::FUN_10b10b80(int p1)
{
    return FUN_10ad24b0(p1) != 0;
}

// FUNCTION: 0x10B10C30 ?FUN_10b10c30@Class_10B10C30@@QAEXH@Z
void Class_10B10C30::FUN_10b10c30(int p1)
{
    FUN_10b10ab0(0, p1);
}
