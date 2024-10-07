
/*
Author: Fabiola Li Wu
Course: CSCI-33500
Date: 09/27/2024

File.cpp implements the File class' functions including the Big 5
*/
#include "File.hpp"

std::string File::getName() const
{
   return filename_;
}

std::string File::getContents() const
{
   return contents_;
}

void File::setContents(const std::string &new_contents)
{
   contents_ = new_contents;
}

int *File::getIcon() const
{
   return icon_;
}

void File::setIcon(int *new_icon)
{
   if (icon_)
   {
      delete[] icon_;
   }
   icon_ = new_icon;
}

std::ostream &operator<<(std::ostream &os, const File &target)
{
   os << "Name: " << target.getName() << std::endl;
   os << "Size: " << target.getSize() << " bytes" << std::endl;
   os << "Contents: " << target.getContents();
   return os;
}

bool File::operator<(const File &rhs) const
{
   return getName() < rhs.getName();
}

//                       DO NOT EDIT ABOVE THIS LINE.
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp

// However, you may notice an operator overload you don't recognize (<<)
// Try calling the following once you've implemented a constructor & getSize():
//    File a;
//    std::cout << a << std::endl;

// =========================== YOUR CODE HERE ===========================

/**
 * @brief Constructs a new File object.
 * @param filename A const reference to a string containing alphanumeric characters and exactly one period in the format "filename" or "filename.extension"
 *    - If the string contains any non-alphanumeric characters besides *exactly_one* period an InvalidFormatException is thrown
 *    - If no extension is provided (e.g. there is no period within the provided filename) or nothing follows the period, then ".txt" is used as the extension
 *    - Default value of "NewFile.txt" if none provided or if filename is empty
 * @param contents A string representing the contents of the file. Default to empty string if none provided.
 * @param icon A pointer to an integer array with length ICON_DIM. Default to nullptr if none provided.
 * @throws InvalidFormatException - An error that occurs if the filename is not valid by the above constraints.
 * @note You'll notice we provide a default value for the first possible argument (filename)
 *       Yes, this means we can define override the default constructor and define a parameterized one simultaneously.
 */
File::File(const std::string &filename, const std::string &contents, int *icon) : contents_{contents}, icon_{icon}
{
   //   Default value of "NewFile.txt" if filename is empty
   if ((filename.size() <= 0) || (filename == " "))
      filename_ = "NewFile.txt";
   else
   {
      // counts the periods in it
      std::string name, extension;
      int periods = 0;
      bool alphabetic = true;
      for (int i = 0; (i < filename.size()) && (alphabetic == true); i++)
      {
         if (filename[i] == '.')
            periods++;

         // if contains more than one period, an exception is thrown
         if ((!isalnum(filename[i]) && filename[i] != '.') || (filename[i] == '.') && (periods > 1))
         {
            alphabetic = false;
            throw InvalidFormatException(filename);
         }
      }

      // modification of extension
      std::istringstream streamingSentence(filename);
      std::getline(streamingSentence, name, '.');
      std::getline(streamingSentence, extension);

      // handles the cases when there's a period
      if (periods == 1)
      {
         filename_ = filename;

         // when there is a period but nothing after the period
         if (extension.size() == 0)
            filename_ = filename + "txt";
      }

      // and when there is no period
      if (periods == 0)
         filename_ = filename + ".txt";
   }
}
/**
 * @brief Calculates and returns the size of the File Object (IN BYTES), using .size()
 * @return size_t The number of bytes the File's contents consumes
 * @note Consider this: how does this relate to the string's length? Why is that the case?
 */
size_t File::getSize() const
{
   return getContents().size();
}

/**
 * @brief (COPY CONSTRUCTOR) Constructs a new File object as a deep copy of the target File
 * @param rhs A const reference to the file to be copied from
 */
File::File(const File &rhs) : filename_{rhs.getName()}, contents_{rhs.getContents()}, icon_{nullptr}
{
   if (rhs.getIcon() != nullptr)
   {
      icon_ = new int[ICON_DIM];
      for (int i = 0; i < ICON_DIM; i++)
         icon_[i] = rhs.icon_[i];
   }
}

/**
 * @brief (COPY ASSIGNMENT) Replaces the calling File's data members using a deep copy of the rhs File.
 *
 * @param rhs A const reference to the File object to be copied
 * @return A reference to the new File copy
 * @note If copy assignment operator is invoked upon itself, do nothing.
 */
//
File &File::operator=(const File &rhs)
{
   if (this != &rhs)
   {
      contents_ = rhs.contents_;
      filename_ = rhs.filename_;
      delete[] icon_;
      icon_ = new int[ICON_DIM];
      for (int i = 0; i < ICON_DIM; i++)
         icon_[i] = rhs.icon_[i];
   }
   return *this;
}
/**
 * @brief (MOVE CONSTRUCTOR) Construct a new File object by moving the data from the righthand side File Object
 * @param rhs The File whose data is moved
 * @post The rhs File object is left in a valid, but ready to be deleted state:
 *    - All string members are themselves moved.
 *    - ALl pointers are set to nullptr
 */
File::File(File &&rhs) : filename_{rhs.filename_}, contents_{rhs.contents_}, icon_{rhs.icon_}
{
   contents_ = std::move(rhs.contents_);
   filename_ = std::move(rhs.filename_);
   icon_ = std::move(rhs.icon_);
   rhs.icon_ = nullptr;
}
/**
 * @brief (MOVE ASSIGNMENT) Move the rhs data to the calling file object
 *
 * @param rhs The File whose data is moved
 * @return A reference to the object which the data was moved into
 * @post The rhs File object is left in a valid, but ready to be deleted state:
 *    - All string members are moved.
 *    - ALl pointers are set to nullptr
 * @note If move assignment operator is invoked upon itself, do nothing.
 */
File &File::operator=(File &&rhs)
{
   if (this != &rhs)
   {
      contents_ = std::move(rhs.contents_);
      filename_ = std::move(rhs.filename_);
      delete[] icon_;
      icon_ = rhs.icon_;
      rhs.icon_ = nullptr;
   }
   return *this;
}
/**
 * @brief (DESTRUCTOR) Routine for object deletion
 * @post All dynamically allocated memory is released
 */
File::~File()
{
   delete[] icon_;
   icon_ = nullptr;
}