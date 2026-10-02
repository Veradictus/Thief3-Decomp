// Game/Unsorted_10A95EE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUN_10a95d90 is the constructor: it stores the vtable and returns this.
class Class_10A95D90
{
public:
    Class_10A95D90* FUN_10a95d90();

    void* Unknown00;
};

class Class_10E5D928
{
public:
    virtual Class_10A95D90* FUN_10a95ee0();
};

// FUN_10a95db0 is the constructor: it stores the vtable and returns this.
class Class_10A95DB0
{
public:
    Class_10A95DB0* FUN_10a95db0();

    void* Unknown00;
};

class Class_10E5D92C
{
public:
    virtual Class_10A95DB0* FUN_10a95f30();
};

// FUN_10a95dd0 is the constructor: it stores the vtable and returns this.
class Class_10A95DD0
{
public:
    Class_10A95DD0* FUN_10a95dd0();

    void* Unknown00;
};

class Class_10E5D930
{
public:
    virtual Class_10A95DD0* FUN_10a95f80();
};

// FUN_10a95df0 is the constructor: it stores the vtable and returns this.
class Class_10A95DF0
{
public:
    Class_10A95DF0* FUN_10a95df0();

    void* Unknown00;
};

class Class_10E5D934
{
public:
    virtual Class_10A95DF0* FUN_10a95fd0();
};

// FUN_10a95e10 is the constructor: it stores the vtable and returns this.
class Class_10A95E10
{
public:
    Class_10A95E10* FUN_10a95e10();

    void* Unknown00;
};

class Class_10E5D920
{
public:
    virtual Class_10A95E10* FUN_10a96020();
};

// FUN_10a95e30 is the constructor: it stores the vtable and returns this.
class Class_10A95E30
{
public:
    Class_10A95E30* FUN_10a95e30();

    void* Unknown00;
};

class Class_10E5D9B0
{
public:
    virtual Class_10A95E30* FUN_10a96070();
};

// FUN_10a95e50 is the constructor: it stores the vtable and returns this.
class Class_10A95E50
{
public:
    Class_10A95E50* FUN_10a95e50();

    void* Unknown00;
};

class Class_10E5D9B4
{
public:
    virtual Class_10A95E50* FUN_10a960c0();
};

// FUN_10a95e70 is the constructor: it stores the vtable and returns this.
class Class_10A95E70
{
public:
    Class_10A95E70* FUN_10a95e70();

    void* Unknown00;
};

class Class_10E5D9B8
{
public:
    virtual Class_10A95E70* FUN_10a96110();
};

// FUN_10a95e90 is the constructor: it stores the vtable and returns this.
class Class_10A95E90
{
public:
    Class_10A95E90* FUN_10a95e90();

    void* Unknown00;
};

class Class_10E5D938
{
public:
    virtual Class_10A95E90* FUN_10a96160();
};

// FUN_10a95eb0 is the constructor: it stores the vtable and returns this.
class Class_10A95EB0
{
public:
    Class_10A95EB0* FUN_10a95eb0();

    void* Unknown00;
};

class Class_10E5D93C
{
public:
    virtual Class_10A95EB0* FUN_10a961b0();
};

// FUN_10a95ed0 is the constructor: it stores the vtable and returns this.
class Class_10A95ED0
{
public:
    Class_10A95ED0* FUN_10a95ed0();

    void* Unknown00;
};

class Class_10E5D924
{
public:
    virtual Class_10A95ED0* FUN_10a96390();
};

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e6cf48[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E6CF48 : public Class_10EB766C
{
public:
    Class_10E6CF48()
    {
        VTable = DAT_10e6cf48;
    }
};

class Class_10E5D830
{
public:
    virtual Class_10E6CF48* FUN_10a97e70();
};

extern void* DAT_10e6cf64[];

class Class_10E6CF64 : public Class_10EB766C
{
public:
    Class_10E6CF64()
    {
        VTable = DAT_10e6cf64;
    }
};

class Class_10E5D82C
{
public:
    virtual Class_10E6CF64* FUN_10a97f10();
};

extern void* DAT_10e6cf80[];

class Class_10E6CF80 : public Class_10EB766C
{
public:
    Class_10E6CF80()
    {
        VTable = DAT_10e6cf80;
    }
};

class Class_10E5D834
{
public:
    virtual Class_10E6CF80* FUN_10a98630();
};

// FUNCTION: 0x10A95EE0 ?FUN_10a95ee0@Class_10E5D928@@UAEPAVClass_10A95D90@@XZ
Class_10A95D90* Class_10E5D928::FUN_10a95ee0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95D90* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95D90), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95D90*>(Memory)->FUN_10a95d90();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A95F30 ?FUN_10a95f30@Class_10E5D92C@@UAEPAVClass_10A95DB0@@XZ
Class_10A95DB0* Class_10E5D92C::FUN_10a95f30()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95DB0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95DB0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95DB0*>(Memory)->FUN_10a95db0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A95F80 ?FUN_10a95f80@Class_10E5D930@@UAEPAVClass_10A95DD0@@XZ
Class_10A95DD0* Class_10E5D930::FUN_10a95f80()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95DD0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95DD0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95DD0*>(Memory)->FUN_10a95dd0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A95FD0 ?FUN_10a95fd0@Class_10E5D934@@UAEPAVClass_10A95DF0@@XZ
Class_10A95DF0* Class_10E5D934::FUN_10a95fd0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95DF0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95DF0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95DF0*>(Memory)->FUN_10a95df0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A96020 ?FUN_10a96020@Class_10E5D920@@UAEPAVClass_10A95E10@@XZ
Class_10A95E10* Class_10E5D920::FUN_10a96020()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95E10* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95E10), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95E10*>(Memory)->FUN_10a95e10();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A96070 ?FUN_10a96070@Class_10E5D9B0@@UAEPAVClass_10A95E30@@XZ
Class_10A95E30* Class_10E5D9B0::FUN_10a96070()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95E30* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95E30), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95E30*>(Memory)->FUN_10a95e30();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A960C0 ?FUN_10a960c0@Class_10E5D9B4@@UAEPAVClass_10A95E50@@XZ
Class_10A95E50* Class_10E5D9B4::FUN_10a960c0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95E50* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95E50), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95E50*>(Memory)->FUN_10a95e50();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A96110 ?FUN_10a96110@Class_10E5D9B8@@UAEPAVClass_10A95E70@@XZ
Class_10A95E70* Class_10E5D9B8::FUN_10a96110()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95E70* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95E70), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95E70*>(Memory)->FUN_10a95e70();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A96160 ?FUN_10a96160@Class_10E5D938@@UAEPAVClass_10A95E90@@XZ
Class_10A95E90* Class_10E5D938::FUN_10a96160()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95E90* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95E90), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95E90*>(Memory)->FUN_10a95e90();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A961B0 ?FUN_10a961b0@Class_10E5D93C@@UAEPAVClass_10A95EB0@@XZ
Class_10A95EB0* Class_10E5D93C::FUN_10a961b0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95EB0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95EB0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95EB0*>(Memory)->FUN_10a95eb0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A96390 ?FUN_10a96390@Class_10E5D924@@UAEPAVClass_10A95ED0@@XZ
Class_10A95ED0* Class_10E5D924::FUN_10a96390()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95ED0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95ED0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95ED0*>(Memory)->FUN_10a95ed0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A97E70 ?FUN_10a97e70@Class_10E5D830@@UAEPAVClass_10E6CF48@@XZ
Class_10E6CF48* Class_10E5D830::FUN_10a97e70()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CF48* Result = new(0, 0, 0, 0, 0) Class_10E6CF48;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A97F10 ?FUN_10a97f10@Class_10E5D82C@@UAEPAVClass_10E6CF64@@XZ
Class_10E6CF64* Class_10E5D82C::FUN_10a97f10()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CF64* Result = new(0, 0, 0, 0, 0) Class_10E6CF64;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A98630 ?FUN_10a98630@Class_10E5D834@@UAEPAVClass_10E6CF80@@XZ
Class_10E6CF80* Class_10E5D834::FUN_10a98630()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CF80* Result = new(0, 0, 0, 0, 0) Class_10E6CF80;
    FUN_10905aa0()->Virtual9();
    return Result;
}
