#include "IODCommon.h"

#ifdef WIN32
int vsscanf(const char  *buffer, const char  *format, va_list argPtr)
{
	int retValue;
	__asm 
	{
		push ebp
			push [buffer]
		push [format]
		push [argPtr]
		mov ebp, esp
			push edi
			push esi
			sub esp, 400
			mov edi, esp
			mov esi, [ebp]
		mov ecx, 100
			rep movsd
			push [ebp + 4]
		push [ebp + 8]
		call dword ptr [sscanf]
		add esp, 408
			pop esi
			pop edi
			add esp, 12
			pop ebp
			mov retValue, eax
	}
	return retValue;
}
#endif