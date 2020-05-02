SUBDIRS += \
		Lexer \
		TextSequencer \
		Config \

BIG_OBJ += \
		Lexer/Lexer.o \
		TextSequencer/TextSequencer.o \
		Config/Config.o \

PROGRAM = oneCC.exec
PROGRAM_TEST = test$(PROGRAM)

QUIET = @
CXX = g++
CXX_STANDARD_FLAGS = -std=c++2a
CXX_WARNING_FLAGS += -Werror
CXXFLAGS = ${CXX_STANDARD_FLAGS} ${CXX_WARNING_FLAGS}

all: build

build: $(PROGRAM)

build_test: $(PROGRAM_TEST)

$(PROGRAM): $(SUBDIRS) main.o
	@echo "$(notdir $(CURDIR)): LINK $(PROGRAM)"
	$(QUIET) $(CXX) main.o $(BIG_OBJ) -o $(PROGRAM)

$(PROGRAM_TEST): $(SUBDIRS) test.o
	@echo "$(notdir $(CURDIR)): LINK $(PROGRAM_TEST)"
	$(QUIET) $(CXX) test.o $(BIG_OBJ) -o $(PROGRAM_TEST)

$(SUBDIRS): 
	$(QUIET) $(MAKE) -C $@

main.o: main.cpp
	@echo "$(notdir $(CURDIR)): C++ $@"
	$(QUIET) $(CXX) $(CXXFLAGS) -o $@ -c $<

test.o: test.cpp
	@echo "$(notdir $(CURDIR)): C++ $@"
	$(QUIET) $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
	done
	@echo "$(notdir $(CURDIR)): CLEAN"
	$(QUIET) rm -rf *.exec *.o

.PHONY: all $(PROGRAM) $(SUBDIRS)
