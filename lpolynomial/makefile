DIR=${PWD}
ASST=$(notdir ${DIR})
MAINPROG=polytest
ifneq (,$(findstring MinGW,$(PATH)))
DISTR=MinGW
EXE=.exe
LFLAGS=
else
DISTR=Unix
EXE=
LFLAGS=
endif
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
CPPFLAGS=-g -Wall -Wextra -I. -D$(DISTR) -std=c++11
CFLAGS=-g
TARGET=$(MAINPROG)$(EXE)
CPPS=polytest.cpp polynomial.cpp
LINK=g++ $(CPPFLAGS)
#
CC=gcc
CPP=g++
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


OBJS=$(CPPS:%.cpp=%.o)
DEPENDENCIES = $(CPPS:%.cpp=%.d)



%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -MMD -o $@ -c $*.cpp

%.o: %.cc
	$(CPP) -g -I. -o $@ -c $*.cc

# 
# Targets:
# 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)

test: polynomial.o testPolynomial.o gtest/gtest_main.o gtest/gtest-all.o
	$(LINK) $(FLAGS) -o $@  $^ -pthread




clean:
	-/bin/rm -f *.d *.o $(TARGET)



make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@

include make.dep
