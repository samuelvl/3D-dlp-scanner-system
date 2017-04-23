# PROGRAM INFORMATION #
NAME	= pGenerator
SRC		= main.cpp linux_fbuffer.cpp dlp4500_pattern.cpp dlp4500_driver.cpp
OBJ		= $(SRC:.cpp=.o)

# COMPILATION INFORMATION #
CXX		 = g++
CXXFLAGS = -std=gnu++11 -g -Wall -ftrapv -pedantic
LDFLAGS	 = -I -L -ldlp4500sdk -lm
RM		 = rm -vf

# COMPILATION ROUTINES #
default: all

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

clean:
	$(RM) $(NAME) $(OBJ)

.PHONY: clean
