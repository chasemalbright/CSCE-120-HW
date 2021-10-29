#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {

int length = 0;
  for (int i =0; str[i] != '\0'; i++){
    if (str[i] != ' '){
      length++; 
    }
  }
  
  return length;
}

unsigned int find(char str[], char character) {

  //int count = 0;

  for (unsigned int i =0; str[i] != '\0'; i++){
    if (str[i] == character) {
      return i;
    }
  }
  return length(str);
}

bool equalStr(char str1[], char str2[]) {
  if (length(str1) != length(str2)){
    return false;
    }
  for (unsigned int i =0; str1[i] != '\0'; i++){
    if (str1[i] != str2[i]){
      return false;
    }
  }
  return true;
}