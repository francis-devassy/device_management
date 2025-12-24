CC = gcc
FLAGS = -Wall

INCLUDES =
INCLUDES += -I./device
INCLUDES += -I./common
INCLUDES += -I./menu
INCLUDES += -I./file

CFLAGS += $(INCLUDES)

SRCS = 
SRCS += main.c
SRCS += device/device.c
SRCS += menu/menu.c
SRCS += file/file.c

main: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o deviceMangaementSystem

clean:
	rm -f deviceMangaementSystem