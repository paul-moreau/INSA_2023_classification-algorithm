from subprocess import os
import subprocess as sp

print('hello world ! ')

command = "classifier.exe -h"
# returnedValue1 = sp.call("make ",shell=True)
# returnedValue2 = sp.call("make clean",shell=True)
returnedValue3 = sp.call(command,shell=True)

print("command = ",command)
print("output = ",returnedValue3)

