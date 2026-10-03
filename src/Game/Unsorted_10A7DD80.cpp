// Game/Unsorted_10A7DD80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10e6becc;

extern const char DAT_10e4da8c[];

int FUN_10af36e0(const char* A, const char* B);

class Class_10E6BEBC
{
public:
    virtual void Virtual0();
    virtual int FUN_10a7dd80(const char* Name);
};

// FUNCTION: 0x10A7DD80 ?FUN_10a7dd80@Class_10E6BEBC@@UAEHPBD@Z
int Class_10E6BEBC::FUN_10a7dd80(const char* Name)
{
    if (FUN_10af36e0((const char*)&DAT_10e6becc, Name) && FUN_10af36e0(DAT_10e4da8c, Name))
        return 0;
    return 1;
}
