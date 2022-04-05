#!/bin/python
import random
import time
import sys

def main():
    random.seed(time.time())
    
    csv_file = open("random.csv", "w")
    list_length = int(input("Enter number of random numbers to be included in csv file: "))
    
    if (list_length > 1000000):
        print("Length specified was too long")
    
    for ii in range(list_length):
        csv_file.write("{}".format(random.uniform(-1000000, 1000000)))
        if ii < list_length - 1:
            csv_file.write(",")

if __name__ == "__main__":
    main()
