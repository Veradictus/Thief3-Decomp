// Game/Unsorted_10A2FAB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e47660[];

int FUN_10af36e0(const char* A, const char* B);

class Class_10E50928
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a2fb40(const Class_10E50928* Other);

    const char* Unknown04;
};

// FUNCTION: 0x10A2FB40 ?FUN_10a2fb40@Class_10E50928@@UAEHPBV1@@Z
int Class_10E50928::FUN_10a2fb40(const Class_10E50928* Other)
{
    if (Other && !FUN_10af36e0(Unknown04 ? Unknown04 : DAT_10e47660, Other->Unknown04 ? Other->Unknown04 : DAT_10e47660))
        return 1;
    return 0;
}
