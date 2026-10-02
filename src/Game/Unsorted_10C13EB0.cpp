// Game/Unsorted_10C13EB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e9864c[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern const char DAT_10e98680[];

extern const char DAT_10e986f8[];

extern const char DAT_10e98738[];

extern const char DAT_10e98798[];

extern const char DAT_10e987e8[];

extern const char DAT_10e98844[];

extern const char DAT_10e98880[];

extern const char DAT_10e988e4[];

extern const char DAT_10e98920[];

extern const char DAT_10e989d8[];

extern const char DAT_10e98a40[];

extern const char DAT_10e98aa0[];

extern const char DAT_10e98ad8[];

extern const char DAT_10e98b24[];

extern const char DAT_10e98b60[];

extern const char DAT_10e98bb8[];

extern const char DAT_10e98be8[];

class Class_10E5B578
{
public:
    virtual void Virtual0() = 0;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E5B578* Listener);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6DC88_Primary
{
public:
    virtual void Virtual0();

    char Unknown04[8];
};

class Class_10E6DC88 : public Class_10E6DC88_Primary, public Class_10E5B578
{
public:
    ~Class_10E6DC88();
};

class Class_10E8C210 : public Class_10E6DC88
{
public:
    ~Class_10E8C210();

    virtual void Virtual0();
};

// FUNCTION: 0x10C13EB0 ??1Class_10E8C210@@QAE@XZ
Class_10E8C210::~Class_10E8C210()
{
    DAT_10f46da0->Virtual2(this);
}

// FUNCTION: 0x10C14570 ?FUN_10c14570@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14570()
{
    return Class_109081E0(DAT_10e9864c);
}

// FUNCTION: 0x10C14590 ?FUN_10c14590@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14590()
{
    return Class_109081E0(DAT_10e98680);
}

// FUNCTION: 0x10C145B0 ?FUN_10c145b0@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c145b0()
{
    return Class_109081E0(DAT_10e986f8);
}

// FUNCTION: 0x10C145D0 ?FUN_10c145d0@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c145d0()
{
    return Class_109081E0(DAT_10e98738);
}

// FUNCTION: 0x10C147A0 ?FUN_10c147a0@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c147a0()
{
    return Class_109081E0(DAT_10e98798);
}

// FUNCTION: 0x10C147C0 ?FUN_10c147c0@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c147c0()
{
    return Class_109081E0(DAT_10e987e8);
}

// FUNCTION: 0x10C147E0 ?FUN_10c147e0@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c147e0()
{
    return Class_109081E0(DAT_10e98844);
}

// FUNCTION: 0x10C14800 ?FUN_10c14800@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14800()
{
    return Class_109081E0(DAT_10e98880);
}

// FUNCTION: 0x10C14820 ?FUN_10c14820@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14820()
{
    return Class_109081E0(DAT_10e988e4);
}

// FUNCTION: 0x10C14840 ?FUN_10c14840@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14840()
{
    return Class_109081E0(DAT_10e98920);
}

// FUNCTION: 0x10C14860 ?FUN_10c14860@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14860()
{
    return Class_109081E0(DAT_10e989d8);
}

// FUNCTION: 0x10C14880 ?FUN_10c14880@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14880()
{
    return Class_109081E0(DAT_10e98a40);
}

// FUNCTION: 0x10C14A00 ?FUN_10c14a00@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14a00()
{
    return Class_109081E0(DAT_10e98aa0);
}

// FUNCTION: 0x10C14A20 ?FUN_10c14a20@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14a20()
{
    return Class_109081E0(DAT_10e98ad8);
}

// FUNCTION: 0x10C14A40 ?FUN_10c14a40@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14a40()
{
    return Class_109081E0(DAT_10e98b24);
}

// FUNCTION: 0x10C14A60 ?FUN_10c14a60@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14a60()
{
    return Class_109081E0(DAT_10e98b60);
}

// FUNCTION: 0x10C14A80 ?FUN_10c14a80@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14a80()
{
    return Class_109081E0(DAT_10e98bb8);
}

// FUNCTION: 0x10C14AA0 ?FUN_10c14aa0@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10c14aa0()
{
    return Class_109081E0(DAT_10e98be8);
}
