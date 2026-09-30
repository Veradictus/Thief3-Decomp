// Game/Unsorted_10B61ED0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e47660[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();
    Class_109081E0& FUN_1090a590(const char* In);

    char* Unknown00;
};

class Class_10B61F80
{
public:
    void FUN_10b61f80();

    char Unknown00[0x168];
    Class_109081E0 Unknown168;
};

// FUNCTION: 0x10B61F80 ?FUN_10b61f80@Class_10B61F80@@QAEXXZ
void Class_10B61F80::FUN_10b61f80()
{
    Unknown168.FUN_1090a590(DAT_10e47660);
}
