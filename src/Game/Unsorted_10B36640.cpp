// Game/Unsorted_10B36640.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's memory manager (0x10905AA0): the allocation happens inside a
// scope of it (slots 8 and 9).
class Class_10905A90_Member
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
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// FUN_10b362f0 is the constructor: it stores the vtable and returns this.
class Class_10B362F0
{
public:
    Class_10B362F0* FUN_10b362f0();

    void* Unknown00;
};

class Class_10E79588
{
public:
    virtual Class_10B362F0* FUN_10b36640();
};

// FUN_10b36310 is the constructor: it stores the vtable and returns this.
class Class_10B36310
{
public:
    Class_10B36310* FUN_10b36310();

    void* Unknown00;
};

class Class_10E7958C
{
public:
    virtual Class_10B36310* FUN_10b36690();
};

// FUN_10b36330 is the constructor: it stores the vtable and returns this.
class Class_10B36330
{
public:
    Class_10B36330* FUN_10b36330();

    void* Unknown00;
};

class Class_10E79590
{
public:
    virtual Class_10B36330* FUN_10b366e0();
};

// FUN_10b36350 is the constructor: it stores the vtable and returns this.
class Class_10B36350
{
public:
    Class_10B36350* FUN_10b36350();

    void* Unknown00;
};

class Class_10E79594
{
public:
    virtual Class_10B36350* FUN_10b36730();
};

// FUN_10b36370 is the constructor: it stores the vtable and returns this.
class Class_10B36370
{
public:
    Class_10B36370* FUN_10b36370();

    void* Unknown00;
};

class Class_10E79598
{
public:
    virtual Class_10B36370* FUN_10b36780();
};

// FUN_10b36390 is the constructor: it stores the vtable and returns this.
class Class_10B36390
{
public:
    Class_10B36390* FUN_10b36390();

    void* Unknown00;
};

class Class_10E7959C
{
public:
    virtual Class_10B36390* FUN_10b367d0();
};

// FUN_10b363d0 is the constructor: it stores the vtable and returns this.
class Class_10B363D0
{
public:
    Class_10B363D0* FUN_10b363d0();

    void* Unknown00;
};

class Class_10E795A0
{
public:
    virtual Class_10B363D0* FUN_10b36820();
};

// FUN_10b36410 is the constructor: it stores the vtable and returns this.
class Class_10B36410
{
public:
    Class_10B36410* FUN_10b36410();

    void* Unknown00;
};

class Class_10E795A4
{
public:
    virtual Class_10B36410* FUN_10b36870();
};

// FUN_10b36430 is the constructor: it stores the vtable and returns this.
class Class_10B36430
{
public:
    Class_10B36430* FUN_10b36430();

    void* Unknown00;
};

class Class_10E795A8
{
public:
    virtual Class_10B36430* FUN_10b368c0();
};

// FUN_10b36470 is the constructor: it stores the vtable and returns this.
class Class_10B36470
{
public:
    Class_10B36470* FUN_10b36470();

    void* Unknown00;
};

class Class_10E795AC
{
public:
    virtual Class_10B36470* FUN_10b36910();
};

// FUN_10b364d0 is the constructor: it stores the vtable and returns this.
class Class_10B364D0
{
public:
    Class_10B364D0* FUN_10b364d0();

    void* Unknown00;
};

class Class_10E79574
{
public:
    virtual Class_10B364D0* FUN_10b36960();
};

// FUNCTION: 0x10B36640 ?FUN_10b36640@Class_10E79588@@UAEPAVClass_10B362F0@@XZ
Class_10B362F0* Class_10E79588::FUN_10b36640()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B362F0* Result = 0;
    void* Memory = operator new(sizeof(Class_10B362F0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B362F0*>(Memory)->FUN_10b362f0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36690 ?FUN_10b36690@Class_10E7958C@@UAEPAVClass_10B36310@@XZ
Class_10B36310* Class_10E7958C::FUN_10b36690()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36310* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36310), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36310*>(Memory)->FUN_10b36310();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B366E0 ?FUN_10b366e0@Class_10E79590@@UAEPAVClass_10B36330@@XZ
Class_10B36330* Class_10E79590::FUN_10b366e0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36330* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36330), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36330*>(Memory)->FUN_10b36330();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36730 ?FUN_10b36730@Class_10E79594@@UAEPAVClass_10B36350@@XZ
Class_10B36350* Class_10E79594::FUN_10b36730()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36350* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36350), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36350*>(Memory)->FUN_10b36350();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36780 ?FUN_10b36780@Class_10E79598@@UAEPAVClass_10B36370@@XZ
Class_10B36370* Class_10E79598::FUN_10b36780()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36370* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36370), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36370*>(Memory)->FUN_10b36370();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B367D0 ?FUN_10b367d0@Class_10E7959C@@UAEPAVClass_10B36390@@XZ
Class_10B36390* Class_10E7959C::FUN_10b367d0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36390* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36390), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36390*>(Memory)->FUN_10b36390();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36820 ?FUN_10b36820@Class_10E795A0@@UAEPAVClass_10B363D0@@XZ
Class_10B363D0* Class_10E795A0::FUN_10b36820()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B363D0* Result = 0;
    void* Memory = operator new(sizeof(Class_10B363D0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B363D0*>(Memory)->FUN_10b363d0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36870 ?FUN_10b36870@Class_10E795A4@@UAEPAVClass_10B36410@@XZ
Class_10B36410* Class_10E795A4::FUN_10b36870()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36410* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36410), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36410*>(Memory)->FUN_10b36410();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B368C0 ?FUN_10b368c0@Class_10E795A8@@UAEPAVClass_10B36430@@XZ
Class_10B36430* Class_10E795A8::FUN_10b368c0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36430* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36430), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36430*>(Memory)->FUN_10b36430();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36910 ?FUN_10b36910@Class_10E795AC@@UAEPAVClass_10B36470@@XZ
Class_10B36470* Class_10E795AC::FUN_10b36910()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36470* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36470), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36470*>(Memory)->FUN_10b36470();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36960 ?FUN_10b36960@Class_10E79574@@UAEPAVClass_10B364D0@@XZ
Class_10B364D0* Class_10E79574::FUN_10b36960()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B364D0* Result = 0;
    void* Memory = operator new(sizeof(Class_10B364D0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B364D0*>(Memory)->FUN_10b364d0();
    FUN_10905aa0()->Virtual9();
    return Result;
}
