HLSDK = /opt/sdk/hlsdk
MM_ROOT = /opt/sdk/metamod
AMXX_DIR = ../../public
AMXX_DIR_SDK = sdk

NAME = regex

COMPILER = /opt/intel/bin/icpc

OBJECTS = sdk/amxxmodule.cpp module.cpp CRegEx.cpp utils.cpp

LINK = -lm -ldl -static-intel -static-libgcc -no-intel-extensions lib_linux/libpcre.a

OPT_FLAGS = -O3 -msse3 -ipo -no-prec-div -fp-model fast=2 -funroll-loops -fomit-frame-pointer -fno-stack-protector

INCLUDE = -I. -I$(AMXX_DIR) -I$(AMXX_DIR_SDK) -I$(HLSDK) -I$(HLSDK)/common -I$(HLSDK)/dlls -I$(HLSDK)/engine \
-I$(HLSDK)/game_shared -I$(HLSDK)/public -I$(MM_ROOT)

BIN_DIR = Release
CFLAGS = $(OPT_FLAGS)

CFLAGS += -g -DNDEBUG -Dlinux -D__linux__ -std=c++0x -shared -wd147,274 -fasm-blocks \
-DPCRE_STATIC -DPAWN_CELL_SIZE=32 -DJIT -DASM32 -DHAVE_STDINT_H -fno-strict-aliasing -m32 -Wall -Werror

OBJ_LINUX := $(OBJECTS:%.c=$(BIN_DIR)/%.o)

$(BIN_DIR)/%.o: %.c
	$(COMPILER) $(INCLUDE) $(CFLAGS) -o $@ -c $<

all:
	mkdir -p $(BIN_DIR)

	$(MAKE) $(NAME) && strip -x $(BIN_DIR)/$(NAME)_amxx_i386.so

$(NAME): $(OBJ_LINUX)
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(OBJ_LINUX) $(LINK) -o$(BIN_DIR)/$(NAME)_amxx_i386.so

check:
	cppcheck $(INCLUDE) --quiet --max-configs=100 -D__linux__ -DNDEBUG -DHAVE_STDINT_H .

debug:	
	$(MAKE) all DEBUG=false

default: all

clean:
	rm -rf Release/*.o
	rm -rf Release/$(NAME)_amxx_i386.so
	rm -rf Debug/*.o
	rm -rf Debug/$(NAME)_amxx_i386.so
