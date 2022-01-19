/*****************************************************************************

  This is a simple example of how to use INT 31h/AX=EEFFh to get information
about the DOS extender and the protected mode system. DOS extender developers
are encouraged to support this call as a standard detection method.

*****************************************************************************/

#include <stdio.h>
#include <i86.h>

main (void)
{
    union REGS r;
    struct SREGS sr;
    char far *copyright;
    char *systems[] = {"Raw", "XMS", "VCPI", "DPMI"};
    char *processor[] = {"80386", "80486", "80586","Unknown"};

    r.x.eax = 3;
    int386 (0x10, &r, &r);

    segread (&sr);
    r.w.ax = 0xEEFF;
    int386x (0x31, &r, &r, &sr);

    if (r.x.cflag) {
        printf ("Extender Info Function Not Present!\n");
        exit (1);
    }

    copyright = MK_FP (sr.es, r.x.ebx);

    printf ("Copyright String:\n");
    printf ("-----------------\n");
    printf ("%s\n\n", copyright);

    printf ("System Information:\n");
    printf ("-------------------\n");

    printf ("Extender Code      : %.6Xh ", r.x.eax);
    printf ("(%c%c%c%c)\n", r.x.eax >> 24, r.x.eax >> 16, r.x.eax >> 8,
            r.x.eax);
    printf ("Extender Version   : v%d.%d\n", r.h.dh, r.h.dl);

    printf ("System Type        : %s\n", systems[r.h.ch]);

    if (r.h.cl > 5) r.h.cl = 6;
    printf ("Processor          : %s\n", processor[r.h.cl-3]);

    return 0;
}

