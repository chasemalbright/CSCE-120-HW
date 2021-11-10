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
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) : userName(userName) {
   if (userName == ""){
    throw std::invalid_argument("UserName cannot be empty");
  }

  string letters = "abcdefghijklmnopqrstuvwxyz";
  int count = 0;
  for (int i = 0; i < letters.size(); i++){
    if(letters[i] == userName[0]){
      count++;
    }
  }
  if (count == 0){
    throw std::invalid_argument("first character in userName was not a-z!");
  }

  string upperLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int countUpper = 0;
  for (int i = 0; i < userName.size(); i++){
    for (int j = 0; j < upperLetters.size(); j++){
      if (userName[i] == upperLetters[j]){
        countUpper++;
      }
    }
  }
  if (countUpper != 0){
    throw std::invalid_argument("userName must not contain upper case letters");
  }

}

string User::getUserName() {
  return userName;
}

vector<Post*>& User::getUserPosts() {
  return userPosts;
}

void User::addUserPost(Post* post) {
  if (post == nullptr){
    throw std::invalid_argument("userpost is a null pointer cannot add");
  }
  userPosts.push_back(post);
}
