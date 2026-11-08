// Game/DeferredActionCallback.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10D43FD0 {
public:
    int FUN_10d43fd0(int Action);
    int FUN_10d41050(int Action, float Amount, int Flag);
};

class Action192 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(Class_10D43FD0* Owner);
    int Unknown04, Unknown08, Count;
};

class Class_10E6CA18 { public: virtual ~Class_10E6CA18(); };

class Class_10E5B578 {
public:
    virtual void Virtual0(int Code, int B, int C, int* D) = 0;
    Class_10D43FD0* Owner;
    Action192* Action;
};

class Class_10E8DC34 : public Class_10E6CA18, public Class_10E5B578 {
public:
    virtual ~Class_10E8DC34();
    virtual void Virtual0(int Code, int B, int C, int* D);
};

class Class_10F46DA0 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(Class_10E5B578* Listener, int Code, int A, int B);
};

extern Class_10F46DA0* DAT_10f46da0;

// FUNCTION: 0x10BB14F0 ?Virtual0@Class_10E8DC34@@UAEHHHHPAH@Z
void Class_10E8DC34::Virtual0(int Code, int B, int C, int* D)
{
    switch (Code) {
    case 0x78:
        if (Owner && Action) {
            DAT_10f46da0->Virtual3(this, 0x7D, -1, -1);
            DAT_10f46da0->Virtual3(this, 0x7E, -1, -1);
            ++Action->Count;
            Action->Virtual4(Owner);
            Owner = 0;
            Action = 0;
        }
        // The native event handler deliberately continues through the0x7D case.
    case 0x7D:
        if (Owner && Action)
            Owner->FUN_10d41050((int)Action, 1.0f, 0);
        break;
    case 0x7E:
        if (Owner && Action)
            Owner->FUN_10d43fd0((int)Action);
        break;
    }
}
