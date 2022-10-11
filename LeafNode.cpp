//
// Created by 乔奥 on 2022/10/11.
//

#include "BPlusTree.h"

using namespace BPlusTree;

bool Leaf_Node::InsertKeyAndValue(int key, int value) {
    int index = 0;
    while ((index < key_count) && (key >= keys[index])) {
        index++;
    }
    for (int i = key_count; i > index; i--) {
        keys[i] = keys[i - 1];
        values[i] = keys[i - 1];
    }
    keys[index] = key;
    values[index] = value;
    key_count++;
    return true;
}

int Leaf_Node::SplitFromMidToNewNodeAndReturnsFirstKey(BPlusTree::Leaf_Node *new_node) {
    int new_node_key_count = 0;
    for (int i = MAX_KEY_COUNT_HALF; i < MAX_KEY_COUNT_HALF * 2; new_node_key_count++, i++) {
        new_node->keys[new_node_key_count] = this->keys[i];
        new_node->values[new_node_key_count] = this->values[i];
    }
    this->key_count = key_count - new_node_key_count;
    new_node->key_count = new_node_key_count;
    return new_node->keys[0];
}