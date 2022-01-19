/*****************************************************************************

  This program demonstrates memory availability under PMODE/W. Keep in mind
that under VCPI, on systems with more than 16 megabytes of memory, you will
have to use PMWSETUP to modify the example program to use more than 4 VCPI
page tables so that PMODE/W can access more extended memory.

*****************************************************************************/

#include <dos.h>
#include <math.h>
#include <stdio.h>

#pragma aux DOSalloc4k =\
        "mov bx,0100h",\
        "mov ax,0100h",\
        "int 31h",\
        "mov ecx,0",\
        "jc short done",\
        "mov bx,dx",\
        "mov ax,0006h",\
        "int 31h",\
        "shl ecx,16",\
        "mov cx,dx",\
        "done:",\
        modify [ax bx dx] value [ecx];

#pragma aux DPMIalloc4k =\
        "mov cx,1000h",\
        "mov bx,0000h",\
        "mov ax,0501h",\
        "int 31h",\
        "mov edx,0",\
        "jc short done",\
        "shrd edx,ebx,16",\
        "mov dx,cx",\
        "done:",\
        modify [ax bx cx si di] value [edx];

void main ()
{
  unsigned u, DOScount, DPMIcount;

  for (DOScount = 0; u = DOSalloc4k (); DOScount ++)
    printf ("Allocated 4k DOS block at:  0x%08x\n", u);

  for (DPMIcount = 0; u = DPMIalloc4k (); DPMIcount ++)
    printf ("Allocated 4k DPMI block at: 0x%08x\n", u);

  printf ("\n"
          "Total DOS 4k blocks allocated:   0x%08x (%dk)\n"
          "Total DPMI 4k blocks allocated:  0x%08x (%dk)\n"
          "\n"
          "Total 4k blocks allocated:       0x%08x (%dk)\n",
          DOScount, DOScount * 4,
          DPMIcount, DPMIcount * 4,
          DOScount + DPMIcount, (DOScount + DPMIcount) * 4);
}

