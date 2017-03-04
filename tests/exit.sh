#!/bin/bash
# Use tests/exit.sh while in rshell directory to run tests 

echo "Testing ouput for exit commands:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
CASENUM=0
RED='\033[0;91m'
REG='\033[0m'

printf "${RED}Basic test commands${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="exit"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo


((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo exit after or || exit; echo \" passed \""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="ehoc double && exit; echo \"passed\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 2 Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo this; #exit && echo \"failure\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="exit || echo \"Did not execute\" && echo \"Test failed\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo hello && ls #do not print; exit"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 5 Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="mkdir exit_case_6 && ls || echo \"ls failed\" && exit"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo hello && ls do not print || EXIT; echo test in progress && exit || echo exit failed"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="rm -rf exit_case_6 || echo test in progress || exit || echo \"exit did not execute\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}exit command with precedence and test command${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="(test -d src && [ -d src ]) && (ls || pwd && exit)"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="((test -d src && [ -d src ]) || (ls || pwd && exit))&& git status"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test -d src && ([ -d src ] || ls )|| pwd && exit && echo "test failed""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo