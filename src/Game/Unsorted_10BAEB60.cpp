// Game/Unsorted_10BAEB60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e8d954[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern const char DAT_10e8d95c[];

class Class_10A68D20;

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

struct Struct_10BAFBF0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BAFBF0
{
public:
    Class_10BAFBF0() : Unknown04(0) {}

    int Unknown04;
};

class Class_10E8DBA4 : public Class_10BAFBF0
{
public:
    Class_10E8DBA4(const Struct_10BAFBF0& A, const int& B, const Class_1090A780& C);

    virtual void FUN_10baeb30(Class_10A68D20* Owner);

    Struct_10BAFBF0 Unknown08;
    int Unknown14;
    Class_1090A780 Unknown18;
};

// FUNCTION: 0x10BAEB60 ?FUN_10baeb60@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10baeb60()
{
    return Class_109081E0(DAT_10e8d954);
}

// FUNCTION: 0x10BAEB80 ?FUN_10baeb80@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10baeb80()
{
    return Class_109081E0(DAT_10e8d95c);
}

// FUNCTION: 0x10BAFBF0 ??0Class_10E8DBA4@@QAE@ABUStruct_10BAFBF0@@ABHABVClass_1090A780@@@Z
Class_10E8DBA4::Class_10E8DBA4(const Struct_10BAFBF0& A, const int& B, const Class_1090A780& C)
    : Unknown08(A), Unknown14(B), Unknown18(C)
{
}
