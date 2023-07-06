import os
import sys

def isElf(flpath) ->  bool:
	with open(flpath, "rb") as f:
		# ELF's files have the first 4 bytes as \x7fELF
		return f.read(4) == "\x7fELF"

def execScript(dirPath):
	files = os.listdir(dirPath)
	# print(files)
	for fl in files:
		pathFile = os.path.join(dirPath, fl)
		# check if it's a path, is exectuable and not and ELF
		if os.path.isfile(pathFile) and os.access(pathFile,os.X_OK) and not isElf(pathFile):
			os.execl(fl, fl)
			print(fl)
	

if __name__ == "__main__":
	# work on current dir
	dirPath = os.getcwd()
	# print(sys.argv)
	if len(sys.argv) > 2:
		print("error: too many arguments")
	elif len(sys.argv) == 2:
		# work on the given dir
		dirPath = sys.argv[1]
		
	execScript(dirPath)

