#!/bin/bash
# Use tests/single_command.sh while in rshell directory to run tests 

echo "Testing ouput for single commands commands:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"

CASENUM=0

((CASENUM++));
echo "Case $CASENUM"
USERINPUT=$'\n'
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT='\0'
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT=" "
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="echo \"testing single commands\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="rmdir case3test_dir"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="pwd"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="ls"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="ls -ca"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="asssds"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="\" \""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="\"\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT=";"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

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
USERINPUT="&&"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT="||"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT=" &&"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT=" ||"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

((CASENUM++));
echo "Case $CASENUM"
USERINPUT=" ;"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case $CASENUM Test Complete"
echo

