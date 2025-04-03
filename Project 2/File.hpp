#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <cstdint>
#include "InvalidFormatException.hpp"

class File {
   private:
      std::string filename_;
      std::string contents_;
      int* icon_;

      static const size_t ICON_DIM = 256; // Representing a 16 x 16 bitmap

   public: 
      File(const std::string& filename = "NewFile.txt", const std::string& contents = "", int* icon = nullptr);
      friend std::ostream& operator<< (std::ostream& os, const File& target);
      bool operator<(const File& rhs) const;
      std::string getName() const;
      std::string getContents() const;
      size_t getSize() const;
      int* getIcon() const;
      void setIcon(int* new_icon); 
      File(const File& rhs);
      File& operator=(const File& rhs);
      File(File&& rhs);
      File& operator=(File&& rhs);

      // Destructor
      ~File();
};