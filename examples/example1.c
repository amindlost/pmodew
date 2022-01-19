/*****************************************************************************

  This is a simple example of some graphics functions in C. I got a bit bored
one day so I decided to make this little plasma. The original idea came from
Jare/VangeliSTeam's VTIRIS and was converted to C just for fun. This program
also makes use of floating point and inline ASM just to show that they do
indeed work under PMODE/W.

*****************************************************************************/

#include <stdio.h>
#include <math.h>

#define M_PI 3.141592654

void vmode (unsigned short);
void waitvr (void);
void tweakvga (void);

#pragma aux tweakvga =\
        "mov dx,3c4h",\
        "mov ax,604h",\
        "out dx,ax",\
        "mov ax,0f02h",\
        "out dx,ax",\
        "mov dx,3d4h",\
        "mov ax,14h",\
        "out dx,ax",\
        "mov ax,0e317h",\
        "out dx,ax",\
        "mov al,9",\
        "out dx,al",\
        "inc dx",\
        "in al,dx",\
        "and al,0e0h",\
        "add al,7",\
        "out dx,al",\
        modify [ax dx];

#pragma aux vmode =\
        "int 10h",\
        parm [ax] modify [ax];

#pragma aux waitvr =\
        "mov dx,3dah",\
        "wait1:",\
        "in al,dx",\
        "test al,8",\
        "jz wait1",\
        modify [al dx];

void main ()
{
  static char wavetable[256], pal[768];

  int  v, x, y;

  char z;
  char *vidmem = (char *)0xA0000;

  char spd1 = 1, spd2 = 2, spd3 = 3, spd4 = 4;
  char pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
  char tpos1, tpos2, tpos3, tpos4;

  for (x=0, y=0; x<64*3; x+=3, y++)
    pal[x] = y;

  for (x=64*3, y=63; x<128*3; x+=3, y--)
    pal[x] = y;

  for (x=128*3, y=0; x<192*3; x+=3, y++)
    pal[x+2] = y;

  for (x=192*3, y=63; x<256*3; x+=3, y--)
    pal[x+2] = y;

  for (x=0; x<256; x++)
    wavetable[x] = 30 * (1 + sin(x*2 * M_PI / 256));

  vmode (0x13);
  tweakvga ();
  setpal (pal);

  while (!kbhit ())
  {
    waitvr ();

    v = 0;
    tpos1 = pos1;
    tpos2 = pos2;

    for (x=0; x<50; x++)
    {
      tpos3 = pos3;
      tpos4 = pos4;

      for(y=0; y<80; y++)
      {
        z = wavetable[tpos1] + wavetable[tpos2] +
            wavetable[tpos3] + wavetable[tpos4];

        vidmem[v ++] = z;

        tpos3 += 1;
        tpos4 += 3;
      }

      tpos1 += 2;
      tpos2 += 1;
    }

    pos1 += spd1;
    pos2 -= spd2;
    pos3 += spd3;
    pos4 -= spd4;
  }

  getch ();
  vmode (3);
}

void setpal (unsigned char palp[])
{
  int pcount;

  outp (0x3c8, 0);

  for (pcount=0; pcount<768; pcount+=3)
  {
    outp (0x3c9, palp[pcount]);
    outp (0x3c9, palp[pcount+1]);
    outp (0x3c9, palp[pcount+2]);
  }
}

