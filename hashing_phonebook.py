class Hashing:
    def __init__(self):
        self.M = int(input("Enter Size of Table = "))
        self._hashTable = [-1]*self.M
        
    def insert(self, telNum):
        self.index = (telNum)%(self.M)
        if(self._hashTable[self.index]==-1):
            self._hashTable[self.index] = telNum
            print("%d inserted at %d"%(telNum, self.index))
        else:
            self.opt = int(input("Collision Occurred, choose a method to handle it,\n1)Linear Probing.\n2)Quadratic Probing.\n Your Choice = "))
            if(self.opt==1):
                self.linearProbing(telNum)
            elif(self.opt==2):
                self.quadraticProbing(telNum)
            else:
                print("Choose Wisely")
   # Way 1 for defining probing             
#    def linearProbing(self, telNum):
#         i = 1
#         while((self.index+i)%self.M!=self.index):
#                 if(self._hashTable[(self.index+i)%self.M]==-1):
#                         self._hashTable[(self.index+i)%self.M] = telNum;
#                         return i;
#                 i += 1
#         else:
#             print("Record Insertion Failed")
            
#     def quadraticProbing(self, telNum):
#         i = 1
#         while((self.index+i**2)%self.M!=self.index):
#                 if(self._hashTable[(self.index+i**2)%self.M]==-1):
#                         self._hashTable[(self.index+i**2)%self.M] = telNum;
#                         return i;
#                 i += 1
#         else:
#             print("Record Insertion Failed")
            
    def linearProbing(self, telNum):
        for i in range(1,self.M):
            self.index = (telNum + i)%(self.M)
            if(self._hashTable[self.index] == -1):
                #Here we just insert chain manipulating code
                self._hashTable[self.index] = telNum
                print("%d inserted at index %d"%(telNum, self.index))
                break
        else:
            print("Record Insertion Failed")
            
    def quadraticProbing(self, telNum):
        for i in range(1,self.M):
            self.index = (telNum + i**2)%(self.M)
            if(self._hashTable[self.index] == -1):
                self._hashTable[self.index] = telNum
                print("%d inserted at index %d"%(telNum, self.index))
                break
        else:
            print("Record Insertion Failed")
            
    def search(self, telNum):
        self.count = 1
        for i in range(self.M):
            self.index = (telNum + i)%(self.M)
            if(self._hashTable[self.index] == telNum):
                print("%d found at index %d"%(telNum, self.index))
                print("%d comparisons required"%(self.count))
                break
            else:
                self.count += 1
        else:
            print("Sorry, Record not found")
            
    def display(self):
        print("\nINDEX\tTELEPHONE NUMBER")
        for i in range(self.M):
            print("  %d --->  %d"%(i,self._hashTable[i]))
            
phoneBook = Hashing()
while(True):
    opt = int(input("\n_-_-_-_-_-_-_-_-_-_-_-_-_ MENU _-_-_-_-_-_-_-_-_-_-_-_-_\n1)Insert a Data.\n2)Display Record.\n3)Search Record.\n4)EXIT.\n Enter Your Choice = "))
    if(opt==1):
        key = int(input("Enter Telephone Number = "))
        phoneBook.insert(key)
    elif(opt==2):
        phoneBook.display()
    elif(opt==3):
        key = int(input("Enter Telephone Number = "))
        phoneBook.search(key)
    elif(opt==4):
        break
    else:
        print("Invalid Option")
