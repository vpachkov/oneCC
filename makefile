SUBDIRS += \
		Lexer \

BIG_OBJ += \
	main.o \
	Lexer/Lexer.o \

PROGRAM = oneCC.exec

QUIET = @

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