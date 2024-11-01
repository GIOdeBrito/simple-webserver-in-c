
# =========================================================
# Makefile for the WebServer
# =========================================================

COMPILER = gcc
CFLAGS = -Wall
HEADER = global.h

SOURCE = server.c request.c utility.c

# Object files
OBJ_DIR = objects
_OBJ = $(patsubst %.c, %.o, $(SOURCE))
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))

# Name of the executable
PROJECT = server.g2

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(COMPILER) -c -o $@ $< $(CFLAGS)

$(PROJECT): $(OBJ)
	$(COMPILER) -o $@ $^ $(CFLAGS)






