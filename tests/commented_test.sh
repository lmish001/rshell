#!/bin/bash
# Use tests/commented_test.sh while in rshell directory to run tests 

echo "Testing ouput for commented commands:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
CASENUM=0

RED='\033[0;91m'
REG='\033[0m'

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="#Do not ouput this # echo \"See what happens\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo hello && echo hi there # mkdir case4_mult_test"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo this; # echo is && echo a || echo test"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="#echo a; echo b # echo c; echo d"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo hello ; ls #do not print"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo \"hello#comment#\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="#"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="mkdir case7_commented_test && rm -rf case7_commented_test && # echo \" what happens\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="rm -rf case8_commented_test ; ls  || # echo \" what happens\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo a# && ls || echo b # echo c"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

# ((++CASENUM))
# echo "Case $CASENUM"
# USERINPUT="echo a# && ls ||# echo c"
# echo "Input: $USERINPUT"
# echo "Output:"
# echo
# bin/rshell <<< $USERINPUT
# echo
# echo "Case $CASENUM Test Complete"
# echo
