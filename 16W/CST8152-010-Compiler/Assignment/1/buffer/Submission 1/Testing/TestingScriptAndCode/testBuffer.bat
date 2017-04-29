:: File Name:     testBuffer.bat
:: Author:        Mark Kaganovsky, 040789903
:: Course:        CST 8152 - Compilers, Lab Section 012
:: Assignment:    1
:: Date:          Feb 2 2015
:: Professor:     Sv. Ranev
:: 
:: Purpose:       To test all of the provided test files in bulk.
::                1. Compile the project with the file "platy_bt_params.c" instead of "platy_bt.c"
::                2. Place the files "ass1.pls", "ass1e.pls", "bigf.pls" and the buffer executable
::                   in the same directory as this script.
::                3. Run the script.
::                4. Compare the output files to the expected files.
:: 
:: Function List: none

:: Create the output file directory if it does not already exist
IF NOT EXIST TestOutputFiles (mkdir TestOutputFiles)

:: Perform the first set of tests on ass1.pls and ass1e.pls
buffer.exe ass1.pls  add  200    15  > TestOutputFiles/ass1ai.out
buffer.exe ass1.pls  mul  200    15  > TestOutputFiles/ass1mi.out
buffer.exe ass1.pls  fix  200    15  > TestOutputFiles/ass1fi.out
buffer.exe ass1e.pls fix  200    15  > TestOutputFiles/ass1e.out

::Perform the next set of tests on bigf.pls
buffer.exe bigf.pls  add  200    15  > TestOutputFiles/bigfai.out
buffer.exe bigf.pls  add  200    128 > TestOutputFiles/bigfai128.out
buffer.exe bigf.pls  add  32767  15  > TestOutputFiles/bigfamax.out
buffer.exe bigf.pls  fix  200    0   > TestOutputFiles/bigffi0.out
buffer.exe bigf.pls  fix  200    128 > TestOutputFiles/bigffi128.out
buffer.exe bigf.pls  mul  200    15  > TestOutputFiles/bigfmi.out
buffer.exe bigf.pls  mul  32757  9   > TestOutputFiles/bigfmi9.out
buffer.exe bigf.pls  mul  32767  15  > TestOutputFiles/bigfmmax.out
buffer.exe bigf.pls  add  200    0   > TestOutputFiles/bigfai0.out
buffer.exe bigf.pls  mul  200    0   > TestOutputFiles/bigfmi0.out
buffer.exe bigf.pls  add  0      15  > TestOutputFiles/bigfac0.out
buffer.exe bigf.pls  mul  0      15  > TestOutputFiles/bigfmc0.out
buffer.exe bigf.pls  mul  200    128 > TestOutputFiles/bigfmi128.out
buffer.exe bigf.pls  fix  0      0   > TestOutputFiles/bigffc0.out
buffer.exe bigf.pls  fix  -1     0   > TestOutputFiles/bigfc-1.out