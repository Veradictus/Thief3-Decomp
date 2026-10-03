// Game/Unsorted_10BA5350_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e8d554[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E8D554 : public Class_10EB766C
{
public:
    Class_10E8D554()
    {
        VTable = DAT_10e8d554;
    }
};

class Class_10E8C5FC
{
public:
    virtual Class_10E8D554* FUN_10ba88e0();
};

extern void* DAT_10e8d570[];

class Class_10E8D570 : public Class_10EB766C
{
public:
    Class_10E8D570()
    {
        VTable = DAT_10e8d570;
    }
};

class Class_10E8C600
{
public:
    virtual Class_10E8D570* FUN_10ba8970();
};

extern void* DAT_10e8d58c[];

class Class_10E8D58C : public Class_10EB766C
{
public:
    Class_10E8D58C()
    {
        VTable = DAT_10e8d58c;
    }
};

class Class_10E8C604
{
public:
    virtual Class_10E8D58C* FUN_10ba8a00();
};

extern void* DAT_10e8d5a8[];

class Class_10E8D5A8 : public Class_10EB766C
{
public:
    Class_10E8D5A8()
    {
        VTable = DAT_10e8d5a8;
    }
};

class Class_10E8C608
{
public:
    virtual Class_10E8D5A8* FUN_10ba8a90();
};

extern void* DAT_10e8d5c4[];

class Class_10E8D5C4 : public Class_10EB766C
{
public:
    Class_10E8D5C4()
    {
        VTable = DAT_10e8d5c4;
    }
};

class Class_10E8C60C
{
public:
    virtual Class_10E8D5C4* FUN_10ba8b20();
};

extern void* DAT_10e8d5e0[];

class Class_10E8D5E0 : public Class_10EB766C
{
public:
    Class_10E8D5E0()
    {
        VTable = DAT_10e8d5e0;
    }
};

class Class_10E8C610
{
public:
    virtual Class_10E8D5E0* FUN_10ba8bb0();
};

extern void* DAT_10e8d5fc[];

class Class_10E8D5FC : public Class_10EB766C
{
public:
    Class_10E8D5FC()
    {
        VTable = DAT_10e8d5fc;
    }
};

class Class_10E8C614
{
public:
    virtual Class_10E8D5FC* FUN_10ba8c40();
};

extern void* DAT_10e8d618[];

class Class_10E8D618 : public Class_10EB766C
{
public:
    Class_10E8D618()
    {
        VTable = DAT_10e8d618;
    }
};

class Class_10E8C618
{
public:
    virtual Class_10E8D618* FUN_10ba8cd0();
};

extern void* DAT_10e8d634[];

class Class_10E8D634 : public Class_10EB766C
{
public:
    Class_10E8D634()
    {
        VTable = DAT_10e8d634;
    }
};

class Class_10E8C61C
{
public:
    virtual Class_10E8D634* FUN_10ba8d60();
};

class Class_10C15EF0
{
public:
    Class_10C15EF0();
    ~Class_10C15EF0();

    char Unknown00[0x4010];
};

class Class_10C15DB0
{
public:
    Class_10C15DB0();
    ~Class_10C15DB0();
};

class Class_10E8D658
{
public:
    Class_10E8D658();
    virtual ~Class_10E8D658();

    Class_10C15EF0 Unknown04;
    Class_10C15DB0 Unknown4014;
};

class Class_10BA8F10
{
public:
    virtual ~Class_10BA8F10();
};

extern Class_10BA8F10* DAT_10ff6684;

// FUNCTION: 0x10BA88E0 ?FUN_10ba88e0@Class_10E8C5FC@@UAEPAVClass_10E8D554@@XZ
Class_10E8D554* Class_10E8C5FC::FUN_10ba88e0()
{
    return new(0, 0, 0, 0, 0) Class_10E8D554;
}

// FUNCTION: 0x10BA8970 ?FUN_10ba8970@Class_10E8C600@@UAEPAVClass_10E8D570@@XZ
Class_10E8D570* Class_10E8C600::FUN_10ba8970()
{
    return new(0, 0, 0, 0, 0) Class_10E8D570;
}

// FUNCTION: 0x10BA8A00 ?FUN_10ba8a00@Class_10E8C604@@UAEPAVClass_10E8D58C@@XZ
Class_10E8D58C* Class_10E8C604::FUN_10ba8a00()
{
    return new(0, 0, 0, 0, 0) Class_10E8D58C;
}

// FUNCTION: 0x10BA8A90 ?FUN_10ba8a90@Class_10E8C608@@UAEPAVClass_10E8D5A8@@XZ
Class_10E8D5A8* Class_10E8C608::FUN_10ba8a90()
{
    return new(0, 0, 0, 0, 0) Class_10E8D5A8;
}

// FUNCTION: 0x10BA8B20 ?FUN_10ba8b20@Class_10E8C60C@@UAEPAVClass_10E8D5C4@@XZ
Class_10E8D5C4* Class_10E8C60C::FUN_10ba8b20()
{
    return new(0, 0, 0, 0, 0) Class_10E8D5C4;
}

// FUNCTION: 0x10BA8BB0 ?FUN_10ba8bb0@Class_10E8C610@@UAEPAVClass_10E8D5E0@@XZ
Class_10E8D5E0* Class_10E8C610::FUN_10ba8bb0()
{
    return new(0, 0, 0, 0, 0) Class_10E8D5E0;
}

// FUNCTION: 0x10BA8C40 ?FUN_10ba8c40@Class_10E8C614@@UAEPAVClass_10E8D5FC@@XZ
Class_10E8D5FC* Class_10E8C614::FUN_10ba8c40()
{
    return new(0, 0, 0, 0, 0) Class_10E8D5FC;
}

// FUNCTION: 0x10BA8CD0 ?FUN_10ba8cd0@Class_10E8C618@@UAEPAVClass_10E8D618@@XZ
Class_10E8D618* Class_10E8C618::FUN_10ba8cd0()
{
    return new(0, 0, 0, 0, 0) Class_10E8D618;
}

// FUNCTION: 0x10BA8D60 ?FUN_10ba8d60@Class_10E8C61C@@UAEPAVClass_10E8D634@@XZ
Class_10E8D634* Class_10E8C61C::FUN_10ba8d60()
{
    return new(0, 0, 0, 0, 0) Class_10E8D634;
}

// FUNCTION: 0x10BA8E40 ??0Class_10E8D658@@QAE@XZ
Class_10E8D658::Class_10E8D658()
{
}

// FUNCTION: 0x10BA8EF0 ??_GClass_10E8D658@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10BA8E40's definition in this unit.

// FUNCTION: 0x10BA8F10 ?FUN_10ba8f10@@YAXXZ
void FUN_10ba8f10()
{
    if (DAT_10ff6684)
    {
        delete DAT_10ff6684;
        DAT_10ff6684 = 0;
    }
}
