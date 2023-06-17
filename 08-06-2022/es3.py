import os

def printTable(listStatus):
	value = [".", "."]
	for fl in listStatus:
		with open(fl, "r") as flstat:
			for line in flstat.read().splitlines():
				info = line.split()[0]
				if info == "Name:":
					value[0] = line.split()[1]
				if info == "VmSize:":
					value[1] = line.split()[1]
			print("Name: {:<10}		VmSize: {:<4}".format(value[0], value[1]) )
			
			

if __name__=="__main__":
	# user id del file corrente
	UID = os.getuid()
	# lista di tutti i proc
	allproc = [os.path.join("/proc", p) for p in os.listdir("/proc") if p.isnumeric()]
	allStatus = []
	for p in allproc:
		if os.stat(p).st_uid == UID:
			allStatus.append(os.path.join(p, "status"))
						
	printTable(allStatus)
	
