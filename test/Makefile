CC := gcc
CFLAGS := -Wall -I$(INC_DIR)

TARGET := test_rng

SRC:=rng_tester.c

all:
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN_DIR)/$(TARGET)
clean:
	rm -rf $(BIN_DIR)/$(TARGET)