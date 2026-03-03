/*
Rules:
- No usage of for-loop, while some reason.
- Can use struct, while forevers, return on void.
- Line should end in newline character '\n', except if end of file is not.
- Returns the first line encounter or NULL in case of error.
- No use of lseek, realloc or whatever. Only malloc.
- Can't use global variables BUT CAN use static. Which is basically the same.
- Bonus: Use only 1 static | Use different file descriptors.
*/

#include <corecrt_io.h>
#include <corecrt_search.h>
#define _CRT_SECURE_NO_WARNINGS

#include <fcntl.h>
#include <io.h>
#include <stdlib.h>

#define FOREVER 1
#define BUFFER_SIZE 14
#define ERROR -1
#define SUCCESS 0
#define END_STRING '\0'
#define CONSOLE_OUTPUT 1
#define RETURN_CARRIAGE '\n'
#define MIN_BUFFER_CAPACITY 32
#define BUFFER_GROW_RATE 2
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/file-handling?view=msvc-170
#define FILE_DESCRIPTORS_SIZE 512

typedef struct readState {
  char buffer[BUFFER_SIZE];
  int bufferSize;
  int bufferIndex;
  int endOfFile;
} ReadState;

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

  if (newBuffer == NULL) {
    return NULL;
  }

  copyBuffer(oldBuffer, newBuffer, oldCapacity);

  return newBuffer;
}

void ensureCapacity(char **bufferPtr, unsigned int *capacityPtr,
                    const unsigned int requiredSize) {

  const unsigned int oldCapacity = *capacityPtr;
  if (oldCapacity >= requiredSize) {
    // Nothing to do
    return;
  }

  unsigned int newCapacity = (oldCapacity == 0)
                                 ? MIN_BUFFER_CAPACITY
                                 : (oldCapacity * BUFFER_GROW_RATE);

  while (newCapacity < requiredSize) {
    newCapacity *= BUFFER_GROW_RATE;
  }

  char *newBuffer = reallocateBuffer(*bufferPtr, oldCapacity, newCapacity);

  if (newBuffer != NULL) {
    free(*bufferPtr);
    *bufferPtr = newBuffer;
    *capacityPtr = newCapacity;
  }
}

int appendChar(char **bufferPtr, unsigned int *lengthPtr,
               unsigned int *capacityPtr, const char value) {
  ensureCapacity(bufferPtr, capacityPtr, *lengthPtr + 1);

  if (*bufferPtr == NULL) {
    return ERROR;
  }

  char *data = *bufferPtr;
  const unsigned int index = *lengthPtr;

  data[index] = value;
  *lengthPtr = index + 1;

  return SUCCESS;
}

int appendOrFail(char **buffer, unsigned int *length, unsigned int *capacity,
                 char value) {
  if (appendChar(buffer, length, capacity, value) == ERROR) {
    free(*buffer);
    *buffer = NULL;
    return ERROR;
  }

  return SUCCESS;
}

char *getNextLine(int fileDescriptor) {
  if (fileDescriptor < 0 || fileDescriptor >= FILE_DESCRIPTORS_SIZE) {
    return NULL;
  }

  static ReadState STATIC_READ_STATE[FILE_DESCRIPTORS_SIZE];

  ReadState *currentState;
  char *newLine = NULL;
  unsigned int length = 0;
  unsigned int capacity = 0;
  char currentCharacter = 0;

  currentState = &STATIC_READ_STATE[fileDescriptor];

  while (FOREVER) {
    if (currentState->bufferIndex >= currentState->bufferSize) {
      currentState->bufferSize =
          _read(fileDescriptor, currentState->buffer, BUFFER_SIZE);
      currentState->bufferIndex = 0;

      if (currentState->bufferSize <= 0) {
        break; // Stop reading, there are no more bytes on this file descriptor
      }
    }

    currentCharacter = currentState->buffer[currentState->bufferIndex];

    if (appendChar(&newLine, &length, &capacity, currentCharacter) == ERROR) {
      free(newLine);
      return NULL;
    }

    if (currentCharacter == RETURN_CARRIAGE) {
      currentState->bufferIndex++;

      if (appendChar(&newLine, &length, &capacity, END_STRING) == ERROR) {
        free(newLine);
        return NULL;
      }

      return newLine;
    }

    currentState->bufferIndex++;
  }

  // Hit here because there are no more bytes to read
  if (length > 0) {

    if (appendChar(&newLine, &length, &capacity, END_STRING) == ERROR) {
      free(newLine);
      return NULL;
    }

    return newLine;
  }

  // Error, free memory and exit
  free(newLine);
  return NULL;
}

int main(int argumentCount, char const *argumentValues[]) {

  int outputHandler = CONSOLE_OUTPUT;

  if (argumentCount < 2) {
    print(outputHandler, "Not enough arguments\n");
    return EXIT_FAILURE;
  }

  int index = 1;

  while (index < argumentCount) {
    int fileDescriptor = _open(argumentValues[index], O_RDONLY | O_BINARY);
    if (fileDescriptor == ERROR) {
      print(outputHandler, "\nFile Opening Failed: ");
      print(outputHandler, argumentValues[index]);
      print(outputHandler, "\n");
      index++;
      continue;
    }

    print(outputHandler, "\nFile: ");
    print(outputHandler, argumentValues[index]);
    print(outputHandler, "\n");

    char *nextLine;
    while ((nextLine = getNextLine(fileDescriptor)) != NULL) {
      print(outputHandler, nextLine);
      free(nextLine);
    }

    _close(fileDescriptor);
    index++;
  }

  return EXIT_SUCCESS;
}