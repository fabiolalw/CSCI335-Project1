/*
Author: Fabiola Li Wu
Course: CSCI-33500
Date: 09/27/2024

Folder.hpp declares the Folder class along with its private and public members
*/
#pragma once

#include "File.hpp"
#include "InvalidFormatException.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <iterator>

class Folder
{
private:
   std::string name_;
   std::vector<File> files_;

public:
   /**
   * @brief Construct a new Folder object
   * @param name A string with alphanumeric characters
      If the folder name is empty / none is provided, default value of "NewFolder" is used.
   * @throw If the name is invalid (eg. contains non-alphanumeric characters) an InvalidFormatException is thrown
   */
   Folder(const std::string &name = "NewFolder");

   /**
    * @brief Get the value stored in name_
    * @return std::string
    */
   std::string getName() const;

   /**
    * @brief Sets the name_ member to the given parameter
    *
    * @param name A string containing only alphanumeric characters
    *    - If the string is invalid the folder is not renamed
    * @return True if the folder was renamed sucessfully. False otherwise.
    */
   bool rename(const std::string &name);

   /**
    * @brief Sorts and prints the names of subfolder and file vectors lexicographically (ie. alphabetically)
    * The contents of subfolders are also printed.
    * Reference the following format (using 3 spaces to indent each directory layer)
    * (FOLDER) <CURRENT_FOLDER_NAME>
    *    <FILENAME_1>
    *    <FILENAME_2>
    *     ...
    *    <FILENAME_N>
    *
    */
   void display();

   //                       DO NOT EDIT ABOVE THIS LINE.
   //                  (with exceptions to include statements)
   // =========================== YOUR CODE HERE ===========================
   size_t getSize() const;
   bool addFile(File &new_file);
   bool removeFile(const std::string &name);
   bool moveFileTo(const std::string &name, Folder &destination);
   bool copyFileTo(const std::string &name, Folder &destination);
};