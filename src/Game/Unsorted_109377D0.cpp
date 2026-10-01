// Game/Unsorted_109377D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1091E3E0
{
public:
    void* FUN_1091e3e0();
};

class Class_1091E3F0 : public Class_1091E3E0
{
public:
    void* FUN_1091e3f0();
};

class Class_10937790
{
public:
    void FUN_10937430(void* A, void* B, void* C);
    void FUN_10938ee0(Class_1091E3F0* Obj);

    char Unknown00[0x6FC];
    int Unknown6FC;
};

// FUNCTION: 0x10938EE0 ?FUN_10938ee0@Class_10937790@@QAEXPAVClass_1091E3F0@@@Z
void Class_10937790::FUN_10938ee0(Class_1091E3F0* Obj)
{
    FUN_10937430(Obj->FUN_1091e3e0(), Obj->FUN_1091e3f0(), &Unknown6FC);
}
