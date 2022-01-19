@echo Compiling C example programs.

wcc386 -i=%WATCOM%\h -fpi example1
wlink @pmodew.lnk system pmodew file example1
wcc386 -i=%WATCOM%\h -fpi example2
wlink @pmodew.lnk system pmodew file example2
wcc386 -i=%WATCOM%\h example3
wlink @pmodew.lnk system pmodew file example3
wcc386 -i=%WATCOM%\h example4
wlink @pmodew.lnk system pmodew file example4
wcc386 -i=%WATCOM%\h example5
wlink @pmodew.lnk system pmodew file example5

@echo Compiling ASM example program.

wasm example6.asm
REM tasm /ml /m2 example6.asm
wlink @pmodew.lnk system pmodew file example6

