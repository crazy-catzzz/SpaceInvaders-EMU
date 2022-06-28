# Library stuff
RAYLIB_SRC_PATH := ~/raylib/src# REPLACE WITH YOUR RAYLIB PATH
LDFLAGS 		:= -L$(RAYLIB_SRC_PATH) -lm -lraylib -pthread #-lopengl32 -lgdi32 -lwinmm -mwindows

# ooga booga variables
TARGET_NAME	:= SpaceInvaders-EMU
INCLUDE 	:= include
SOURCE		:= source
OUT			:= out

# Source files
CXX_SRC_FILES	:= $(wildcard $(addsuffix /*.cpp ,$(SOURCE)))
CC_SRC_FILES	:= $(wildcard $(addsuffix /*.c ,$(SOURCE)))

all:
	$(CXX) $(CC_SRC_FILES) $(CXX_SRC_FILES) -o $(OUT)/$(TARGET_NAME) -I$(INCLUDE) $(LDFLAGS)