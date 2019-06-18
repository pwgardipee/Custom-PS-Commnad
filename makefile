CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537ps
SCAN_BUILD_DIR = scan-build-out

all: main.o optionParser.o readCmd.o readFile.o setInfo.o listProcesses.o isPidValid.o
	$(CC) -o $(EXE) main.o  optionParser.o readCmd.o readFile.o setInfo.o listProcesses.o isPidValid.o

main.o: main.c main.h listProcesses.h setInfo.h optionParser.h readCmd.h isPidValid.h
	$(CC) $(WARNING_FLAGS) -c main.c

optionParser.o: optionParser.c optionParser.h
	$(CC) $(WARNING_FLAGS) -c optionParser.c

readCmd.o: readCmd.c readCmd.h main.h readFile.h
	$(CC) $(WARNING_FLAGS) -c readCmd.c

readFile.o: readFile.c readFile.h
	$(CC) $(WARNING_FLAGS) -c readFile.c

setInfo.o: setInfo.c setInfo.h
	$(CC) $(WARNING_FLAGS) -c setInfo.c

listProcesses.o: listProcesses.c listProcesses.h readFile.h
	$(CC) $(WARNING_FLAGS) -c listProcesses.c

isPidValid.o: isPidValid.c isPidValid.h readFile.h
	$(CC) $(WARNING_FLAGS) -c isPidValid.c	

clean:
	rm $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
