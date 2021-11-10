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
#include <string>
#include <stdexcept>
#include <vector>
#include "Post.h"

using std::string;
using std::vector;


Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
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
    
    vector<string> hashtags;
    
    for (int i = 0; i < holder.size(); i++){
        if (holder[i][0] == '#'){
            string word = holder[i].substr(1);
            for (int i = 0; i < word.length(); i++){
  		        word[i] = tolower(word[i]);
  	        }
            
            while(word[word.size()-1] =='!' || word[word.size()-1] ==',' || word[word.size()-1] =='.' || word[word.size()-1] =='?'){
                word.pop_back();
            }
            word.insert(0, "#");
            hashtags.push_back(word);
        }
    }
    
    return hashtags;
}
