#!/bin/bash
# Use tests/single_command.sh while in rshell directory to run tests 

echo "Testing ouput for single commands commands:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
echo "Case 1"
USERINPUT=$'\n'
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 1 Test Complete"
echo

echo "Case 2"
USERINPUT=" "
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 2 Test Complete"
echo

echo "Case 3"
USERINPUT="echo \"testing single commands\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 3 Test Complete"
echo

echo "Case 4"
USERINPUT="rmdir case3test_dir"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 4 Test Complete"
echo

echo "Case 5"
USERINPUT="pwd"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 5 Test Complete"
echo

echo "Case 6"
USERINPUT="ls"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 6 Test Complete"
echo

echo "Case 7"
USERINPUT="ls -ca"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 7 Test Complete"
echo

echo "Case 8"
USERINPUT="asssds"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 8 Test Complete"
echo

echo "Case 9"
USERINPUT="\" \""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 9 Test Complete"
echo

echo "Case 10"
USERINPUT="\"\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 10 Test Complete"
echo

echo "Case 11"
USERINPUT=";"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 11 Test Complete"
echo

echo "Case 12"
USERINPUT="exit"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 12 Test Complete"
echo

echo "Case 13"
USERINPUT="&&"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 13 Test Complete"
echo

echo "Case 14"
USERINPUT="||"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 14 Test Complete"
echo

echo "Case 15"
USERINPUT="&"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 15 Test Complete"
echo

echo "Case 16"
USERINPUT="|"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 16 Test Complete"
echo