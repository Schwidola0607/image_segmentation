# Executable names:
EXE = main
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o util/util.o graph.o edmondkarps.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk