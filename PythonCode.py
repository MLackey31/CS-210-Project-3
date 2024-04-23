import re
import string

# Opens and Reads Input File
grocery_items = dict()
input_file = open("CS210_Project_Three_Input_File.txt", "r")
for line in input_file:
    line = line.strip()
    words = line.split(" ")
    for word in words:
        if word in grocery_items:
            grocery_items[word] = grocery_items[word] + 1
        else:
            grocery_items[word] = 1
input_file.close()

# Prints item and quantity
def printItemCount():
    print("\nQUANTITY OF EACH ITEM PURCHASED TODAY\n")
    for item in list(grocery_items.keys()):
        print(item, end = "")
        print(":", grocery_items[item])
    print()

# Prints user item
def printCount(userItem):
    userItem = userItem.capitalize()
    for item in list(grocery_items.keys()):
        if (userItem == item):
            return grocery_items[item]
    return 0

def createFile(fileName):
    input_file = open(fileName, "w")
    for item in list(grocery_items.keys()):
        input_file.write("\n" + item + " " + str(grocery_items[item]))
    input_file.close()
    return 0