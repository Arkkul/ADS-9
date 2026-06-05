// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 public:
  struct Node {
    char value;
    std::vector<Node*> children;

    explicit Node(char v) : value(v) {}
  };

 private:
  Node* root_;
  int size_;

  void build(Node* node, const std::vector<char>& symbols) {
    if (symbols.empty()) {
      return;
    }

    for (char ch : symbols) {
      Node* child = new Node(ch);
      node->children.push_back(child);

      std::vector<char> rest;

      for (char x : symbols) {
        if (x != ch) {
          rest.push_back(x);
        }
      }

      build(child, rest);
    }
  }

  void clear(Node* node) {
    if (node == nullptr) {
      return;
    }

    for (Node* child : node->children) {
      clear(child);
    }

    delete node;
  }

 public:
  explicit PMTree(const std::vector<char>& symbols) {
    root_ = new Node('\0');
    size_ = static_cast<int>(symbols.size());
    build(root_, symbols);
  }

  ~PMTree() {
    clear(root_);
  }

  Node* root() const {
    return root_;
  }

  int size() const {
    return size_;
  }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
