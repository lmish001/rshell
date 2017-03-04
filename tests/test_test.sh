#!/bin/bash
# Use tests/test_test.sh while in rshell directory to run tests 

echo "Testing ouput with test command:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
CASENUM=0
RED='\033[0;91m'
REG='\033[0m'

printf "${RED}Basic test commands${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test src"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test -e src"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test -f src"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test -f src/main.cpp"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test -d src"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test -d src/main.cpp"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Test commands with brackets${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[ src ]"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[ -e src ]"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[ -f src/main.cpp ]"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[ -d src/main.cpp ]"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Test command with connectors and other commandsTest commands with brackets${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[ -d src/main.cpp ] || echo \"Test failed\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo \"Starting\" && test src/main.cpp && echo \"Test Passed\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo \"Starting\" && echo \"Test failed\" || test src/main.cpp"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Using test with no flags passed${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test src/main.cpp && echo passed"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[ src ] && echo passed"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Using test and one flag${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test -e && echo passed"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[ -f ] && echo passed"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Passing multiple flags${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo \"Starting\" && test -e -d src/main.cpp"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[ -d -f src/main.cpp ]"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Syntax errors${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[src/main.cpp]"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="[ src/main.cpp] && ls"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test || echo \"test properly did not execute\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo \"Should just be echo and ls \" ; [ src/main.cpp] || ls"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="test"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo


printf "${RED}Precedence integration of test operator${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="((pwd && test src) && (ls ; [ -f Makefile ])) || echo \"after or \""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo


((CASENUM++));
echo "Case $CASENUM"
USERINPUT="(pwd && test noFile) && (ls ; [ -f Makefile ])"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="(pwd && test noFile) || (ls ; [ -f Makefile ])"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

# USERINPUT="exit"
# bin/rshell <<< $USERINPUT
# echo
