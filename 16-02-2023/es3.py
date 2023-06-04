import sys 
import os

# total arguments
n = len(sys.argv)
dirpath = sys.argv[1]

try:
    allFiles = [files for files in os.listdir(dirpath) if os.path.isfile(os.path.join(dirpath, files))]
except:
    print("argument passed is wrong!")
    exit()

noCarLine = []

for file in allFiles:
    with open(os.path.join(dirpath, file)) as file2read:
        countLine = 0
        for line in file2read:
            if len(noCarLine) <= countLine:
                noCarLine.append(0)
            
            noCarLine[countLine] = noCarLine[countLine] + len(line)
            countLine += 1

count = 1
for noLines in noCarLine:
    print("line{}: {}".format(count, noLines))

