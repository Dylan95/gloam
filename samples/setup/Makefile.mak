#usage: make -f Makefile.mak all



#configure the shell
#if you're using windows, you can install cygwin to use bash.
SHELL:=bash
SCRIPT_RECURSIVE_INCLUDE = buildScripts/recursiveInclude.sh



#some directories
SRC_DIR := src
BUILD_DIR := build
#
DEPS_DIR := $(BUILD_DIR)/deps
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
GENERATED_INCLUDE_DIR := $(BUILD_DIR)/generatedInclude
#
#binary name
BIN := $(BIN_DIR)/openglProject
#
GENERATED_INCLUDE_RECURSIVE := $(GENERATED_INCLUDE_DIR)/includeDirs_recursive.txt
GENERATED_INCLUDE_ALL := $(GENERATED_INCLUDE_DIR)/includeDirs_all.txt




CONFIGURATION := ./buildConfig/DEBUG
#CONFIGURATION := ./buildConfig/DEBUG
#CONFIGURATION := ./buildConfig/E_FENCE_DEBUG
#
#files that describe include directories.
#the CONFIG_INCLUDE can be modified, but the other's should be left alone, 
#because they're generated by the makefile. 
CONFIG_INCLUDE := $(CONFIGURATION)/includeDirs.txt
#
#other config files
CONFIG_LIB_DIRS := $(CONFIGURATION)/libDirs.txt
CONFIG_LIBS := $(CONFIGURATION)/libs.txt
#
CONFIG_CFLAGS := $(CONFIGURATION)/cflags.txt
CONFIG_LFLAGS := $(CONFIGURATION)/lflags.txt
#
CONFIG_CLANG_COMPLETE := $(CONFIGURATION)/clang_complete/config.txt
#
#a file for the vim "clang_complete" plugin, used for c++ autocompletion
CLANG_COMPLETE := .clang_complete






#only works on unix systems
#INCLUDE_RECURSIVE = $(shell bash $(SCRIPT_RECURSIVE_INCLUDE))
#INCLUDE_FILE = $(shell cat $(CONFIG_INCLUDE))
#INCLUDE_DIRS = $(INCLUDE_RECURSIVE)$(INCLUDE_FILE)
INCLUDE_DIRS = $(shell cat $(GENERATED_INCLUDE_ALL)) #updates every time make runs
#
LIB_DIRS = $(shell cat $(CONFIG_LIB_DIRS))
#
LIBS = $(shell cat $(CONFIG_LIBS))
#
CFLAGS = $(shell cat $(CONFIG_CFLAGS))
LFLAGS = $(shell cat $(CONFIG_LFLAGS))



#c compiler
#CC = gcc 
#g++ 6.1.1 20160511
CC = g++-6



#all source files, ex: "src/main.cpp src/util.cpp"
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))




#rules:

all: $(CLANG_COMPLETE) $(BIN)

$(CLANG_COMPLETE): $(GENERATED_INCLUDE_ALL) $(CONFIG_CFLAGS)
	cat $(CONFIG_CLANG_COMPLETE) > $(CLANG_COMPLETE)
	cat $(GENERATED_INCLUDE_ALL) >> $(CLANG_COMPLETE)
	echo '' >> $(CLANG_COMPLETE)
	cat $(CONFIG_CFLAGS) >> $(CLANG_COMPLETE)
	
$(GENERATED_INCLUDE_ALL): config_include_recursive_update $(GENERATED_INCLUDE_RECURSIVE) $(CONFIG_INCLUDE)
	cat $(CONFIG_INCLUDE) > $(GENERATED_INCLUDE_ALL)
	cat $(GENERATED_INCLUDE_RECURSIVE) >> $(GENERATED_INCLUDE_ALL)

config_include_recursive_update:
	$(SHELL) $(SCRIPT_RECURSIVE_INCLUDE) > $(GENERATED_INCLUDE_RECURSIVE)

$(CONFIG_INCLUDE):
$(CONFIG_LIB_DIRS):
$(CONFIG_LIBS):
$(CONFIG_CFLAGS):
$(CONFIG_LFLAGS):
$(CONFIG_CLANG_COMPLETE):



#link
$(BIN): $(OBJS) $(CONFIG_LFLAGS) $(CONFIG_LIB_DIRS) $(CONFIG_LIBS)
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN) $(LIB_DIRS) $(LIBS)

# compile pattern rule, aka implicit rule, doesn't say which files it applies to.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(CONFIG_CFLAGS)
	$(CC) $(INCLUDE_DIRS) -c -o $@ $< $(CFLAGS)
	$(CC) $(INCLUDE_DIRS) -M -MT $@ -MP $(CFLAGS) $< > $(DEPS_DIR)/$*.d



# remove compilation products
clean:
	rm $(OBJ_DIR)/*.o
	rm $(BIN)
	rm $(DEPS_DIR)/*.d
	echo '' > .clang_complete
	echo '' > $(GENERATED_INCLUDE_RECURSIVE)
	echo '' > $(GENERATED_INCLUDE_ALL)



#dependancies:

#DEPS = $(wildcard deps/*.d)
DEPS = $(wildcard $(DEPS_DIR)/*.d)
include $(DEPS)








