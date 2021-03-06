TARGET = ks.exe

SRCS = part2.c\
        part1.c\
        main.c\
        
#to add a file, put filename.extension\ before

OBJ_DIR = ./obj
SRC_DIR = ./src
BIN_DIR = ./bin
INC_DIR = ./include

DEP_DIRS =

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

SYS_LIBS = 

INCLUDES = -I$(INC_DIR) $(addprefix -I, $(DEP_DIRS))
LDLIBS = $(addprefix -l, $(SYS_LIBS))
LDFLAGS = -W -Wall
CXX = gcc

.PHONY: all clean fclean

debug: CFLAGS += -DDEBUG
debug: CXXFLAGS += -g
debug: LDFLAGS += -g
debug: all

release: CFLAGS += -O2
release: CFLAGS += -DRELEASE
release: clean all

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJS): $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(BIN_DIR)/$(TARGET)
	
rodolphe: CFLAGS += -DRODOLPHE
rodolphe: clean debug

antoine: CFLAGS += -DANTOINE
antoine: clean debug

