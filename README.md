# Pokemon-Emerald-Battle-Engine-Upgrade

Installation instructions:

1. Download devkitpro. Follow the instructions.
  (Note: you can only install devkitARM)

2. Download the latest version of python(3.5).
  After downloading and before proceeding to install make sure that the 'add to path' checkbox is ticked, otherwise you'll have to add the python path in the environment variables manually.

3. Download the master folder from this github page
  (click 'Clone or Download', then 'Download Zip')

4. Get your ROM, rename it BPEE0.gba and place it the main(master) folder.
  Go to step 5 (in case you are installing for the first time and don't want specify the freespace offset yourself) or otherwise got o step 7,

5. Run the cmd.exe in the main folder and type 'python scripts//make.py'.
  You can do this by typing 'cmd' and hitting enter in the url address or selecting 'run command prompt from here' from right clciking on empty space while holding the shift key

6. Go to step 10 while skipping 7-9. 
  
7. Make the changes in the src files as described below:
  * in the 'insert.py' file in the folder 'scripts' change OFFSET_TO_PUT=0xF00000 to the location you want to insert the Upgrade data (let it be X)
  * in the 'linker.ld' file change 'ORIGIN = 0x08F00000' to X+0x8000000 (for e.g if default=0x1A10000 then ORIGIN = 0x9a10000)

8. Run the cmd.exe in the main folder.

9. In command prompt window, type 'python scripts//build.py', press Enter and then 'python scripts//insert.py', press Enter.

10. A new gba file will appear named as test.gba.
  That is your resultant file.

If you want to create a INI file for PGE:

11. Place a copy of a valid roms.ini in the master folder and in cmd prompt type 'python scripts\PGEinidump.py'.
  A corresponding test.ini will be created for test.gba.
