// Game/Unsorted_10B42300.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B42300
{
    char Unknown00[0x968];
    int Unknown968;
    int Unknown96C;
};

class Class_10B42340
{
public:
    void FUN_10b42300(int A, int B);

    char Unknown00[8];
    int Unknown08;
    char Unknown0C[4];
    Struct_10B42300** Unknown10;
};

// FUNCTION: 0x10B42300 ?FUN_10b42300@Class_10B42340@@QAEXHH@Z
void Class_10B42340::FUN_10b42300(int A, int B)
{
    for (int i = 0; i < Unknown08; i++)
    {
        Struct_10B42300* Entry = Unknown10[i];
        for (int j = Entry->Unknown968; j != Entry->Unknown96C; j++)
        {
            if (j + 1 == 200)
                j = -1;
        }
    }
}
