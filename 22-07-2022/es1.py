import os
import sys


def printFileSystem(path, level):
	files = os.listdir(path)
	for fl in files:
		if os.path.isdir(os.path.join(path, fl)):
			printFile(fl, level)
			printFileSystem(os.path.join(path, fl), level+1)
		else:
			printFile(fl, level)
		
def printFile(fl, level):
	print("\t"*level, fl)

if __name__ == "__main__":
	path = os.sys.argv[1]
	printFileSystem(path, 0)

	
	
	
