# Executable names:
EXE = main

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o util/util.o graph.o 

# Use the cs225 makefile template:
include cs225/make/cs225.mk