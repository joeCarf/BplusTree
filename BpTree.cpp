//
// Created by 乔奥 on 2022/10/11.
//

#include "BPlusTree.h"

using namespace std;
using namespace BPlusTree;

int BpTree::Search(int key) {
    Leaf_Node* leafNode = FindLeafNodeByKey(key);
    if (leafNode == nullptr) {
        return -1; //B树不存在，暂定返回-1
    }

    //遍历搜索叶子节点
    //TODO 换成二分查找
    Leaf_Node *t = (Leaf_Node *) leafNode;
    int key_index = 0;
    for (; key_index < t->key_count; key_index++) {
        if (key == t->keys[key_index]) {
            return t->values[key_index];
        }
    }
    return -1;
}

bool BpTree::Insert(int key, int value) {
    //若key已经存在，则不允许插入
    //TODO 支持可重复key
    if (Search(key) != -1) {
        return false;
    }

    Leaf_Node* old_leaf_node = FindLeafNodeByKey(key);
    if (old_leaf_node == nullptr) { //若为空说明整棵树为空
        old_leaf_node = new Leaf_Node;
        root = old_leaf_node;
    }

    if (old_leaf_node->key_count < MAX_KEY_COUNT_HALF * 2) { //有空间则插入
        return old_leaf_node->InsertKeyAndValue(key,value);
    }
    
    //叶子节点分裂
    Leaf_Node* new_leaf_node = new Leaf_Node;
    int new_leaf_node_first_key = old_leaf_node->SplitFromMidToNewNodeAndReturnsFirstKey(new_leaf_node);
    
    //更新节点
    Leaf_Node* old_leaf_node_next = old_leaf_node->next_node;
    new_leaf_node->next_node = old_leaf_node_next;
    old_leaf_node->next_node = new_leaf_node;
    new_leaf_node->pre_node = old_leaf_node;
    if (old_leaf_node_next != nullptr) {
        old_leaf_node_next->pre_node = new_leaf_node;
    }
    
    if (key < new_leaf_node_first_key) {//小于newnode key[0]，插前面，否则插后面
        old_leaf_node->InsertKeyAndValue(key, value);
    } else {
        new_leaf_node->InsertKeyAndValue(key, value);
    }
    Non_Leaf_Node* old_node_parent = old_leaf_node->parent;

    if (old_node_parent == nullptr) { //若没有父结点，新建一个
        Non_Leaf_Node* new_root = new Non_Leaf_Node;
        new_root->children[0] = old_leaf_node;
        new_root->keys[0] = new_leaf_node_first_key;
        new_root->children[1] = new_leaf_node;
        old_leaf_node->parent = new_root;
        new_leaf_node->parent = new_root;
        root = new_root;
        return true;
    }

    return AddNewNodeToTree(old_node_parent, new_leaf_node_first_key, new_leaf_node);
}

Leaf_Node* BpTree::FindLeafNodeByKey(int key) {
    Virtual_Node *p = root;
    if (p == nullptr) {
        return nullptr; //树为空
    }

    //寻找叶子节点
    Non_Leaf_Node *q;
    while (p != nullptr) {
        if (p->isLeafNode) {
            break;
        }

        int index = 0; //选择子树的指针索引
        while ((index < p->key_count) && (key >= p->keys[index])) {
            index++;
        }
        if (index > 0) {
            index -= 1;
        }

        q = (Non_Leaf_Node *) p;
        p = q->children[index];
    }

    return (Leaf_Node*) p;
}

