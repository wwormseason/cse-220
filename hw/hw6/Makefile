# CSE 220 Homework 6
#
#   make           build bin/searchreplace and bin/run_tests
#   make test      build if needed, then run every graded test
#   make valgrind  run the valgrind checks, which are feedback only
#   make clean     remove build/, bin/, tests.in/ and tests.out/
#
# make test wipes tests.in and tests.out. Keep your own input files in
# tests.in.orig, which is never touched.
#
# Criterion is found through pkg-config when it is installed that way, which
# covers a Homebrew install on macOS and the usual Linux packages. If pkg-config
# does not know about it, plain -lcriterion is used instead.

CC := gcc

SRCD := src
TSTD := tests
BLDD := build
BIND := bin
INCD := -I include

EXEC := searchreplace
TEST := run_tests

ALL_SRCF := $(shell find $(SRCD) -type f -name '*.c')
ALL_OBJF := $(patsubst $(SRCD)/%,$(BLDD)/%,$(ALL_SRCF:.c=.o))
TEST_SRC := $(shell find $(TSTD) -type f -name '*.c')
TEST_OBJ := $(patsubst $(TSTD)/%,$(BLDD)/%,$(TEST_SRC:.c=.o))

CFLAGS := -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -pedantic -Werror
STD := -std=gnu11
DFLAGS := -g
CFLAGS += $(STD) $(DFLAGS)

CRITERION_CFLAGS := $(shell pkg-config --cflags criterion 2>/dev/null)
CRITERION_LIBS := $(shell pkg-config --libs criterion 2>/dev/null)
ifeq ($(strip $(CRITERION_LIBS)),)
CRITERION_LIBS := -lcriterion
endif

TEST_RESULTS := test_results.json

.PHONY: all setup test valgrind clean

all: setup $(BIND)/$(EXEC) $(BIND)/$(TEST)

setup:
	@mkdir -p $(BIND) $(BLDD) $(TSTD).in $(TSTD).out

$(BIND)/$(EXEC): $(ALL_OBJF)
	$(CC) $(CFLAGS) $(ALL_OBJF) -o $@

$(BIND)/$(TEST): $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(CRITERION_LIBS) -o $@

$(BLDD)/%.o: $(SRCD)/%.c include/searchreplace.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCD) -c -o $@ $<

$(BLDD)/%.o: $(TSTD)/%.c include/searchreplace.h $(TSTD)/test_helpers.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCD) -I $(TSTD) $(CRITERION_CFLAGS) -c -o $@ $<

test: all
	@rm -rf $(TSTD).in $(TSTD).out
	@mkdir -p $(TSTD).in $(TSTD).out
	./$(BIND)/$(TEST) --full-stats --verbose --json=$(TEST_RESULTS) -j1

# Feedback only. --always-succeed means a valgrind complaint never fails your
# build, and HW6_VALGRIND switches the checks on. Linux only.
valgrind: all
	@rm -rf $(TSTD).in $(TSTD).out
	@mkdir -p $(TSTD).in $(TSTD).out
	@HW6_VALGRIND=1 ./$(BIND)/$(TEST) --filter 'base_valgrind/*' --always-succeed -j1
	@echo
	@echo "These results are feedback only. They are not part of your grade."

clean:
	rm -rf $(BLDD) $(BIND) $(TSTD).in $(TSTD).out $(TEST_RESULTS)
