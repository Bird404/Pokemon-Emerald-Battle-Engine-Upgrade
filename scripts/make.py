#!/usr/bin/env python3

import shutil
import os

############
#Options go here.
############

CLEAN_REPOINTED_DATA = True #cleans repointed data if true; leaves it if false
FREE_SPACE = 0xF00001
BUILD_CODE = True #Set to False if you want to modify and run the build/insert scripts manually

#############
#Options end here.
#############

###############
#Functions start here.
###############

def end_hex_zero(number):
	return str(hex(number)).endswith('00')

def align_offset(offset):
	while end_hex_zero(offset) != True:
		offset += 1
	return offset

def find_offset_to_put(rom, needed_bytes, start_loc):
	offset = start_loc
	found_bytes = 0
	while (found_bytes < needed_bytes):
		for i in range (0, needed_bytes):
			rom.seek(offset + i)
			byte = rom.read(1)
			if (byte):
				if (byte != b'\xFF'):
					offset += i + 1
					align_offset(offset)
					found_bytes = 0
					break
				found_bytes += 1
			else:
				return 0
	return offset

def get_pointer(rom, loc):
	rom.seek(loc)
	return int.from_bytes(rom.read(4), byteorder = 'little') - 0x08000000
	
def clear_space(rom, loc, bytes):
	if (CLEAN_REPOINTED_DATA == True):
		rom.seek(loc)
		for i in range(0, bytes):
			rom.write(b'\xFF')
	
def update_ptrs(rom, oldptr, newptr):
	rom.seek(0x0)
	copy = rom.read(0x1E8000)
	copy = copy.replace((oldptr + 0x08000000).to_bytes(4, byteorder = 'little'), (newptr + 0x08000000).to_bytes(4, byteorder = 'little'))
	rom.seek(0x0)
	rom.write(copy)

def repoint_table(rom, table_address, bytes, offset, name):
	rom.seek(table_address)
	to_copy = rom.read(bytes)
	clear_space(rom, table_address, bytes)
	rom.seek(offset)
	rom.write(to_copy)
	save_table_ptrs(name, offset, 0)
	update_ptrs(rom, table_address, offset)
	offset += bytes
	return offset

def replace_word(file, to_search, replacement):
	get = 0
	break_loop = 0
	to_replace = to_search + " "
	file.seek(0x0)
	for line in file:
		if (break_loop == 1):
			break
		for word in line.split():
			if (word == to_search):
				get = 1
			elif (get == 1):
				to_replace += word
				break_loop = 1
				break
	file.seek(0x0)
	copy = file.read()
	copy = copy.replace(to_replace, to_search + " " + replacement)
	file.seek(0x0)
	file.write(copy)
		
def build_insert_code(offset, only_build):
	linker = open("linker.ld", 'r+')
	replace_word(linker, '+', hex(offset) + "),")
	linker.close()
	if only_build == True:
		os.system("python scripts//build.py")
		return
	else:
		os.system("python scripts//build.py")
		insert = open("scripts//insert.py", 'r+')
		replace_word(insert, "at',", "default=" + hex(offset) + ')')
		insert.close()
		os.system("python scripts//insert.py --debug>function_offsets.ini")
		return

##############
#Functions end here.
##############
		
shutil.copyfile("BPEE0.gba", "test.gba")
with open("test.gba", 'rb+') as rom:

###############
#Add your code here.
###############



###############
#End your code here.
###############

		offset = align_offset(FREE_SPACE)
		if BUILD_CODE == True:
			build_insert_code(offset, True)
			offset = find_offset_to_put(rom, os.stat("build//output.bin").st_size, align_offset(FREE_SPACE))
			if offset == 0:
				print("Not enough free space to insert code")
			else:
				build_insert_code(offset, False)
rom.close()
