# Pokemon-Emerald-Battle-Engine-Upgrade

Installation instructions:
- Download devkitpro.

Follow the instructions.

(Note: you can only install devkitARM)

- Download the latest version of python(3.5).
After downloading and before proceeding to install make sure that the 'add to path' checkbox is ticked, otherwise you'll have to add the python path in the environment variables manually.

- Download the master folder from this github page
(click 'Clone or Download', then 'Download Zip')

- Get your ROM, rename it BPEE0.gba and place it the main(master) folder.

- To decide the offsets where you want to insert the code:

* in the 'linker.ld' file change 'ORIGIN = 0x08F00000' to whatever location you want

* in the 'insert' file in the folder 'scripts' change default=0xF00000 to the same location you used before but without the bus(08-prefix)

- Run the cmd.exe in the main folder.
You can do this by typing 'cmd' and hitting enter in the url address or selecting 'run command prompt from here' from right clciking on empty space while holding the shift key

- In command prompt window, type 'python scripts//build', press Enter and then 'python scripts//insert' or 'python scripts//insert --debug>offsets.txt'(the latter will create a file with all functions and tables' addresses), press Enter.
A new gba file will appear named as test.gba.
That is your resultant file.

If you want to create a INI file for PGE:

- Place a copy of a valid roms.ini in the master folder and in cmd prompt type 'python scripts\PGEinidump'.
A corresponding test.ini will be created for test.gba.
