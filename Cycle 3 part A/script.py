# each question has folder 
# each folder has 5 in1.txt ,in2.txt ,,,in5.txt out1.txt,out2.txt,...,out5.txt
# Structure of folder Asg1 -> 


import sys
import subprocess 
import os
from shutil import copyfile
import os.path
from os import path

W  = "\033[0m"  # white (normal)
#R  = "\033[31m" # red
G  = "\033[32m" # green
R  = "\033[33m" # orange
B  = "\033[34m" # blue
P  = "\033[35m" # purple
hashes=["fcebd8f170cc66722813706436e1f2f4","872facd65c7999fc4be474720ae68f22","a9cf849497fc62391b6faa5e0d6aa2c3","109d0e4aaad01737ec15edc9f65b6fef","d30028b9b449174af860d945f3699b1c"]

program_name = sys.argv[0]
arguments = sys.argv[1:]
count = len(arguments)
if(count<1):
    print("""Usage : Invalid use\n\npython tester.py <pgmname.c> <question_folder>\n\nEg: python tester.py q1""")
    sys.exit(1)
    
folder=arguments[0]

if path.exists(folder) ==False:
    print (R+"Wrong Question Folder"+W)
    sys.exit(1)

#path=pwd
#print("path:",os.path
#print(folder[-2])
for f in os.listdir(os.getcwd()):    
    if not f.startswith("q") and os.path.isdir(f):
        #print(f)
        for subf in os.listdir(f):
            #print("subfile:",subf[-3])
            
            if subf.endswith(".c") and subf[-3]==folder[-1]:
                print("File : " + subf)
                pgmname = f+"/"+subf
                compret=subprocess.call(["gcc", pgmname,"-lm"])

                if compret!=0:
                    #compilation error
                    print (R+"\n\nCompilation Error!!!!.\n\n Not Compiled "+W)
                    #sys.exit()
                    break
                ntestcase=len(os.listdir(folder))/2
                correct=[]
                wrong=[]
                print ("\n")
                FNULL = open(os.devnull, 'w')

                for f in os.listdir(folder):  
                	
                    if f.endswith(".txt") and f.startswith("in"):
                        inputfile=os.path.join(folder, f)
                        copyfile(inputfile, "input.txt")
                        cmd=["./a.out", "<input.txt", ">output.txt"]

                        #Calling the excecuting function
                        os.system("./a.out <input.txt >output.txt")
                        testcaseno=f[-5] # assuming only max 9 testcase 
                        
                        outputf = open(folder+"/out"+testcaseno+".txt","r")
                        outputf1=open("output.txt","r")
                        cortxt=outputf.read()
                        acttxt=outputf1.read()
                        cortxt=cortxt.rstrip()
                        acttxt=acttxt.rstrip()
                        lines=acttxt.split('\n')
                        proctxt=""        
                        for line in lines:
                            proctxt=proctxt+line.rstrip()+"\n"
                        lines=cortxt.split('\n')
                        cotxt=""        
                        for line in lines:
                            cotxt=cotxt+line.rstrip()+"\n"

                        if cotxt==proctxt:
                            print (G+"\tTestcase #{0}: Correct".format(testcaseno)+W)
                            correct.append(testcaseno)
                        else:
                            print (R+"\tTestcase #{0}: Wrong".format(testcaseno)+W)
                            wrong.append(testcaseno)
                            open("checkc.txt","w").write(proctxt)
                            open("checkact.txt","w").write(cotxt)
                correct.sort()
                wrong.sort()
                print(W+"\nCORRECT : "+' '.join([str(v) for v in correct]))
                print("WRONG   : "+' '.join([str(v) for v in wrong]))
                print ("\n\tPassed %d / %d\n" % (len(correct),ntestcase))
