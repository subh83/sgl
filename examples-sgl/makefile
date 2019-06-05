# Change these if needed or pass as input parameter
# PREFIX = /usr/local

# ================================

# Macros
# ------
PACKAGE_CONFIG = $(if $(shell pkg-config --cflags --libs --silence-errors $(1)), `pkg-config --cflags --libs $(1)` -D__$(1)=1, -D__$(1)=0)

# INCLUDE FOLDER
# --------------

ifneq ("$(wildcard /usr/local/include/sgl)","")
    SGL_INC_FOLDER = /usr/local/include
    INC_SGL=
else ifneq ("$(wildcard ../sgl)","")
    SGL_INC_FOLDER=..
    INC_SGL=-I$(SGL_INC_FOLDER)
else
    SGL_INC_FOLDER = $(PREFIX)/include
    INC_SGL=-I$(SGL_INC_FOLDER)
endif

INC_LOCAL=-I.

# --------------------------------------------

SGL_INTRO_STRING = "Including SGL from '$(SGL_INC_FOLDER)/'\n"

# --------------------------------------------
# common flags

CC = g++
CFLAGS = -std=gnu++11 -O3 -g 
WARNS = -w

LIBS := -lm -pthread
LIBS_OPENGL := `pkg-config --cflags --libs x11 xi gl glu` -lglut
LIB_OPENCV := $(call PACKAGE_CONFIG,opencv) -L/usr/local/share/OpenCV/3rdparty/lib/  # the -L option fixes bug with libippicv
LIB_ARMADILLO := $(call PACKAGE_CONFIG,armadillo)
LIB_PNG := $(call PACKAGE_CONFIG,libpng)

# --------------------------------------------
all: example0 example1 example2


.PHONY: example0
example0:
	@printf "\nNow compiling '$@'...\n"
	@printf $(SGL_INTRO_STRING)
	$(CC) $(CFLAGS) $(WARNS) $(INC_LOCAL) $(INC_SGL) -o $@ $@.cpp $(LIBS) $(LIBS_OPENGL) $(LIB_OPENCV)

.PHONY: example1
example1:
	@printf "\nNow compiling '$@'...\n"
	@printf $(SGL_INTRO_STRING)
	$(CC) $(CFLAGS) $(WARNS) $(INC_LOCAL) $(INC_SGL) -o $@ $@.cpp $(LIBS) $(LIBS_OPENGL)

.PHONY: example2
example2:
	@printf "\nNow compiling '$@'...\n"
	@printf $(SGL_INTRO_STRING)
	$(CC) $(CFLAGS) $(WARNS) $(INC_LOCAL) $(INC_SGL) -o $@ $@.cpp $(LIBS) $(LIBS_OPENGL)

