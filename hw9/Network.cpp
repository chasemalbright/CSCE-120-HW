/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;

bool isNum(char x){
    switch(x){
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            return true;
        default:
            return false;
    }
}

vector<string> lineToVector(string postText){
    vector<string> holder;
    
    string temp = "";
    for (int i = 0; i < postText.size(); i++){
        if (postText[i]== ' '){
            holder.push_back(temp);
            temp = "";
        } else {
            temp.push_back(postText[i]);
        }
        
    }
    holder.push_back(temp);
    return holder;
}

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {

  std::ifstream ifs(fileName);

  //check if file can be opened
  if (!ifs.is_open()){
    throw std::invalid_argument("File could not be opened");
  }

  // read in file line by line 

  string line;

  while (getline(ifs, line)){
  
    if (line[0] == 'U'){ // handle user
      vector<string> linevector = lineToVector(line);
      if (linevector.size() != 2){
        throw std::runtime_error("wrong format for user name must be two words");
      }

      if (linevector.size() ==2){
        if (linevector[0] != "User"){
          throw std::runtime_error("Wrong enrty, must be *User*");
        }

        try{
          addUser(linevector[1]);
        } catch (const std::invalid_argument& e){
          throw std::runtime_error("could not add user");
        }
        
      }

    } else if (line[0] == 'P'){ //handle post
      // ********
        vector<string> linevector = lineToVector(line);
        if (linevector.size() < 4){
            throw std::runtime_error("bad format too short");
        }
        for (int i =0; i < linevector[1].size(); i++){
            if(isNum(linevector[1][i]) == false){
                throw std::runtime_error("id is wrong format");
            }
        }
        
        if (isNum(linevector[2][0])){
            throw std::runtime_error("user cannot start with number");
        }
        
        std::string postData = "";
        for (int i = 3; i < linevector.size()-1 ; i++){
            postData += linevector[i] + " ";
        }
        postData += linevector[linevector.size()-1];
      // ********

      try {
        addPost(std::stoul(linevector[1]), linevector[2], postData);
      } catch (const std::invalid_argument& e) {
        throw std::runtime_error("could not add post");
      }
    } else {
      throw std::runtime_error("wrong format in file or unknown entry");
    }
  }


}

void Network::addUser(string userName) {
  string toLower = userName;
  for (long unsigned int i = 0; i < toLower.length(); i++){
    toLower[i] = tolower(toLower[i]);
  }

  int countDuplicateUsers = 0;
  for (long unsigned int i = 0; i < users.size(); i ++){
    string name = users[i]->getUserName();
    if(name == toLower){
      countDuplicateUsers++;
    }
  }

  if (countDuplicateUsers != 0){
    throw std::invalid_argument("userName already exist");
  }

  User* newUser = new User(toLower);
  users.push_back(newUser);

  std::cout << "Added User " << toLower << std::endl;

}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network
  
  //check if id exists
  int countDuplicateId = 0;
  for (long unsigned int i = 0; i < posts.size(); i ++){
    unsigned int id = posts[i]->getPostId();
    if (postId == id){
      countDuplicateId++;
    }
  }
  if(countDuplicateId != 0){
    throw std::invalid_argument("post with this id already exists!");
  }

  //check if user name exists
  int countUser = 0;
  for (long unsigned int i = 0; i < users.size(); i ++){
    string name = users[i]->getUserName();
    if(name == userName){
      countUser++;
    }
  }
  if(countUser == 0){
    throw std::invalid_argument("no user with this name exists!");
  }

  //create and add new post to <posts>
  Post* newPost = new Post(postId, userName, postText);
  posts.push_back(newPost);

  //add post to corresponding user
  for (long unsigned int i = 0; i < users.size(); i ++){
    string name = users[i]->getUserName();
    if(name == userName){
      users[i]->addUserPost(newPost);
    }
  }

  //extracting tags from postText
  std::vector<string> potentialTags = newPost->findTags();
  ///////////////////////////////TESTAREA////////////

  /////////////////////////////////

  for (long unsigned int i = 0; i < potentialTags.size(); i++){
    int countDuplicateTag = 0;
    for (long unsigned int j = 0; j < tags.size(); j++){
      string name = tags[j]->getTagName();
      if (potentialTags[i] == name){
        tags[j]->addTagPost(newPost);
      }
    }

    //add tag if it does not exist


    try {
      Tag* newTag = new Tag(potentialTags[i]);
      //if (newTag != nullptr){
      tags.push_back(newTag);
      newTag->addTagPost(newPost);

      //}
    } catch(const std::invalid_argument& e) {
      std::cerr << "Error: Invalid Argument: " << e.what() << std::endl;
    }

    
  }
  
  std::cout << "Added Post "<< postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
  if (userName == "" || userName == " "){
    throw std::invalid_argument("username cannot be empty!");
  }
  
  std::vector<Post*> postByUser;

  for (int i = 0; i < users.size(); i++){
    string currName = users[i]->getUserName();
    if (userName == currName){
      postByUser = users[i]->getUserPosts();
      return postByUser;
    }
  } 
  //***
  throw std::invalid_argument("username not found cannot return posts");
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
  if (tagName == "" || tagName == " "){
    throw std::invalid_argument("tagname cannot be empty!");
  }
  std::vector<Post*> postsWithTag;

  for (int i =0; i < tags.size(); i++){
    string currTag = tags[i]->getTagName();
    if (tagName == currTag){
      postsWithTag = tags[i]->getTagPosts();
      return postsWithTag;
    }
  }
  throw std::invalid_argument("tagname not found cannot return posts");
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts

  vector<string> hashtags;
  for (int i = 0; i < posts.size(); i++){
    vector<string> currTags = posts[i]->findTags();

    for (int i = 0; i < currTags.size(); i++){
      hashtags.push_back(currTags[i]);
    }
  }


  vector<string> most;
  int bestCount = 0;
  string mostOccuring = "";
  for (int i = 0; i < hashtags.size(); i++){
    int currCount = 0;
    for (int j = 0; j < hashtags.size(); j++){
      if (hashtags[j] == hashtags[i]){
        currCount++;
      }
    }
    if (currCount > bestCount){
      most.clear();
      most.push_back(hashtags[i]);
      bestCount = currCount;
    }
    if (currCount == bestCount){
      most.push_back(hashtags[i]);
    }
  }

  //return most;

  vector<string> next;
  next.push_back(most[0]);
  for (int i =0; i < most.size(); i++){
    if (next[0] != most[i]){
      next.push_back(most[i]);
    }
    // for (int j =0; j < most.size(); j++){

    // }
  }
  return next;

}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
