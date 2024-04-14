/**
 * @file gadgets.c
 * This file provides a collection of functions for practicing Return-Oriented
 * Programming (ROP).
 *
 * Compilation is performed with optimizations disabled to ensure the assembly
 * instructions execute as written without alteration by the compiler.
 *
 * #pragma optimize("", off)
 *
 * Social Media Links:
 * - Twitter: https://twitter.com/7etsuo
 * - GitHub: https://github.com/7etsuo
 * - YouTube: https://www.youtube.com/@snowcrash-
 *
 * Author: 7etsuo, 2024
 */

#include "gadgets.h"

#pragma optimize("", off)

void
gadget1 (void)
{
  __asm {
		mov[eax], ecx
		ret
  }
  ;
}

void
gadget2 (void)
{
  __asm {
		add eax, ecx
		ret
  }
  ;
}

void
gadget3 (void)
{
  __asm {
		neg eax
		ret
  }
  ;
}

void
gadget4 (void)
{
  __asm {
		inc eax
		ret
  }
  ;
}

void
gadget5 (void)
{
  __asm {
		mov eax, esi
		pop esi
		ret
  }
  ;
}

void
gadget6 (void)
{
  __asm {
		mov ecx, eax
		mov eax, esi
		pop esi
		retn 0x0010
  }
  ;
}

void
gadget7 (void)
{
  __asm {
		pop eax
		ret
  }
  ;
}

void
gadget8 (void)
{
  __asm {
		pop ecx
		ret
  }
  ;
}

void
gadget9 (void)
{
  __asm {
		push eax
		pop esi
		ret
  }
  ;
}

void
gadgetA (void)
{
  __asm {
		push esp
		pop esi
		ret
  }
  ;
}

void
gadgetB (void)
{
  __asm {
		xchg eax, esp
		ret
  }
  ;
}

void
gadgetC (void)
{
  __asm {
		mov eax, [eax]
		ret
  }
  ;
}
