// Game/GridControllerDestructor.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cString.h"
#include "Game/Class_109B6D50.h"
#include "Game/Struct_10C26A60.h"

extern "C" void* memmove(void* Dest, const void* Source, unsigned Count);

extern void* DAT_10e9925c[];

class cIntArray
{
public:
    ~cIntArray()
    {
        SetCount(0);
        if (CapacityBytes)
        {
            GetAllocator()->Virtual5(Data);
            Data = 0;
            CapacityBytes = 0;
        }
    }
    void SetCount(int NewCount);
    void RemoveAt(int Index)
    {
        if (Index != Count - 1)
        {
            int From = Index + 1;
            int To = Index;
            int Move = Count - Index - 1;
            if (From != To && Move)
                memmove(Data + To, Data + From, Move * sizeof(int));
        }
        SetCount(Count - 1);
    }
    int Count, CapacityBytes;
    int* Data;
};

class Class_10C26E80 { public: void FUN_10c26d60(); };

class Class_10E992D4 { public: void Unregister(); };

struct Struct_10C26890 { int X, Y, Z; };

struct Struct_10C26310 { int X, Y, Z; };

class Class_10E9925C
{
public:
    virtual void Clear();
    virtual bool Virtual1();
    virtual void FUN_10c26210(float A, float B, float C, int OpaqueDeltaBits);
    virtual void FUN_10c26920();
    virtual void FUN_10c267c0(float DeltaTime);
    virtual void FUN_10c26890();
    virtual void AddToRegistry();
    virtual void FUN_10c26770()
    {
        if (Virtual14())
        {
            Class_109B6D50* Object = FUN_10c26490();
            if (Object && Registered == true)
            {
                if (Object->FUN_109b6d50(RegistryId) == true)
                    Object->FUN_109b6d10(RegistryId);
            }
            Registered = false;
        }
    }
    virtual bool Virtual8();
    virtual Struct_10C26890 Virtual9(int X, int Y, int Z) = 0;
    virtual float FUN_10c26200();
    virtual Struct_10C26310 FUN_10c26310();
    virtual Struct_10C26310 FUN_10c26340();
    virtual float FUN_10c26290();
    virtual bool Virtual14();
    ~Class_10E9925C();
    Class_109B6D50* FUN_10c26490();
    char Unknown04[8];
    int RegistryId;
    cString Name;
    char Unknown14[0x20];
    unsigned char Flag34;
    unsigned char Registered;
    cIntArray Items;
};

// FUNCTION: 0x10C26EE0 ??1Class_10E9925C@@QAE@XZ
Class_10E9925C::~Class_10E9925C()
{
    while (Items.Count > 0)
    {
        delete (Struct_10C26A60*)Items.Data[0];
        Items.RemoveAt(0);
    }
    ((Class_10C26E80*)this)->FUN_10c26d60();
    FUN_10c26770();
    ((Class_10E992D4*)this)->Unregister();
}
