f = open('execution_order_check.txt')
lines = f.readlines()
f.close()
child_parent = 0
parent_child = 0
invalid_order = 0
print "Evaluating results"

for i in range(0,len(lines),2):
	if(lines[i] == "child \n" and lines[i+1] == "parent \n"):
		child_parent+=1
	elif(lines[i+1] == "child \n" and lines[i] == "parent \n"):
		parent_child+=1
	else:
		invalid_order+=1
print "################ results ##################"
print "child first exectued : " + str(child_parent) + " times"
print  "parent first : " + str(parent_child) + " times"
print "invalid order of execution (printed child child or parent parent) : " + str(invalid_order) + " times"