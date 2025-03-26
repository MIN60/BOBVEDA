#ifndef _FILE_H_
#define _FILE_H_
#include "struct.h"

void ReadOrigin(MEMBER* Optr, const char* file_name);
void ReadPrev(MEMBER* Rptr, const char* file_name);
void WriteText(TEAM* Wptr, const char* file_name);

#endif