#!/bin/bash
# Use tests/pipe.sh while in rshell directory to run tests 


# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
CASENUM=0
RUN=0
USERINPUT="N"
STOP=0;

RED='\033[0;91m'
GREEN='\033[0;92m'
YELLOW='\033[0;93m'
REG='\033[0m'

rm -rf "pipeCmds.txt"

#sprintf "${YELLOW}Please note any \"*****This Test Fails*****\"${REG}"; echo;\
printf "${RED}Testing ouput for input redirection:${REG} \n"
echo

# printf "${GREEN}Display all test results at once? (Enter Y for 'yes')${REG} \n"
# echo
# read USERINPUT
# if [ $USERINPUT = "Y" ]
#     then
#         STOP=1;
# fi    

printf "${RED}Basic Pipe Usage:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="ls | grep --color "src""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="ps aux | wc -l"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="ls -al | grep '^d'"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Pipe usage with Connectors:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="pwd && ls | grep --color "src""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="ps aux | wc -l; echo \"finished\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="ls -al | grep ^d || echo \"did not execute\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Pipe Chaining:${REG} \n"

echo "Case $CASENUM"
USERINPUT="ls | tr A-Z a-z | tr a-z A-Z"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

echo "Case $CASENUM"
USERINPUT="ls -al | grep \"Feb\" | tr a-z A-Z | tr A-Z a-z"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Parentheses:${REG} \n"
touch TIME.cpp
echo "Case $CASENUM"
USERINPUT="(ls && ps aux) | grep \"TIME\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo


rm -rf "pipeCmds.txt"
rm -rf "TIME.cpp"