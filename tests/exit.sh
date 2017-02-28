#!/bin/bash
# Use tests/exit.sh while in rshell directory to run tests 

echo "Testing ouput for exit commands:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
echo "Case 1"
USERINPUT="echo exit after or || exit; echo \" passed \""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 1 Test Complete"
echo

echo "Case 2"
USERINPUT="ehoc double && exit; echo \"passed\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 2 Test Complete"
echo

echo "Case 3"
USERINPUT="echo this; #exit && echo \"failure\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 3 Test Complete"
echo

echo "Case 4"
USERINPUT="exit || echo \"Did not execute\" && echo \"Test failed\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 4 Test Complete"
echo

echo "Case 5"
USERINPUT="echo hello && ls #do not print; exit"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 5 Test Complete"
echo

echo "Case 6"
USERINPUT="mkdir exit_case_6 && ls || echo \"ls failed\" && exit"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 6 Test Complete"
echo

echo "Case 7"
USERINPUT="echo hello && ls do not print || EXIT; echo test in progress && exit || echo exit failed"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 7 Test Complete"
echo

echo "Case 8"
USERINPUT="rm -rf exit_case_6 || echo test in progress || exit || echo \"exit did not execute\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 8 Test Complete"
echo



