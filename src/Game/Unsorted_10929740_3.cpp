// Game/Unsorted_10929740_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10e49684;

struct Struct_10929510
{
    int Pitch;
    unsigned char* Bits;
};

struct Struct_10929D60
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

// A 32-bit pixel format: slot 0 reads a pixel, slot 1 writes one (0x10929510, 0x10929530).
class Class_10E49AE0
{
public:
    virtual void FUN_10929510(Struct_10929510* p1, int p2, int p3, unsigned long* p4);
    virtual void FUN_10929530(Struct_10929510* p1, int p2, int p3, int p4);
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_109299d0(Struct_10929510* Surface, int X, int Y, Struct_10929D60* Out);
};

// FUNCTION: 0x109299D0 ?FUN_109299d0@Class_10E49AE0@@UAEXPAUStruct_10929510@@HHPAUStruct_10929D60@@@Z
void Class_10E49AE0::FUN_109299d0(Struct_10929510* Surface, int X, int Y, Struct_10929D60* Out)
{
    unsigned long Pixel;
    FUN_10929510(Surface, X, Y, &Pixel);
    Out->Unknown00 = ((Pixel >> 16) & 0xff) * (2.0f / 255.0f) - DAT_10e49684;
    Out->Unknown04 = ((Pixel >> 8) & 0xff) * (2.0f / 255.0f) - DAT_10e49684;
    Out->Unknown08 = (Pixel & 0xff) * (2.0f / 255.0f) - DAT_10e49684;
}
