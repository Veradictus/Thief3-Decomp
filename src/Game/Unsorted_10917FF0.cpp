// Game/Unsorted_10917FF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" int __cdecl sprintf(char* Out, const char* Format, ...);

// What Direct3D 8 reports about an adapter: D3DADAPTER_IDENTIFIER8
// (d3d8types.h packs to 4 bytes, so DriverVersion is two dwords here).
struct D3DADAPTER_IDENTIFIER8
{
    char Driver[512];
    char Description[512];
    unsigned long DriverVersionLowPart;
    long DriverVersionHighPart;
    unsigned long VendorId;
    unsigned long DeviceId;
    unsigned long SubSysId;
    unsigned long Revision;
    unsigned char DeviceIdentifier[16];
    unsigned long WHQLLevel;
};

class IDirect3D8
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
    virtual int __stdcall Virtual3();
    virtual int __stdcall Virtual4();
    virtual int __stdcall GetAdapterIdentifier(unsigned int Adapter, unsigned long Flags, D3DADAPTER_IDENTIFIER8* pIdentifier);
};

extern IDirect3D8* GDirect3D8;

class Config
{
public:
    static Config* Instance();
    bool FUN_10910a20(const char* Section, const char* Key, int* Value, int D);
};

// FUNCTION: 0x10918040 ?FUN_10918040@@YAHI@Z
int FUN_10918040(unsigned int Adapter)
{
    D3DADAPTER_IDENTIFIER8 Identifier;
    char Device[32];
    char Vendor[32];
    int Value;
    GDirect3D8->GetAdapterIdentifier(Adapter, 2, &Identifier);
    sprintf(Vendor, "Vendor_%04x", Identifier.VendorId);
    sprintf(Device, "%04x", Identifier.DeviceId);
    Config* Settings = Config::Instance();
    if (Settings->FUN_10910a20(Vendor, Device, &Value, 0))
        return Value;
    if (!Settings->FUN_10910a20(Vendor, "other", &Value, 0))
        return 1;
    return Value;
}
