# Target programs
programs := basic.x	\
	half_limit.x	\
	square_start.x

# Default rule
all: $(programs)

# Avoid builtin rules and variables
MAKEFLAGS += -rR

# Don't print the commands unless explicitly requested with `make V=1`
ifneq ($(V),1)
Q = @
V = 0
endif

# Current directory
CUR_PWD := $(shell pwd)

# Define compilation toolchain
CC	= gcc

# General gcc options
CFLAGS	:= -Wall -Werror
CFLAGS	+= -pipe
## Debug flag
ifneq ($(D),1)
CFLAGS	+= -O2
else
CFLAGS	+= -O0
CFLAGS	+= -g
endif

# Linker options
LDFLAGS := -L$(FSPATH) -lfs

# Generate dependencies
DEPFLAGS = -MMD -MF $(@:.o=.d)

src := $(wildcard *.c)
objs := $(src:.c=.o)
deps := $(src:.c=.d)

# Include dependencies
-include $(deps)

# Generic rule for linking final applications
%.x: %.c bitmap.o
	@echo "LD	$@"
	$(Q)$(CC) $(CFLAGS) -o $@ $< bitmap.o $(LDFLAGS)

# Generic object compilation
%.o: %.c
	@echo "CC	$@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $< $(DEPFLAGS)

# Cleaning rule
clean:
	@echo "CLEAN	$(CUR_PWD)"
	$(Q)rm -rf $(objs) $(deps) $(programs)

# Keep bitmap.o around
.PRECIOUS: bitmap.o
.PHONY: clean
