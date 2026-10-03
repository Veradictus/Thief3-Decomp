// Game/Unsorted_10AA2D30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EName
{
    NAME_None = 0
};

enum EFindName
{
    FNAME_Find = 0,
    FNAME_Add = 1,
    FNAME_Intrinsic = 2
};

class FName
{
public:
    FName(EName N) : Value(N) {}
    FName(const char* Name, EFindName FindType);

    int operator==(const FName& Other) const { return Value == Other.Value; }
    int operator!=(const FName& Other) const { return Value != Other.Value; }

    unsigned long Value;
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

extern const char DAT_10e47660[];

// Ion Storm's string (0x109081E0): a char pointer to a block allocated 4 bytes before it.
class Class_109081E0
{
public:
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            char* Block = Unknown00 - 4;
            FUN_10905aa0()->Virtual5(Block);
            Unknown00 = 0;
        }
    }

    const char* operator*() const { return Unknown00 ? Unknown00 : DAT_10e47660; }

    char* Unknown00;
};

class Class_1096A960
{
public:
    Class_109081E0 FUN_1096a960();
};

class UClass;

class UObject
{
public:
    virtual void Destroy();

    int IsA(UClass* SomeBaseClass) const;
    const FName GetFName() const { return Name; }

    int Index;                  // 0x04
    UObject* HashNext;          // 0x08
    void* StateFrame;           // 0x0C
    void* _Linker;              // 0x10
    int _LinkerIndex;           // 0x14
    UObject* Outer;             // 0x18
    unsigned long ObjectFlags;  // 0x1C
    FName Name;                 // 0x20
    UClass* Class;              // 0x24
    unsigned long PropertyHash; // 0x28
};

class UField : public UObject
{
public:
    UField* SuperField;         // 0x2C
    UField* Next;               // 0x30
};

class UStruct : public UField
{
public:
    char Unknown34[8];          // 0x34
    UField* Children;           // 0x3C
};

class UProperty : public UField
{
};

class UClass : public UStruct
{
private:
    static UClass* PrivateStaticClass;

public:
    static UClass* GetPrivateStaticClassUClass(const char* Package);
    static void InitializePrivateStaticClassUClass();
    static UClass* StaticClass()
    {
        if (!PrivateStaticClass)
        {
            PrivateStaticClass = GetPrivateStaticClassUClass("Core");
            InitializePrivateStaticClassUClass();
        }
        return PrivateStaticClass;
    }
};

// Unreal's TFieldIterator<UProperty>: a struct's properties, then its super structs'.
class Class_10983C30
{
public:
    Class_10983C30(UStruct* InStruct) : Struct(InStruct), Field(InStruct ? InStruct->Children : 0)
    {
        FUN_10983c30();
    }

    operator int() const { return Field != 0; }

    void operator++()
    {
        Field = Field->Next;
        FUN_10983c30();
    }

    UProperty* operator*() { return (UProperty*)Field; }
    UProperty* operator->() { return (UProperty*)Field; }

    void FUN_10983c30();

    UStruct* Struct;
    UField* Field;
};

int FUN_10af36e0(const char* A, const char* B);

// FUNCTION: 0x10AA2E30 ?FUN_10aa2e30@@YAPAVUProperty@@PAVUStruct@@PBD@Z
UProperty* FUN_10aa2e30(UStruct* Struct, const char* Name)
{
    if (Struct->IsA(UClass::StaticClass()))
    {
        FName FieldName(Name, FNAME_Find);
        if (FieldName != NAME_None)
        {
            for (Class_10983C30 It(Struct); It; ++It)
            {
                if (It->GetFName() == FieldName)
                    return *It;
            }
        }
    }
    for (Class_10983C30 It(Struct); It; ++It)
    {
        if (FUN_10af36e0(*((Class_1096A960*)*It)->FUN_1096a960(), Name) == 0)
            return *It;
    }
    return 0;
}
