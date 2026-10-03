// Game/Unsorted_10AB0560.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string>

class Class_10E6D4F0
{
public:
    virtual ~Class_10E6D4F0() = 0;
};

inline Class_10E6D4F0::~Class_10E6D4F0() {}

// A string holder: FUN_10aaf830 stores this vtable and copies its argument to +0x04.
class Class_10E77978 : public Class_10E6D4F0
{
public:
    Class_10E77978(std::string A);
    virtual ~Class_10E77978();

    std::string Unknown04;
};

// The object FUN_10ab04a0 constructs: a Class_10E77978 whose own vtable folded into its base's.
class Class_10AB04A0 : public Class_10E77978
{
public:
    Class_10AB04A0(std::string A);
};

class Class_10E6DDB4 : public Class_10E77978
{
public:
    Class_10E6DDB4(std::string A, int B);
    virtual ~Class_10E6DDB4();

    int Unknown20;
    Class_10AB04A0* Unknown24;
};

// FUNCTION: 0x10AB0570 ??0Class_10E6DDB4@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
Class_10E6DDB4::Class_10E6DDB4(std::string A, int B) : Class_10E77978(A), Unknown20(B)
{
    Unknown24 = new Class_10AB04A0(A);
}
