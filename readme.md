# PMODE/W DOS EXTENDER

This repository contains the source code of PMODE/W v1.33, a 32-bit Protected Mode DOS extender for the Watcom C/C++ Compiler released in 1997-01, for the purpose of archival and preservation. As of 2022-01, the original host website is still [functional](http://www.sid6581.net/pmodew/).

File and directory names have been converted to lowercase, and the directory structure has been reorganized from the original archives. Object files and executables from the source archive (pmw133s.zip) have been removed (the pmodew.exe causes DOSBox to crash), while the contents from the original binary distribution (pmw133.zip) are now in the bin/ subdirectory. Source code, examples, and documentation have similarly been placed in their own respective subdirectories. The *scaled down ultra-tiny version* binaries and documentation have also been placed in the respective directories.

PMODE/W is Copyright &copy; 1994-1997, Charles Scheffold and Thomas Pytel.

______

## Overview

PMODE/W is a DOS extender for the Watcom C/C++ package. It allows DOS programs to run in full 32 bit protected mode, with access to all memory available in the system. PMODE/W basically extends the DOS environment to protected mode and provides a simple interface to the real mode DOS system services for your code. PMODE/W takes care of all aspects of running the system in protected mode and maintaining compatibility with the underlying real mode software. PMODE/W deals with low level necessities such as descriptor tables, memory management, IRQ and interrupt redirection, real/protected mode translation functions, exception handling, and other miscellaneous aspects of running in protected mode. Your code does not need to deal with specific aspects of different systems, such as XMS/EMS/VCPI/DPMI availability. PMODE/W will run on top of almost any system and provide common protected mode services to your program through the DPMI interface specification, as well as most standard DOS functions extended for protected mode use.

PMODE/W replaces DOS/4GW extender in the Watcom C/C++ package. Whereas DOS/4GW requires a stub and an large external extender, PMODE/W is the stub and extender in one. The generated executable contains the PMODE/W extender within it as the stub. When run, PMODE/W will take care of setting up the system and executing the protected mode portion of the program. PMODE/W has the added advantage of allowing you to compress you protected mode programs. PMODE/W is also completely interchangeable with DOS/4GW. You may plug PMODE/W into almost any Watcom C/C++ programs without worry. So long as the program does not use any DOS/4GW specific functions, the code will work fine. This allows you to switch directly back to DOS/4GW if for any reason you are not satisfied with PMODE/W. This also allows you to debug PMODE/W programs unsing the Watcom debugger, as any uncompressed PMODE/W executable can be run with DOS/4GW simply by executing it with DOS4GW.EXE.

Several years have gone into the development of PMODE/W. It is now a fairly mature DOS extender, and has gone through its fair share of bugs and incompatibilities. It is at this point, a very stable protected mode system. Great pains have gone into the optimization and testing of PMODE/W. Our major goals have been speed, size, and stability. We now feel that we have achieved a good deal of those things. But don't take our word for it, try it yourself. Just plug PMODE/W into any popular program out there which uses DOS/4GW.

To sum it up, if you are looking for a good solid, stable, and fast extender, PMODE/W may be just what you need.

Here are some of the advantages of PMODE/W:

* No external extender required (everything needed to execute is in the EXE).
* Small size (less than 12k for the entire extender program).
* Compression of protected mode executables.
* Low extended memory overhead.
* Does not require ANY extended memory to load OR execute.
* Fast execution.
* FREE! 

_Important Note: PMODE/W is no longer supported by the authors (us). No claims are made as to its current state of functionality so use it at your own risk. If it kills your cat or something, don't say we didn't warn you._

___

## License

From the original website:

**PMODE/W is now FREE.**

Due to the fact that PMODE/W is no longer supported it is now free for use in commercial and non-commercial applications, provided said applications are not themselves DOS extenders. To put it bluntly, don't go ripping off our DOS extender to make your own.
