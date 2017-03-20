#!/bin/bash
# Use tests/io_syntax.sh while in rshell directory to run tests 


# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
CASENUM=0

RED='\033[0;91m'
REG='\033[0m'

printf "${RED}Testing ouput for sytax errors:${REG} \n"
echo

printf "${RED}Input Redirection:${REG} \n"

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

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="< file_list.text"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="&& < file_list.text"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo a && < file_list.text"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Output Redirection:${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT=">"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="> NE_OutputFile2"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT=">>"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo a >> NE_OutputFile2 >>"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="command1 | command2 || | command 3 "
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Input and Output Redirection${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="command1 >> command2 << command3 | command4"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo a | echo b > > echo c < command4"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Parentheses and Quotations${REG} \n"

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="(command1 >> command2 <<) command3 | command4"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((++CASENUM))
echo "Case $CASENUM"
USERINPUT="echo a \"| echo b >\" > >> command3 < command4"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

printf "${RED}Done!${REG} \n"

