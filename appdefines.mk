GIT_BRANCH := $(shell git rev-parse --abbrev-ref HEAD)
GIT_HASH := $(shell git rev-parse --short HEAD)
VERSION := 0.2-alpha

ifeq ($(OS),Windows_NT)
    HARDWARE += -D WIN32
	OS += WIN32
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        HARDWARE += -D AMD64
		ARC += AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            HARDWARE += -D AMD64
			ARC += AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            HARDWARE += -D IA32
			ARC += IA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        HARDWARE += -D LINUX
		OS += LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        HARDWARE += -D MACOS
		OS += MACOS
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        HARDWARE += -D AMD64
		ARC += AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        HARDWARE += -D IA32
		ARC += IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        HARDWARE += -D ARM
		ARC += ARM
    endif
endif

APP_DEFINES = -D GIT_BRANCH=\"${GIT_BRANCH}\" -D GIT_HASH=\"${GIT_HASH}\" -D VERSION=\"${VERSION}\" ${HARDWARE}