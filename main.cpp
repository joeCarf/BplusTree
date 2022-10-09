//
// Created by 乔奥 on 2022/10/9.
//

#include "BplusTree.h"
#include <string>
using namespace std;
using namespace BplusTree;

int main() {
    Virtual_Node<int, string>* node = new Virtual_Node<int, string>();
    Leaf_Node<int, string>* node2 = new Leaf_Node<int, string>();
    Non_Leaf_Node<int, string>* node3 = new Non_Leaf_Node<int, string>();
};
