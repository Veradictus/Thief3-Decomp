// Core/Core.h: the engine core's types, as far as matched functions need them.
// Layouts are from docs/engine.md ("Names", "Objects"); what nothing has
// shown yet is left out or named by offset.
#ifndef T3_CORE_CORE_H
#define T3_CORE_CORE_H

// --- Basic types (Unreal's names) ---------------------------------------------------

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned long DWORD;
typedef signed char SBYTE;
typedef signed short SWORD;
typedef signed int INT;
typedef INT UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef char ANSICHAR;
typedef DWORD BITFIELD;                 // a script bool: one bit of a 32-bit word

#ifndef NULL
#define NULL 0
#endif

// A compile-time check of a class's size against the size the game registers
// for it (the generated <Package>Classes.h headers use it).
#define T3_CHECK_SIZE(T, Size) typedef char T3_SizeCheck_##T[sizeof(T) == (Size) ? 1 : -1]

class FFrame;
class UObject;
class UField;
class UStruct;
class UFunction;
class UProperty;
class UState;
class UClass;

// --- Names --------------------------------------------------------------------------

enum EName
{
    NAME_None = 0,
};

// One 32-bit value: the low 16 bits index FName::Names, the high 16 bits are
// an instance number (not stock Unreal Engine 2, where it is a plain index).
class FName
{
public:
    FName() {}
    FName(EName N) : Value(N) {}

    UBOOL operator==(const FName& Other) const { return Value == Other.Value; }
    UBOOL operator!=(const FName& Other) const { return Value != Other.Value; }

    DWORD Value;
};

// --- Strings and math ---------------------------------------------------------------

// A dynamic array's header; the elements live at Data.
class FArray
{
public:
    INT Num() const { return ArrayNum; }

    void* Data;
    INT ArrayNum;
    INT ArrayMax;
};

// A typed dynamic array; element access is inline, as in stock Unreal Engine 2.
template <class T> class TArray : public FArray
{
public:
    T& operator()(INT i) { return ((T*)Data)[i]; }
};

// A string: its characters and terminator in an array (TArray<ANSICHAR> in
// stock Unreal Engine 2), with these members out of line in this build.
class FString : public FArray
{
public:
    FString();                                                // 0x10AF8230
    FString(const FString& Other);                            // 0x10AF8250
    FString(const ANSICHAR* In);                              // 0x10AF82B0
    ~FString();                                               // 0x10AF83B0

    FString& operator=(const ANSICHAR* Other);                // 0x10AF81C0
    FString& operator=(const FString& Other);                 // 0x10AF8340
    FString& operator+=(const ANSICHAR* Str);                 // 0x10AF8420
    FString& operator+=(const FString& Str);                  // 0x10AF8490
    INT InStr(const ANSICHAR* SubStr, UBOOL Right = 0) const; // 0x10AF80F0
    INT InStr(const FString& SubStr, UBOOL Right = 0) const;  // 0x10AF8190

    INT Len() const;                                          // 0x10AF7F70
};

class FVector
{
public:
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}

    FVector operator+(const FVector& V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator+=(const FVector& V)
    {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        return *this;
    }

    UBOOL Normalize();

    FLOAT X, Y, Z;
};

// Unreal angles: 65536 units per turn.
class FRotator
{
public:
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}

    FRotator operator+(const FRotator& R) const { return FRotator(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll); }

    INT Pitch, Yaw, Roll;
};

// --- Output devices -----------------------------------------------------------------

// GLog's vtable[0] is FOutputDeviceFile::Serialize(const char*, EName).
class FOutputDevice
{
public:
    virtual void Serialize(const ANSICHAR* V, EName Event) = 0;

    void Logf(EName Event, const ANSICHAR* Fmt, ...);  // 0x10AF5230
};

// --- Objects ------------------------------------------------------------------------

#define DECLARE_FUNCTION(func) void func(FFrame& Stack, RESULT_DECL);
#define RESULT_DECL void* const Result

// The first 0x28 bytes match stock Unreal Engine 2 (the SDK checks Name, Class
// and Outer at runtime); the game registers UObject with 0x2C. Of the virtual
// functions, only CallFunction's slot is known; the others are named by their
// vtable offset.
class UObject
{
public:
    virtual ~UObject();
    virtual void Unknown04();
    virtual void Unknown08();
    virtual void Unknown0C();
    virtual void Unknown10();
    virtual void Unknown14();
    virtual void Unknown18();
    virtual void Unknown1C();
    virtual void Unknown20();
    virtual void Unknown24();
    virtual void Unknown28();
    virtual void Unknown2C();
    virtual void Unknown30();
    virtual void Unknown34();
    virtual void Unknown38();
    virtual void Unknown3C();
    virtual void Unknown40();

    // Runs a script function (execFinalFunction and the other calls).
    virtual void CallFunction(FFrame& Stack, RESULT_DECL, UFunction* Function);

    UClass* GetClass() const { return Class; }
    const FName GetFName() const { return Name; }

    // Writes the object's config properties (execSaveConfig); resets a
    // class's (execResetConfig).
    void SaveConfig(DWORD Flags, const ANSICHAR* Filename);
    static void ResetConfig(UClass* Class);

    // Script natives, named by the game's native table (docs/engine.md,
    // "Script natives").
    DECLARE_FUNCTION(execAbs)
    DECLARE_FUNCTION(execAddAdd_Byte)
    DECLARE_FUNCTION(execAddAdd_Int)
    DECLARE_FUNCTION(execAddAdd_PreByte)
    DECLARE_FUNCTION(execAddAdd_PreInt)
    DECLARE_FUNCTION(execAddEqual_ByteByte)
    DECLARE_FUNCTION(execAddEqual_FloatFloat)
    DECLARE_FUNCTION(execAddEqual_IntInt)
    DECLARE_FUNCTION(execAddEqual_RotatorRotator)
    DECLARE_FUNCTION(execAddEqual_VectorVector)
    DECLARE_FUNCTION(execAdd_FloatFloat)
    DECLARE_FUNCTION(execAdd_IntInt)
    DECLARE_FUNCTION(execAdd_RotatorRotator)
    DECLARE_FUNCTION(execAdd_VectorVector)
    DECLARE_FUNCTION(execAndAnd_BoolBool)
    DECLARE_FUNCTION(execAnd_IntInt)
    DECLARE_FUNCTION(execArrayElement)
    DECLARE_FUNCTION(execAsc)
    DECLARE_FUNCTION(execAssert)
    DECLARE_FUNCTION(execAt_StringString)
    DECLARE_FUNCTION(execAtan)
    DECLARE_FUNCTION(execBoolToByte)
    DECLARE_FUNCTION(execBoolToFloat)
    DECLARE_FUNCTION(execBoolToInt)
    DECLARE_FUNCTION(execBoolToString)
    DECLARE_FUNCTION(execBoolVariable)
    DECLARE_FUNCTION(execByteConst)
    DECLARE_FUNCTION(execByteToBool)
    DECLARE_FUNCTION(execByteToFloat)
    DECLARE_FUNCTION(execByteToInt)
    DECLARE_FUNCTION(execByteToString)
    DECLARE_FUNCTION(execCaps)
    DECLARE_FUNCTION(execCase)
    DECLARE_FUNCTION(execChr)
    DECLARE_FUNCTION(execClamp)
    DECLARE_FUNCTION(execClassContext)
    DECLARE_FUNCTION(execClassIsChildOf)
    DECLARE_FUNCTION(execComplementEqual_FloatFloat)
    DECLARE_FUNCTION(execComplementEqual_StringString)
    DECLARE_FUNCTION(execComplement_PreInt)
    DECLARE_FUNCTION(execConcat_StringString)
    DECLARE_FUNCTION(execContext)
    DECLARE_FUNCTION(execCos)
    DECLARE_FUNCTION(execCross_VectorVector)
    DECLARE_FUNCTION(execDefaultVariable)
    DECLARE_FUNCTION(execDisable)
    DECLARE_FUNCTION(execDivideEqual_ByteByte)
    DECLARE_FUNCTION(execDivideEqual_FloatFloat)
    DECLARE_FUNCTION(execDivideEqual_IntFloat)
    DECLARE_FUNCTION(execDivideEqual_RotatorFloat)
    DECLARE_FUNCTION(execDivideEqual_VectorFloat)
    DECLARE_FUNCTION(execDivide_FloatFloat)
    DECLARE_FUNCTION(execDivide_IntInt)
    DECLARE_FUNCTION(execDivide_RotatorFloat)
    DECLARE_FUNCTION(execDivide_VectorFloat)
    DECLARE_FUNCTION(execDot_VectorVector)
    DECLARE_FUNCTION(execDynArrayElement)
    DECLARE_FUNCTION(execDynArrayInsert)
    DECLARE_FUNCTION(execDynArrayLength)
    DECLARE_FUNCTION(execDynArrayRemove)
    DECLARE_FUNCTION(execDynamicCast)
    DECLARE_FUNCTION(execDynamicLoadObject)
    DECLARE_FUNCTION(execEatString)
    DECLARE_FUNCTION(execEnable)
    DECLARE_FUNCTION(execEndFunctionParms)
    DECLARE_FUNCTION(execEqualEqual_BoolBool)
    DECLARE_FUNCTION(execEqualEqual_FloatFloat)
    DECLARE_FUNCTION(execEqualEqual_RotatorRotator)
    DECLARE_FUNCTION(execEqualEqual_StringString)
    DECLARE_FUNCTION(execEqualEqual_VectorVector)
    DECLARE_FUNCTION(execExp)
    DECLARE_FUNCTION(execFClamp)
    DECLARE_FUNCTION(execFMax)
    DECLARE_FUNCTION(execFMin)
    DECLARE_FUNCTION(execFRand)
    DECLARE_FUNCTION(execFinalFunction)
    DECLARE_FUNCTION(execFloatConst)
    DECLARE_FUNCTION(execFloatToBool)
    DECLARE_FUNCTION(execFloatToByte)
    DECLARE_FUNCTION(execFloatToInt)
    DECLARE_FUNCTION(execFloatToString)
    DECLARE_FUNCTION(execGetAxes)
    DECLARE_FUNCTION(execGetEnum)
    DECLARE_FUNCTION(execGetPropertyText)
    DECLARE_FUNCTION(execGetStateName)
    DECLARE_FUNCTION(execGetUnAxes)
    DECLARE_FUNCTION(execGlobalFunction)
    DECLARE_FUNCTION(execGotoLabel)
    DECLARE_FUNCTION(execGotoState)
    DECLARE_FUNCTION(execGreaterEqual_FloatFloat)
    DECLARE_FUNCTION(execGreaterEqual_IntInt)
    DECLARE_FUNCTION(execGreaterEqual_StringString)
    DECLARE_FUNCTION(execGreaterGreaterGreater_IntInt)
    DECLARE_FUNCTION(execGreaterGreater_IntInt)
    DECLARE_FUNCTION(execGreaterGreater_VectorRotator)
    DECLARE_FUNCTION(execGreater_FloatFloat)
    DECLARE_FUNCTION(execGreater_IntInt)
    DECLARE_FUNCTION(execGreater_StringString)
    DECLARE_FUNCTION(execHighNative0)
    DECLARE_FUNCTION(execHighNative1)
    DECLARE_FUNCTION(execHighNative10)
    DECLARE_FUNCTION(execHighNative11)
    DECLARE_FUNCTION(execHighNative12)
    DECLARE_FUNCTION(execHighNative13)
    DECLARE_FUNCTION(execHighNative14)
    DECLARE_FUNCTION(execHighNative15)
    DECLARE_FUNCTION(execHighNative2)
    DECLARE_FUNCTION(execHighNative3)
    DECLARE_FUNCTION(execHighNative4)
    DECLARE_FUNCTION(execHighNative5)
    DECLARE_FUNCTION(execHighNative6)
    DECLARE_FUNCTION(execHighNative7)
    DECLARE_FUNCTION(execHighNative8)
    DECLARE_FUNCTION(execHighNative9)
    DECLARE_FUNCTION(execInStr)
    DECLARE_FUNCTION(execInstanceVariable)
    DECLARE_FUNCTION(execIntConstByte)
    DECLARE_FUNCTION(execIntToByte)
    DECLARE_FUNCTION(execIntToFloat)
    DECLARE_FUNCTION(execIntToString)
    DECLARE_FUNCTION(execInvert)
    DECLARE_FUNCTION(execIsA)
    DECLARE_FUNCTION(execIsInState)
    DECLARE_FUNCTION(execJump)
    DECLARE_FUNCTION(execJumpIfNot)
    DECLARE_FUNCTION(execLeft)
    DECLARE_FUNCTION(execLen)
    DECLARE_FUNCTION(execLerp)
    DECLARE_FUNCTION(execLessEqual_FloatFloat)
    DECLARE_FUNCTION(execLessEqual_IntInt)
    DECLARE_FUNCTION(execLessEqual_StringString)
    DECLARE_FUNCTION(execLessLess_IntInt)
    DECLARE_FUNCTION(execLessLess_VectorRotator)
    DECLARE_FUNCTION(execLess_FloatFloat)
    DECLARE_FUNCTION(execLess_IntInt)
    DECLARE_FUNCTION(execLess_StringString)
    DECLARE_FUNCTION(execLet)
    DECLARE_FUNCTION(execLetBool)
    DECLARE_FUNCTION(execLocalVariable)
    DECLARE_FUNCTION(execLocalize)
    DECLARE_FUNCTION(execLog)
    DECLARE_FUNCTION(execLoge)
    DECLARE_FUNCTION(execMax)
    DECLARE_FUNCTION(execMetaCast)
    DECLARE_FUNCTION(execMid)
    DECLARE_FUNCTION(execMin)
    DECLARE_FUNCTION(execMirrorVectorByNormal)
    DECLARE_FUNCTION(execMultiplyEqual_ByteByte)
    DECLARE_FUNCTION(execMultiplyEqual_FloatFloat)
    DECLARE_FUNCTION(execMultiplyEqual_IntFloat)
    DECLARE_FUNCTION(execMultiplyEqual_RotatorFloat)
    DECLARE_FUNCTION(execMultiplyEqual_VectorFloat)
    DECLARE_FUNCTION(execMultiplyEqual_VectorVector)
    DECLARE_FUNCTION(execMultiplyMultiply_FloatFloat)
    DECLARE_FUNCTION(execMultiply_FloatFloat)
    DECLARE_FUNCTION(execMultiply_FloatRotator)
    DECLARE_FUNCTION(execMultiply_FloatVector)
    DECLARE_FUNCTION(execMultiply_IntInt)
    DECLARE_FUNCTION(execMultiply_RotatorFloat)
    DECLARE_FUNCTION(execMultiply_VectorFloat)
    DECLARE_FUNCTION(execMultiply_VectorVector)
    DECLARE_FUNCTION(execNameConst)
    DECLARE_FUNCTION(execNameToString)
    DECLARE_FUNCTION(execNativeParm)
    DECLARE_FUNCTION(execNew)
    DECLARE_FUNCTION(execNormal)
    DECLARE_FUNCTION(execNormalize)
    DECLARE_FUNCTION(execNotEqual_BoolBool)
    DECLARE_FUNCTION(execNotEqual_FloatFloat)
    DECLARE_FUNCTION(execNotEqual_RotatorRotator)
    DECLARE_FUNCTION(execNotEqual_StringString)
    DECLARE_FUNCTION(execNotEqual_VectorVector)
    DECLARE_FUNCTION(execNot_PreBool)
    DECLARE_FUNCTION(execOrOr_BoolBool)
    DECLARE_FUNCTION(execOr_IntInt)
    DECLARE_FUNCTION(execOrthoRotation)
    DECLARE_FUNCTION(execPercent_FloatFloat)
    DECLARE_FUNCTION(execPrimitiveCast)
    DECLARE_FUNCTION(execRand)
    DECLARE_FUNCTION(execResetConfig)
    DECLARE_FUNCTION(execRight)
    DECLARE_FUNCTION(execRotRand)
    DECLARE_FUNCTION(execRotationConst)
    DECLARE_FUNCTION(execRotatorToBool)
    DECLARE_FUNCTION(execRotatorToString)
    DECLARE_FUNCTION(execRotatorToVector)
    DECLARE_FUNCTION(execSaveConfig)
    DECLARE_FUNCTION(execSelf)
    DECLARE_FUNCTION(execSetPropertyText)
    DECLARE_FUNCTION(execSin)
    DECLARE_FUNCTION(execSmerp)
    DECLARE_FUNCTION(execSqrt)
    DECLARE_FUNCTION(execSquare)
    DECLARE_FUNCTION(execStaticSaveConfig)
    DECLARE_FUNCTION(execStop)
    DECLARE_FUNCTION(execStringConst)
    DECLARE_FUNCTION(execStringToBool)
    DECLARE_FUNCTION(execStringToByte)
    DECLARE_FUNCTION(execStringToFloat)
    DECLARE_FUNCTION(execStringToInt)
    DECLARE_FUNCTION(execStringToRotator)
    DECLARE_FUNCTION(execStringToVector)
    DECLARE_FUNCTION(execStructCmpEq)
    DECLARE_FUNCTION(execStructCmpNe)
    DECLARE_FUNCTION(execStructMember)
    DECLARE_FUNCTION(execSubtractEqual_ByteByte)
    DECLARE_FUNCTION(execSubtractEqual_FloatFloat)
    DECLARE_FUNCTION(execSubtractEqual_IntInt)
    DECLARE_FUNCTION(execSubtractEqual_RotatorRotator)
    DECLARE_FUNCTION(execSubtractEqual_VectorVector)
    DECLARE_FUNCTION(execSubtractSubtract_Byte)
    DECLARE_FUNCTION(execSubtractSubtract_Int)
    DECLARE_FUNCTION(execSubtractSubtract_PreByte)
    DECLARE_FUNCTION(execSubtractSubtract_PreInt)
    DECLARE_FUNCTION(execSubtract_FloatFloat)
    DECLARE_FUNCTION(execSubtract_IntInt)
    DECLARE_FUNCTION(execSubtract_PreFloat)
    DECLARE_FUNCTION(execSubtract_PreInt)
    DECLARE_FUNCTION(execSubtract_PreVector)
    DECLARE_FUNCTION(execSubtract_RotatorRotator)
    DECLARE_FUNCTION(execSubtract_VectorVector)
    DECLARE_FUNCTION(execSwitch)
    DECLARE_FUNCTION(execTan)
    DECLARE_FUNCTION(execUndefined)
    DECLARE_FUNCTION(execUnicodeStringConst)
    DECLARE_FUNCTION(execVRand)
    DECLARE_FUNCTION(execVSize)
    DECLARE_FUNCTION(execVectorConst)
    DECLARE_FUNCTION(execVectorToBool)
    DECLARE_FUNCTION(execVectorToRotator)
    DECLARE_FUNCTION(execVectorToString)
    DECLARE_FUNCTION(execVirtualFunction)
    DECLARE_FUNCTION(execWarn)
    DECLARE_FUNCTION(execXorXor_BoolBool)
    DECLARE_FUNCTION(execXor_IntInt)

    INT Index;                      // 0x04: slot in GObjObjects
    UObject* HashNext;              // 0x08: GObjHash bucket chain
    struct FStateFrame* StateFrame; // 0x0C
    class ULinkerLoad* _Linker;     // 0x10
    INT _LinkerIndex;               // 0x14
    UObject* Outer;                 // 0x18
    DWORD ObjectFlags;              // 0x1C
    FName Name;                     // 0x20
    UClass* Class;                  // 0x24
    DWORD PropertyHash;             // 0x28: Ion Storm's (Object.uc: ObjectInternalPropertyHash)
};
T3_CHECK_SIZE(UObject, 0x2C);

// SuperField is at 0x2C in this build (0x28 in stock Unreal Engine 2): UObject
// is one field longer.
class UField : public UObject
{
public:
    UField* SuperField;             // 0x2C: all 287 classes chain up to Object
    UField* Next;                   // 0x30 (stock order, not yet seen)
};
T3_CHECK_SIZE(UField, 0x34);

class UStruct : public UField
{
public:
    BYTE Unknown34[0x14];           // 0x34
    TArray<BYTE> Script;            // 0x48: the bytecode (FFrame's constructor, 0x10B0FCA0)
};

class UFunction : public UStruct
{
};

class UState : public UStruct
{
};

// UStruct's fields end at 0x54 and UState has none known yet, so UClass's
// padding covers the rest: shrink it when they get more.
class UClass : public UState
{
public:
    BYTE Unknown54[0x94];
    UObject* ClassDefaultObject;    // 0xE8 (docs/engine.md: static, probable)
};

// --- Script execution ---------------------------------------------------------------

// A native's signature; the tables the interpreter dispatches opcodes and
// native indices through (FFrame::Step), and primitive casts
// (execPrimitiveCast).
typedef void (UObject::*Native)(FFrame& Stack, RESULT_DECL);
extern Native GNatives[];
extern Native GCasts[];

// What the last Step() evaluated as a variable: its property and address
// (execDynArrayLength reads them), and flags for the script compiler.
extern UProperty* GProperty;        // 0x10F45C30
extern BYTE* GPropAddr;             // 0x10F45C34
extern DWORD GRuntimeUCFlags;       // 0x10F45C44

enum ERuntimeUCFlags
{
    RUC_ArrayLengthSet = 0x01,      // a dynamic array's length was assigned
};

// The state of one running script function (stock Unreal Engine 2 layout; the
// natives read Object and Code at these offsets).
class FFrame : public FOutputDevice
{
public:
    FFrame(UObject* InObject, UStruct* InNode, INT CodeOffset, void* InLocals);  // 0x10B0FCA0
    virtual void Serialize(const ANSICHAR* V, EName Event);

    // Runs the next expression, writing its value to Result. Out of line in
    // this build (0x10B0FC50), where stock Unreal Engine 2 inlines it, like the
    // readers below that take a constant from the bytecode.
    void Step(UObject* Context, RESULT_DECL);

    INT ReadInt();                  // 0x10B0FC70
    FLOAT ReadFloat();              // 0x10B0FC80
    FName ReadName();               // 0x10B0FCD0

    // The linker folded ReadObject into ReadInt: they compile to the same code.
    UObject* ReadObject() { return (UObject*)ReadInt(); }

    UStruct* Node;                  // 0x04
    UObject* Object;                // 0x08
    BYTE* Code;                     // 0x0C
    BYTE* Locals;                   // 0x10
};

// A native's parameters, read in order by running their expressions.
#define P_GET_UBOOL(var)       DWORD var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_BYTE(var)        BYTE var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_INT(var)         INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_FLOAT(var)       FLOAT var = 0.f; Stack.Step(Stack.Object, &var);
#define P_GET_NAME(var)        FName var = NAME_None; Stack.Step(Stack.Object, &var);
#define P_GET_STR(var)         FString var; Stack.Step(Stack.Object, &var);
#define P_GET_VECTOR(var)      FVector var; Stack.Step(Stack.Object, &var);
#define P_GET_ROTATOR(var)     FRotator var; Stack.Step(Stack.Object, &var);
#define P_GET_OBJECT(cls, var) cls* var = NULL; Stack.Step(Stack.Object, &var);
#define P_FINISH               Stack.Code++;

#endif
