// Game/Unsorted_10BB8290.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A2C2F0
{
public:
    int FUN_10a2c2f0(void* A, void* B);
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

Class_10A2C2F0* FUN_10a2c6b0();

class Class_10BB8330
{
public:
    bool FUN_10bb8330();

    char Unknown00[8];
    Class_10c7d570* Unknown08;
    char Unknown0C[0x278];
    int Unknown284;
};

class Class_10BB84F0 {
public:
    void FUN_10bb84f0(int p1, int p2);

    char Unknown00[0x2DC];
    int Unknown2DC;
    int Unknown2E0;
};

class Class_10BB8510 {
public:
    int FUN_10bb8510(int* Out);

    char Unknown00[0x2DC];
    int Unknown2DC;
    int Unknown2E0;
};

class Class_10bb8530
{
public:
    char Unknown00[0x2e4];
    float Unknown2e4;
    void FUN_10bb8530(float p1);
};

class Class_10bb8540
{
public:
    char Unknown00[0x2e4];
    float Unknown2e4;
    float FUN_10bb8540();
};

class Class_10bb8550
{
public:
    char Unknown00[0x2e8];
    float Unknown2e8;
    float FUN_10bb8550();
};

// FUNCTION: 0x10BB8330 ?FUN_10bb8330@Class_10BB8330@@QAE_NXZ
bool Class_10BB8330::FUN_10bb8330()
{
    Class_10c7d570* Item = Unknown08;
    return FUN_10a2c6b0()->FUN_10a2c2f0(Item->FUN_10c7d570(), &Unknown284) != 0;
}

// FUNCTION: 0x10BB84F0 ?FUN_10bb84f0@Class_10BB84F0@@QAEXHH@Z
void Class_10BB84F0::FUN_10bb84f0(int p1, int p2)
{
    Unknown2DC = p1;
    Unknown2E0 = p2;
}

// FUNCTION: 0x10BB8510 ?FUN_10bb8510@Class_10BB8510@@QAEHPAH@Z
int Class_10BB8510::FUN_10bb8510(int* Out)
{
    *Out = Unknown2E0;
    return Unknown2DC;
}

// FUNCTION: 0x10BB8530 ?FUN_10bb8530@Class_10bb8530@@QAEXM@Z
void Class_10bb8530::FUN_10bb8530(float p1)
{
    Unknown2e4 = p1;
}

// FUNCTION: 0x10BB8540 ?FUN_10bb8540@Class_10bb8540@@QAEMXZ
float Class_10bb8540::FUN_10bb8540()
{
    return Unknown2e4;
}

// FUNCTION: 0x10BB8550 ?FUN_10bb8550@Class_10bb8550@@QAEMXZ
float Class_10bb8550::FUN_10bb8550()
{
    return Unknown2e8;
}
