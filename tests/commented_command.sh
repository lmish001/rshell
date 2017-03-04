#!/bin/bash
# Use tests/commented_command.sh while in rshell directory to run tests 

echo "Testing ouput with comments:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
CASENUM=0
RED='\033[0;91m'
REG='\033[0m'

printf "${RED}Testing comments after parentheses${REG} \n"

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="( echo a && echo b ) && (echo c && echo d) #hello"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="((echo a && echo b) && (echo c && echo d)) #echo \"this is a comment\" && ls"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Syntax errors${REG} \n"

((CASENUM++))
echo "Case $CASENUM"
USERINPUT="(echo a && echo b # stop)"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="(echo a # stop) && echo b)"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="((echo a # stop) && echo b)"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

