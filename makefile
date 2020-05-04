SUBDIRS += \
		Lexer \
		Config \
		
SUBDIRS_TEST += \
		$(SUBDIRS) \
		Tests \

BIG_OBJ += \
		Lexer/ProgLexer.o \
		Config/ProgConfig.o \

BIG_OBJ_TEST += \
		$(BIG_OBJ) \
		Tests/ProgTester.o \

PROGRAM = oneCC.exec
PROGRAM_TEST = test$(PROGRAM)

QUIET = @
CXX = g++
CXX_STANDARD_FLAGS = -std=c++2a
CXX_WARNING_FLAGS += -Werror
CXXFLAGS = ${CXX_STANDARD_FLAGS} ${CXX_WARNING_FLAGS}

all: build

run: build
	./$(PROGRAM)

test: build_test
	./$(PROGRAM_TEST)

debug: build_debug
	gdb $(PROGRAM)

build: $(PROGRAM)
build_test: $(PROGRAM_TEST)
build_debug: CXXFLAGS += -g
build_debug: $(PROGRAM)

$(PROGRAM): $(SUBDIRS) main.o
	@echo "$(notdir $(CURDIR)): LINK $(PROGRAM)"
	$(QUIET) $(CXX) main.o $(BIG_OBJ) -o $(PROGRAM)

$(PROGRAM_TEST): $(SUBDIRS_TEST)
	@echo "$(notdir $(CURDIR)): LINK $(PROGRAM_TEST)"
	$(QUIET) $(CXX) $(BIG_OBJ_TEST) -o $(PROGRAM_TEST)

$(SUBDIRS): 
	$(QUIET) $(MAKE) -C $@

$(SUBDIRS_TEST): 
	$(QUIET) $(MAKE) -C $@

main.o: main.cpp
	@echo "$(notdir $(CURDIR)): C++ $@"
	$(QUIET) $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@for dir in $(SUBDIRS_TEST); do \
        $(MAKE) clean -C $$dir; \
	done
	@echo "$(notdir $(CURDIR)): CLEAN"
	$(QUIET) rm -rf *.exec *.o

.PHONY: all clean run test debug $(PROGRAM) $(SUBDIRS) $(SUBDIRS_TEST)