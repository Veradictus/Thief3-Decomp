// Game/Unsorted_10B56980.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10B56C80
{
public:
    Class_1090A780 FUN_10b56c80();

    char Unknown00[0x1BC];
    Class_1090A780 Unknown1BC;
};

extern void* DAT_10e82058;

extern void* DAT_10e7edb8[];

extern void FUN_10a51620(void);

class Class_10B592E0 {
public:
    char Unknown00[0x118];
    void* Field118;
    void FUN_10b592e0();
};

void FUN_10b79560();

void FUN_10b792d0();

void FUN_10b7a3b0();

extern void* DAT_10e822b0[];

class Class_10A66190
{
public:
    void FUN_10a66190();

    void* VTable;
};

class Class_10B59E00 : public Class_10A66190
{
public:
    void FUN_10b59e00();
};


// Declare as functions to get direct mov instructions
extern void* DAT_10e828b0[];

class Class_10E69080
{
public:
    Class_10E69080();

    void* vtable;
};

class Class_10B5AB90 : public Class_10E69080
{
public:
    char Unknown004[0x114];
    void* field118;
    char Unknown11C[0xB4];
    int field1D0;

    Class_10B5AB90* FUN_10b5ab90();
};

extern void FUN_10a58e50(void);

class Class_10B5ABE0 {
public:
    char Unknown00[0x118];
    void* Field118;
    void FUN_10b5abe0();
};

void FUN_10a58950();

void FUN_10a593a0();

extern void* DAT_10e82af8[];

class Class_10B78780
{
public:
    void FUN_10b78780();

    void** Unknown00;
    char Unknown04[0x18C];
};

class Class_10E82AF8 : public Class_10B78780
{
public:
    Class_10E82AF8* FUN_10b5aea0();

    int Unknown190;
    int Unknown194;
};

class Class_10B787F0
{
public:
    void FUN_10b787f0();
};

class Class_10B5AEC0 : public Class_10B787F0
{
public:
    void* Field00;

    void FUN_10b5aec0();
};

void FUN_10b78080();

extern const char DAT_10e82cf4[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10B5B050
{
public:
    Class_109081E0 FUN_10b5b050();
};

void FUN_10b45c20();

extern void* DAT_10e83230[];

class Class_10E88900
{
public:
    Class_10E88900();

    void** Unknown00;
    char Unknown04[0x2C8];
};

class Class_10E83230 : public Class_10E88900
{
public:
    Class_10E83230* FUN_10b5c400();

    int Unknown2CC;
    int Unknown2D0;
    int Unknown2D4;
};

void FUN_10b59e30();

class Class_10B5FAE0
{
public:
    void FUN_10b5fae0(bool Param);
};

extern Class_10B5FAE0* DAT_10ff6598;

extern void* DAT_10e83c48;


class Class_10B460C0
{
public:
    void* Field00;

    void FUN_10b460c0();
};

class Class_10B60F30 : public Class_10B460C0
{
public:
    void FUN_10b60f30();
};

void FUN_10a529e0();

// Parameter setter at field offset 0x1ec

class Class_10B61020 {
public:
    char Unknown00[0x1ec];
    int Field1ec;
    void FUN_10b61020(int param);
};

class Class_10B61C90
{
public:
    char Unknown00[0x1ac];
    void* Field1AC;

    void* FUN_10b61c90();
};

extern void* DAT_10ff659c[];

class Class_10B61D20 {
public:
    void FUN_10b61be0();
};

extern const char DAT_10e84284[];

class Class_10B61EA0
{
public:
    Class_109081E0 FUN_10b61ea0();
};

void FUN_10b74330();

void FUN_10b74400();

void FUN_10b79770();

// Parameter setter at field offset 0x2fc

class Class_10B64430 {
public:
    char Unknown00[0x2fc];
    int Field2fc;
    void FUN_10b64430(int param);
};

// Constructor-like initialization with mixed vtable stores

extern void* DAT_10e68d80;

class Class_10B65DE0 {
public:
    char Unknown00[0x118];
    void* Field118;
    void FUN_10b65de0();
};

extern void* DAT_10e84978[];

class Class_10E87D58
{
public:
    Class_10E87D58* FUN_10b75b10();

    void* Unknown00;
    char Unknown04[0x114];
    void* Unknown118;
    char Unknown11C[0xE4];
};

class Class_10E84978 : public Class_10E87D58
{
public:
    Class_10E84978* FUN_10b65e00();

    int Unknown200;
};

void FUN_10b76060();

void FUN_10b760b0();

struct Info_10B66060
{
    char Unknown00[0x2C];
};

struct Data_10B66060
{
    char Unknown000[0x178];
    Info_10B66060 Unknown178;
};

class Class_10B66060
{
public:
    void FUN_10b66060(int A, Data_10B66060* B);

    char Unknown000[0x154];
    Data_10B66060* Unknown154;
    Info_10B66060 Unknown158;
    int Unknown184;
};

// FUNCTION: 0x10B56C80 ?FUN_10b56c80@Class_10B56C80@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10B56C80::FUN_10b56c80()
{
    return Class_1090A780(Unknown1BC);
}

// FUNCTION: 0x10B592E0 ?FUN_10b592e0@Class_10B592E0@@QAEXXZ
void Class_10B592E0::FUN_10b592e0()
{
    *(void**)this = &DAT_10e82058;
    Field118 = DAT_10e7edb8;
    FUN_10a51620();
}

// FUNCTION: 0x10B59670 ?FUN_10b59670@@YAXXZ
void FUN_10b59670()
{
    FUN_10b79560();
}

// FUNCTION: 0x10B59710 ?FUN_10b59710@@YAXXZ
void FUN_10b59710()
{
    FUN_10b792d0();
}

// FUNCTION: 0x10B59720 ?FUN_10b59720@@YAXXZ
void FUN_10b59720()
{
    FUN_10b7a3b0();
}

// FUNCTION: 0x10B59E00 ?FUN_10b59e00@Class_10B59E00@@QAEXXZ
void Class_10B59E00::FUN_10b59e00()
{
    VTable = DAT_10e822b0;
    FUN_10a66190();
}

// FUNCTION: 0x10B59F70 ?FUN_10b59f70@@YAHXZ
int FUN_10b59f70()
{
    return 0;
}

// FUNCTION: 0x10B5AB90 ?FUN_10b5ab90@Class_10B5AB90@@QAEPAV1@XZ
Class_10B5AB90* Class_10B5AB90::FUN_10b5ab90()
{
    this->Class_10E69080::Class_10E69080();
    this->vtable = (void*)DAT_10e828b0;
    this->field118 = (void*)DAT_10e7edb8;
    this->field1D0 = 0;
    return this;
}

// FUNCTION: 0x10B5ABE0 ?FUN_10b5abe0@Class_10B5ABE0@@QAEXXZ
void Class_10B5ABE0::FUN_10b5abe0()
{
    *(void**)this = DAT_10e828b0;
    Field118 = DAT_10e7edb8;
    FUN_10a58e50();
}

// FUNCTION: 0x10B5AC00 ?FUN_10b5ac00@@YAXXZ
void FUN_10b5ac00()
{
    FUN_10a58950();
}

// FUNCTION: 0x10B5AC10 ?FUN_10b5ac10@@YAXXZ
void FUN_10b5ac10()
{
    FUN_10a593a0();
}

// FUNCTION: 0x10B5AEA0 ?FUN_10b5aea0@Class_10E82AF8@@QAEPAV1@XZ
Class_10E82AF8* Class_10E82AF8::FUN_10b5aea0()
{
    FUN_10b78780();
    Unknown190 = 0;
    Unknown194 = 0;
    Unknown00 = DAT_10e82af8;
    return this;
}

// FUNCTION: 0x10B5AEC0 ?FUN_10b5aec0@Class_10B5AEC0@@QAEXXZ
void Class_10B5AEC0::FUN_10b5aec0()
{
    Field00 = (void*)DAT_10e82af8;
    FUN_10b787f0();
}

// FUNCTION: 0x10B5AED0 ?FUN_10b5aed0@@YAXXZ
void FUN_10b5aed0()
{
    FUN_10b78080();
}

// FUNCTION: 0x10B5B050 ?FUN_10b5b050@Class_10B5B050@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10B5B050::FUN_10b5b050()
{
    return Class_109081E0(DAT_10e82cf4);
}

// FUNCTION: 0x10B5B750 ?FUN_10b5b750@@YAXXZ
void FUN_10b5b750()
{
    FUN_10b45c20();
}

// FUNCTION: 0x10B5C400 ?FUN_10b5c400@Class_10E83230@@QAEPAV1@XZ
Class_10E83230* Class_10E83230::FUN_10b5c400()
{
    this->Class_10E88900::Class_10E88900();
    Unknown2CC = 0;
    Unknown2D0 = 0;
    Unknown2D4 = 0;
    Unknown00 = DAT_10e83230;
    return this;
}

// FUNCTION: 0x10B5C430 ?FUN_10b5c430@@YAXXZ
void FUN_10b5c430()
{
    FUN_10b59e30();
}

// FUNCTION: 0x10B60580 ?FUN_10b60580@@YAXH@Z
void FUN_10b60580(int Param)
{
    DAT_10ff6598->FUN_10b5fae0(Param == 1);
    DAT_10ff6598 = 0;
}

// FUNCTION: 0x10B60F30 ?FUN_10b60f30@Class_10B60F30@@QAEXXZ
void Class_10B60F30::FUN_10b60f30()
{
    Field00 = (void*)&DAT_10e83c48;
    FUN_10b460c0();
}

// FUNCTION: 0x10B60FB0 ?FUN_10b60fb0@@YAXXZ
void FUN_10b60fb0()
{
    FUN_10a529e0();
}

// FUNCTION: 0x10B61020 ?FUN_10b61020@Class_10B61020@@QAEXH@Z
void Class_10B61020::FUN_10b61020(int param)
{
    Field1ec = param;
}

// FUNCTION: 0x10B61C90 ?FUN_10b61c90@Class_10B61C90@@QAEPAXXZ
void* Class_10B61C90::FUN_10b61c90()
{
    return Field1AC;
}

// FUNCTION: 0x10B61D20 ?FUN_10b61d20@@YAXXZ
void FUN_10b61d20()
{
    ((Class_10B61D20*)DAT_10ff659c[0])->FUN_10b61be0();
}

// FUNCTION: 0x10B61EA0 ?FUN_10b61ea0@Class_10B61EA0@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10B61EA0::FUN_10b61ea0()
{
    return Class_109081E0(DAT_10e84284);
}

// FUNCTION: 0x10B64260 ?FUN_10b64260@@YAXXZ
void FUN_10b64260()
{
    FUN_10b74330();
}

// FUNCTION: 0x10B64270 ?FUN_10b64270@@YAXXZ
void FUN_10b64270()
{
    FUN_10b74400();
}

// FUNCTION: 0x10B642B0 ?FUN_10b642b0@@YAXXZ
void FUN_10b642b0()
{
    FUN_10b79770();
}

// FUNCTION: 0x10B64430 ?FUN_10b64430@Class_10B64430@@QAEXH@Z
void Class_10B64430::FUN_10b64430(int param)
{
    Field2fc = param;
}

// FUNCTION: 0x10B65DE0 ?FUN_10b65de0@Class_10B65DE0@@QAEXXZ
void Class_10B65DE0::FUN_10b65de0()
{
    *(void**)this = &DAT_10e68d80;
    Field118 = DAT_10e7edb8;
    FUN_10a58e50();
}

// FUNCTION: 0x10B65E00 ?FUN_10b65e00@Class_10E84978@@QAEPAV1@XZ
Class_10E84978* Class_10E84978::FUN_10b65e00()
{
    FUN_10b75b10();
    Unknown00 = DAT_10e84978;
    Unknown118 = (void*)DAT_10e7edb8;
    Unknown200 = 0;
    return this;
}

// FUNCTION: 0x10B65E50 ?FUN_10b65e50@@YAXXZ
void FUN_10b65e50()
{
    FUN_10b76060();
}

// FUNCTION: 0x10B65E60 ?FUN_10b65e60@@YAXXZ
void FUN_10b65e60()
{
    FUN_10b760b0();
}

// FUNCTION: 0x10B66060 ?FUN_10b66060@Class_10B66060@@QAEXHPAUData_10B66060@@@Z
void Class_10B66060::FUN_10b66060(int A, Data_10B66060* B)
{
    Unknown184 = A;
    Unknown154 = B;
    Unknown158 = B->Unknown178;
}
