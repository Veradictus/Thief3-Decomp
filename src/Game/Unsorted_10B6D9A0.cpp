// Game/Unsorted_10B6D9A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e86fd0[];

class Class_10E87B68
{
public:
    Class_10E87B68();

    void** Unknown00;
};

class Class_10E86FD0 : public Class_10E87B68
{
public:
    Class_10E86FD0* FUN_10b6f9e0();
};

void* FUN_10b154c0();

class Class_10B15960
{
public:
    bool FUN_10b15960(int p1);
};

class Class_10B64280
{
public:
    void FUN_10b744b0();
    void FUN_10b6f870();
};

class Class_10E88900
{
public:
    Class_10E88900();

    virtual ~Class_10E88900();

    char Unknown04[0x2C8];
};

class Class_10B59FA0_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10B59F20_Member
{
public:
    Class_10B59F20_Member(Class_10B59FA0_Member* In = 0) : Unknown00(In)
    {
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10B59F20_Member()
    {
        if (Unknown00)
            Unknown00->Virtual2();
    }

    Class_10B59FA0_Member* Unknown00;
};

class Class_10E86DC0 : public Class_10E88900
{
public:
    Class_10E86DC0(int A);

    virtual ~Class_10E86DC0();

    int Unknown2CC;
    int Unknown2D0;
    int Unknown2D4;
    int Unknown2D8;
    int Unknown2DC;
    int Unknown2E0;
    int Unknown2E4;
    int Unknown2E8;
    int Unknown2EC;
    int Unknown2F0;
    bool Unknown2F4;
    Class_10B59F20_Member Unknown2F8;
    int Unknown2FC;
};

// FUNCTION: 0x10B6F400 ??0Class_10E86DC0@@QAE@H@Z
Class_10E86DC0::Class_10E86DC0(int A)
    : Unknown2CC(0), Unknown2D0(0), Unknown2D4(0), Unknown2D8(0), Unknown2DC(0), Unknown2E0(0),
      Unknown2E4(0), Unknown2E8(0), Unknown2EC(0), Unknown2F0(0), Unknown2F4(false), Unknown2FC(A)
{
}

// FUNCTION: 0x10B6F870 ?FUN_10b6f870@Class_10B64280@@QAEXXZ
void Class_10B64280::FUN_10b6f870()
{
    FUN_10b744b0();
    static_cast<Class_10B15960*>(FUN_10b154c0())->FUN_10b15960(0);
}

// FUNCTION: 0x10B6F9E0 ?FUN_10b6f9e0@Class_10E86FD0@@QAEPAV1@XZ
Class_10E86FD0* Class_10E86FD0::FUN_10b6f9e0()
{
    this->Class_10E87B68::Class_10E87B68();
    Unknown00 = DAT_10e86fd0;
    return this;
}
