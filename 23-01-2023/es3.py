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

CommonFiles = Files1 & Files2