#include <iostream>
#include <string>
#include <vector>
#include <utility>  
#include <queue>

template<typename T>
class Node{
    T data;
    Node<T> *left, *right;
public:
    Node(const T &input){
        data = input;
        left = nullptr;
        right = nullptr;
    }
};

template<typename T>
class Heap{
public :
    Node<T>* add(Node<T> *root, const T data) {
        if(root == NULL){
            Node<T> *head = new Node<T>(data);

            return head;        
        }
        else{
            Node<T> *head = root;

            search(head, data, left, right);

            return root;
        }
    }

    void search(Node<T> *root, T val, T left, T right){
        
        if(root != NULL){
            if(root->data == val){
                if(left != '.'){
                    Node<T> *tmpLeft = new Node<T>(left);
                    root->leftNode = tmpLeft;
                }
                if(right != '.'){
                    Node<T> *tmpRight = new Node<T>(right);
                    root->rightNode = tmpRight;
                }
            }
            else{
                if(root->leftNode != NULL)
                    search(root->leftNode, val, left, right);

                if(root->rightNode != NULL)
                    search(root->rightNode, val, left, right);
            }
        }
    }

    void preOrder(Node<T> *root) {
        if(root != NULL){
            std::cout << root->data;
            preOrder(root->leftNode);
            preOrder(root->rightNode);
        }
    }

    void inOrder(Node<T> *root) {
        if(root != NULL){
            inOrder(root->leftNode);
            std::cout << root->data;
            inOrder(root->rightNode);
        }
    }

    void postOrder(Node<T> *root) {
        if(root != NULL){
            postOrder(root->leftNode);
            postOrder(root->rightNode);
            std::cout << root->data;
        }
    } 
};


int main(){
    std::ios::sync_with_stdio(false);
    int N = 0;
    std::cin >> N;

    Node<int> *root = NULL;
    Heap<int> heap;

    int data;
    while(--N){
        std::cin >> data;
        
        root = heap.add(root, data);
    }
    
    std::cout << "\n";
    heap.preOrder(root);
    std::cout << "\n";
}