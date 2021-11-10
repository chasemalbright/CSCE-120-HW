/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "Tag.h"

using std::string;
using std::vector;

bool containsPunc(char x){

  switch (x){
    case '!':
    case ',':
    case '.':
    case '?':
      return true;
    default:
      return false;
  }
}

Tag::Tag(string tagName) : tagName(tagName) {
  if (tagName.length() < 2){
    throw std::invalid_argument("tagName length is less than 2!");
  }

  if (tagName[0] != '#'){
    throw std::invalid_argument("tagName nust begin with # character!");
  }

  string letters = "abcdefghijklmnopqrstuvwxyz";
  int count = 0;
  for (int i = 0; i < letters.size(); i++){
    if(letters[i] == tagName[1]){
      count++;
    }
  }
  if (count == 0){
    throw std::invalid_argument("second character in tagname was not a-z!");
  }

  string upperLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int countUpper = 0;
  for (int i = 0; i < tagName.size(); i++){
    for (int j = 0; j < upperLetters.size(); j++){
      if (tagName[i] == upperLetters[j]){
        countUpper++;
      }
    }
  }
  if (countUpper != 0){
    throw std::invalid_argument("tagName must not contain upper case letters");
  }

  int countPunc = 0;

  for (int i = 0; i < tagName.size()-1; i++){
    if (containsPunc(tagName[i]) && containsPunc(tagName[i+1])){
      countPunc++;
    }
  }
  if (countPunc != 0){
    throw std::invalid_argument("consecutive punctuation not allowed in tagName!");
  }

}

string Tag::getTagName() {
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  if (post == nullptr){
    throw std::invalid_argument("post is a null pointer cannot add");
  }
  tagPosts.push_back(post);
}
