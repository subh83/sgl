# Change these if needed or pass as input parameter
# PREFIX = /usr/local/include

# ================================

# INCLUDE FOLDER
# --------------

ifneq ("$(wildcard /usr/local/include/sgl)","")
    SGL_FOLDER = /usr/local/include
else ifneq ("$(wildcard ../sgl)","")
    SGL_FOLDER = ..
else
	SGL_FOLDER = $(PREFIX)
endif

INC_SGL = -I$(SGL_FOLDER)
INC_LOCAL = -I. -Iinclude

SGL_INTRO_STRING = "Including SGL from '$(SGL_FOLDER)/'\n"

# --------------------------------------------
# common flags

CC = g++
CFLAGS = -std=gnu++11 -O3 -g 
WARNS = -w

LIBS = -lm
LIBS_OPENCV = -lopencv_core -lopencv_highgui -lopencv_imgproc
LIBS_OPENGL = -lglut -lGLU -lGL -lXi -lXmu -lX11 -lXext
LIB_ARMADILLO = -larmadillo

# --------------------------------------------
all: example1 example2


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

