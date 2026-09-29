##############################################################################################################
#  _  ___   ____  __    _____         _ _  ___ _   
# | \| \ \ / /  \/  |__|_   _|__  ___| | |/ (_) |_ 
# | .` |\ V /| |\/| / -_)| |/ _ \/ _ \ | ' <| |  _|
# |_|\_| \_/ |_|  |_\___||_|\___/\___/_|_|\_\_|\__|
#                                                              
# MIT License
# 
# Copyright (c) 2026 Eric L. Yang
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# 
# https://github.com/elyyang
# elyyang@gmail.com
#
##############################################################################################################

TARGET = nvmeToolKit
VERBOSE = FALSE
RUN = FALSE
SOURCE_NAME = app drv lib
UTIL_NAME = general menu prbs
TEST_NAME = sample mock unit

##############################################################################################################

# paths
PROJECT_ROOT := $(realpath ./)
SOURCE_ROOT := $(PROJECT_ROOT)/src
UTIL_ROOT := $(PROJECT_ROOT)/util
TEST_ROOT := $(PROJECT_ROOT)/test

SOURCE_DIRS = $(foreach index, $(SOURCE_NAME), $(addprefix $(SOURCE_ROOT)/, $(index)))
UTIL_DIRS = $(foreach index, $(UTIL_NAME), $(addprefix $(UTIL_ROOT)/, $(index)))
TEST_DIRS = $(foreach index, $(TEST_NAME), $(addprefix $(TEST_ROOT)/, $(index)))

BUILD_DIR = $(PROJECT_ROOT)/build

#includes
INCLUDES =  $(addprefix -I , $(SOURCE_ROOT)/include)
INCLUDES += $(foreach index, $(SOURCE_DIRS), $(addprefix -I , $(index)/include))
INCLUDES += $(foreach index, $(TEST_DIRS), $(addprefix -I , $(index)/include))
INCLUDES += $(foreach index, $(UTIL_DIRS), $(addprefix -I , $(index)/include))

# add this list to VPATH, the place make will look for the source files
VPATH = $(SOURCE_DIRS)
VPATH += $(TEST_DIRS)
VPATH += $(UTIL_DIRS)

# sources
SOURCES = $(PROJECT_ROOT)/main.cpp
SOURCES += $(foreach index, $(SOURCE_DIRS), $(wildcard $(index)/*.cpp $(index)/*.c))
SOURCES += $(foreach index, $(TEST_DIRS), $(wildcard $(index)/*.cpp $(index)/*.c))
SOURCES += $(foreach index, $(UTIL_DIRS), $(wildcard $(index)/*.cpp $(index)/*.c))

##############################################################################################################

# defines (if any)
DEFINES = 	-D ENABLE_DEBUG_MSG=1
DEFINES +=	-D ENABLE_ASSERT_LIB=1

##############################################################################################################

# Compiler
CC = g++
#CC = clang++

# Compile Flags
CFLAGS =	-std=c++2a
CFLAGS += 	-Wall
CFLAGS += 	-Werror
CFLAGS += 	-Wextra
CFLAGS +=	-g
CFLAGS +=	-x c++    # compile .c sources as C++ (matches g++ behavior, silences clang deprecation)

##############################################################################################################

# helpers
RM = rm -rf
RMDIR = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null
SEP = /

# Remove space after separator
PSEP = $(strip $(SEP))

# Verbosity
ifeq ($(VERBOSE),TRUE)
HIDE =
else
HIDE = @
endif


ifeq ($(RUN),TRUE)
POST_BUILD = $(BUILD_DIR)$(PSEP)$(TARGET)
else
POST_BUILD =
endif

##############################################################################################################

all: clean dir $(TARGET)
	@echo "Done" $@
	$(HIDE)$(POST_BUILD)

$(TARGET):
	@echo "[Building...]"
	$(HIDE)$(CC) $(CFLAGS) $(DEFINES) $(SOURCES) $(INCLUDES) -o $(BUILD_DIR)$(PSEP)$(TARGET)

dir:
	@echo "[Create Build Directory...]"
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(BUILD_DIR)) $(ERRIGNORE)
	@echo "Done" $@

clean:
	@echo "[Cleaning...]"
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(BUILD_DIR)) $(ERRIGNORE)
	$(HIDE)$(RM) $(TARGET) $(ERRIGNORE)
	@echo "Done" $@

debug:
	@echo "SOURCES"
	@echo $(SOURCES)
	@echo "INCLUDES"
	@echo $(INCLUDES)	
	@echo "SOURCES DIRS"
	@echo $(SOURCE_DIRS)	
	@echo "Done" $@