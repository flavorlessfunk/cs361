DIR=${PWD}
ASST=$(notdir ${DIR})
MAINPROG=spellcheck
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
CPPS=correction.cpp edit1.cpp replacement.cpp replchoices.cpp soundex.cpp spellcheck.cpp token.cpp wordoccurrence.cpp
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



%.d: %.c
	touch $@
%.d: %.cc
	touch $@
%.d: %.C
	touch $@
%.d: %.cpp
	touch $@

DEPENDENCIES = $(OBJS:.o=.d)

# 
# Targets:
# 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)

clean:
	-rm -f $(TARGET) $(OBJS) $(DEPENDENCIES) make.dep


make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > make.dep

include make.dep


########################################################################
#
#  Advanced notes:  managing multiple programs with one makefile
#
#    If you want to create 2 or more programs (usually in the same directory)
#    using a single makefile, do the following:
#
#      1) For each program that you want to build, make distinct copies of
#         the TARGET= and OBJS= lines, adding a number to distinguish each.
#         For example:
#              TARGET1=myprogram1
#              TARGET2=myprogram2
#              OBJS1=mymain1.o foo.o bar.o
#              OBJS2=mymain2.o foo.o baz.o
#      2) Redefine TARGET and OBJS as the combination of the TARGETi and 
#         OBJSi lists.  For example,
#              TARGET=$(TARGET1) $(TARGET2)
#              OBJS=$(OBJS1) $(OBJS2)
#      3) In the "Dependencies:" area near the end of the file, find
#         the lines
#           $(TARGET): $(OBJS)
#       	$(LINK) $(FLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)
#         and, as in step 1, make distinct, numbered copies for each program
#         you want to build.  For example,
#           $(TARGET1): $(OBJS1)
#       	$(LINK) $(FLAGS) -o $(TARGET1) $(OBJS1) $(LFLAGS)
#           $(TARGET2): $(OBJS2)
#       	$(LINK) $(FLAGS) -o $(TARGET2) $(OBJS2) $(LFLAGS)
#         These copies replace the original 2 lines.
#
########################################################################
#  Changes: 
#     6/4/96  Fixes to allow use under both "standard" Sun "make" and under
#             the GNU make.
#             Added notes on building multiple targets.
