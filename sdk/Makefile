# PROGRAM INFORMATION #
SRC		= dlp4500_sdk.cpp
INCLUDE = dlp4500_sdk*.h
OBJ		= $(SRC:.cpp=.o)
TARGET  = libdlp4500sdk.so

# COMPILATION INFORMATION #
CXX		 = g++
CXXFLAGS = -std=gnu++11 -g -fPIC -Wall -ftrapv -pedantic
LDFLAGS	 = -I -L -lhidapi-libusb -lm -shared
RM		 = rm -vf

# INSTALLATION FOLDER
INCLUDE_DIR = /usr/local/include
LIBS_DIR = /usr/local/lib

# COMPILATION ROUTINES #
default: all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJ)

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
