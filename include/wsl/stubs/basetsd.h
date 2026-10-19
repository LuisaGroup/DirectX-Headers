// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

// These #defines prevent the idl-generated headers from trying to include
// Windows.h from the SDK rather than this one.
#ifndef RPC_NO_WINDOWS_H
#define RPC_NO_WINDOWS_H
#endif
#ifndef COM_NO_WINDOWS_H
#define COM_NO_WINDOWS_H
#endif

// When DXC's WinAdapter.h has already been included it exposes a family of
// DXC_*_DEFINED macros signalling which Windows types/macros it provides.
// Skip the conflicting definitions below in that case so the two adapter
// layers can coexist in the same translation unit.

// Allcaps type definitions
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

// Note: using fixed-width here to match Windows widths
// Specifically this is different for 'long' vs 'LONG'
#ifndef DXC_UINT8_DEFINED
typedef uint8_t UINT8;
#endif
typedef int8_t INT8;
typedef uint16_t UINT16;
typedef int16_t INT16;
#ifndef DXC_UINT32_DEFINED
typedef uint32_t UINT32, UINT;
#endif
#ifndef DXC_ULONG_DEFINED
typedef uint32_t ULONG;
#endif
#ifndef DXC_DWORD_DEFINED
typedef uint32_t DWORD;
#endif
#ifndef DXC_BOOL_DEFINED
typedef uint32_t BOOL, WINBOOL;
#endif
typedef int32_t INT32, INT;
#ifndef DXC_LONG_DEFINED
typedef int32_t LONG;
#endif
#ifndef DXC_UINT64_DEFINED
typedef uint64_t UINT64;
#endif
#ifndef DXC_ULONG_PTR_DEFINED
typedef uint64_t ULONG_PTR;
#endif
typedef int64_t INT64;
typedef int64_t *PLONGLONG;
#ifndef DXC_LONG_PTR_DEFINED
typedef int64_t LONG_PTR;
#endif
typedef int64_t *PLONG_PTR;
typedef void VOID;
#ifndef DXC_WIN_ADAPTER_DEFINED
typedef void *HANDLE, *RPC_IF_HANDLE, *LPVOID;
typedef const void *LPCVOID;
typedef size_t SIZE_T;
#endif
typedef float FLOAT;
typedef double DOUBLE;
#ifndef DXC_WIN_ADAPTER_DEFINED
typedef unsigned char BYTE;
#endif
typedef int HWND;
typedef int PALETTEENTRY;
typedef int HDC;
#ifndef DXC_WORD_DEFINED
typedef uint16_t WORD;
#endif
typedef void* PVOID;
#ifndef DXC_BOOLEAN_DEFINED
typedef char BOOLEAN;
#endif
#ifndef DXC_ULONGLONG_DEFINED
typedef uint64_t ULONGLONG;
#endif
typedef uint16_t USHORT, *PUSHORT;
#ifndef DXC_LONGLONG_DEFINED
typedef int64_t LONGLONG;
#endif
typedef int64_t LONG64, *PLONG64;
typedef uint64_t ULONG64, *PULONG64;
#ifndef DXC_WIN_ADAPTER_DEFINED
typedef wchar_t WCHAR, *PWSTR;
#else
typedef wchar_t *PWSTR;
#endif
typedef uint8_t UCHAR, *PUCHAR;
#ifndef DXC_ULONG_PTR_DEFINED
typedef uint64_t ULONG_PTR, *PULONG_PTR;
#else
typedef uint64_t *PULONG_PTR;
#endif
typedef uint64_t UINT_PTR, *PUINT_PTR;
typedef int64_t INT_PTR, *PINT_PTR;

// Note: WCHAR is not the same between Windows and Linux, to enable
// string manipulation APIs to work with resulting strings.
// APIs to D3D/DXCore will work on Linux wchars, but beware with
// interactions directly with the Windows kernel.
typedef char CHAR, *PSTR, *LPSTR, TCHAR, *PTSTR;
typedef const char *LPCSTR, *PCSTR, *LPCTSTR, *PCTSTR;
#ifndef DXC_WIN_ADAPTER_DEFINED
typedef wchar_t WCHAR, *PWSTR, *LPWSTR, *PWCHAR;
typedef const wchar_t *LPCWSTR, *PCWSTR;
#else
typedef wchar_t *LPWSTR, *PWCHAR;
typedef const wchar_t *LPCWSTR, *PCWSTR;
#endif

#undef LONG_MAX
#define LONG_MAX INT_MAX
#undef ULONG_MAX
#define ULONG_MAX UINT_MAX

// Misc defines
#ifndef DXC_WIN_ADAPTER_DEFINED
#define MIDL_INTERFACE(x) interface
#endif
#define __analysis_assume(x)
#ifndef DXC_WIN_ADAPTER_DEFINED
#define TRUE 1u
#define FALSE 0u
#define DECLSPEC_UUID(x)
#define DECLSPEC_NOVTABLE
#define DECLSPEC_SELECTANY
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif
#endif // DXC_WIN_ADAPTER_DEFINED
#define APIENTRY
#define OUT
#define IN
#define CONST const
#define MAX_PATH 260
#define GENERIC_ALL 0x10000000L
#ifndef DXC_WIN_ADAPTER_DEFINED
#define C_ASSERT(expr) static_assert((expr))
#define _countof(a) (sizeof(a) / sizeof(*(a)))
#define UNREFERENCED_PARAMETER(P) (P)
#endif

typedef struct tagRECTL
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECTL;

typedef struct tagPOINT
{
    int x;
    int y;
} POINT;

#ifndef DXC_GUID_DEFINED
typedef struct _GUID {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t  Data4[ 8 ];
} GUID;

#ifdef INITGUID
#ifdef __cplusplus
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) EXTERN_C const GUID DECLSPEC_SELECTANY name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }
#else
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) const GUID DECLSPEC_SELECTANY name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }
#endif
#else
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) EXTERN_C const GUID name
#endif

typedef GUID IID;
typedef GUID UUID;
typedef GUID CLSID;
#ifdef __cplusplus
#define REFGUID const GUID &
#define REFIID const IID &
#define REFCLSID const IID &

__inline int InlineIsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
    return (
        ((uint32_t *)&rguid1)[0] == ((uint32_t *)&rguid2)[0] &&
        ((uint32_t *)&rguid1)[1] == ((uint32_t *)&rguid2)[1] &&
        ((uint32_t *)&rguid1)[2] == ((uint32_t *)&rguid2)[2] &&
        ((uint32_t *)&rguid1)[3] == ((uint32_t *)&rguid2)[3]);
}

inline bool operator==(REFGUID guidOne, REFGUID guidOther)
{
    return !!InlineIsEqualGUID(guidOne, guidOther);
}

inline bool operator!=(REFGUID guidOne, REFGUID guidOther)
{
    return !(guidOne == guidOther);
}

#else
#define REFGUID const GUID *
#define REFIID const IID *
#define REFCLSID const IID *
#endif
#endif // DXC_GUID_DEFINED

// SAL annotations
#ifndef _In_
#define _In_
#endif
#ifndef _In_z_
#define _In_z_
#endif
#ifndef _In_opt_
#define _In_opt_
#endif
#ifndef _In_opt_z_
#define _In_opt_z_
#endif
#ifndef _In_reads_
#define _In_reads_(x)
#endif
#ifndef _In_reads_opt_
#define _In_reads_opt_(x)
#endif
#ifndef _In_reads_bytes_
#define _In_reads_bytes_(x)
#endif
#ifndef _In_reads_bytes_opt_
#define _In_reads_bytes_opt_(x)
#endif
#ifndef _In_range_
#define _In_range_(x, y)
#endif
#ifndef _In_bytecount_
#define _In_bytecount_(x)
#endif
#ifndef _Out_
#define _Out_
#endif
#ifndef _Out_opt_
#define _Out_opt_
#endif
#ifndef _Outptr_
#define _Outptr_
#endif
#ifndef _Outptr_opt_result_z_
#define _Outptr_opt_result_z_
#endif
#ifndef _Outptr_opt_result_bytebuffer_
#define _Outptr_opt_result_bytebuffer_(x)
#endif
#ifndef _COM_Outptr_
#define _COM_Outptr_
#endif
#ifndef _COM_Outptr_result_maybenull_
#define _COM_Outptr_result_maybenull_
#endif
#ifndef _COM_Outptr_opt_
#define _COM_Outptr_opt_
#endif
#ifndef _COM_Outptr_opt_result_maybenull_
#define _COM_Outptr_opt_result_maybenull_
#endif
#ifndef _Out_writes_
#define _Out_writes_(x)
#endif
#ifndef _Out_writes_z_
#define _Out_writes_z_(x)
#endif
#ifndef _Out_writes_opt_
#define _Out_writes_opt_(x)
#endif
#ifndef _Out_writes_all_
#define _Out_writes_all_(x)
#endif
#ifndef _Out_writes_all_opt_
#define _Out_writes_all_opt_(x)
#endif
#ifndef _Out_writes_to_opt_
#define _Out_writes_to_opt_(x, y)
#endif
#ifndef _Out_writes_bytes_
#define _Out_writes_bytes_(x)
#endif
#ifndef _Out_writes_bytes_all_
#define _Out_writes_bytes_all_(x)
#endif
#ifndef _Out_writes_bytes_all_opt_
#define _Out_writes_bytes_all_opt_(x)
#endif
#ifndef _Out_writes_bytes_opt_
#define _Out_writes_bytes_opt_(x)
#endif
#ifndef _Inout_
#define _Inout_
#endif
#ifndef _Inout_opt_
#define _Inout_opt_
#endif
#ifndef _Inout_updates_
#define _Inout_updates_(x)
#endif
#ifndef _Inout_updates_bytes_
#define _Inout_updates_bytes_(x)
#endif
#ifndef _Field_size_
#define _Field_size_(x)
#endif
#ifndef _Field_size_opt_
#define _Field_size_opt_(x)
#endif
#ifndef _Field_size_bytes_
#define _Field_size_bytes_(x)
#endif
#ifndef _Field_size_full_
#define _Field_size_full_(x)
#endif
#ifndef _Field_size_full_opt_
#define _Field_size_full_opt_(x)
#endif
#ifndef _Field_size_bytes_full_
#define _Field_size_bytes_full_(x)
#endif
#ifndef _Field_size_bytes_full_opt_
#define _Field_size_bytes_full_opt_(x)
#endif
#ifndef _Field_size_bytes_part_
#define _Field_size_bytes_part_(x, y)
#endif
#ifndef _Field_range_
#define _Field_range_(x, y)
#endif
#ifndef _Field_z_
#define _Field_z_
#endif
#ifndef _Check_return_
#define _Check_return_
#endif
#ifndef _IRQL_requires_
#define _IRQL_requires_(x)
#endif
#ifndef _IRQL_requires_min_
#define _IRQL_requires_min_(x)
#endif
#ifndef _IRQL_requires_max_
#define _IRQL_requires_max_(x)
#endif
#ifndef _At_
#define _At_(x, y)
#endif
#ifndef _Always_
#define _Always_(x)
#endif
#ifndef _Return_type_success_
#define _Return_type_success_(x)
#endif
#ifndef _Translates_Win32_to_HRESULT_
#define _Translates_Win32_to_HRESULT_(x)
#endif
#ifndef _Maybenull_
#define _Maybenull_
#endif
#ifndef _Outptr_result_maybenull_
#define _Outptr_result_maybenull_
#endif
#ifndef _Outptr_result_nullonfailure_
#define _Outptr_result_nullonfailure_
#endif
#ifndef _Analysis_assume_
#define _Analysis_assume_(x)
#endif
#ifndef _Success_
#define _Success_(x)
#endif
#ifndef _In_count_
#define _In_count_(x)
#endif
#ifndef _In_opt_count_
#define _In_opt_count_(x)
#endif
#ifndef _Use_decl_annotations_
#define _Use_decl_annotations_
#endif
#ifndef _Null_terminated_
#define _Null_terminated_
#endif

// Calling conventions
#ifndef DXC_WIN_ADAPTER_DEFINED
#define __cdecl
#define __stdcall
#define STDMETHODCALLTYPE
#endif
#define STDAPICALLTYPE
#define STDAPI EXTERN_C HRESULT STDAPICALLTYPE
#define WINAPI

#define interface struct
#if defined (__cplusplus) && !defined (CINTERFACE)
#ifndef DXC_WIN_ADAPTER_DEFINED
#define STDMETHOD(method) virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type, method) virtual type STDMETHODCALLTYPE method
#define THIS_
#define THIS void
#endif
#define PURE = 0
#ifndef DXC_WIN_ADAPTER_DEFINED
#define DECLARE_INTERFACE(iface) interface DECLSPEC_NOVTABLE iface
#define DECLARE_INTERFACE_(iface, baseiface) interface DECLSPEC_NOVTABLE iface : public baseiface
#endif

interface IUnknown;
#ifndef DXC_WIN_ADAPTER_DEFINED
extern "C++"
{
    template<typename T> void** IID_PPV_ARGS_Helper(T** pp)
    {
        (void)static_cast<IUnknown*>(*pp);
        return reinterpret_cast<void**>(pp);
    }
}
#define IID_PPV_ARGS(ppType) __uuidof (**(ppType)), IID_PPV_ARGS_Helper (ppType)
#endif
#else
#ifndef DXC_WIN_ADAPTER_DEFINED
#define STDMETHOD(method) HRESULT (STDMETHODCALLTYPE *method)
#define STDMETHOD_(type, method) type (STDMETHODCALLTYPE *method)
#define THIS_ INTERFACE *This,
#define THIS INTERFACE *This
#endif
#ifdef CONST_VTABLE
#define DECLARE_INTERFACE(iface) typedef interface iface { const struct iface##Vtbl *lpVtbl; } iface; typedef const struct iface##Vtbl iface##Vtbl; const struct iface##Vtbl
#else
#define DECLARE_INTERFACE(iface) typedef interface iface { struct iface##Vtbl *lpVtbl; } iface; typedef struct iface##Vtbl iface##Vtbl; struct iface##Vtbl
#endif
#define DECLARE_INTERFACE_(iface, baseiface) DECLARE_INTERFACE (iface)
#endif

#define IFACEMETHOD(method) /*override*/ STDMETHOD (method)
#define IFACEMETHOD_(type, method) /*override*/ STDMETHOD_(type, method)
#ifndef BEGIN_INTERFACE
#define BEGIN_INTERFACE
#define END_INTERFACE
#endif

// Error codes
#ifndef DXC_HRESULT_DEFINED
typedef LONG HRESULT;
#endif
#ifndef DXC_WIN_ADAPTER_DEFINED
#define SUCCEEDED(hr)  (((HRESULT)(hr)) >= 0)
#define FAILED(hr)     (((HRESULT)(hr)) < 0)
#define S_OK           ((HRESULT)0L)
#define S_FALSE        ((HRESULT)1L)
#define E_NOTIMPL      ((HRESULT)0x80004001L)
#define E_OUTOFMEMORY  ((HRESULT)0x8007000EL)
#define E_INVALIDARG   ((HRESULT)0x80070057L)
#define E_NOINTERFACE  ((HRESULT)0x80004002L)
#define E_POINTER      ((HRESULT)0x80004003L)
#define E_HANDLE       ((HRESULT)0x80070006L)
#define E_ABORT        ((HRESULT)0x80004004L)
#define E_FAIL         ((HRESULT)0x80004005L)
#define E_ACCESSDENIED ((HRESULT)0x80070005L)
#define E_UNEXPECTED   ((HRESULT)0x8000FFFFL)
#endif // DXC_WIN_ADAPTER_DEFINED
#define DXGI_ERROR_INVALID_CALL ((HRESULT)0x887A0001L)
#define DXGI_ERROR_NOT_FOUND ((HRESULT)0x887A0002L)
#define DXGI_ERROR_MORE_DATA ((HRESULT)0x887A0003L)
#define DXGI_ERROR_UNSUPPORTED ((HRESULT)0x887A0004L)
#define DXGI_ERROR_DEVICE_REMOVED ((HRESULT)0x887A0005L)
#define DXGI_ERROR_DEVICE_HUNG ((HRESULT)0x887A0006L)
#define DXGI_ERROR_DEVICE_RESET ((HRESULT)0x887A0007L)
#define DXGI_ERROR_DRIVER_INTERNAL_ERROR ((HRESULT)0x887A0020L)
#define DXGI_ERROR_SDK_COMPONENT_MISSING ((HRESULT)0x887A002DL)

typedef struct _LUID
{
    ULONG LowPart;
    LONG HighPart;
} LUID;

typedef struct _RECT
{
    int left;
    int top;
    int right;
    int bottom;
} RECT;

#ifndef DXC_LARGE_INTEGER_DEFINED
typedef union _LARGE_INTEGER {
  struct {
    uint32_t LowPart;
    uint32_t HighPart;
  } u;
  int64_t QuadPart;
} LARGE_INTEGER;
typedef LARGE_INTEGER *PLARGE_INTEGER;
#endif

#ifndef DXC_ULARGE_INTEGER_DEFINED
typedef union _ULARGE_INTEGER {
  struct {
    uint32_t LowPart;
    uint32_t HighPart;
  } u;
  uint64_t QuadPart;
} ULARGE_INTEGER;
typedef ULARGE_INTEGER *PULARGE_INTEGER;
#endif

#ifndef DXC_WIN_ADAPTER_DEFINED
#define DECLARE_HANDLE(name)                                                   \
  struct name##__ {                                                            \
    int unused;                                                                \
  };                                                                           \
  typedef struct name##__ *name
#endif

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES;

#ifndef DXC_STATSTG_DEFINED
struct STATSTG;
#endif

#ifndef DXC_ENUM_FLAG_OPERATORS_DEFINED
#ifdef __cplusplus
// ENUM_FLAG_OPERATORS
// Define operator overloads to enable bit operations on enum values that are
// used to define flags. Use DEFINE_ENUM_FLAG_OPERATORS(YOUR_TYPE) to enable these
// operators on YOUR_TYPE.
extern "C++" {
    template <size_t S>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE;

    template <>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE<1>
    {
        typedef int8_t type;
    };

    template <>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE<2>
    {
        typedef int16_t type;
    };

    template <>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE<4>
    {
        typedef int32_t type;
    };

    template <>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE<8>
    {
        typedef int64_t type;
    };

    // used as an approximation of std::underlying_type<T>
    template <class T>
    struct _ENUM_FLAG_SIZED_INTEGER
    {
        typedef typename _ENUM_FLAG_INTEGER_FOR_SIZE<sizeof(T)>::type type;
    };

}
#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) \
extern "C++" { \
inline constexpr ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a) | ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline ENUMTYPE &operator |= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type &)a) |= ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline constexpr ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a) & ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline ENUMTYPE &operator &= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type &)a) &= ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline constexpr ENUMTYPE operator ~ (ENUMTYPE a) { return ENUMTYPE(~((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a)); } \
inline constexpr ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a) ^ ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline ENUMTYPE &operator ^= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type &)a) ^= ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
}
#else
#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) /* */
#endif
#endif // DXC_ENUM_FLAG_OPERATORS_DEFINED

// D3DX12 uses these
#ifndef DXC_WIN_ADAPTER_DEFINED
#include <stdlib.h>
#define HeapAlloc(heap, flags, size) malloc(size)
#define HeapFree(heap, flags, ptr) free(ptr)
#endif

#if defined(lint)
// Note: lint -e530 says don't complain about uninitialized variables for
// this variable.  Error 527 has to do with unreachable code.
// -restore restores checking to the -save state
#define UNREFERENCED_PARAMETER(P) \
    /*lint -save -e527 -e530 */ \
    { \
        (P) = (P); \
    } \
    /*lint -restore */
#endif
