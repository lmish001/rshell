#!/bin/bash
# Use tests/io_redir.sh while in rshell directory to run tests 


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

printf "${YELLOW}Please note any \"*****This Test Fails*****\"${REG}"; echo;

printf "${GREEN}Display all test results at once? (Enter Y for 'yes')${REG} \n"
echo
read USERINPUT
if [ $USERINPUT = "Y" ]
    then
        STOP=1;
fi 

printf "${RED}Testing ouput using < , > , and >>:${REG} \n"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo \"Output File 1\" > newOutputFile1 ; cat < newOutputFile1 && echo \" More stuff for Output file 1\" >> newOutputFile1 && cat < newOutputFile1; echo \"Finished task\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo "Case $CASENUM Test Complete"
echo 

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="sort < NE_1.txt && pwd >> newOutputFile1 ; cat < NE_1.txt || ls > NE_1.txt ; echo \"Finished task\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo "Case $CASENUM Test Complete"
echo 

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

printf "${RED}Parentheses:${REG}"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="(echo \"Dog\" > NE_1.txt && pwd >> NE_1.txt) > NE_2.txt && cat < NE_2.txt"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo "Case $CASENUM Test Complete"
echo 

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="(ls ; cat < NE_3.txt && echo \"Dog\" > NE_1.txt && pwd >> NE_1.txt) > NE_2.txt"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo "Case $CASENUM Test Complete"
echo 

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi


