bool exists(Node *root, int x) {
    if (root == nullptr) return false;
    if (x < root->x) {
        return exists(root->left, x);
    } else if (x > root->x) {
        return exists(root->right, x);
    } else
        return true;
}
