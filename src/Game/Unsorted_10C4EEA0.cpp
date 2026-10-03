// Game/Unsorted_10C4EEA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// An array of 20-byte elements (count, capacity, data).
class Class_10C4E970
{
public:
    Class_10C4E970() : Unknown00(0), Unknown04(0), Unknown08(0) {}
    ~Class_10C4E970();

    void FUN_10c4e910(const Class_10C4E970* Other);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

struct Item_10C50320
{
    Item_10C50320(const Item_10C50320& Other);

    Class_10C4E970 Unknown00;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

// FUNCTION: 0x10C4F080 ??0Item_10C50320@@QAE@ABU0@@Z
Item_10C50320::Item_10C50320(const Item_10C50320& Other)
    : Unknown0C(Other.Unknown0C), Unknown10(Other.Unknown10), Unknown14(Other.Unknown14)
{
    Unknown00.FUN_10c4e910(&Other.Unknown00);
}
