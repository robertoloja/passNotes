CC=gcc
BUILD_DIR=./build
SRC_DIR=./src
CFLAGS=-g -pthread -Wall

all: $(BUILD_DIR)/server $(BUILD_DIR)/client

$(BUILD_DIR)/server: $(SRC_DIR)/server.o
	$(CC) -o $(BUILD_DIR)/server $(SRC_DIR)/server.o 

$(BUILD_DIR)/client: $(SRC_DIR)/client.o
	$(CC) -o $(BUILD_DIR)/client $(SRC_DIR)/client.o

$(BUILD_DIR)/server.o: $(SRC_DIR)/server.c $(SRC_DIR)/server.h $(SRC_DIR)/passNotes.h
	$(CC) -c $(SRC_DIR)/server.c $(SRC_DIR)/server.h $(SRC_DIR)/passNotes.h $(CFLAGS)

$(BUILD_DIR)/client.o: $(SRC_DIR)/client.c $(SRC_DIR)/client.h $(SRC_DIR)/passNotes.h
	$(CC) -c $(SRC_DIR)/client.c $(SRC_DIR)/client.h $(SRC_DIR)/passNotes.h $(CFLAGS)
