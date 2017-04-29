:: File Name:     testScanner.bat
:: Author:        Mark Kaganovsky, 040789903
:: Course:        CST 8152 - Compilers, Lab Section 012
:: Assignment:    2
:: Date:          Feb 27 2015
:: Professor:     Sv. Ranev
:: 
:: Purpose:       To test all of the provided test files in bulk.
:: 
:: Function List: none

:: Create the output file directory if it does not already exist
IF NOT EXIST TestOutputFiles (mkdir TestOutputFiles)

:: Perform all the tests
scanner.exe a2empty.pls > TestOutputFiles/a2empty.out
scanner.exe a2error.pls > TestOutputFiles/a2error.out
scanner.exe ass2r.pls   > TestOutputFiles/ass2r.out
scanner.exe ass2w.pls   > TestOutputFiles/ass2w.out