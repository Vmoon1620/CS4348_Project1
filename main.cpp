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




int main(int argc, char* argv[]) {

    //this strip will successfully open directory #1, this is the pwd for D1
   

    pid_t pid = fork();




if (pid < 0){
    std::cerr << "Fork failed" << std::endl;
    return 1;
}
else if (pid == 0){
    std::cout << "we are in the child process" << std::endl;
    

    const char* directoryPathforD1 = "/workspaces/CS4348_Project1/Directory1"; 
    DIR* directory1;

    directory1 = opendir(directoryPathforD1);
    
    if (directory1 == nullptr) {
        std::cout << "Failed to open directory." << std::endl;
        return 1;
    }

    dirent* file;
    while ((file = readdir(directory1)) != nullptr) {
        std::cout << file->d_name << std::endl;
    }

    closedir(directory1);
}
else {
       std::cout << "we are in the parent process" << std::endl;


       const char* directoryPathforD2 = "/workspaces/CS4348_Project1/Directory2";
       DIR* directory2;

    directory2 = opendir(directoryPathforD2);
    
    if (directory2 == nullptr) {
        std::cout << "Failed to open directory." << std::endl;
        return 1;
    }

    dirent* file;
    while ((file = readdir(directory2)) != nullptr) {
        std::cout << file->d_name << std::endl;
    }

    closedir(directory2);


}

    
}

/*
    DIR* directory;
    struct dirent* entry;


  
     // Open the specified directory
    directory = opendir(directoryPathforD1);
   
     if (directory) {
        // Iterate over each entry in the directory
        while ((entry = readdir(directory)) != nullptr) {
            std::cout << entry->d_name << std::endl;
        }

        // Close the directory
        closedir(directory);
    } else {
        std::cerr << "Failed to open the directory." << std::endl;
        return 1;
    }
  
    return 0;
    */


/*
    const char* directoryPath = "/home/vmoon/d1"; 

    DIR* directory;
    struct dirent* entry;

     // Open the specified directory
    directory = opendir(directoryPath);

     if (directory) {
        // Iterate over each entry in the directory
        while ((entry = readdir(directory)) != nullptr) {
            std::cout << entry->d_name << std::endl;
        }

        // Close the directory
        closedir(directory);
    } else {
        std::cerr << "Failed to open the directory." << std::endl;
        return 1;
    }
*/