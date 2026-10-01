// Game/Unsorted_10AA6390.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA63A0 {
public:
    char Unknown00[0x18];
    int Unknown18;
    void FUN_10aa63a0();
};

class Class_10AA63B0
{
public:
    char Unknown00[0x0c];
    int* Field0C;

    int FUN_10aa63b0();
};

class Class_10E6D8F0
{
public:
    Class_10E6D8F0();

    virtual ~Class_10E6D8F0();

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

typedef struct _iobuf FILE;

extern char DAT_10e6c0f0[];

extern "C" int fprintf(FILE* File, const char* Format, ...);

class Class_10AA71F0
{
public:
    int FUN_10aa71f0(FILE* File, int Param);

    char Unknown00[0x0C];
    int Unknown0C;
    char Unknown10[0x10];
    int Unknown20;
};

class Class_10AA7220 {
public:
    char Unknown00[0x20];
    void* Unknown20;
    void* FUN_10aa7220();
};

struct Class_10AA7230 {
	char unknown_00[0x18];
	void* unknown_18;

	void* FUN_10aa7230();
};

struct Class_10AA7240 {
	char unknown_00[0x24];
	void* unknown_24;

	void* FUN_10aa7240();
};

class Class_10AA7740
{
public:
	int FUN_10aa7740();
};

class Class_10AA7B30
{
public:
	int FUN_10aa7b30();
};

class Class_10AA82C0 {
public:
    char Unknown00[0x8];
    void* Unknown8;
    void* FUN_10aa82c0();
};

struct Class_10AA82D0 {
	char unknown_00[0xc];
	int unknown_0c;

	int FUN_10aa82d0();
};

struct Class_10AA82E0 {
	char unknown_00[0x14];
	int unknown_14;

	int FUN_10aa82e0();
};

struct Class_10AA82F0 {
	char unknown_00[0x1c];
	void* unknown_1c;

	void* FUN_10aa82f0();
};

struct Class_10AA8300 {
	char unknown_00[0x18];
	int unknown_18;

	int FUN_10aa8300();
};

class Class_10AA9D90 {
public:
    char Unknown00[0x28];
    int Unknown28;
    int FUN_10aa9d90();
};

class Class_10AA9DA0 {
public:
    char Unknown00[0x10];
    void* Unknown10;
    void* FUN_10aa9da0();
};

class Class_10AA9DB0
{
public:
    char Unknown00[36];
    int Unknown24;
    void* FUN_10aa9db0();
};

class Class_10AA9DC0
{
public:
    char Unknown00[48];
    int Unknown30;
    void* FUN_10aa9dc0();
};

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10AAA130
{
public:
    Class_1090A780 FUN_10aaa130();

    char Unknown00[0x20];
    Class_1090A780 Unknown20;
};

extern char DAT_10e6d9e0[];

class Class_10AAAA60
{
public:
    int FUN_10aaaa60(FILE* File, int Param);

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Class_10AAAEB0 {
	char unknown_00[0xc];
	void* unknown_0c;

	void* FUN_10aaaeb0();
};

struct Class_10AAB5C0 {
	char unknown_00[0x8];
	int unknown_08;

	int FUN_10aab5c0();
};

struct Class_10AACF40 {
	char unknown_00[0x14];
	unsigned char unknown_14;

	void FUN_10aacf40();
};

class Class_10AAE300 {
public:
    char Unknown00[0x814];
    int Field814;

    void FUN_10aae300(int param);
};

class Class_10AAE310
{
public:
    char Unknown00[0x818];
    int Field818;
    void FUN_10aae310(int param);
};

struct Class_10AAF570 {
	char unknown_00[0x10];
	int unknown_10;

	int FUN_10aaf570();
};

class Member_10AB0140
{
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
    virtual void F5() = 0;
};

class Class_10AB0140
{
public:
    char Unknown00[0x24];
    Member_10AB0140* Field24;
    void FUN_10ab0140();
};

struct Class_10AB37C0 {
	char unknown_00[0x4];
	void* unknown_04;

	void* FUN_10ab37c0();
};

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

class Class_10AB37F0
{
public:
    void FUN_10ab37f0(const Class_109081E0& Value);

    Class_109081E0 Unknown00;
};

void FUN_10ab57c0();

struct Class_10AB5A80 {
	char unknown_00[0x58];
	unsigned char unknown_58;

	unsigned char FUN_10ab5a80();
};

struct Class_10AB5A90 {
	char unknown_00[0x58];
	unsigned char unknown_58;

	void FUN_10ab5a90();
};

class Class_10AB5AA0
{
public:
    char Unknown00[89];
    unsigned char Unknown59;
    unsigned char FUN_10ab5aa0();
};

// FUNCTION: 0x10AA63A0 ?FUN_10aa63a0@Class_10AA63A0@@QAEXXZ
void Class_10AA63A0::FUN_10aa63a0()
{
    Unknown18 = 0;
}

// FUNCTION: 0x10AA63B0 ?FUN_10aa63b0@Class_10AA63B0@@QAEHXZ
int Class_10AA63B0::FUN_10aa63b0()
{
    return *Field0C;
}

// FUNCTION: 0x10AA6860 ??0Class_10E6D8F0@@QAE@XZ
Class_10E6D8F0::Class_10E6D8F0()
{
    Unknown04 = 0x7fffffff;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
}

// FUNCTION: 0x10AA69E0 ??_GClass_10E6D8F0@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10AA6860's definition in this unit.

// FUNCTION: 0x10AA71F0 ?FUN_10aa71f0@Class_10AA71F0@@QAEHPAU_iobuf@@H@Z
int Class_10AA71F0::FUN_10aa71f0(FILE* File, int Param)
{
    fprintf(File, DAT_10e6c0f0, Unknown0C, Unknown20);
    return 1;
}

// FUNCTION: 0x10AA7220 ?FUN_10aa7220@Class_10AA7220@@QAEPAXXZ
void* Class_10AA7220::FUN_10aa7220()
{
    return &Unknown20;
}

// FUNCTION: 0x10AA7230 ?FUN_10aa7230@Class_10AA7230@@QAEPAXXZ
void* Class_10AA7230::FUN_10aa7230() {
	return &unknown_18;
}

// FUNCTION: 0x10AA7240 ?FUN_10aa7240@Class_10AA7240@@QAEPAXXZ
void* Class_10AA7240::FUN_10aa7240() {
	return &unknown_24;
}

// FUNCTION: 0x10AA7740 ?FUN_10aa7740@Class_10AA7740@@QAEHXZ
int Class_10AA7740::FUN_10aa7740()
{
	return 0xa;
}

// FUNCTION: 0x10AA7B30 ?FUN_10aa7b30@Class_10AA7B30@@QAEHXZ
int Class_10AA7B30::FUN_10aa7b30()
{
	return 0x9;
}

// FUNCTION: 0x10AA7F70 ?FUN_10aa7f70@@YGHHH@Z
int __stdcall FUN_10aa7f70(int p1, int p2)
{
    return 1;
}

// FUNCTION: 0x10AA8050 ?FUN_10aa8050@@YAHXZ
int FUN_10aa8050()
{
    return 4;
}

// FUNCTION: 0x10AA82B0 ?FUN_10aa82b0@@YAHXZ
int FUN_10aa82b0()
{
    return 0xb;
}

// FUNCTION: 0x10AA82C0 ?FUN_10aa82c0@Class_10AA82C0@@QAEPAXXZ
void* Class_10AA82C0::FUN_10aa82c0()
{
    return &Unknown8;
}

// FUNCTION: 0x10AA82D0 ?FUN_10aa82d0@Class_10AA82D0@@QAEHXZ
int Class_10AA82D0::FUN_10aa82d0() {
	return unknown_0c;
}

// FUNCTION: 0x10AA82E0 ?FUN_10aa82e0@Class_10AA82E0@@QAEHXZ
int Class_10AA82E0::FUN_10aa82e0() {
	return unknown_14;
}

// FUNCTION: 0x10AA82F0 ?FUN_10aa82f0@Class_10AA82F0@@QAEPAXXZ
void* Class_10AA82F0::FUN_10aa82f0() {
	return &unknown_1c;
}

// FUNCTION: 0x10AA8300 ?FUN_10aa8300@Class_10AA8300@@QAEHXZ
int Class_10AA8300::FUN_10aa8300() {
	return unknown_18;
}

// FUNCTION: 0x10AA9440 ?FUN_10aa9440@@YAHXZ
int FUN_10aa9440()
{
    return 5;
}

// FUNCTION: 0x10AA9D80 ?FUN_10aa9d80@@YAHXZ
int FUN_10aa9d80()
{
    return 0xd;
}

// FUNCTION: 0x10AA9D90 ?FUN_10aa9d90@Class_10AA9D90@@QAEHXZ
int Class_10AA9D90::FUN_10aa9d90()
{
    return Unknown28;
}

// FUNCTION: 0x10AA9DA0 ?FUN_10aa9da0@Class_10AA9DA0@@QAEPAXXZ
void* Class_10AA9DA0::FUN_10aa9da0()
{
    return &Unknown10;
}

// FUNCTION: 0x10AA9DB0 ?FUN_10aa9db0@Class_10AA9DB0@@QAEPAXXZ
void* Class_10AA9DB0::FUN_10aa9db0()
{
    return (void*)Unknown24;
}

// FUNCTION: 0x10AA9DC0 ?FUN_10aa9dc0@Class_10AA9DC0@@QAEPAXXZ
void* Class_10AA9DC0::FUN_10aa9dc0()
{
    return (void*)Unknown30;
}

// FUNCTION: 0x10AAA130 ?FUN_10aaa130@Class_10AAA130@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10AAA130::FUN_10aaa130()
{
    return Class_1090A780(Unknown20);
}

// FUNCTION: 0x10AAAA10 ?FUN_10aaaa10@@YAHXZ
int FUN_10aaaa10()
{
    return 0xc;
}

// FUNCTION: 0x10AAAA60 ?FUN_10aaaa60@Class_10AAAA60@@QAEHPAU_iobuf@@H@Z
int Class_10AAAA60::FUN_10aaaa60(FILE* File, int Param)
{
    fprintf(File, DAT_10e6c0f0, DAT_10e6d9e0, Unknown08);
    return 1;
}

// FUNCTION: 0x10AAAEA0 ?FUN_10aaaea0@@YAHXZ
int FUN_10aaaea0()
{
    return 0xe;
}

// FUNCTION: 0x10AAAEB0 ?FUN_10aaaeb0@Class_10AAAEB0@@QAEPAXXZ
void* Class_10AAAEB0::FUN_10aaaeb0() {
	return &unknown_0c;
}

// FUNCTION: 0x10AAB5C0 ?FUN_10aab5c0@Class_10AAB5C0@@QAEHXZ
int Class_10AAB5C0::FUN_10aab5c0() {
	return unknown_08;
}

// FUNCTION: 0x10AACF40 ?FUN_10aacf40@Class_10AACF40@@QAEXXZ
void Class_10AACF40::FUN_10aacf40() {
	unknown_14 = 0x0;
}

// FUNCTION: 0x10AAE300 ?FUN_10aae300@Class_10AAE300@@QAEXH@Z
void Class_10AAE300::FUN_10aae300(int param)
{
    Field814 = param;
}

// FUNCTION: 0x10AAE310 ?FUN_10aae310@Class_10AAE310@@QAEXH@Z
void Class_10AAE310::FUN_10aae310(int param)
{
    Field818 = param;
}

// FUNCTION: 0x10AAF570 ?FUN_10aaf570@Class_10AAF570@@QAEHXZ
int Class_10AAF570::FUN_10aaf570() {
	return unknown_10;
}

// FUNCTION: 0x10AB0140 ?FUN_10ab0140@Class_10AB0140@@QAEXXZ
void Class_10AB0140::FUN_10ab0140()
{
    Field24->F5();
}

// FUNCTION: 0x10AB37C0 ?FUN_10ab37c0@Class_10AB37C0@@QAEPAXXZ
void* Class_10AB37C0::FUN_10ab37c0() {
	return &unknown_04;
}

// FUNCTION: 0x10AB37F0 ?FUN_10ab37f0@Class_10AB37F0@@QAEXABVClass_109081E0@@@Z
void Class_10AB37F0::FUN_10ab37f0(const Class_109081E0& Value)
{
    Unknown00 = Value;
}

// FUNCTION: 0x10AB5820 ?FUN_10ab5820@@YAXXZ
void FUN_10ab5820()
{
    FUN_10ab57c0();
}

// FUNCTION: 0x10AB5A80 ?FUN_10ab5a80@Class_10AB5A80@@QAEEXZ
unsigned char Class_10AB5A80::FUN_10ab5a80() {
	return unknown_58;
}

// FUNCTION: 0x10AB5A90 ?FUN_10ab5a90@Class_10AB5A90@@QAEXXZ
void Class_10AB5A90::FUN_10ab5a90() {
	unknown_58 = 0x0;
}

// FUNCTION: 0x10AB5AA0 ?FUN_10ab5aa0@Class_10AB5AA0@@QAEEXZ
unsigned char Class_10AB5AA0::FUN_10ab5aa0()
{
    return Unknown59;
}
