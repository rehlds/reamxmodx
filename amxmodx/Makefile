HLSDK = ../public/cssdk
MM_ROOT = ../public/metamod
AMXX_SDK = ../public
AMXX_AMTL = ../public/amtl
AMXX_HASHER = hashing/
AMXX_MEMTOOLS = memtools/

NAME = amxmodx

COMPILER = /opt/intel/bin/icpc

OBJECTS = meta_api.cpp CVault.cpp vault.cpp float.cpp file.cpp modules.cpp CMisc.cpp CTask.cpp string.cpp \
amxmodx.cpp CEvent.cpp CCmd.cpp CLogEvent.cpp srvcmd.cpp strptime.cpp amxcore.cpp amxtime.cpp \
power.cpp amxxlog.cpp fakemeta.cpp amxxfile.cpp CLang.cpp emsg.cpp CForward.cpp CPlugin.cpp \
CModule.cpp CMenu.cpp util.cpp amx.cpp amxdbg.cpp natives.cpp newmenus.cpp debugger.cpp optimizer.cpp \
format.cpp messages.cpp libraries.cpp vector.cpp sorting.cpp nongpl_matches.cpp CFlagManager.cpp datastructs.cpp \
trie_natives.cpp CDataPack.cpp datapacks.cpp stackstructs.cpp CTextParsers.cpp textparse.cpp CvarManager.cpp cvars.cpp \
CLibrarySys.cpp CGameConfigs.cpp gameconfigs.cpp CoreConfig.cpp

OBJECTS += sdk/mod_rehlds_api.cpp sdk/interface.cpp

OBJECTS += $(AMXX_MEMTOOLS)MemoryUtils.cpp $(AMXX_MEMTOOLS)CDetour/detours.cpp $(AMXX_MEMTOOLS)CDetour/asm/asm.c

OBJECTS += $(AMXX_HASHER)hashing.cpp $(AMXX_HASHER)hashers/crc32.cpp $(AMXX_HASHER)hashers/keccak.cpp \
	$(AMXX_HASHER)hashers/md5.cpp $(AMXX_HASHER)hashers/sha1.cpp $(AMXX_HASHER)hashers/sha3.cpp $(AMXX_HASHER)hashers/sha256.cpp

OBJECTS += JIT/amxexecn.o JIT/amxjitsn.o JIT/natives-x86.o JIT/helpers-x86.o

LINK = -lm -ldl -static-intel -static-libgcc -no-intel-extensions -Lzlib -L$(AMXX_HASHER) -lz -shared

OPT_FLAGS = -O3 -msse3 -no-prec-div -fp-model fast=2 -funroll-loops -fomit-frame-pointer -fno-stack-protector -pipe

INCLUDE = -I. -I$(AMXX_SDK) -I$(AMXX_SDK)/sdk -I$(HLSDK) -I$(HLSDK)/common -I$(HLSDK)/dlls -I$(HLSDK)/engine -I$(HLSDK)/game_shared \
	  -I$(HLSDK)/pm_shared -I$(HLSDK)/public -I$(MM_ROOT) -I$(AMXX_HASHER) -I$(AMXX_MEMTOOLS)

BIN_DIR = Release
CFLAGS = $(OPT_FLAGS)

CFLAGS += -g -DNDEBUG -DLINUX -D__linux__ -Dlinux -std=c++11 -wd147,274 \
           -DJIT -DASM32 -DHAVE_STDINT_H -D_vsnprintf=vsnprintf -m32 -Werror -Wno-attributes -Wno-write-strings

LIB_EXT = so

LIB_SUFFIX = _mm_i386

BINARY = $(NAME)$(LIB_SUFFIX).$(LIB_EXT)

ifeq "$(BINLOG)" "true"
	LIB_SUFFIX := _bl$(LIB_SUFFIX)
	BIN_DIR := $(BIN_DIR)BinLog
	OBJECTS += binlog.cpp
	CFLAGS += -DBINLOG_ENABLED
endif

CPPFLAGS += -fno-exceptions -fno-rtti

OBJ_BIN := $(OBJECTS:%.cpp=$(BIN_DIR)/%.o)

MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))

$(BIN_DIR)/%.o: %.cpp
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

all:
	mkdir -p $(BIN_DIR)
	mkdir -p $(BIN_DIR)/memtools
	mkdir -p $(BIN_DIR)/memtools/CDetour
	mkdir -p $(BIN_DIR)/hashing
	mkdir -p $(BIN_DIR)/hashing/hashers
	mkdir -p $(BIN_DIR)/sdk
	$(MAKE) -f $(MAKEFILE_NAME) $(NAME)

binlog:
	$(MAKE) -f $(MAKEFILE_NAME) all BINLOG=true

binlog_debug:
	$(MAKE) -f $(MAKEFILE_NAME) all BINLOG=true DEBUG=true

$(NAME): $(OBJ_BIN)
	$(COMPILER) $(INCLUDE) $(OBJ_BIN) $(LINK) -o $(BIN_DIR)/$(BINARY)

debug:
	$(MAKE) -f $(MAKEFILE_NAME) all DEBUG=true

default: all

clean:
	rm -rf $(BIN_DIR)/*.o
	rm -rf $(BIN_DIR)/memtools/*.o
	rm -rf $(BIN_DIR)/memtools/CDetour/*.o
	rm -rf $(BIN_DIR)/hashing/*.o
	rm -rf $(BIN_DIR)/hashing/hashers/*.o
	rm -rf $(BIN_DIR)/sdk/*.o
	rm -f $(BIN_DIR)/$(BINARY)
