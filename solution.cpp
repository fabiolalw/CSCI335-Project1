#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp


/**
 * @brief Helper for displayInOrder(). Prints the unique file sizes in-order given a specified root
 * @param root The root of the tree to be printed
 */
void getInOrder(Node* root, size_t min, size_t max, std::vector<File*>& result, bool swapped) {
    if(root == nullptr) {return;}
    if(root->size_ > min)
        getInOrder(root->left_, min, max, result, swapped);
    if(root->files_.size() >= min && root->files_.size() <= max)
        if(swapped)
            result.insert(result.end(), root->files_.rbegin(), root->files_.rend());
        else
            result.insert(result.end(), root->files_.begin(), root->files_.end());
    if(root->size_ < max)
        getInOrder(root->right_, min, max, result, swapped);
}
/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */
std::vector<File*> FileAVL::query(size_t min, size_t max) {
    std::vector<File*> result;
    bool swapped = false;
    if(min > max){
        std::swap(min, max);
        swapped = true;
    }
    getInOrder(root_, min, max, result, swapped);
    if (swapped) 
        std::reverse(result.begin(), result.end());
    return result;
}

 // Add file, ignore case
void FileTrie::addFile(File* f){

}

// Search
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const{
    return std::unordered_set<File*>();
}

        // Destructor
FileTrie::~FileTrie(){
    delete head;
}
