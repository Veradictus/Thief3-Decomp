// Game/RopeStateTransition.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Native witness: 10B493A0; offsets 18/1C/20 are initialized by accepted 10B492F0.
class Class_10B39870;

class Class_10AA82D0
{
public:
    virtual void Virtual0();
    Class_10B39870* GetLinkedObject();
};

class Class_10B39700
{
public:
    void FUN_10b39700();
};

class Class_10B39710
{
public:
    void FUN_10b39710();
};

class Class_10B395E0
{
public:
    void FUN_10b395e0(int A);
};

class Class_10E7E610 : public Class_10AA82D0
{
public:
    void FUN_10b493a0();

    char Pad04[0x14];
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

// FUNCTION: 0x10B493A0 ?FUN_10b493a0@Class_10E7E610@@QAEXXZ
void Class_10E7E610::FUN_10b493a0()
{
    if (Unknown18 != Unknown1C)
    {
        if (Unknown18 == 0)
            ((Class_10B39700*)GetLinkedObject())->FUN_10b39700();
        else if (Unknown18 == Unknown20)
            ((Class_10B39710*)GetLinkedObject())->FUN_10b39710();
        else if (Unknown18 == 1)
        {
            ((Class_10B395E0*)GetLinkedObject())->FUN_10b395e0(0x49);
            Unknown20 = 1;
        }
        else
        {
            ((Class_10B395E0*)GetLinkedObject())->FUN_10b395e0(0x4A);
            Unknown20 = 2;
        }
        Unknown1C = Unknown18;
    }
}
