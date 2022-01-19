/*****************************************************************************

  The original purpose of this test program was to show that floating point
calculations do in fact work under PMODE/W. However, during development we
found that floating point under DOS/4GW was EXTREMELY slow. Run this on a
PC without an FPU or disable the FPU on your 486. Try it under DOS/4GW and
under PMODE/W and notice the speed difference. If the timing values are too
close to be able to tell, try changing the variable "count" to something
larger.

  For those who think this is not accurate because of the cprintf () that is
in there, if you remove the cprintf () from the innermost loop you will find
that the results are pretty much the same as far as the ratio of the speeds
goes.

*****************************************************************************/

#include <conio.h>
#include <math.h>
#include <time.h>
#include <dos.h>

#define M_PI 3.141592654

#pragma aux mode3 =\
        "mov ax,3",\
        "int 10h",\
        modify [ax];

void main (void)
{
  clock_t tstart, tend;

  double  dtemp;
  int     x, line, count = 10000;

  mode3 ();

  printf ("This program will test several Watcom C floating point functions\n"
          "for speed. Each function will be executed %d times. Depending\n"
          "on the speed of your system, this may take a while. This test is\n"
          "only of use on systems WITHOUT a floating point unit.\n", count);

  line = 6;
  gotoxy (0, line);

  tstart = clock ();
  cprintf ("pow () Test");

  for (x=0; x<count; x++)
  {
    gotoxy (30, line);
    dtemp = pow (1234, 56);
    cprintf ("%-6u", x);
  }

  tend = clock ();
  gotoxy (40, line);
  cprintf ("%.4f Seconds\r\n", (float)(tend-tstart) / (float)CLOCKS_PER_SEC);
  line ++;

  tstart = clock ();
  cprintf ("sin () Test");

  for(x=0; x<count; x++)
  {
    gotoxy (30, line);
    dtemp = sin (123456789);
    cprintf ("%-6u", x);
  }

  tend = clock ();
  gotoxy (40, line);
  cprintf ("%.4f Seconds\r\n", (float)(tend-tstart) / (float)CLOCKS_PER_SEC);
  line ++;

  tstart = clock ();
  cprintf ("sqrt () Test");

  for(x=0; x<count; x++)
  {
    gotoxy (30, line);
    dtemp = sqrt (123456789);
    cprintf ("%-6u", x);
  }

  tend = clock ();
  gotoxy (40, line);
  cprintf ("%.4f Seconds\r\n", (float)(tend-tstart) / (float)CLOCKS_PER_SEC);
}

void gotoxy (char gx, char gy)
{
  union REGS r;

  r.h.ah = 2;
  r.h.bh = 0;
  r.h.dl = gx;
  r.h.dh = gy;

  int386 (0x10, &r, &r);
}

