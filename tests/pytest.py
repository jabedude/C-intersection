#!/usr/bin/env python3
import pexpect

correct_out ='''blow	2
se7en	2
swordfish	2
'''

p = pexpect.spawnu('../intersect passwords.txt movies.txt')
actual_out = p.read()

print(actual_out)
print(correct_out)

if correct_out == actual_out:
    print("CORRECT")
else:
    print("WRONG")
