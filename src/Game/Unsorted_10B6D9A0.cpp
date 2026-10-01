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
