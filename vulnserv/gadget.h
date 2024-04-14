/**
 * @file gadget.h
 * Assembly "gadget" subroutines for ROP (Return-Oriented Programming) practice.
 *
 * Social Media Links:
 * - Twitter: https://twitter.com/7etsuo
 * - GitHub: https://github.com/7etsuo
 * - YouTube: https://www.youtube.com/@snowcrash-
 *
 * Author: 7etsuo, 2024
 */

#ifndef GADGET_H
#define GADGET_H

 /**
  * Write-what-where gadget: Writes the value in ECX to the address pointed by EAX.
  */
void gadget1(void);

/**
 * Arithmetic gadget: Adds the value in ECX to EAX.
 */
void gadget2(void);

/**
 * Arithmetic gadget: Negates the value in EAX.
 */
void gadget3(void);

/**
 * Arithmetic gadget: Increments the value in EAX.
 */
void gadget4(void);

/**
 * Register transfer gadget: Moves the value in ESI to EAX, then pops ESI off the stack.
 */
void gadget5(void);

/**
 * Complex gadget: Moves the value from EAX to ECX, then moves the value from ESI to EAX,
 * pops ESI, and returns skipping 16 bytes on the stack.
 */
void gadget6(void);

/**
 * Stack operation gadget: Pops the top value of the stack into EAX.
 */
void gadget7(void);

/**
 * Stack operation gadget: Pops the top value of the stack into ECX.
 */
void gadget8(void);

/**
 * Stack manipulation gadget: Pushes EAX onto the stack, then pops it into ESI.
 */
void gadget9(void);

/**
 * Stack manipulation gadget: Pushes ESP onto the stack, then pops it into ESI.
 */
void gadgetA(void);

/**
 * Register swap gadget: Exchanges the values of EAX and ESP.
 */
void gadgetB(void);

/**
 * Memory dereference gadget: Moves the value at the address pointed by EAX into EAX.
 */
void gadgetC(void);

#endif // GADGET_H
