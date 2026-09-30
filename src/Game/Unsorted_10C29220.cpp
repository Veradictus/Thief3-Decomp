// Game/Unsorted_10C29220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e993c0[];

class Class_10E993C0
{
public:
    Class_10E993C0(int A);

    void** Unknown00;        // +0x00: DAT_10e993c0
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

class Class_10E99370
{
public:
    Class_10E99370(int A, int B);

    virtual void FUN_10c28260();

    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10E993C4 : public Class_10E99370
{
public:
    Class_10E993C4(int A, int B);

    virtual void FUN_10c28260();
};

void FUN_10c28280();

extern void* DAT_10e9aa7c[];

void FUN_10c27290();

class Class_10C2EB30
{
public:
    void* Field00;
    void FUN_10c2eb30();
};

extern const char DAT_10e9aaa8[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10C2EBD0
{
public:
    Class_109081E0 FUN_10c2ebd0();
};

class Class_10C2ECF0
{
public:
    char Unknown00[0x160];
    unsigned char Field160;
    unsigned char FUN_10c2ecf0();
};

class Class_10C2EE10
{
public:
    char Unknown00[0x114];
    unsigned char Field114;
    unsigned char FUN_10c2ee10();
};

class Class_10C2EEB0 {
public:
    char Unknown00[0x10c];
    unsigned char Field10c;
    unsigned char FUN_10c2eeb0();
};

class Class_10C2F530 {
public:
    char Unknown00[0xcc];
    void* Fieldcc;
    void* FUN_10c2f530();
};

class Class_10C2F570
{
public:
    bool FUN_10c2f570(int Key, int* Out);

    char Unknown00[0x150];
    int Unknown150;
    int Unknown154;
};

class Class_10C2F5C0 {
public:
    char Unknown00[0x9d];
    unsigned char Field9d;
    void FUN_10c2f5c0();
};

struct Info_10C2F870
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C2F870
{
public:
    void FUN_10c2f870(const Info_10C2F870* In);

    char Unknown00[0x74];
    Info_10C2F870 Unknown74;
    char Unknown80[0x1F];
    char Unknown9F;
};

class Class_10C2F960 {
public:
    char Unknown00[0x12c];
    unsigned char Field12c;
    void FUN_10c2f960();
};

class Class_10C35650
{
public:
    char Unknown00[0x60];
    float Field60;

    virtual float FUN_10c35650();
};

struct Struct_10C35670
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C35670
{
public:
    void FUN_10c35670(Struct_10C35670* Value);

    char Unknown00[0x68];
    Struct_10C35670 Unknown68;
    char Unknown74[0x27];
    bool Unknown9B;
};

class Class_10C356A0
{
public:
    char Unknown00[0x9f];
    unsigned char Field9f;
    void FUN_10c356a0();
};

extern const char DAT_10e9adc8[];

class Class_10C36860
{
public:
    Class_109081E0 FUN_10c36860();
};

void FUN_10c36a20();

extern const char DAT_10e9ae18[];

class Class_10C374E0
{
public:
    Class_109081E0 FUN_10c374e0();
};

extern const char DAT_10e9ae54[];

class Class_10C378A0
{
public:
    Class_109081E0 FUN_10c378a0();
};

void FUN_10c372e0();

extern const char DAT_10e9aeb8[];

class Class_10C38040
{
public:
    Class_109081E0 FUN_10c38040();
};

extern const char DAT_10e9aef4[];

class Class_10C382B0
{
public:
    Class_109081E0 FUN_10c382b0();
};

extern const char DAT_10e9af34[];

class Class_10C38430
{
public:
    Class_109081E0 FUN_10c38430();
};

extern void* DAT_10e9aad0[];

class Class_10C384F0
{
public:
    void* Field00;
    void FUN_10c384f0();
};

class Class_10B26930
{
public:
    void FUN_10b26930(int Value);

    int Unknown00;
    int Unknown04;
};

class Class_10C38610
{
public:
    void FUN_10c38610();

    char Unknown00[0xBC];
    Class_10B26930 Unknown0BC;
    int Unknown0C4;
    char Unknown0C8[0x34];
    int Unknown0FC;
};

// FUNCTION: 0x10C296B0 ??0Class_10E993C0@@QAE@H@Z
Class_10E993C0::Class_10E993C0(int A)
{
    Unknown04 = A;
    Unknown00 = DAT_10e993c0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
}

// FUNCTION: 0x10C29EC0 ??0Class_10E993C4@@QAE@HH@Z
Class_10E993C4::Class_10E993C4(int A, int B) : Class_10E99370(A, B)
{
}

// FUNCTION: 0x10C29EE0 ?FUN_10c29ee0@@YAXXZ
void FUN_10c29ee0()
{
    FUN_10c28280();
}

// FUNCTION: 0x10C2EB30 ?FUN_10c2eb30@Class_10C2EB30@@QAEXXZ
void Class_10C2EB30::FUN_10c2eb30()
{
    Field00 = (void*)DAT_10e9aa7c;
    FUN_10c27290();
}

// FUNCTION: 0x10C2EBD0 ?FUN_10c2ebd0@Class_10C2EBD0@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10C2EBD0::FUN_10c2ebd0()
{
    return Class_109081E0(DAT_10e9aaa8);
}

// FUNCTION: 0x10C2ECF0 ?FUN_10c2ecf0@Class_10C2ECF0@@QAEEXZ
unsigned char Class_10C2ECF0::FUN_10c2ecf0()
{
    return Field160;
}

// FUNCTION: 0x10C2EE10 ?FUN_10c2ee10@Class_10C2EE10@@QAEEXZ
unsigned char Class_10C2EE10::FUN_10c2ee10()
{
    return Field114;
}

// FUNCTION: 0x10C2EEB0 ?FUN_10c2eeb0@Class_10C2EEB0@@QAEEXZ
unsigned char Class_10C2EEB0::FUN_10c2eeb0()
{
    return Field10c;
}

// FUNCTION: 0x10C2F530 ?FUN_10c2f530@Class_10C2F530@@QAEPAXXZ
void* Class_10C2F530::FUN_10c2f530()
{
    return Fieldcc;
}

// FUNCTION: 0x10C2F570 ?FUN_10c2f570@Class_10C2F570@@QAE_NHPAH@Z
bool Class_10C2F570::FUN_10c2f570(int Key, int* Out)
{
    if (Key == Unknown150) {
        *Out = Unknown154;
        return true;
    }
    return false;
}

// FUNCTION: 0x10C2F5C0 ?FUN_10c2f5c0@Class_10C2F5C0@@QAEXXZ
void Class_10C2F5C0::FUN_10c2f5c0()
{
    Field9d = 1;
}

// FUNCTION: 0x10C2F870 ?FUN_10c2f870@Class_10C2F870@@QAEXPBUInfo_10C2F870@@@Z
void Class_10C2F870::FUN_10c2f870(const Info_10C2F870* In)
{
    Unknown9F = 1;
    Unknown74 = *In;
}

// FUNCTION: 0x10C2F960 ?FUN_10c2f960@Class_10C2F960@@QAEXXZ
void Class_10C2F960::FUN_10c2f960()
{
    Field12c = 1;
}

// FUNCTION: 0x10C35650 ?FUN_10c35650@Class_10C35650@@UAEMXZ
float Class_10C35650::FUN_10c35650()
{
    return Field60;
}

// FUNCTION: 0x10C35670 ?FUN_10c35670@Class_10C35670@@QAEXPAUStruct_10C35670@@@Z
void Class_10C35670::FUN_10c35670(Struct_10C35670* Value)
{
    Unknown68 = *Value;
    Unknown9B = true;
}

// FUNCTION: 0x10C356A0 ?FUN_10c356a0@Class_10C356A0@@QAEXXZ
void Class_10C356A0::FUN_10c356a0()
{
    Field9f = 0;
}

// FUNCTION: 0x10C36860 ?FUN_10c36860@Class_10C36860@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10C36860::FUN_10c36860()
{
    return Class_109081E0(DAT_10e9adc8);
}

// FUNCTION: 0x10C36F30 ?FUN_10c36f30@@YAXXZ
void FUN_10c36f30()
{
    FUN_10c36a20();
}

// FUNCTION: 0x10C374E0 ?FUN_10c374e0@Class_10C374E0@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10C374E0::FUN_10c374e0()
{
    return Class_109081E0(DAT_10e9ae18);
}

// FUNCTION: 0x10C378A0 ?FUN_10c378a0@Class_10C378A0@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10C378A0::FUN_10c378a0()
{
    return Class_109081E0(DAT_10e9ae54);
}

// FUNCTION: 0x10C37E80 ?FUN_10c37e80@@YAXXZ
void FUN_10c37e80()
{
    FUN_10c372e0();
}

// FUNCTION: 0x10C38040 ?FUN_10c38040@Class_10C38040@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10C38040::FUN_10c38040()
{
    return Class_109081E0(DAT_10e9aeb8);
}

// FUNCTION: 0x10C382B0 ?FUN_10c382b0@Class_10C382B0@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10C382B0::FUN_10c382b0()
{
    return Class_109081E0(DAT_10e9aef4);
}

// FUNCTION: 0x10C382E0 ?FUN_10c382e0@@YAHXZ
int FUN_10c382e0()
{
    return 0x3;
}

// FUNCTION: 0x10C38430 ?FUN_10c38430@Class_10C38430@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10C38430::FUN_10c38430()
{
    return Class_109081E0(DAT_10e9af34);
}

// FUNCTION: 0x10C384F0 ?FUN_10c384f0@Class_10C384F0@@QAEXXZ
void Class_10C384F0::FUN_10c384f0()
{
    Field00 = (void*)DAT_10e9aad0;
}

// FUNCTION: 0x10C38610 ?FUN_10c38610@Class_10C38610@@QAEXXZ
void Class_10C38610::FUN_10c38610()
{
    Unknown0BC.FUN_10b26930(0);
    Unknown0C4 = 0;
    Unknown0FC = 0;
}
