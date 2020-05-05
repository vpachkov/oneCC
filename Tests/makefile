SUBDIRS += \
		Lexer \
		Config \

BIG_OBJ += \
		Lexer/ProgLexerTester.o \
		Config/ProgConfigTester.o \

PROGRAM = ProgTester.o

CXXFLAGS = ${CXX_STANDARD_FLAGS} ${CXX_WARNING_FLAGS}
LDFLAGS = -r

all: clean build

build: $(PROGRAM)

$(PROGRAM): $(SUBDIRS) main.o
	@echo "$(notdir $(CURDIR)): MERGE $(PROGRAM)"
	$(QUIET) $(CXX) $(LDFLAGS) main.o $(BIG_OBJ) -o $(PROGRAM)

$(SUBDIRS): 
	$(QUIET) $(MAKE) -C $@

%.o: %.cpp
	@echo "$(notdir $(CURDIR)): C++ $@"
	$(QUIET) $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
	done
	@echo "$(notdir $(CURDIR)): CLEAN"
	$(QUIET) rm -rf *.exec *.o

.PHONY: all $(PROGRAM) $(SUBDIRS)