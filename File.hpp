/*
Author: Fabiola Li Wu
Course: CSCI-33500
Date: 09/27/2024

File.hpp declares the File class along with its private and public members
*/
#pragma once

#include "InvalidFormatException.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <algorithm>

class File
{
private:
   std::string filename_;
   std::string contents_;
   int *icon_;

   static const size_t ICON_DIM = 256; // Representing a 16 x 16 bitmap

public:
   /**
    * @brief Enables printing the object via std::cout
    */
   friend std::ostream &operator<<(std::ostream &os, const File &target);

   /**
    * @brief Overloads the less than comparison operator.
    * @return True if the name of the File alphabetically precedes the name of the rhs. False otherwise.
    */
   bool operator<(const File &rhs) const;

   /**
    * @brief Get the value stored in name_
    */
   std::string getName() const;

   /**
    * @brief Get the value of contents_
    */
   std::string getContents() const;

   /**
    * @brief Set the value of contents_ to the provided string
    *
    * @param new_contents A string representing the new contents of the file
    */
   void setContents(const std::string &new_contents);

   /**
    * @brief Gets the value of the icon_ member
    */
   int *getIcon() const;

   /**
    * @brief Sets the value of icon_ to the given parameter. De-allocates the previous array if necessary.
    * @param new_icon A pointer to a length 256 (ie. ICON_DIM) array of unsigned 8 bit integers
    */
   void setIcon(int *new_icon);

   //                       DO NOT EDIT ABOVE THIS LINE.
   //                  (with exceptions to include statements)
   // =========================== YOUR CODE HERE ===========================

   File(const std::string &filename = "NewFile.txt", const std::string &contents = "", int *icon = nullptr);
   size_t getSize() const;
   File(const File &rhs);
   File &operator=(const File &rhs);
   File(File &&rhs);
   File &operator=(File &&rhs);
   ~File();
};
