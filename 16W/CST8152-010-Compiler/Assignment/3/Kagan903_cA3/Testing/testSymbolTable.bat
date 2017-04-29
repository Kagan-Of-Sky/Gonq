:: File Name:     testSymbolTable.bat
:: Author:        Mark Kaganovsky, 040789903
:: Course:        CST 8152 - Compilers, Lab Section 012
:: Assignment:    3
:: Date:          March 18 2015
:: Professor:     Sv. Ranev
:: Purpose:       To test all of the provided test files in bulk.
::                
::                How to create the various testing executables:
::                    stable: Compile the files with platy_tt.c as the main driver.
::                            Set the constant TEST_BONUS_2 to 0
::                    
::                    stableTestBonus2: Same as the above, except set the TEST_BONUS_2
::                                      constant to 1.
::                    
::                    stableTestFunc: Compile the files with test_st_funcs.c as the main
::                                    driver.
:: 
:: Function List: none

:: If you have a unix terminal emulator you can use the following command to compare files faster.
:: printf "\nTest Output Files\n";  md5sum *.ste TestOutputFiles/*;  printf "\nProvided Test files\n";  md5sum ProvidedOutputFiles/*




:: Create the output file directory if it does not already exist.
	IF NOT EXIST TestOutputFiles (mkdir TestOutputFiles)

:: Perform all the standard tests.
	stable ass3r.pls         > TestOutputFiles/ass3r.out
	stable ass3m.pls -stz 10 > TestOutputFiles/ass3m_stz10.out
	stable ass3m.pls         > TestOutputFiles/ass3m.out

:: Perform test for bonus #1
	stable ass3r.pls -sts:A  > TestOutputFiles/ass3r_stsa.out

:: Perform tests for bonus #2
	stableTestBonus2 ass3r.pls -sts:A > TestOutputFiles/ass3r_stsa_lexemes.out
	stableTestBonus2 ass3r.pls -sts:D > TestOutputFiles/ass3r_stsd_lexemes.out
	stableTestBonus2 ass3m.pls -sts:A > TestOutputFiles/ass3m_stsa_lexemes.out
	stableTestBonus2 ass3m.pls -sts:D > TestOutputFiles/ass3m_stsd_lexemes.out

:: Perform my own tests
	stableTestFunc                    > TestOutputFiles/test_func.out