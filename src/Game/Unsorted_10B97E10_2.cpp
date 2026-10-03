// Game/Unsorted_10B97E10_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

struct Struct_10B98E00;

class Class_10E93020
{
public:
    Class_10E93020(int A, int B, bool C, bool D);

    int Unknown00[22];
};

class Class_10E4CCD0
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual Class_10E93020* FUN_10b98050(Struct_10B98E00* A, bool B, bool C);
};

// FUNCTION: 0x10B98050 ?FUN_10b98050@Class_10E4CCD0@@UAEPAVClass_10E93020@@PAUStruct_10B98E00@@_N1@Z
Class_10E93020* Class_10E4CCD0::FUN_10b98050(Struct_10B98E00* A, bool B, bool C)
{
    return new(0, 0, 0, 0, 0) Class_10E93020((int)A, (int)this, B, C);
}
