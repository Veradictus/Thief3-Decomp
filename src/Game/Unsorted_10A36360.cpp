// Game/Unsorted_10A36360.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class AMetaProperty;

class AVulnerabilityObject
{
    DECLARE_CLASS(AVulnerabilityObject, AMetaProperty, 0x0, Engine)
};

class Class_10A36380_Param
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual int Virtual22(UClass* SomeBaseClass);
};

class Class_10E664C0
{
public:
    virtual int FUN_10a36380(int A, int B, Class_10A36380_Param* Object, int D);

    int FUN_10b10060(int A, int B, Class_10A36380_Param* Object, int D);
};

// FUNCTION: 0x10A36380 ?FUN_10a36380@Class_10E664C0@@UAEHHHPAVClass_10A36380_Param@@H@Z
int Class_10E664C0::FUN_10a36380(int A, int B, Class_10A36380_Param* Object, int D)
{
    if (!Object->Virtual22(AVulnerabilityObject::StaticClass()))
        return 0;
    return FUN_10b10060(A, B, Object, D);
}
