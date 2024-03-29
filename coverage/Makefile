SRCDIR=../src
TESTDIR=../tests

CC=gcc
## progs
GENHTML=genhtml
GCOV=gcov
LCOV=lcov

## we employ two versions of CFLAGS:
## 1st -- here we want to measure coverage
CFLAGS=-W -Wall -Wpedantic -O0 -std=c99 -fprofile-arcs -ftest-coverage -I$(SRCDIR)
## 2nd -- we do not measure coverage
CFLAGS_X=-W -Wall -Wpedantic -O0 -std=c99 -I$(SRCDIR)

LDFLAGS=-fprofile-arcs -ftest-coverage

TEST_X0 = dcslinear dcsstack
#TEST_X1 = intio uint
#TEST_Y0 = io prec add mul eq pval

INFO_FILE=bilisdcs.info
HTML_DIR=html

TEST_X0_PROGS = $(TEST_X0:%=%_test)
TEST_X0_OBJS = $(TEST_X0_PROGS:%=%.o)
TEST_X0_SOURCES = $(TEST_X0_PROGS:%=$(TESTDIR)/%.c)

#TEST_X1_PROGS = $(TEST_X1:%=%_test)
#TEST_X1_OBJS = $(TEST_X1_PROGS:%=%.o)
#TEST_X1_SOURCES = $(TEST_X1_PROGS:%=$(TESTDIR)/%.c)

#TEST_Y0_PROGS = $(TEST_Y0:%=bigdecimal128_%_test)
#TEST_Y0_OBJS = $(TEST_Y0_PROGS:%=%.o)
#TEST_Y0_SOURCES = $(TEST_Y0_PROGS:%=$(TESTDIR)/%.c)


TEST_COMMON_OBJS = 

LIB_OBJS = \
 l_DcsHashSet.o \
 l_DcsHoF.o \
 l_DcsInternal.o \
 l_DcsLinSet.o \
 l_DcsLinear.o \
 l_DcsStack.o

LIB_SOURCES = $(LIB_OBJS:l_%.o=$(SRCDIR)/%.c)
LIB_GCDA = $(LIB_OBJS:%.o=%.gcda)
LIB_GCNO = $(LIB_OBJS:%.o=%.gcno)
LIB_GCOV = $(LIB_OBJS:l_%.o=%.c.gcov)

## main target
all: $(INFO_FILE)

## not main, still popular target#1
html: $(HTML_DIR)/index.html

$(HTML_DIR)/index.html: $(INFO_FILE)
	$(GENHTML) $< --branch-coverage --output-directory $(HTML_DIR)

## not main, still popular target#2
gcov: $(LIB_GCOV)

%.c.gcov: l_%.gcda
	$(GCOV) -abcfu -o $< $(@:.gcov=)

$(INFO_FILE): $(LIB_GCDA)
	$(LCOV) --rc lcov_branch_coverage=1 -c --directory . --output-file $@

%.gcda: $(TEST_X0_PROGS) # $(TEST_X1_PROGS) $(TEST_Y0_PROGS)
	$(foreach x,$^,./$(x);)

$(TEST_X0_PROGS): $(TEST_COMMON_OBJS)

#$(TEST_Y0_PROGS): $(TEST_COMMON_OBJS)

%_test: %_test.o $(LIB_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%_test.o: $(TESTDIR)/%_test.c
	$(CC) -c $(CFLAGS_X) -o $@ $<

test_commo%.o: $(TESTDIR)/test_commo%.c
	$(CC) -c $(CFLAGS_X) -o $@ $<

l_%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

## other targets
clean:
	$(LCOV) -z --directory .
	rm -f $(INFO_FILE)
	rm -f $(LIB_OBJS)
	rm -f $(LIB_GCDA)
	rm -f $(LIB_GCNO)
	rm -f $(LIB_GCOV)
	rm -f $(TEST_X0_PROGS)
	rm -f $(TEST_X0_OBJS)
	rm -rf $(HTML_DIR)

.PHONY: clean html gcov

## keep everything
.PRECIOUS: $(TEST_X1_PROGS) $(TEST_X0_PROGS) $(TEST_COMMON_OBJS) $(LIB_OBJS)

