#!/bin/bash
# Use tests/input_redir.sh while in rshell directory to run tests 


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
printf "${RED}Testing ouput for input redirection:${REG} \n"
echo

printf "${GREEN}Display all test results at once? (Enter Y for 'yes')${REG} \n"
echo
read USERINPUT
if [ $USERINPUT = "Y" ]
    then
        STOP=1;
fi    

printf "${RED}Input Redirection with Existing Files:${REG} \n"
#########################################################
touch newOutputFile1;
touch newOutputFile2;
touch test.cpp;

echo "Output_File_1_is_longer" > newOutputFile1;
echo "A : This is because it contains an extra line :)" >> newOutputFile1;
echo "Output File 2" > newOutputFile2;

echo "#include <iostream>" > test.cpp;
echo "using namespace std;" >> test.cpp;
echo  "int main(){" >> test.cpp;
echo  "string s;" >> test.cpp;
echo "cout << \"Executing ./test.o: \" << endl << endl;" >> test.cpp;
echo "cout << \"Enter a string: \" << endl;" >> test.cpp;
echo "getline(cin, s);" >> test.cpp;
echo "cout << \"String with getline is: \" << endl;" >> test.cpp;
echo "cout << s << endl;" >> test.cpp;
echo  "return 0;" >> test.cpp;
echo "}" >> test.cpp;
g++ test.cpp -o test.o
#########################################################

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="./test.o < newOutputFile1"
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
USERINPUT="./test.o < newOutputFile2"
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
USERINPUT="cat < newOutputFile1"
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
USERINPUT="grep --color \"extra\" < newOutputFile1"
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
USERINPUT="sort < newOutputFile2"
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

printf "${RED}Input Redirection with Non-Existent(NE) Files:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="cat < NE_OutputFile1"
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
USERINPUT="sort < NE_OutputFile2"
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

printf "${RED}Chained Input Redirection${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="./test.o < newOutputFile1 < newOutputFile2"
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
USERINPUT="./test.o < newOutputFile2 < test.cpp < newOutputFile1"
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

printf "${RED}Input Redirection with Connectors:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="sort < newOutputFile1 && echo \"done\""
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
USERINPUT="echo \"In the middle\" ; sort < newOutputFile1 && echo \"done\""
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
USERINPUT="echo \"At the end\" && cat < newOutputFile2 ; sort < newOutputFile1"
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
printf "${YELLOW}*****This Test Fails*****${REG}"; echo;
USERINPUT="rmdir Not_A_Real_Dir || ./test.o < newOutputFile2 && echo \"done done\""
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

printf "${RED}Input Redirection with Parentheses:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
printf "${YELLOW}*****This Test Fails*****${REG}"; echo;
USERINPUT="(sort && cat ; ./test.o) < newOutputFile1"
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
printf "${YELLOW}*****This Test Fails*****${REG}"; echo;
USERINPUT="(cat || sort) < newOutputFile1"
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

printf "${RED}Syntax Errors with <:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="<"
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
USERINPUT="cat < "
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
USERINPUT="cat < newOutputFile1 < sort"
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
USERINPUT="sort < newOutputFile2 < cat < newOutputFile1"
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

rm -rf newOutputFile1
rm -rf newOutputFile2
rm -rf test.cpp
rm -rf test.o