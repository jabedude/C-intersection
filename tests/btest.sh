#!/bin/bash

aspell check ../writeup

############### TEST CASE ONE ################
ans1="blow	2
se7en	2
swordfish	2"
out1=$(../intersect passwords.txt movies.txt)

if [ "$out1" == "$ans1" ]
then
        echo "TEST 1: PASS"
else
        echo "TEST 1: FAIL"
fi

############### TEST CASE TWO ################
ans2="Blow	2
Se7en	2
Swordfish	2"
out2=$(../intersect movies.txt passwords.txt)

if [ "$out2" == "$ans2" ]
then
        echo "TEST 2: PASS"
else
        echo "TEST 2: FAIL"
fi

############## TEST CASE THREE ###############
ans3="and	2
blow	2
half	2
hunter2	2
letmein	2
me	2
se7en	2
swordfish	2"
out3=$(../intersect passwords.txt passwords.txt)

if [ "$out3" == "$ans3" ]
then
        echo "TEST 3: PASS"
else
        echo "TEST 3: FAIL"
fi

############## TEST CASE FOUR ################
ans4="cat	3
mat	3
oN	3
The	3"
out4=$(../intersect test1.dat test2.dat test3.dat)

if [ "$out4" == "$ans4" ]
then
        echo "TEST 4: PASS"
else
        echo "TEST 4: FAIL"
fi

############### TEST CASE FIVE ################
ans5="cat	3
mat	3
on	3
THE	3"
out5=$(../intersect test3.dat test1.dat test2.dat)

if [ "$out5" == "$ans5" ]
then
        echo "TEST 5: PASS"
else
        echo "TEST 5: FAIL"
fi

############### TEST CASE SIX ###############
ans6="cat	3
MaT	3
ON	3
The	3"
out6=$(../intersect test2.dat test1.dat test3.dat)

if [ "$out6" == "$ans6" ]
then
        echo "TEST 6: PASS"
else
        echo "TEST 6: FAIL"
fi

############### TEST CASE SEVEN ###############
ans7="mAt	4
oN	4
The	4"
out7=$(../intersect test4.dat test2.dat test1.dat test3.dat)

if [ "$out7" == "$ans7" ]
then
        echo "TEST 7: PASS"
else
        echo "TEST 7: FAIL"
fi

############### TEST CASE EIGHT ###############
ans8="mat	4
on	4
THE	4"
out8=$(../intersect test3.dat test2.dat test4.dat test1.dat)

if [ "$out8" == "$ans8" ]
then
        echo "TEST 8: PASS"
else
        echo "TEST 8: FAIL"
fi
