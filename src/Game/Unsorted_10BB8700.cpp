// Game/Unsorted_10BB8700.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10BB8A60
{
public:
    void FUN_10bb8a60(float Delta);

    char Unknown00[0x258];
    float Unknown258;
};

class Class_10BB8AA0
{
public:
    void FUN_10bb8aa0(float Delta);

    char Unknown00[0x260];
    float Unknown260;
};

// FUNCTION: 0x10BB8A60 ?FUN_10bb8a60@Class_10BB8A60@@QAEXM@Z
void Class_10BB8A60::FUN_10bb8a60(float Delta)
{
    Unknown258 += Delta;
    Unknown258 = (DAT_10eafbdc >= Unknown258) ? 0.0f : Unknown258;
}

// FUNCTION: 0x10BB8AA0 ?FUN_10bb8aa0@Class_10BB8AA0@@QAEXM@Z
void Class_10BB8AA0::FUN_10bb8aa0(float Delta)
{
    Unknown260 += Delta;
    Unknown260 = (DAT_10eafbdc >= Unknown260) ? 0.0f : Unknown260;
}
