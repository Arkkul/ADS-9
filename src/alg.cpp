// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>
#include "tree.h"

namespace {

void DfsPerms(PMTree::Node* node,
              std::vector<char>& current,
              std::vector<std::vector<char>>& result) {
  if (node == nullptr) {
    return;
  }

  if (node->value != '\0') {
    current.push_back(node->value);
  }

  if (node->children.empty()) {
    result.push_back(current);
  } else {
    for (PMTree::Node* child : node->children) {
      DfsPerms(child, current, result);
    }
  }

  if (node->value != '\0') {
    current.pop_back();
  }
}

int64_t Factorial(int n) {
  int64_t result = 1;

  for (int i = 2; i <= n; ++i) {
    result *= i;
  }

  return result;
}

}  // namespace

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;

  DfsPerms(tree.root(), current, result);

  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> perms = getAllPerms(tree);

  if (num < 1 || num > static_cast<int>(perms.size())) {
    return {};
  }

  return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  const int n = tree.size();

  if (num < 1 || num > Factorial(n)) {
    return {};
  }

  --num;

  std::vector<char> result;
  PMTree::Node* node = tree.root();

  for (int i = 0; i < n; ++i) {
    int64_t block = Factorial(n - i - 1);

    int index = static_cast<int>(num / block);

    if (index >= static_cast<int>(node->children.size())) {
      return {};
    }

    node = node->children[index];
    result.push_back(node->value);

    num %= block;
  }

  return result;
}
