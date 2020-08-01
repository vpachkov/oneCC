###########
# Build params
###########

include appdefines.mk

PROJECT_BASE_DIR = $(shell pwd)
QUIET = @
CXX = g++-10
CXX_STANDARD_FLAGS = -std=c++2a
CXX_WARNING_FLAGS += -Werror
# CXX_APP_DEBUG_FLAGS += -DDEBUG_REGMANAGER_PRINT_INFO -DDEBUG_TRANSLATOR_TRACER
CXXFLAGS = ${CXX_STANDARD_FLAGS} ${CXX_WARNING_FLAGS} ${CXX_APP_DEBUG_FLAGS} ${APP_DEFINES}

# Flags which we pass to sub makefiles
PASS_VARS = CXX="$(CXX)" CXX_STANDARD_FLAGS="$(CXX_STANDARD_FLAGS)" CXX_WARNING_FLAGS="$(CXX_WARNING_FLAGS)" QUIET="$(QUIET)" PROJECT_BASE_DIR="$(PROJECT_BASE_DIR)"


###########
# Sources
###########

BASE_PATH = src

SUBDIRS += \
		${BASE_PATH}/Lexer \
		${BASE_PATH}/Config \
		${BASE_PATH}/ArgsParser \
		${BASE_PATH}/Parser \
		${BASE_PATH}/AST \
		${BASE_PATH}/Utils \
		${BASE_PATH}/SemanticAnalyzer \
		${BASE_PATH}/CodeGenerator \

SRCS := $(shell find $(SUBDIRS) -name "*.cpp")
OBJS := $(patsubst %.cpp, %.o, $(SRCS))


###########
# Sources with Tests
# Note: not to edit, all you need is in SUBDIRS
###########

SUBDIRS_TEST += \
		${BASE_PATH}/Tests \

SRCS_TEST := $(shell find $(SUBDIRS) $(SUBDIRS_TEST) -name "*.cpp")
OBJS_TEST := $(patsubst %.cpp, %.o, $(SRCS_TEST))

HEADERS += $(shell find . -name "*.h")

###########
# Outputs
###########

PROGRAM = oneCC
PROGRAM_TEST = $(PROGRAM)-test
PROGRAM_DEBUG = $(PROGRAM)-debug
PROGRAM_SYMBOLS = $(PROGRAM_DEBUG).dSYM

###########
# Build rules
###########

all: build

run: build
	./$(PROGRAM)

test: build_test
	./$(PROGRAM_TEST)

debug: build_debug
	gdb $(PROGRAM_DEBUG)

release:
	@make clean
	@make build
	@mv $(PROGRAM) $(PROGRAM)-$(OS)-$(ARC)

build: $(PROGRAM)
build_test: $(PROGRAM_TEST)

build_debug: CXX_STANDARD_FLAGS += -g 
build_debug: $(PROGRAM_DEBUG)
build_debug: $(PROGRAM_SYMBOLS)

$(PROGRAM): $(OBJS) ${BASE_PATH}/main.o
	@echo "$(notdir $(CURDIR)): LINK $@"
	$(QUIET) $(CXX) $^ -o $@

$(PROGRAM_DEBUG): $(OBJS) ${BASE_PATH}/main.o
	@echo "$(notdir $(CURDIR)): LINK $@"
	$(QUIET) $(CXX) $^ -o $@

$(PROGRAM_SYMBOLS): $(PROGRAM_DEBUG)
	@echo "$(notdir $(CURDIR)): SYMBOLS"
	$(QUIET) xcrun dsymutil $^ -o $@

$(PROGRAM_TEST): $(OBJS_TEST)
	@echo "$(notdir $(CURDIR)): LINK $(PROGRAM_TEST)"
	$(QUIET) $(CXX) $^ -o $@

%.o: %.cpp $(HEADERS)
	@echo "$(notdir $(CURDIR)): C++ $@"
	$(QUIET) $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@echo "$(notdir $(CURDIR)): CLEANED"
	$(QUIET) rm -rf $(PROGRAM) $(PROGRAM_TEST) $(PROGRAM_DEBUG) $(PROGRAM_SYMBOLS) $(OBJS_TEST) ${BASE_PATH}/main.o

.PHONY: all clean run test debug build build_test build_debug $(PROGRAM_TEST) $(PROGRAM_DEBUG) $(PROGRAM_SYMBOLS)