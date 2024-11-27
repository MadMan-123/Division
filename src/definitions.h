#pragma once


#ifdef DIVISION_EXPORT
#define DIVAPI __declspec(dllexport)
#else
#define DIVAPI __declspec(dllimport)
#endif // DIVISION_EXPORT
