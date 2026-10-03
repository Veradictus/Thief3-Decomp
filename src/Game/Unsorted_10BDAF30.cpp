// Game/Unsorted_10BDAF30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFF240
{
public:
    void FUN_10bff240(unsigned char A);
};

class Class_10BFF460 : public Class_10BFF240
{
public:
    bool FUN_10bff330();
};

class Class_10BBB410
{
public:
    Class_10BFF460* FUN_10bbb410();
};

class Class_10E94578
{
public:
    virtual void FUN_10bdaf30();

    void FUN_10bc5b50();
};

class Class_10E94698 : public Class_10E94578
{
public:
    virtual void FUN_10bdaf30();

    Class_10BBB410* Unknown04;
};

// FUNCTION: 0x10BDAF30 ?FUN_10bdaf30@Class_10E94698@@UAEXXZ
void Class_10E94698::FUN_10bdaf30()
{
    Class_10BFF460* Obj = Unknown04->FUN_10bbb410();
    if (Obj && !Obj->FUN_10bff330())
        Obj->FUN_10bff240(1);
    FUN_10bc5b50();
}
