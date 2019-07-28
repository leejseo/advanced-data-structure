#include <vector>
#include <string.h>
#include <iostream>
using namespace std;

namespace Cartesian{
    struct Node{
        int value;
        Node *lchild, *rchild, *parent;
        Node(int v_){
            value = v_;
            lchild = nullptr, rchild = nullptr, parent = nullptr;
        }
        Node(){
            value = 0;
            lchild = nullptr, rchild = nullptr, parent = nullptr;
        }
    };
    Node* assign_tree(int node, Node* parent, vector<int> &arr, int lchild[],
                     int rchild[], int par[]){
        if (node == -1) return nullptr;
        Node *cur = new Node(arr[node]);
        cur->parent = parent;
        cur->lchild = assign_tree(lchild[node], cur, arr, lchild,
                                  rchild, par);
        cur->rchild = assign_tree(rchild[node], cur, arr, lchild,
                                  rchild, par);
        return cur;
    }
    Node* build_tree(vector<int> &arr){
        int N = arr.size();
        int par[N], lchild[N], rchild[N];
        memset(par, -1, sizeof(par));
        memset(lchild, -1, sizeof(lchild));
        memset(rchild, -1, sizeof(rchild));
        int root = 0;
        for (int i=1; i<N; i++){
            int p = i-1;
            while (p != root && arr[p] <= arr[i]) p = par[p];
            if (arr[p] <= arr[i]){ // i : largest
                par[root] = i, lchild[i] = root, root = i;
            }
            else if (rchild[p] == -1){ // p has no right child => insert
                rchild[p] = i, par[i] = p, lchild[i] = -1;
            }
            else{ // swap
                // p -> rchild[p] into p -> i -> rchild[p]
                par[rchild[p]] = i, lchild[i] = rchild[p];
                rchild[p] = i, par[i] = p;
            }
        }
        par[root] = -1;
        Node *ret = assign_tree(root, nullptr, arr, lchild, rchild, par);
        delete[] par;
        delete[] lchild;
        delete[] rchild;
        return ret;
    }
    void inorder_traversal(Node *node){
        if (node == nullptr) return;
        inorder_traversal(node->lchild);
        std::cout << node->value << '\n';
        inorder_traversal(node->rchild);
    }
};
