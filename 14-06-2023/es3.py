import sys
import os

def printTree(dirPath, level):
	for fl in os.listdir(dirPath):
		print("\t"*level, fl)
		if os.path.isdir(os.path.join(dirPath, fl)):
			printTree(os.path.join(dirPath, fl), level+1)


def deletesymlink(directory):
	for dirpath, dirs, files in os.walk(directory):
		for fl in files:
			path = os.path.join(dirpath, fl)
			if os.path.islink(path):
				flpath = os.readlink(path)
				if not flpath.startswith("/"):
					os.remove(path)

if __name__ == "__main__":

	if len(sys.argv)!=2:
		print("invalid number of arguments")
		exit()
	
	if os.path.exists(sys.argv[1]) and os.path.isdir(sys.argv[1]):
		printTree(sys.argv[1], 0)
		deletesymlink(sys.argv[1])
		print("\n\nsymbolic link are deleted\n\n")
		printTree(sys.argv[1], 0)
	else:
		print("the directory " + sys.argv[1] + " doesn't exist")
			
