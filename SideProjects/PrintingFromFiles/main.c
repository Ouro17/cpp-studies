#include <corecrt_io.h>
#define _CRT_SECURE_NO_WARNINGS

#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 14
#define ERROR -1
#define END_STRING '\0'
#define CONSOLE_OUTPUT 1
#define RETURN_CARRIAGE '\n'
#define MIN_BUFFER_CAPACITY 32
#define BUFFER_GROW_RATE 2

unsigned int stringLength(const char *str) {
  unsigned int length = 0;

  while (str[length] != END_STRING) {
    length++;
  }

  return length;
}

void print(const int outputHandler, const char *string) {
  _write(outputHandler, string, stringLength(string));
}

int isEndOfLine(const char character) { return character == RETURN_CARRIAGE; }

void copyBuffer(char *fromBuffer, char *toBuffer, const unsigned int capacity) {
  unsigned int index = 0;
  while (index < capacity) {
    toBuffer[index] = fromBuffer[index];
    index++;
  }
}

char *reallocateBuffer(char *oldBuffer, const unsigned int oldCapacity,
                       const unsigned int newCapacity) {
  char *newBuffer = malloc(newCapacity);

  if (newBuffer == 0) {
    free(oldBuffer);
    exit(EXIT_FAILURE);
  }

  copyBuffer(oldBuffer, newBuffer, oldCapacity);

  free(oldBuffer);
  return newBuffer;
}

void ensureCapacity(char **bufferPtr, unsigned int *capacityPtr,
                    const unsigned int requiredSize) {

  const unsigned int capacity = *capacityPtr;
  if (capacity >= requiredSize) {
    // Nothing to do
    return;
  }

  unsigned int newCapacity =
      (capacity == 0) ? MIN_BUFFER_CAPACITY : (capacity * BUFFER_GROW_RATE);

  while (newCapacity < requiredSize) {
    newCapacity *= BUFFER_GROW_RATE;
  }

  *bufferPtr = reallocateBuffer(*bufferPtr, capacity, newCapacity);
  *capacityPtr = newCapacity;
}

void appendChar(char **bufferPtr, unsigned int *lengthPtr,
                unsigned int *capacityPtr, const char value) {
  ensureCapacity(bufferPtr, capacityPtr, *lengthPtr + 1);

  char *data = *bufferPtr;
  const unsigned int index = *lengthPtr;

  data[index] = value;
  *lengthPtr = index + 1;
}

void printLine(char **bufferPtr, unsigned int *lengthPtr,
               unsigned int *capacityPtr, const int outputHandler) {

  // Finish the string
  appendChar(bufferPtr, lengthPtr, capacityPtr, END_STRING);

  _write(outputHandler, *bufferPtr, *lengthPtr);

  // Reset the line
  *lengthPtr = 0;
}

void printFromFileDescriptor(const int fileDescriptor,
                             const int outputHandler) {
  char readBuffer[BUFFER_SIZE];

  char *lineBuffer = 0;
  unsigned int lineLength = 0;
  unsigned int lineCapacity = 0;

  int bytesRead = 0;

  while ((bytesRead = _read(fileDescriptor, readBuffer, BUFFER_SIZE)) > 0) {
    unsigned int index = 0;

    while (index < bytesRead) {

      appendChar(&lineBuffer, &lineLength, &lineCapacity, readBuffer[index]);

      if (isEndOfLine(readBuffer[index])) {
        printLine(&lineBuffer, &lineLength, &lineCapacity, outputHandler);
      }

      index++;
    }
  }

  // If the read loop is finished and there is some line still not printed,
  // print it
  if (lineLength > 0) {
    printLine(&lineBuffer, &lineLength, &lineCapacity, outputHandler);
  }

  free(lineBuffer);

  if (bytesRead == ERROR) {
    perror("read error");
  }
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    print(CONSOLE_OUTPUT, "Not enough arguments\n");
    return 1;
  }

  const int outputHandler = 1;
  int fileDescriptor;
  const char *text = argv[1];

  if ((fileDescriptor = _open(text, O_RDONLY | O_BINARY)) == ERROR) {
    print(CONSOLE_OUTPUT, "File Opening Failed\n");
    return EXIT_FAILURE;
  } else {
    printFromFileDescriptor(fileDescriptor, outputHandler);

    _close(fileDescriptor);
  }

  return EXIT_SUCCESS;
}