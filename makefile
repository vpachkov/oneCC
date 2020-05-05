###########
# Build params
###########

QUIET = @
CXX = g++
CXX_STANDARD_FLAGS = -std=c++2a
CXX_WARNING_FLAGS += -Werror
CXXFLAGS = ${CXX_STANDARD_FLAGS} ${CXX_WARNING_FLAGS}

# Flags which we pass to sub makefiles
PASS_VARS = CXX="$(CXX)" CXX_STANDARD_FLAGS="$(CXX_STANDARD_FLAGS)" CXX_WARNING_FLAGS="$(CXX_WARNING_FLAGS)" QUIET="$(QUIET)"


###########
# Sources
###########

SUBDIRS += \
		Lexer \
		Config \
		
BIG_OBJ += \
		Lexer/ProgLexer.o \
		Config/ProgConfig.o \


###########
# Sources with Test included
# Note: not to edit, all you need is in Sources Group
###########

SUBDIRS_TEST += \
		$(SUBDIRS) \
		Tests \

BIG_OBJ_TEST += \
		$(BIG_OBJ) \
		Tests/ProgTester.o \

###########
# Outputs
###########

PROGRAM = oneCC.exec
PROGRAM_TEST = test$(PROGRAM)


###########
# Build rules
###########

all: build

run: build
	./$(PROGRAM)

test: build_test
	./$(PROGRAM_TEST)

debug: build_debug
	gdb $(PROGRAM)

build: $(PROGRAM)
build_test: $(PROGRAM_TEST)
build_debug: CXX_STANDARD_FLAGS += -g
build_debug: $(PROGRAM)
	xcrun dsymutil $(PROGRAM) -o $(PROGRAM).dSYM

$(PROGRAM): $(SUBDIRS) main.o
	@echo "$(notdir $(CURDIR)): LINK $(PROGRAM)"
	$(QUIET) $(CXX) main.o $(BIG_OBJ) -o $(PROGRAM)

$(PROGRAM_TEST): $(SUBDIRS_TEST)
	@echo "$(notdir $(CURDIR)): LINK $(PROGRAM_TEST)"
	$(QUIET) $(CXX) $(BIG_OBJ_TEST) -o $(PROGRAM_TEST)

$(SUBDIRS): 
	$(QUIET) $(MAKE) -C $@ $(PASS_VARS)

$(SUBDIRS_TEST): 
	$(QUIET) $(MAKE) -C $@ $(PASS_VARS)

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