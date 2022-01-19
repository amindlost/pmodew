/*****************************************************************************

 NOTE: As of v1.22, PMODE/W passes INT 1Ch up when hooked in protected mode.
       This method of hooking 1Ch is no longer necessary, however it still
       serves as a good example of how to setup a real mode callback.

  This is an example of how to set up a real mode callback and hook the BIOS
timer tick interrupt (INT 1Ch) in protected mode. For speed purposes, PMODE/W
does not normally pass this interrupt up to protected mode automatically from
real mode. Therefore, it must be hooked in real mode first and then passed up
to protected mode by way of a DPMI callback. In this example, a character is
incremented in the upper right hand corner of the screen on every tick (in
protected mode). This will ONLY work under PMODE/W if there are DPMI callbacks
available (specified in PMWSETUP). If PMODE/W is running under the control of
a DPMI host, the DPMI host must provide PMODE/W with real mode callbacks.
Under DOS/4GW this is not necessary since DOS/4GW passes up 1Ch all the time.
PMODE/W does not pass it up in order to prevent redundant mode switches which
consequently slow down the system. Hooking INT 8 for timing is a much better
idea.

*****************************************************************************/

#include <stdio.h>
#include <dos.h>

void (__interrupt __far timerproc) (void);

#pragma aux intp =\
        "push eax",\
        "mov ax,[esi]",\
        "mov es:[edi+2ah],ax",\
        "mov ax,[esi+2]",\
        "mov es:[edi+2ch],ax",\
        "mov ax,[esi+4]",\
        "mov es:[edi+20h],ax",\
        "add word ptr es:[edi+2eh],6",\
        "pop eax",\
        "int 1ch",\
        "iretd",\
        modify [eax];

void main (void)
{
  union REGS r;
  unsigned   rmvector;

  r.x.eax = 0x205;
  r.h.bl = 0x1c;
  r.x.ecx = FP_SEG (timerproc);
  r.x.edx = FP_OFF (timerproc);
  int386 (0x31, &r, &r);                /* Hook Protected Mode INT 1Ch */

  setpassup_1C (&rmvector);             /* Initialize 1Ch Passup Handler */
  getch ();
  resetpassup_1C (&rmvector);           /* Reset 1Ch Passup Handler */
}

void (__interrupt __far timerproc) (void)
{
  static char *vidmem = (char *)0xb8000;

  vidmem[158] ++;
}

int setpassup_1C (unsigned *oldvector)
{
  void int1C_handler (void);

  union REGS   pr;
  struct SREGS psr;

  unsigned short cbseg, cboff;
  char           regbuf[0x32];

  pr.x.eax = 0x303;
  psr.ds = FP_SEG (int1C_handler);
  pr.x.esi = FP_OFF (int1C_handler);
  psr.es = FP_SEG (regbuf);
  pr.x.edi = FP_OFF (regbuf);
  int386x (0x31, &pr, &pr, &psr);       /* Allocate A Realmode Callback */

  if (pr.x.cflag != 0)                  /* Exit If Error Allocating Callback */
    return -1;

  cbseg = (unsigned short)pr.x.ecx;
  cboff = (unsigned short)pr.x.edx;

  pr.x.eax = 0x200;
  pr.h.bl = 0x1c;
  int386 (0x31, &pr, &pr);              /* Save The Realmode INT 1Ch Vector */

  *((unsigned short *)oldvector+1) = pr.x.ecx;
  *((unsigned short *)oldvector) = pr.x.edx;

  pr.x.eax = 0x201;
  pr.h.bl = 0x1c;
  pr.x.ecx = cbseg;
  pr.x.edx = cboff;
  int386 (0x31, &pr, &pr);              /* Point INT 1Ch To Callback Address */

  return 0;
}

int resetpassup_1C(unsigned *oldvector)
{
  union REGS pr;

  pr.x.eax = 0x201;
  pr.h.bl = 0x1c;
  pr.x.ecx = *((unsigned short *)oldvector+1);
  pr.x.edx = *((unsigned short *)oldvector);
  int386 (0x31, &pr, &pr);              /* Reset Old Realmode INT 1Ch Vector */

  return 0;
}

/* This handler is called by the realmode INT 1Ch by way of a DPMI callback.
   It takes the return address & flags from the realmode stack (DS:ESI) and
   places them into the DPMI register structure (ES:EDI) so that the routine
   may return to the proper place on termination. It then initiates an INT 1Ch
   in protected mode before returning control with an IRETD */

#pragma off (check_stack);

void int1C_handler (void)
{
  intp ();
}

#pragma on (check_stack);

