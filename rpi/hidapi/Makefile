# PROGRAM INFORMATION #
SRC		= hidapi.c
INCLUDE = hidapi.h
OBJ		= $(SRC:.c=.o)
TARGET  = libhidapi-libusb.so

# COMPILATION INFORMATION #
CC		 = gcc
CFLAGS	 = -std=c11 -g -fPIC -Wall -w -ftrapv -pedantic
LDFLAGS	 = -I -L `pkg-config libusb-1.0 --libs` -lrt -lpthread -shared
RM		 = rm -vf

# INSTALLATION FOLDER
INCLUDE_DIR = /usr/local/include
LIBS_DIR = /usr/local/lib

# COMPILATION ROUTINES #
default: all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJ)

install:
	cp $(INCLUDE) $(INCLUDE_DIR)
	cp $(TARGET) $(LIBS_DIR)
	ln -sf $(LIBS_DIR)/$(TARGET) $(LIBS_DIR)/$(TARGET).0
	ln -sf $(LIBS_DIR)/$(TARGET).0 $(LIBS_DIR)/$(TARGET).1

uninstall:
	rm $(INCLUDE_DIR)/$(INCLUDE)
	rm $(LIBS_DIR)/$(TARGET)*

clean:
	$(RM) $(TARGET) $(OBJ)

.PHONY: install clean
