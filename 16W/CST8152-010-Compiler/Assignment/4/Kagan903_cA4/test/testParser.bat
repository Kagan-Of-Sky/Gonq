:: File Name:     testParser.bat
:: Author:        Mark Kaganovsky, 040789903
:: Course:        CST 8152 - Compilers, Lab Section 012
:: Assignment:    4
:: Date:          April 22 2016
:: Professor:     Svillen Ranev
:: Purpose:       To test all the provided testing files in bulk.
:: Function List: none
:: 
:: Notes:
::   If you have a unix terminal emulator you can use the following commands to compare files faster.
::     fdupes ProvidedOutputFiles TestOutputFiles
::             OR
::     printf "\nTest Output Files\n"; md5sum *.ste TestOutputFiles/*; printf "\nProvided Test files\n"; md5sum ProvidedOutputFiles/*




:: Create the output file directory if it does not already exist.
	IF NOT EXIST TestOutputFiles (mkdir TestOutputFiles)

:: Perform standard tests.
	parser.exe    ass4e.pls     >    TestOutputFiles/ass4e_kaganovsky.out
	parser.exe    ass4w1.pls    >    TestOutputFiles/ass4w1_kaganovsky.out
	parser.exe    ass4w2.pls    >    TestOutputFiles/ass4w2_kaganovsky.out
	parser.exe    ass4w3.pls    >    TestOutputFiles/ass4w3_kaganovsky.out
	parser.exe    ass4w4.pls    >    TestOutputFiles/ass4w4_kaganovsky.out
	parser.exe    ass4r.pls     >    TestOutputFiles/ass4r_kaganovsky.out

:: Perform bonus tests.
	parser.exe    ass2r.pls     >    TestOutputFiles/ass2r_kaganovsky.out
	parser.exe    ass4w5op.pls  >    TestOutputFiles/ass4w5op1_kaganovsky.out