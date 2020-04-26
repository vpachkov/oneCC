SUBDIRS += \
		Lexer \

BIG_OBJ += \
	main.o \
	Lexer/Lexer.o \

PROGRAM = oneCC.exec

QUIET = @
CXX = g++
CXX_STANDARD_FLAGS = -std=c++2a
CXX_WARNING_FLAGS += -Werror
CXXFLAGS = ${CXX_STANDARD_FLAGS} ${CXX_WARNING_FLAGS}

all: $(PROGRAM)

$(PROGRAM): $(SUBDIRS) main.o
	@echo "$(notdir $(CURDIR)): LINK $(PROGRAM)"
	$(QUIET) $(CXX) $(BIG_OBJ) -o $(PROGRAM)

$(SUBDIRS): 
	$(QUIET) $(MAKE) -C $@

main.o: main.cpp
	@echo "$(notdir $(CURDIR)): C++ $@"
	$(QUIET) $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	$(QUIET) $(MAKE) clean -C $(SUBDIRS)

	@echo "$(notdir $(CURDIR)): CLEAN"
	$(QUIET) rm -rf *.exec *.o

.PHONY: all $(PROGRAM) $(SUBDIRS)