HLSDK = /opt/sdk/hlsdk
MM_ROOT = /opt/sdk/metamod
AMXX_DIR = ../../public
AMXX_DIR_SDK = sdk
MYSQL_DIR = mysql_lin

NAME = mysql

COMPILER = /opt/intel/bin/icpc

OBJECTS = basic_sql.cpp handles.cpp module.cpp threading.cpp sdk/amxxmodule.cpp oldcompat_sql.cpp thread/BaseWorker.cpp \
thread/ThreadWorker.cpp mysql/MysqlQuery.cpp mysql/MysqlResultSet.cpp mysql/MysqlDatabase.cpp mysql/MysqlDriver.cpp thread/PosixThreads.cpp

LINK = -lm -ldl -static-intel -static-libgcc -no-intel-extensions -shared $(MYSQL_DIR)/lib/libmysqlclient_r.a -lpthread -L$(MYSQL_DIR)/lib

OPT_FLAGS = -O3 -msse3 -ipo -no-prec-div -fp-model fast=2 -funroll-loops -fomit-frame-pointer -fno-stack-protector -pipe

INCLUDE = -I. -I$(AMXX_DIR) -I$(AMXX_DIR_SDK) -I$(HLSDK) -I$(HLSDK)/common -I$(HLSDK)/dlls -I$(HLSDK)/engine \
-I$(HLSDK)/game_shared -I$(HLSDK)/public -I$(MM_ROOT) -I$(MYSQL_DIR)/include -Ithread -Imysql

ifeq "$(DEBUG)" "true"
	BIN_DIR = Debug
else
	BIN_DIR = Release
endif

CFLAGS = $(OPT_FLAGS)

CFLAGS += -g -DNDEBUG -Dlinux -D__linux__ -std=c++0x -shared -wd147,274 -fasm-blocks \
-DSM_DEFAULT_THREADER -DPAWN_CELL_SIZE=32 -DJIT -DASM32 -DHAVE_STDINT_H -Dstricmp=strcasecmp -fno-strict-aliasing -Wall -Werror

LIB_EXT = so

LIB_SUFFIX = _amxx_i386

BINARY = $(NAME)$(LIB_SUFFIX).$(LIB_EXT)

OBJ_LINUX := $(OBJECTS:%.cpp=$(BIN_DIR)/%.o)

CPPFLAGS += -fno-exceptions -fno-rtti

$(BIN_DIR)/%.o: %.cpp
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

all:
	mkdir -p $(BIN_DIR)
	mkdir -p $(BIN_DIR)/mysql
	mkdir -p $(BIN_DIR)/thread
	mkdir -p $(BIN_DIR)/sdk

	$(MAKE) $(NAME) && strip -x $(BIN_DIR)/$(NAME)_amxx_i386.so

$(NAME): $(OBJ_LINUX)
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(OBJ_LINUX) $(LINK) -o$(BIN_DIR)/$(NAME)_amxx_i386.so

check:
	cppcheck $(INCLUDE) --quiet --max-configs=100 -D__linux__ -DNDEBUG -DHAVE_STDINT_H .

debug:	
	$(MAKE) all DEBUG=false

default: all

clean:
	rm -rf $(BIN_DIR)/*.o
	rm -rf $(BIN_DIR)/mysql/*.o
	rm -rf $(BIN_DIR)/thread/*.o
	rm -rf $(BIN_DIR)/sdk/*.o
	rm -f $(BIN_DIR)/$(BINARY)