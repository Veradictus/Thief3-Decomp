// Game/Unsorted_10C00C80_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const char* In);

    char* Unknown00;
};

class Class_10E97B00
{
public:
    Class_10E97B00(const char* Name);

    virtual void FUN_10c01ff0(void* p1);

    Class_109081E0 Unknown04;
};

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);

    char* Unknown00;
};

class Class_10C01990
{
public:
    Class_10C01990(int A, const Class_1090A780& B);

    int Unknown00;
    Class_1090A780 Unknown04;
};

class Class_10C01CE0
{
public:
    void FUN_10c01ce0();
    void FUN_10c01c10(int A);

    int Unknown00;
};

// FUNCTION: 0x10C013A0 ??0Class_10E97B00@@QAE@PBD@Z
Class_10E97B00::Class_10E97B00(const char* Name) : Unknown04(Name)
{
}

// FUNCTION: 0x10C01990 ??0Class_10C01990@@QAE@HABVClass_1090A780@@@Z
Class_10C01990::Class_10C01990(int A, const Class_1090A780& B) : Unknown00(A), Unknown04(B)
{
}

// FUNCTION: 0x10C01CE0 ?FUN_10c01ce0@Class_10C01CE0@@QAEXXZ
void Class_10C01CE0::FUN_10c01ce0()
{
    while (Unknown00 > 0)
        FUN_10c01c10(0);
}
