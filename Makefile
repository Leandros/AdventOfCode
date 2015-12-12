CC			= gcc
CXX			= g++

CFLAGS		=
LDFLAGS		=
CXXFLAGS	= -std=c++11

RM			= rm
RMFLAGS		= -f

SRCS_C		= day1.c day2.c day4.c day5.c day6.c
OBJS_C		= $(SRCS_C:.c=.o)
EXEC_C		= $(SRCS_C:.c=)
SRCS_CXX	= day3.cpp
OBJS_CXX	= $(SRCS_CXX:.cpp=.o)
EXEC_CXX	= $(SRCS_CXX:.cpp=)

.PHONY: clean

all: day1 day2 day3 day4 day5 day6

day1: day1.o
	$(CC) $(CFLAGS) -o day1 $<

day2: day2.o
	$(CC) $(CFLAGS) -o day2 $<

day3: day3.o
	$(CXX) $(CXXFLAGS) -o day3 $<

day4: day4.o
	$(CC) $(CFLAGS) -lcrypto -o day4 $<

day5: day5.o
	$(CC) $(CFLAGS) -o day5 $<

day6: day6.o
	$(CC) $(CFLAGS) -o day6 $<

clean:
	$(RM) $(RMFLAGS) $(OBJS_C) $(OBJS_CXX)
	$(RM) $(RMFLAGS) $(EXEC_C) $(EXEC_CXX)
