#!/bin/bash
# Use tests/output_redir.sh while in rshell directory to run tests 


# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
CASENUM=0
RUN=0
USERINPUT="N"
STOP=0;


RED='\033[0;91m'
GREEN='\033[0;92m'
REG='\033[0m'

printf "${RED}Testing ouput with output redirection:${REG} \n"
echo

printf "${GREEN}Deleting file and folder names that are used in the test:${REG}"
echo
rm -rf newOutputFile1;
rm -rf newOutputFile2;
rm -rf NE_OutputFile1;
rm -rf NE_OutputFile2;
rm -rf NE_OutputFile3;
rmdir caseA;

printf "${GREEN}Display all test results at once? (Enter Y for 'yes')${REG} \n"
echo
read USERINPUT
if [ $USERINPUT = "Y" ]
    then
        STOP=1;
fi        

printf "${RED}Output Redirection with Existing Files:${REG} \n"
touch newOutputFile1;
touch newOutputFile2;


((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo \"Output File 1\" > newOutputFile1"
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
USERINPUT="ls >> newOutputFile1"
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
USERINPUT="echo \"Output File 2 is a bit longer\" > newOutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
#cat newOutputFile2;
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
USERINPUT="pwd >> newOutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

printf "${RED}Output Redirection with Non-Existent(NE) Files:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo \"NE_Output File 1 is real!\" > NE_OutputFile1"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="ls >> NE_OutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

printf "${RED}Chained Output Redirection ${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="pwd > newOutputFile1 > newOutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="ls >> newOutputFile1 > newOutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="echo \"burger king\" > newOutputFile2 >> newOutputFile1"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="echo \"wendy's\" >> newOutputFile1 >> newOutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="echo \"WWWWWWendy's\" > newOutputFile1 >> newOutputFile2 > NE_OutputFile3"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

printf "${RED}Output Redirection with Standard Connectors:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo \"Krispy Kreme\" && ls > newOutputFile1"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="pwd || echo \"Jack in the Box\" >> newOutputFile2 && ls"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="echo \"Johnny Rocket's\" > newOutputFile2; cat newOutputFile2; echo \"AMC Movie Theatre\" >> newOutputFile2 || ls;"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="(pwd || echo \"this shouldn't be here\") > newOutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

printf "${RED}Output Redirection using Parentheses:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="(grep \"Case\" tests/output_redir.sh && ls && echo \"done\") > newOutputFile1"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="(mkdir caseA && echo \"made case A\") > newOutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

printf "${RED}Output Redirection using Test${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="test src/main.cpp >> newOutputFile1"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="[ src/main100.cpp ] > newOutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

printf "${RED}Output Redirection using Exit:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="exit > newOutputFile1"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
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
USERINPUT="pwd > newOutputFile2 && exit >> newOutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

if [ $STOP -eq 0 ]
    then
        printf "${GREEN}Press enter to continue${REG}"
        echo
        read RUN
fi

printf "${RED}Output Redirection using Comments:${REG} \n"

printf "${GREEN}Deleting files and folders${REG}"
echo
rm -rf newOutputFile1;
echo "done";

rm -rf newOutputFile2;
echo "done";

rm -rf NE_OutputFile1;
echo "done";

rm -rf NE_OutputFile2;
echo "done";

rm -rf NE_OutputFile3;
echo "done";

rmdir caseA;
echo "done";