#!/bin/bash
#----------------------------------------------------------
# COURSE:    CST8234 
# SEMESTER:  Fall 2015 
# A01:       sms
# AUTHOR:    C Ayala
#----------------------------------------------------------

TESTDIR=Test
PROG=sms
C_FILE=sms.c

GREEN='\E[32m'
RED='\E[31m'

#----------------------------------------------------------
# Functions 
#----------------------------------------------------------
function Check {
	echo -e -n "\t\t[$1 $2 "
	tput sgr0
	echo -n "]" 
	echo -e "\t\t$3"
}

function Header {
	echo -n "$1"
}

function Test_Abend {
	arg=($2)
	Header "TEST $1:  $2" 
	./$PROG < $TESTDIR/$1 | grep -i "${arg[1]}" >& /dev/null
	if [ $? == 0 ]; then
		./$PROG < $TESTDIR/$1 >& /dev/null
		if [ $? == 1 ]; then
			let GRADE+=1
			Check $GREEN OK
		else
			Check $RED FAIL
		fi
	else
		Check $RED FAIL
	fi
}
function Test_Normal {
	Header "TEST $1:  $2"
	./$PROG < $TESTDIR/$1 | grep -i "accumulator" | grep $3 >& /dev/null
	if [ $? == 0 ]; then
		let GRADE+=1 
		Check $GREEN OK
	else 
		Check $RED FAIL
	fi
}
#---VARIABLES----------------------------------------------
let GRADE=0
let TEST=0

#----------------------------------------------------------
# Test:  Correct Compilation
#----------------------------------------------------------
Header "TEST $TEST:  COMPILATION"  
gcc -o $PROG $C_FILE -ansi -pedantic -Wall >& /dev/null
if [ $? != 0 ]; then
	Check $FAIL "DID not compile - Trying not pedantic"
	gcc -o $PROG $PROG.c
	if [ $? != 0 ]; then
		Check $FAIL  
		exit
	fi
else
	Check $GREEN OK
	let GRADE+=1
fi
let TEST+=1

#----------------------------------------------------------
# NORMAL Tests
#----------------------------------------------------------
normal=("ADDITION" "SUBTRACTION" "MULTIPLICATION" "DIVISION" "BRANCH  " "BRANCH NEG" "BRANCH ZERO") 
ans=( 17 2 920 28 12 11 0)
i=0
for n in "${normal[@]}"
do 
	Test_Normal  $TEST "$n" "${ans[i]}"
	let TEST+=1
	let i+=1
done

#----------------------------------------------------------
# ABEND Tests
#----------------------------------------------------------
abend=("TOO BIG" "INVALID WORD" "ADD OVERFLOW" "ADD UNDERFLOW" "SUB OVERFLOW" "SUB UNDERFLOW" "MUL OVERFLOW" "MUL UNDERFLOW" "MUL INVALID" "DIVISION_BY 0" "DIV INVALID" "BRNCH ADDRESS")

for t in "${abend[@]}"
do 
	Test_Abend  $TEST "$t" 
	let TEST+=1
done

echo "Your Grade $GRADE"
