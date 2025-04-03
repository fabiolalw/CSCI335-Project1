#include <iostream>
#include "Folder.hpp"

int main()
{
    // std::cout << "Hello World" << std::endl;
    int *icon = new int[2];
    File file("NewFolderAlpha.txt", "7878", icon);
    // std::string name = file.getName();
    // std::cout << name << std::endl;
    File file2("dddc", "ee", icon);
    File file3("dwd", "ffc", icon);

    // std::cout << "Hello World" << std::endl;
    //  std::cout << file.getName() << std::endl;
    //   File file1("Beta.txt", "jhj");

    // File file2("ccc", "h");
    Folder folder("filesSaved");

    std::cout << "Added? " << folder.addFile(file) << std::endl
              << std::endl;
    std::cout << "Added? " << folder.addFile(file2) << std::endl;
    std::cout << "Added? " << folder.addFile(file3) << std::endl;
    folder.removeFile("NewFolderAlpha.txt");
    folder.display();

    // icon = nullptr;
    return 0;
}