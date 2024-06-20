#ifndef CLASS_HELPERS_H
#define CLASS_HELPERS_H

char* getFileName(const char* path);
void removeFileExtension(char* fileName);
char* getClassName(const char* path);

void loadClassFile(const char* path);
void executeClassFile(const char* path);

#endif // CLASS_HELPERS_H
