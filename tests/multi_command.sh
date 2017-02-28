#!/bin/bash
# Use tests/multi_command.sh while in rshell directory to run tests 

echo "Testing ouput for multiple commands:"
echo

# The last prompt "username@machinename$" is just a text prompt. rshell will break after it is printed.
# No command will be executed between the last prompt to "Case [#] Test Complete"
echo "Case 1"
USERINPUT="ls; echo \"hello\"&&asd || mkdir hello ; git status && rmdir hello"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 1 Test Complete"
echo

echo "Case 2"
USERINPUT="ls -a; echo hello ; mkdir case2_mult_test;"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 2 Test Complete"
echo

echo "Case 3"
USERINPUT="asd || echo \"hi there\" && rmdir case3_mult_test; rmdir case2_mult_test; echo last #testing commands"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 3 Test Complete"
echo

echo "Case 4"
USERINPUT="la || echo next"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 4 Test Complete"
echo

echo "Case 5"
USERINPUT="ls && echo hi there ; rmdir notadirectory || echo world"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 5 Test Complete"
echo

echo "Case 6"
USERINPUT="echo this; echo is || echo a && echo test"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 6 Test Complete"
echo

echo "Case 7"
USERINPUT="rmdir case3_mult_test && rmdir case4_mult_test; rmdir case5_mult_test || echo \"could not remove non-existant directory\""
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 7 Test Complete"
echo

echo "Case 8"
USERINPUT="ls -a; echo hello && mkdir test || echo world; git status && rmdir test;"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 8 Test Complete"
echo

echo "Case 9"
USERINPUT="echo next command ; pwd # comment"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 9 Test Complete"
echo

echo "Case 10"
USERINPUT="ls ;"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 10 Test Complete"
echo

echo "Case 11"
USERINPUT="echo this && ;"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 11 Test Complete"
echo

echo "Case 12"
USERINPUT="echo \"hello && echo \"world && rm -rf case2_mult_test"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 12 Test Complete"
echo

# PARENTHESES
echo "Case 13"
USERINPUT="(echo \"hello && echo \"world) && rm -rf case2_mult_test"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 13 Test Complete"
echo

echo "Case 14"
USERINPUT="echo a && echo b || (echo c && echo d)"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 14 Test Complete"
echo

echo "Case 15"
USERINPUT="(echo a && echo b) || (echo c && echo d)"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 15 Test Complete"
echo

echo "Case 16"
USERINPUT="echo a && (echo b || (echo c && echo d))"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 16 Test Complete"
echo

#Wrong Number of Parentheses
echo "Case 17"
USERINPUT="(echo a && (echo b || (echo c && echo d))"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 17 Test Complete"
echo

echo "Case 18"
USERINPUT="echo a && (echo b || (echo c) && echo d))"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 18 Test Complete"
echo

#Parentheses and Quotations
echo "Case 19"
USERINPUT="(echo \"a && echo b\") || echo c && echo d"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 19 Test Complete"
echo

echo "Case 20"
USERINPUT="echo \"a && (echo b || echo c)\" && echo d"
echo "Input: $USERINPUT"
echo "Output:"
echo
bin/rshell <<< $USERINPUT
echo
echo "Case 20 Test Complete"
echo

