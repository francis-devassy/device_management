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
	$(CC) $(CFLAGS) $(SRCS) -o deviceManagementSystem
#Build debug target debugDeviceManagementSystem
debug: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -g -o debugDeviceManagementSystem
#Run gdb on the binary
gdb: debugDeviceManagementSystem
	gdb ./debugDeviceManagementSystem
#Clean target
clean:
	rm -f deviceManagementSystem
#Delete the data file
del:ls
	rm -f devices.dat