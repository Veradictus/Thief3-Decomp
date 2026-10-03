// Game/Unsorted_10AA6200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10a58c70(const Class_10BFBD70& Other);

    Class_10BFBD70& operator=(const Class_10BFBD70& Other)
    {
        Unknown00 = 0;
        FUN_10a58c70(Other);
        return *this;
    }

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

struct Struct_10AA6340
{
    int Unknown00[7];
};

struct Struct_10AA6050
{
    int Unknown00;
    Struct_10AA6340 Unknown04;
    Class_10BFBD70 Unknown20;
};

class Class_10AA6050
{
public:
    Struct_10AA6050* FUN_10aa6050(int Value)
    {
        for (int i = 0; i < Unknown04; i++)
        {
            Struct_10AA6050* Entry = Unknown0C[i];
            if (Entry->Unknown00 == Value)
                return Entry;
        }
        return 0;
    }

    void FUN_10aa6340(int Value, const Struct_10AA6340& A, const Class_10BFBD70& B);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Struct_10AA6050** Unknown0C;
};

// FUNCTION: 0x10AA6340 ?FUN_10aa6340@Class_10AA6050@@QAEXHABUStruct_10AA6340@@ABVClass_10BFBD70@@@Z
void Class_10AA6050::FUN_10aa6340(int Value, const Struct_10AA6340& A, const Class_10BFBD70& B)
{
    Struct_10AA6050* Entry = FUN_10aa6050(Value);
    Entry->Unknown04 = A;
    Entry->Unknown20 = B;
}
