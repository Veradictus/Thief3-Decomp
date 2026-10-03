// Game/Unsorted_109335C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

extern "C" void* memset(void* Dest, int Value, unsigned int Count);

// A stateful allocator: a pool id and the name of the container it serves.
template <class T>
class Allocator_109335C0
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef unsigned int size_type;
    typedef int difference_type;

    template <class U>
    struct rebind
    {
        typedef Allocator_109335C0<U> other;
    };

    Allocator_109335C0(int InPool, const char* InName) : Pool(InPool), Name(InName) {}

    template <class U>
    Allocator_109335C0(const Allocator_109335C0<U>& Other) : Pool(Other.Pool), Name(Other.Name) {}

    pointer allocate(size_type Count, const void* Hint = 0);
    void deallocate(pointer Ptr, size_type Count);
    void construct(pointer Ptr, const T& Value);
    void destroy(pointer Ptr);
    size_type max_size() const;
    pointer address(reference X) const;
    const_pointer address(const_reference X) const;

    int Pool;
    const char* Name;
};

struct Struct_10932ED0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E49D1C
{
public:
    Class_10E49D1C()
    {
        Unknown04 = 0;
        Unknown08 = -1;
        memset(&Unknown10, 0, sizeof(Unknown10));
        Unknown0C = 0;
    }

    virtual ~Class_10E49D1C();

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Struct_10932ED0 Unknown10;
};

class Class_10E49E50 : public Class_10E49D1C
{
public:
    Class_10E49E50();

    virtual ~Class_10E49E50();

    std::vector<void*, Allocator_109335C0<void*> > Unknown1C;
    int Unknown30;
    int Unknown34;
};

// FUNCTION: 0x109335C0 ??0Class_10E49E50@@QAE@XZ
Class_10E49E50::Class_10E49E50()
    : Unknown1C(Allocator_109335C0<void*>(0x1a, "VBPoolStaticImpermanent::m_vecVertexBuffers"))
{
    Unknown30 = 0;
    Unknown34 = 0;
}
