UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CPP=g++ --std=c++11 -Wall
endif
ifeq ($(UNAME_S),Darwin)
	CPP=/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ --std=c++11 -Wall
endif

EXEC = Main

SRC_DIR = src
BIN_DIR = bin
EXEC_FILE= $(BIN_DIR)/$(EXEC)

SRC_FILES= $(wildcard $(SRC_DIR)/**.cpp) $(wildcard $(SRC_DIR)/**/**.cpp) $(wildcard $(SRC_DIR)/**/**/**.cpp) $(wildcard $(SRC_DIR)/**/**/**/**.cpp) 
OBJ_FILES= $(patsubst %.cpp, %.o,  $(subst $(SRC_DIR), $(BIN_DIR),$(SRC_FILES)))

all: $(EXEC_FILE)

$(EXEC_FILE): $(OBJ_FILES)
	$(CPP) -o $@ $^

$(OBJ_FILES): $(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CPP) -c -o $@ $^

run:
	./$(EXEC_FILE)

clean:
	rm -rf $(BIN_DIR)/*.o

mrproper: clean
	rm -rf $(BIN_DIR)/*

send:
	sh /opt/toev3.sh $(EXEC_FILE)
