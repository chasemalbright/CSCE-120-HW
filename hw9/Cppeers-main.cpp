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
#include "Network.h"

using std::cout, std::cin, std::endl;
using std::string, std::vector;

void printMenu() {
  cout << "Welcome to CPPeers" << endl;
  cout << "The options are: " << endl;
  cout << "1. load data file and add information" << endl;
  cout << "2. show posts by user" << endl;
  cout << "3. show posts with hashtag" << endl;
  cout << "4. show most popular hashtag" << endl;
  cout << "9. quit" << endl;
  cout << "--------> Enter your option: ";
}

void processLoad(Network& cppeers) {
  string fileName = "";
  cout << "Enter filename: ";
  cin >> fileName;
  cppeers.loadFromFile(fileName);
}

void processPostsByUser(Network& cppeers) {
  // TODO(student): implement
  string userName = "";
  cout << "Enter username: ";
  std::cin >> userName;
  std::vector<Post*> userposts = cppeers.getPostsByUser(userName);
  for (int i = 0; i < userposts.size(); i++){
    string data = userposts[i]->getPostText();
    cout << data << endl;
  }
  cout << endl;
}

void processPostsWithHashtags(Network& cppeers) {
  // TODO(student): implement
  string tag = "";
  cout << "Enter tagname: ";
  std::cin >> tag;
  std::vector<Post*> postlist = cppeers.getPostsWithTag(tag);
  for (int i = 0; i < postlist.size(); i++){
    string data = postlist[i]->getPostText();
    cout << data << endl;
  }
  cout << endl;
}

void processMostPopularHashtag(Network& cppeers) {
  // TODO(student): implement
  std::vector<string> poptags= cppeers.getMostPopularHashtag();
  for (int i = 0; i < poptags.size(); i++){
    cout << poptags[i] << endl;
  }
  cout << endl;
}

int main() {

  // Network test;
  // test.loadFromFile("valid_file.txt");
  // cout << std::endl;

  // std::vector<Post*> x = test.getPostsWithTag("#dynamic");
  // cout << x.size() << endl;

  // for (int i =0; i < x.size(); i++){
  //   cout << x[i]->getPostId() << std::endl;
  // }

  // std::vector<string> hashtags = test.getMostPopularHashtag();
  // for (int i = 0; i < hashtags.size(); i++){
  //   cout << hashtags[i] << endl;
  // }


  try {
    Network cppeers;

    int choice = 0;

    // present menu
    do {
      printMenu();
      cin >> choice;
      switch(choice) {
        case 1: {
          processLoad(cppeers);
          break;
        }
        case 2: {
          processPostsByUser(cppeers);
          break;
        }
        case 3: {
          processPostsWithHashtags(cppeers);
          break;
        }
        case 4: {
          processMostPopularHashtag(cppeers);
          break;
        }
      }
    } while (choice != 9);
  } catch (std::exception& exc) {
    std::cout << exc.what() << endl;
  }

  return 0;
}
