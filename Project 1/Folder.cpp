/*
Author: Fabiola Li Wu
Course: CSCI-33500
Date: 09/27/2024

Folder.cpp implements the Folder class' functions
*/
#include "Folder.hpp"

/**
* @brief Construct a new Folder object
* @param name A string with alphanumeric characters.
   If the folder name is empty / none is provided, default value of "NewFolder" is used.
* @throw If the name is invalid (eg. contains non-alphanumeric characters) an InvalidFormatException is thrown
*/
Folder::Folder(const std::string &name) : name_{"NewFolder"}
{
   if (name.empty())
   {
      return;
   }

   for (const char &c : name)
   {
      if (!std::isalnum(c))
      {
         // We have found a non-alphanumeric character
         throw InvalidFormatException("Invalid folder name: " + name);
      }
   }

   name_ = name;
}

/**
 * @brief Get the value stored in name_
 * @return std::string
 */
std::string Folder::getName() const
{
   return name_;
}

/**
 * @brief Sets the name_ member to the given parameter
 *
 * @param new_foldername A string containing only alphanumeric characters
 *    - If the string is invalid the folder is not renamed
 * @return True if the folder was renamed sucessfully. False otherwise.
 */
bool Folder::rename(const std::string &name)
{
   for (const char &c : name)
   {
      if (!std::isalnum(c))
      {
         return false;
      }
   }

   name_ = name;
   return true;
}

/**
 * @brief Sorts and prints the names of subfolder and file vectors lexicographically (ie. alphabetically)
 * The contents of subfolders are not printed.
 * Reference the following format (using 3 spaces to indent the contained filenames)
 * <CURRENT_FOLDER_NAME>
 *    <SUBFOLDER1_NAME>
 *    <SUBFOLDER2_NAME>
 *    ...
 *    <SUBFOLDER_N_NAME>
 *    <FILENAME_1>
 *    <FILENAME_2>
 *     ...
 *    <FILENAME_N>
 *
 * @note: This CAN be done more efficiently by maintaining sorted order in the vectors already, instead of sorting each time we print.
 *    However, we'll hold off on that for now, since we just want to get used to iterating with iterators.
 */
void Folder::display()
{
   std::sort(files_.begin(), files_.end());

   std::cout << getName() << std::endl;
   for (auto it = files_.begin(); it != files_.end(); ++it)
   {
      std::cout << "   " << it->getName() << std::endl;
   }
}

//                       DO NOT EDIT ABOVE THIS LINE.
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp
// =========================== YOUR CODE HERE ===========================

/**
 * @brief Iterate through the files vector, calculating the total size of all child files
 * @return size_t The total size of all child files
 */
size_t Folder::getSize() const
{
   size_t size = 0;
   for (std::vector<File>::const_iterator it = files_.begin(); it != files_.end(); ++it)
      size += it->getSize();
   return size;
}

/**
 * @brief Appends the given file to the files_ vector using move_semantics on the parameter File object, if a file with the
 *  same name does not exist within the files_ vector
 *    (HINT!) Consider push_back(). What happens when we give it an l-value vs. an r-value? Does it change anything?
 *
 * @param new_file A reference to a File object to be added. If the name of the File object is empty
 * (ie. its contents have been taken via move) then add fails
 * @return True if the file was added successfully. False otherwise.
 * @post If the file was added, leaves the parameter File object in a valid but unspecified state
 */
bool Folder::addFile(File &new_file)
{
   // std::cout << "Entered to addFile function" << std::endl;
   if (new_file.getName().empty())
   {
      return false;
   }

   // checks if name is already in vector
   for (const auto &file : files_)
   {
      if (file.getName() == new_file.getName())
         return false;
   }

   // std::cout << "gone through check name in vector" << std::endl;
   files_.push_back(std::move(new_file));
   // std::cout << "Added" << std::endl;

   return true;
}

/**
 * @brief Searches for a file within the files_ vector to be deleted.
 * If a file object with a matching name is found, erase it from the vector in linear [O(N)] time or better.
 * Order does not matter.
 *
 * @param name A const reference to a string representing the filename to be deleted
 * @return True if the file was found & successfully deleted.
 */
bool Folder::removeFile(const std::string &name)
{
   for (std::vector<File>::iterator it = files_.begin(); it != files_.end(); ++it)
   {
      if (it->getName() == name)
      {
         files_.erase(it);
         return true;
      }
   }
   return false;
}

/**
 * @brief Moves a file from the current folder to a specified folder
 * If a matching name is found, use move semantics to move the object from the current directory to the file vector within the destination folder'
 *    and erase it from the current folder.
 * If a matching name is not found within the source folder or an object with the same name already exists within the
 *    destination folder, nothing is moved.
 * If the source folder and destination folders are the same, the move is always considered successful.
 *
 * @param name The name of the file to be moved, as a const reference to a string
 * @param destination The target folder to be moved to, as a reference to a Folder object
 * @return True if the file was moved successfully. False otherwise.
 */
bool Folder::moveFileTo(const std::string &name, Folder &destination)
{
   // If the source folder and destination folders are the same, the move is always considered successful.
   if (this->getName() == destination.getName())
      return true;

   // check if the same name is in the destination folder or not
   for (std::vector<File>::iterator it = destination.files_.begin(); it != destination.files_.end(); ++it)
   {
      if (it->getName() == name)
         return false;
   }

   // if name is found local folder, then move the file by using move semantic to destination folder
   for (std::vector<File>::iterator it = files_.begin(); it != files_.end(); ++it)
   {
      if (it->getName() == name)
      {
         destination.files_.push_back(std::move(*it));
         removeFile(name);
         return true;
      }
   }
   return false;
}

/**
 * @brief Copies a file within the current folder to the destination folder.
 * If there is already an object with the same name in the destination folder,
 *    or the object with the specified name does not exist, do nothing.
 * Otherwise, if there exists a file with the given name from the source folder,
 *    use the copy constructor or assignment operations to create a deep copy of the
 *    the file into the destination.
 *
 * @param name The name of the copied object, as a const string reference
 * @param destination The destination folder, as a reference to a Folder object
 * @return True if the file was copied successfully. False otherwise.
 */
bool Folder::copyFileTo(const std::string &name, Folder &destination)
{
   // same name as in destination, then dont do anything
   for (std::vector<File>::iterator it = destination.files_.begin(); it != destination.files_.end(); ++it)
   {
      if (it->getName() == name)
         return false;
   }

   // search locally for the file that we want to copy
   for (std::vector<File>::iterator it = files_.begin(); it != files_.end(); ++it)
   {
      if (it->getName() == name)
      {
         File file(*it);
         destination.addFile(file);
         return true;
      }
   }
   return false;
}
