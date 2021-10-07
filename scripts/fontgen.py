#!/usr/bin/env python3
# Converts a TTF file to a c file for use with arcticOS.
import sys, os, string, shlex

fontpath = sys.argv[1]
outputfile = sys.argv[2]
size = sys.argv[3]
name = sys.argv[4]

width = size.split("x")[0]
height = size.split("x")[1]
bytesperrow = str(int(int(width) / 8))

output = "int " + name + "[] = {" + bytesperrow + "," + height + ","

output += "\n"
for character in " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~":
    os.system("convert +dither -scale " + size + " -font " + fontpath + " -pointsize 32 label:" + shlex.quote(character) + " temp.xbm")
    with open("temp.xbm") as tempfile:
        contents = tempfile.read()
        character_width = contents.split("\n")[0][19:]
        character_height = contents.split("\n")[1][20:]
        character_bytes = contents.split("{")[1].split("}")[0]
        output += character_width + "," + character_height + "," + character_bytes
output += "0};"

with open(outputfile, "w") as outfile:
    outfile.write(output)
        
