#!/bin/bash
# Use tests/exit_test.sh while in rshell directory to run tests 

echo "Testing ouput with test command:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
CASENUM=0

RED='\033[0;91m'
REG='\033[0m'

printf "${RED}Weird Exit Commands${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="exit exit"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="exit now"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Exit commands with parentheses${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="(echo \"Running exit\" && exit) ; echo \"Exit failed\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo \"Running exit\" && (exit ; echo \"Exit failed\")"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo \"Running exit\" && (rmdir Not_a_real_dir || exit) ; echo \"Exit properly failed\" "
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Exit Commands with nested parentheses${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo a && (echo b || ( echo c && exit) && echo \"exit properly failed\") "
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo a && (echo b && ( echo c && exit); echo \"exit failure\") "
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo