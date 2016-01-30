###############################################################################
# This is where all of the top-level, project-specific information is supplied.

CFLAGS         += -MMD -MP -m64 -Wall -Wpedantic
CXXFLAGS       += $(CFLAGS) -std=c++1y

CFLAGS_DEBUG   += $(CXXFLAGS) -g -ggdb -gstabs
CFLAGS_RELEASE += $(CXXFLAGS) -Ofast -march=corei7 -mtune=corei7

CFLAGS_LIB     += -fPIC

ifdef OPT
    CXXFLAGS_TO_USE = $(CFLAGS_RELEASE)
else
    CXXFLAGS_TO_USE = $(CFLAGS_DEBUG)
endif

CC  := g++
CXX := g++
LD  := g++

LDFLAGS :=
LDFLAGS_LIB := -shared

INSTALL_PREFIX := $(HOME)/tmp

ifeq ($(OS),OSX)
    #LIBXML2_INCLUDE := /opt/local/include/libxml2
    CFLAGS          += -DOS_OSX
else
    #LIBXML2_INCLUDE := /usr/include/libxml2
    CFLAGS          += -DOS_LINUX
endif

# This variable controls whether rule commands are echoed
# or suppressed infavor of more terse log output.
#V ?= YES

###############################################################################
# Dependency info

PARSERSDEFAULT_deps := PARSERS
PARSERS_deps := TOOLS
CASNUMBERDEFAULT_deps := CASNUMBER PARSERS
CASNUMBER_deps := PARSERS

#LIB_deps  := LIB_INT

# This is the location holding the main runnable program
#MAIN_PROGRAM := CMD
