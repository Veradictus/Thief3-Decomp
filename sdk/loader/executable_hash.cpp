// See executable_hash.hpp for what this module is for.
#include "executable_hash.hpp"

#include <bcrypt.h>

#include <cstring>
#include <new>

namespace t3sdk::engine {

HashCheck CheckSupportedExecutableHash(const wchar_t* path) {
    HANDLE file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                              OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        return {HashFailure::OpenFile, GetLastError(), 0, false};
    }

    BCRYPT_ALG_HANDLE algorithm = nullptr;
    BCRYPT_HASH_HANDLE hash = nullptr;
    PUCHAR hashObject = nullptr;
    HashFailure failure = HashFailure::None;
    DWORD win32Error = ERROR_SUCCESS;
    // Each step below runs only if `status` is still success (BCrypt's NTSTATUS
    // convention: negative is failure), threading the first failure through to
    // the cleanup at the end instead of nesting or early-returning.
    NTSTATUS status = BCryptOpenAlgorithmProvider(&algorithm, BCRYPT_SHA1_ALGORITHM, nullptr, 0);
    DWORD objectLength = 0, resultLength = 0, hashLength = 0;
    if (status >= 0) status = BCryptGetProperty(algorithm, BCRYPT_OBJECT_LENGTH, reinterpret_cast<PUCHAR>(&objectLength),
                                                sizeof(objectLength), &resultLength, 0);
    if (status >= 0) status = BCryptGetProperty(algorithm, BCRYPT_HASH_LENGTH, reinterpret_cast<PUCHAR>(&hashLength),
                                                sizeof(hashLength), &resultLength, 0);
    if (status >= 0 && hashLength == 20) {
        hashObject = new (std::nothrow) UCHAR[objectLength];
        if (hashObject) status = BCryptCreateHash(algorithm, &hash, hashObject, objectLength, nullptr, 0, 0);
        else status = static_cast<NTSTATUS>(0xC0000017L);  // STATUS_NO_MEMORY
    } else if (status >= 0) {
        status = static_cast<NTSTATUS>(0xC000000DL);  // STATUS_INVALID_PARAMETER
    }

    UCHAR buffer[64 * 1024];
    DWORD bytesRead = 0;
    while (status >= 0) {
        if (!ReadFile(file, buffer, sizeof(buffer), &bytesRead, nullptr)) {
            failure = HashFailure::ReadFile;
            win32Error = GetLastError();
            break;
        }
        if (!bytesRead) break;
        status = BCryptHashData(hash, buffer, bytesRead, 0);
    }
    UCHAR digest[20]{};
    if (failure == HashFailure::None && status >= 0) status = BCryptFinishHash(hash, digest, sizeof(digest), 0);
    if (failure == HashFailure::None && status < 0) failure = HashFailure::Crypto;

    bool matches = false;
    if (failure == HashFailure::None) {
        static constexpr UCHAR expected[20] = {0x40,0xbf,0x68,0xa5,0x42,0x46,0xbc,0xde,0x2f,0xb5,
                                                0xfc,0xbc,0x75,0xb9,0x4d,0xc7,0xc7,0xf7,0x83,0x05};
        matches = memcmp(digest, expected, sizeof(expected)) == 0;
    }

    if (hash) BCryptDestroyHash(hash);
    delete[] hashObject;
    if (algorithm) BCryptCloseAlgorithmProvider(algorithm, 0);
    CloseHandle(file);
    return {failure, win32Error, status, matches};
}

}  // namespace t3sdk::engine
