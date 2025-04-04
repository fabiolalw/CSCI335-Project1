/*
Author: Fabiola Li Wu
Course: CSCI-33500
Date: 11/27/2024

Solution.cpp implements the FileTrie class' functions and some other functions
*/
#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp
// helper funciton for 
void getInOrder(Node* root, size_t min, size_t max, std::vector<File*>& result) {
    if(root == nullptr) {return;}
    if(root->size_ > min)
        getInOrder(root->left_, min, max, result);
    if(root->size_ >= min && root->size_ <= max){
        for(auto& file : root->files_){
            if(file->getSize() >= min && file->getSize() <= max){
                result.push_back(file);
            }
        }
    }
    if(root->size_ < max)
        getInOrder(root->right_, min, max, result);
}
// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

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
    getInOrder(root_, min, max, result);
    return result;
}

// Default constructor
FileTrie::FileTrie(){
    head = new FileTrieNode();
}

 // Add file, ignore case
void FileTrie::addFile(File* f){
    std::string lowerCaseName = f->getName();
    for (char& character : lowerCaseName) {
        character = std::tolower(character);
    }
    head->matching.insert(f);
    FileTrieNode* current = head;
    for(auto&character : lowerCaseName){
        FileTrieNode* found = nullptr;

        // find the node in the vector
        for(auto&node : current->next){
            if(node->stored == character){
                found = node;
                break;
            }
        }
        if(found == nullptr){
            FileTrieNode* newNode = new FileTrieNode(character, f);
            current->next.push_back(newNode);
            found = newNode;
        }
        current = found;
        current->matching.insert(f);

        // this ia for map
        // if(current->next.find(character) == current->next.end()){
        //     current->next[character] = new FileTrieNode(character);
        // }
        // current = current->next[character];
        // current->matching.insert(f);
    }
}

// The implementation of a prefix trie using for efficient prefix search. This trie differs from a standard trie in that at each node, 
//it will hold all files whose names begin with the prefix defined by the path leading to that node. This is a significant trade-off of 
//space for time.
// In struct FileTrieNode:
// - stored is the character that leads to the node. It is not actually needed, but it's useful for debugging.
// - matching is the set of pointers to Files whose filenames start with the prefix corresponding to the path leading to the node.
// - next is the set of the node's child pointers. Each node can have a child for each letter, so we use a map to efficiently map each 
//letter to the corresponding child node.
// Additional specifications:
// - The root, representing the empty string (0 characters), should hold a pointer to every File.
// - The search should support a filename and extension, e.g. importantstuff.doc
// - The actual file system is not part of this project, so there are no file paths or directories, just filenames with extensions.
// - Characters allowed are a-z, 0-9, and . (period).
// - The search should be case-insensitive.
// Search
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const{
    std::string lowerCasePrefix = prefix;
    for (char& character : lowerCasePrefix) {
        character = std::tolower(character);
    }
    
    FileTrieNode* current = head;
    for(auto&character : lowerCasePrefix){
        FileTrieNode* found = nullptr;

        // find the node in the vector 
        for(auto&node : current->next){
            if(node->stored == character){
                found = node;
                break;
            }
        }
        if(found == nullptr){
            return {};
        }
        current = found;

        // this is for map
        // if(current->next.find(character) == current->next.end()){
        //     return {};
        // }
        // current = current->next[character];
    }
    return current->matching;
}

//Destructor
FileTrie::~FileTrie(){
    std::queue<FileTrieNode*> deleteNode;
    deleteNode.push(head);
    while(!deleteNode.empty()){
        FileTrieNode* current = deleteNode.front();
        deleteNode.pop();
        for(auto&node : current->next)
            deleteNode.push(node);
        delete current;
    }
}

// int main(){
//     File first("apple.txt", "This is the first file");
//     File second("abricot.txt", "This is the second file");
//     File third("lalala.txt", "This is the third file");
//     File fourth("abee.txt", "This is the fourth file");
//     FileTrie trie;
//     trie.addFile(&first);
//     trie.addFile(&second);
//     trie.addFile(&third);
//     trie.addFile(&fourth);
//     //std::cout << trie.getHeadMactchingSize() << std::endl;
//     //std::unordered_set<File*> matching = trie.getHeadMatchingFiles();
//     // for(auto&file : matching){
//     //     std::cout << file->getName() << std::endl;
//     // }
//     std::unordered_set<File*> prefixFiles = trie.getFilesWithPrefix("A");
//     std::cout << prefixFiles.size() << std::endl;
//     for(auto&file : prefixFiles){
//         std::cout << file->getName() << std::endl;
//     }
//     return 0;
// }