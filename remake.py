#-*-encoding:utf-8-*-

import csv

c = open('dearMao.txt', "w")

with open("coordinate(2).csv", "r") as f:
    reader = csv.reader(f)
    for row in reader:
        c.write(row[0])
        c.write('\n')
        c.write(row[1])
        c.write('\n')
        c.write(row[2])
        c.write('\n')
        c.write(row[3])
        c.write('\n')
        c.write(row[4])
        c.write('\n')
        c.write(row[5])
        c.write('\n')

