#include "../include/tree.h"
#include "zmq.h"

TreeNode* root = NULL;

void print_tree_recursive(TreeNode* node, int level) {
    if (node == NULL) {
        return;
    }
    print_tree_recursive(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("(%d, %d)\n", node->id, node->pid);
    print_tree_recursive(node->left, level + 1);
}

void print_tree(TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    printf("Binary Tree Structure:\n");
    print_tree_recursive(root, 0);
}

TreeNode* create_node(int node_id, pid_t process_id, const char* endpoint) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->id = node_id;
    node->pid = process_id;
    strcpy(node->endpoint, endpoint);
    node->available = true;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* insert_node(TreeNode* root, int node_id, pid_t process_id, const char* endpoint) {
    if (root == NULL) {
        return create_node(node_id, process_id, endpoint);
    }

    if (node_id < root->id) {
        root->left = insert_node(root->left, node_id, process_id, endpoint);
    } else if (node_id > root->id) {
        root->right = insert_node(root->right, node_id, process_id, endpoint);
    }

    return root;
}

int determine_child_to_forward(TreeNode* root, int current_id, int target_id) {
    TreeNode* current_node = find_node(root, current_id);
    if (current_node == NULL) {
        return -1;
    }

    if (target_id < current_id) {
        if (current_node->left) {
            return current_node->left->id;
        } else {
            return -1;
        }
    } else {
        if (current_node->right) {
            return current_node->right->id;
        } else {
            return -1;
        }
    }
}

TreeNode* find_node(TreeNode* root, int node_id) {
    if (root == NULL || root->id == node_id) {
        return root;
    }

    if (node_id < root->id) {
        return find_node(root->left, node_id);
    }
    return find_node(root->right, node_id);
}

TreeNode* find_node_by_pid(TreeNode* root, pid_t pid) {
    if (root == NULL) return NULL;
    if (root->pid == pid) return root;
    TreeNode* left = find_node_by_pid(root->left, pid);
    if (left) return left;
    return find_node_by_pid(root->right, pid);
}

bool is_node_exists(TreeNode* root, int node_id) {
    return find_node(root, node_id) != NULL;
}

void kill_tree(TreeNode* root) {
    if (root != NULL) {
        kill_tree(root->left);
        kill_tree(root->right);
        kill(root->pid, SIGTERM);
    }
}

void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}