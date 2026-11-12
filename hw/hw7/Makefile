# CSE 220 Homework 7
#
#   make           build the test runner and the auxiliary programs
#   make test      build if needed, then run every graded test
#   make valgrind  run the valgrind checks, which are graded this time
#   make clean     remove build/, bin/, tests.out/
#
# Criterion is found through pkg-config when it is installed that way, which
# covers the CodeGrade terminal and a Homebrew install on macOS. If pkg-config does
# not know about it, plain -lcriterion is used instead.

CC := gcc

SRCD := src
TSTD := tests
AUXD := tests_aux
BLDD := build
BIND := bin
INCD := -I include

TEST := run_tests

ALL_SRCF := $(shell find $(SRCD) -type f -name '*.c')
ALL_OBJF := $(patsubst $(SRCD)/%,$(BLDD)/%,$(ALL_SRCF:.c=.o))
TEST_SRC := $(shell find $(TSTD) -type f -name '*.c')
TEST_OBJ := $(patsubst $(TSTD)/%,$(BLDD)/%,$(TEST_SRC:.c=.o))
AUX_SRC := $(shell find $(AUXD) -type f -name '*.c')
AUX_OBJS := $(patsubst $(AUXD)/%,$(BLDD)/%,$(AUX_SRC:.c=.o))
AUX_PGMS := $(patsubst $(AUXD)/%,$(BIND)/%,$(AUX_SRC:.c=))

CFLAGS := -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -pedantic -Werror
STD := -std=gnu11
CFLAGS += $(STD) -g

CRITERION_CFLAGS := $(shell pkg-config --cflags criterion 2>/dev/null)
CRITERION_LIBS := $(shell pkg-config --libs criterion 2>/dev/null)
ifeq ($(strip $(CRITERION_LIBS)),)
CRITERION_LIBS := -lcriterion
endif
LIBS := -lm

TEST_RESULTS := test_results.json

.PHONY: all setup test valgrind clean

all: setup $(BIND)/$(TEST) $(AUX_PGMS)

setup:
	@mkdir -p $(BIND) $(BLDD) $(TSTD).out

$(BIND)/$(TEST): $(ALL_OBJF) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(ALL_OBJF) $(TEST_OBJ) $(CRITERION_LIBS) -o $@ $(LIBS)

$(BIND)/%: $(BLDD)/%.o $(ALL_OBJF)
	@mkdir -p $(BIND)
	$(CC) $(CFLAGS) $< $(ALL_OBJF) -o $@ $(LIBS)

$(BLDD)/%.o: $(SRCD)/%.c include/matrixscript.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCD) -c -o $@ $<

$(BLDD)/%.o: $(AUXD)/%.c include/matrixscript.h $(TSTD)/test_helpers.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCD) -I $(TSTD) $(CRITERION_CFLAGS) -c -o $@ $<

$(BLDD)/%.o: $(TSTD)/%.c include/matrixscript.h $(TSTD)/test_helpers.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCD) -I $(TSTD) $(CRITERION_CFLAGS) -c -o $@ $<

test: all
	@rm -rf $(TSTD).out
	@mkdir -p $(TSTD).out
	./$(BIND)/$(TEST) --full-stats --verbose --json=$(TEST_RESULTS) -j1

# The valgrind checks are graded on this assignment. They need Linux.
valgrind: all
	@rm -rf $(TSTD).out
	@mkdir -p $(TSTD).out
	./$(BIND)/$(TEST) --filter 'base_*valgrind/*' -j1

clean:
	rm -rf $(BLDD) $(BIND) $(TSTD).out $(TEST_RESULTS)
