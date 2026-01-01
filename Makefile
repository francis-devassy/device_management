#Compiler to use
CC = gcc
#Compiler flags
FLAGS = -Wall
#Include directories
INCLUDES =
INCLUDES += -I./device
INCLUDES += -I./common
INCLUDES += -I./menu
INCLUDES += -I./file
CFLAGS += $(INCLUDES)
#Source files
SRCS = 
SRCS += main.c
SRCS += device/device.c
SRCS += menu/menu.c
SRCS += file/file.c
#Build target deviceManagementSystem
main: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -g -o deviceManagementSystem
#Run gdb on the binary
gdb: deviceManagementSystem
	gdb ./deviceManagementSystem
#Clean target
clean:
	rm -f deviceManagementSystem
#Delete the data file
del:ls
	rm -f devices.dat