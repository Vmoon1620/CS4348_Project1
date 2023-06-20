/*
In this project, you will use ordinary pipes to implement an inter-process communication scheme for message
passing between processes. Assume there are two directories, d1 and d2, and there are three different files in each one
of them. the names of files in d1 are different from the names of files in d2. Each file contains a short-length string of
characters. You have to use a parent process that forks two children processes, and have each child process check one
of the directories.
• Assume that child 1 (child 2) is responsible to check the directory d1 (directory d2, respectively). This child
process has to create a list of names of the files in the directory and be able to open and read the contents of the
files.
• After creating the list, each child process will send its list to the other child process using a pipe.
• Upon receiving the list, child 2 (child 1) will create the files listed by child 1 (child 2) in directory d2 (directory
d1, respectively);
• Each child process will send to the other child process, using pipes, the contents of the files in its directory. The
receiving child should populate the files with their corresponding received contents.
After these steps, the directories d1 and d2 should be identical in terms of the list of files, and the contents of the files.
In your code you should not make any assumption about the size of files.
*/

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <fstream>


int main(int argc, char * argv[]) {

  pid_t child1, child2;

  child1 = fork();

  if (child1 == 0) {
    std::cout << "we are in the child process #1 \n" << std::endl;
   

    const char * directoryPathforD1 = "/workspaces/CS4348_Project1/Directory1";


    DIR * directory1;
    struct dirent * entry;
    std::vector<std::string> fileList;
    

    directory1 = opendir(directoryPathforD1);

    if (directory1 == nullptr) {
      std::cerr << "Failed to open directory." << std::endl;
      exit(1);
    }

    while((entry = readdir(directory1)) != nullptr){
      // this will skip the deault '.' and '..' entries
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry ->d_name, "..") ==0){
        continue;
      }

      //getting the file name
      std::string fileName = entry->d_name;
      fileList.push_back(fileName);

      //this will opena nd read the conents of the files
      std::ifstream file("/workspaces/CS4348_Project1/Directory1/" + fileName);
      if(file.is_open()){
        std::string line;
        std::cout << "contents of " << fileName << ":"<< std::endl;
        while (std::getline(file,line)){
          std::cout << line <<std::endl;
        }
        file.close();
        std::cout << std::endl;
      } else{
        std::cerr << "failed to open file: " << fileName << std::endl;
      }
    }
    /* this does the cout of the name of the files to make sure it was working
    dirent * file;
    while ((file = readdir(directory1)) != nullptr) {
      std::cout << file -> d_name << std::endl;
    }
    */

    closedir(directory1);

    std::cout << "list of files in directory 1" << std::endl;
    for(const auto& fileName : fileList){
      std::cout << fileName << std::endl;
    }
    std::cout << std::endl;

  } else {
    child2 = fork();

    if (child2 == 0) {
      std::cout << "we are in the child process #2" << std::endl;
      

      const char * directoryPathforD2 = "/workspaces/CS4348_Project1/Directory2";
      DIR * directory2;
      struct dirent*entry;
      std::vector<std::string> fileList;

      directory2 = opendir(directoryPathforD2);

      if (directory2 == nullptr) {
        std::cout << "Failed to open directory." << std::endl;
        return 1;
      }

      while((entry = readdir(directory2)) != nullptr){
      // this will skip the deault '.' and '..' entries
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry ->d_name, "..") ==0){
        continue;
      }

      //getting the file name
      std::string fileName = entry->d_name;
      fileList.push_back(fileName);

      //this will opena nd read the conents of the files
      std::ifstream file("/workspaces/CS4348_Project1/Directory2/" + fileName);
      if(file.is_open()){
        std::string line;
        std::cout << "contents of " << fileName << ":"<< std::endl;
        while (std::getline(file,line)){
          std::cout << line <<std::endl;
        }
        file.close();
        std::cout << std::endl;
      } else{
        std::cerr << "failed to open file: " << fileName << std::endl;
      }
    }

      /*
      dirent * file;
      while ((file = readdir(directory2)) != nullptr) {
        std::cout << file -> d_name << std::endl;
      }
      */
      closedir(directory2);


      std::cout << "list of files in directory 2" << std::endl;
    for(const auto& fileName : fileList){
      std::cout << fileName << std::endl;
    }
    std::cout << std::endl;

    } else {
      waitpid(child1, NULL, 0);
      waitpid(child2, NULL, 0);

    }
  }
}

