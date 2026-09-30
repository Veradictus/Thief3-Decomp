// Game/Unsorted_10C5F370.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C5F410_Member {
public:
    char Unknown00[0x30];
    int Field30;
    int Field34;
};

class Class_10C5F410 {
public:
    Class_10C5F410_Member* Field00;
    void FUN_10c5f410(int p1, int p2);
};

extern unsigned char DAT_10ff7111;

extern unsigned char DAT_10ff7112;

extern unsigned char DAT_10ff7113;

extern int DAT_10f06a6c;

extern unsigned char DAT_10ff7114;

// FUNCTION: 0x10C5F410 ?FUN_10c5f410@Class_10C5F410@@QAEXHH@Z
void Class_10C5F410::FUN_10c5f410(int p1, int p2)
{
    Field00->Field30 = p1;
    Field00->Field34 = p2;
}

// FUNCTION: 0x10C5F430 ?FUN_10c5f430@@YAXEEE@Z
void FUN_10c5f430(unsigned char p1, unsigned char p2, unsigned char p3)
{
    DAT_10ff7111 = p1;
    DAT_10ff7112 = p2;
    DAT_10ff7113 = p3;
}

// FUNCTION: 0x10C5F450 ?FUN_10c5f450@@YAXH@Z
void FUN_10c5f450(int p1)
{
    DAT_10f06a6c = p1;
}

// FUNCTION: 0x10C5F460 ?FUN_10c5f460@@YAXE@Z
void FUN_10c5f460(unsigned char param)
{
    DAT_10ff7114 = param;
}
