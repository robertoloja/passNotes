CC=gcc
BUILD_DIR=./build
SRC_DIR=./src
CFLAGS=-g -Wall -MMD

all: $(BUILD_DIR)/server $(BUILD_DIR)/client

$(BUILD_DIR)/server: $(SRC_DIR)/server.o
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/server $(SRC_DIR)/server.o -lpthread

$(BUILD_DIR)/client: $(SRC_DIR)/client.o
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/client $(SRC_DIR)/client.o

$(SRC_DIR)/server.o: $(SRC_DIR)/server.h

$(SRC_DIR)/client.o: $(SRC_DIR)/client.h
