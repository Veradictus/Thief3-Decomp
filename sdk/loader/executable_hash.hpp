#pragma once

// SHA-1 of T3Main.exe via Windows CNG (BCrypt), so the SDK can refuse to run
// against a build it was not verified on even if the timestamp/image size
// happen to match. See engine.cpp's SupportedExecutableHash for the call site
// and docs/sdk.md for the expected hash.

#include <windows.h>
#include <bcrypt.h>

namespace t3sdk::engine {

enum class HashFailure { None, OpenFile, ReadFile, Crypto };

struct HashCheck {
    HashFailure failure;
    DWORD win32Error;
    NTSTATUS cryptoStatus;
    bool matches;
};

HashCheck CheckSupportedExecutableHash(const wchar_t* path);

}  // namespace t3sdk::engine
