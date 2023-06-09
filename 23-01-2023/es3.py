import os
import sys

dir3 = "terzaDir"
dir4 = "quartaDir"
curPath = os.getcwd()

# creo le dir3 e dir4 nella dir corrente
os.mkdir(os.path.join(curPath, dir3))
os.mkdir(os.path.join(curPath, dir4))

dirpath1 = sys.argv[1]
dirpath2 = sys.argv[2]

Files1 = [files for files in os.listdir(dirpath1) if os.path.isfile(os.path.join(dirpath1, files))]
Files2 = [files for files in os.listdir(dirpath2) if os.path.isfile(os.path.join(dirpath2, files))]

CommonFiles = [files for files in Files1 if files in Files2]

for file in CommonFiles:
    with open(os.path.join(os.path.join(curPath, dir3), file), "x") as f:
         with open(os.path.join(dirpath1, file), "r") as f2c:
             f.write(f2c.read())

for file in CommonFiles:
    with open(os.path.join(os.path.join(curPath, dir4), file), "x") as f:
         with open(os.path.join(dirpath2, file), "r") as f2c:
             f.write(f2c.read())

