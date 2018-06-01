Purpose of software:
	Read from a binary file, get practice with signals and hanld multiple children processes.
Author:
	Steven Stapleton Dec 8th
Organization:
	4 Make files each one corresponding to the given task,
	Makefile 1, singlePrime.c, singlePrime.h
	Makefile 2, singleSpawn.c, singleSpawn.h
	Makefile 3, multiSpawn.c, multiSpawn.h
	Makefile 4, multiSpawnSignal.c, multiSpawnSignal.h
Instructions on use and on compilation
	Pick which program you would like to use. type cp Makefile"Number here" Makefile.
	Then type make clean, make to compile program. Type ./programName yourFile.bin.
Limitations
	program are expecting an unsigned int with at least 10 entries. Will not read any more then 10 numbers. Signal should work.
