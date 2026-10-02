// Game/Unsorted_10B97C40_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

class Class_10BBDB40
{
public:
    float FUN_10bbdb40();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int Id);
};

struct Struct_10B98E00
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

void* FUN_10be1c60();

extern float DAT_10eafbdc;

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

// 0x4c bytes; its constructor (0x10BE1B70) stores the vtable 0x10E95898.
class Class_10E95898 : public Class_10E90D70
{
public:
    Class_10E95898(int A, int B, int C, bool D);

    float Unknown40;
    int Unknown44;
    bool Unknown48;
    bool Unknown49;
};

class Class_10E95288;

class Class_10E4CCD0
{
public:
    virtual void Virtual0();
    virtual Class_10E95288* FUN_10b98e00(Struct_10B98E00* A);
    virtual void Virtual2();
    virtual Class_10E95898* FUN_10b98f60(Struct_10B98E00* A, int B, bool C);
};

// FUNCTION: 0x10B98F60 ?FUN_10b98f60@Class_10E4CCD0@@UAEPAVClass_10E95898@@PAUStruct_10B98E00@@H_N@Z
Class_10E95898* Class_10E4CCD0::FUN_10b98f60(Struct_10B98E00* A, int B, bool C)
{
    void* Id = FUN_10be1c60();
    if (Id && A->Unknown08->FUN_10dbd510((int)Id)->FUN_10bbdb40() > DAT_10eafbdc)
        return new(0, 0, 0, 0, 0) Class_10E95898((int)A, (int)this, B, C);
    return 0;
}
