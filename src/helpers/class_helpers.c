#include "./class_helpers.h"

char* getFileName(const char* path) {
    const char* slash = strrchr(path, '/');
    if (slash) {
        return strdup(slash + 1);
    }
    return strdup(path);
}

void removeFileExtension(char* fileName) {
    char* dot = strrchr(fileName, '.');
    if (dot && strcmp(dot, ".class") == 0) {
        *dot = '\0';
    }
}

char* getClassName(const char* path) {
    char* fileName = getFileName(path);
    removeFileExtension(fileName);
    return fileName;
}
