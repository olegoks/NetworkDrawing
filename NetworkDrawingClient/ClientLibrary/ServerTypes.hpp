#pragma once

#ifndef SERVERTYPES_HPP
#define SERVERTYPES_HPP

#pragma warning (disable: 4996)

#define CALLBACK __stdcall

#include <functional>
#include <cstdint>

#ifndef _M_X64 
	using Size = unsigned __int32;
#else
	using Size = unsigned __int64;
#endif

#define COMPILING_DLL

#ifdef COMPILING_DLL
	#define EXPIMP __declspec(dllexport)
#else
	#define EXPIMP __declspec(dllimport)
#endif

using Number = Size;
using Port = unsigned short;
using Ip = unsigned long;
using Byte = char;

enum class error_code : uint8_t {

	Success = 0,
	Failure,
	ServerIsRunningYet,
	ServerStopedYet,
	AddressUndefined,
	PortNumberUndefined,
	InitializationError,
	FailureNewThreadStarting

};

#endif //SERVERTYPES_HPP