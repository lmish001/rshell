#!/bin/bash
# Use tests/commented_command.sh while in rshell directory to run tests 

echo "Testing ouput for commented commands:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
echo "Case 1"
USERINPUT="#Do not ouput this # echo \"See what happens\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 1 Test Complete"
echo

echo "Case 2"
USERINPUT="echo hello && echo hi there # mkdir case4_mult_test"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 2 Test Complete"
echo

echo "Case 3"
USERINPUT="echo this; # echo is && echo a || echo test"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 3 Test Complete"
echo

echo "Case 4"
USERINPUT="#echo a; echo b # echo c; echo d"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 4 Test Complete"
echo

echo "Case 5"
USERINPUT="echo hello ; ls #do not print"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 5 Test Complete"
echo

echo "Case 6"
USERINPUT="echo \"hello#comment#\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 6 Test Complete"
echo

echo "Case 7"
USERINPUT="#"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 7 Test Complete"
echo

echo "Case 8"
USERINPUT="mkdir case7_commented_test && rm -rf case7_commented_test && # echo \" what happens\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 8 Test Complete"
echo

echo "Case 9"
USERINPUT="rm -rf case8_commented_test ; ls  ||# echo \" what happens\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 9 Test Complete"
echo

echo "Case 10"
USERINPUT="echo a ("
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 9 Test Complete"
echo
