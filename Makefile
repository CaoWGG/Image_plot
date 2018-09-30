VPATH=./src/:./examples
EXEC=main
OBJDIR=./obj/

CC=gcc
CPP=g++
OPTS=-Ofast
LDFLAGS= -lm -pthread 
COMMON=-Iinclude/ -Isrc/
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC

CFLAGS+=$(OPTS)

COMMON+= -DOPENCV
CFLAGS+= -DOPENCV
LDFLAGS+= `pkg-config --libs opencv` -lstdc++
COMMON+= `pkg-config --cflags opencv` 

OBJS= image.o main.o

EXECOBJ = $(addprefix $(OBJDIR), $(OBJS))

DEPS = $(wildcard src/*.hpp) Makefile include/afx.hpp

$(OBJDIR)%.o: %.cpp $(DEPS)
	$(CPP) $(COMMON) $(CFLAGS) -c $< -o $@

$(EXEC): $(EXECOBJ)
	$(CPP) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS)


obj:
	mkdir -p obj

.PHONY: clean

clean:
	rm -rf $(EXEC) $(EXECOBJ) $(OBJDIR)/*
