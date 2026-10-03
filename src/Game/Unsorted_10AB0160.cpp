// Game/Unsorted_10AB0160.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string>

class Class_10E6D4F0
{
public:
    virtual ~Class_10E6D4F0() = 0;
};

inline Class_10E6D4F0::~Class_10E6D4F0() {}

class Class_10E77978 : public Class_10E6D4F0
{
public:
    virtual ~Class_10E77978();

    std::string Unknown04;
};

inline Class_10E77978::~Class_10E77978() {}

template <class T>
class Owner
{
public:
    ~Owner() { delete P; }

    T* P;
};

class Class_10E6DD68 : public Class_10E77978
{
public:
    Class_10E6DD68();

    int Unknown20;
    Owner<Class_10E77978> Unknown24;
};

// FUNCTION: 0x10AB0180 ??1Class_10E6DD68@@UAE@XZ
Class_10E6DD68::Class_10E6DD68()
{
}
