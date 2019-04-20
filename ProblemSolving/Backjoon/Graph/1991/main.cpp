/*
https://www.acmicpc.net/problem/1991

이진 트리를 입력받아 전위 순회(preorder traversal), 중위 순회(inorder traversal), 후위 순회(postorder traversal)한 결과를 출력하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <memory>

template<typename T>
class Node{
    public : 
        Node(const T data) { 
            this->data = data;
            this->leftNode = NULL;
            this->rightNode = NULL; 
        }
        
        T data;
        Node<T> *leftNode, *rightNode;
};

template<typename T>
class Tree{
public :
    Node<T>* add(Node<T> *root, const T data, const T left, const T right) {
        if(root == NULL){
            Node<T> *head = new Node<T>(data);

            if(left != '.'){
                Node<T> *headLeft = new Node<T>(left);
                head->leftNode = headLeft;
            }
            if(right != '.'){
                Node<T> *headRight = new Node<T>(right);
                head->rightNode = headRight;
            }

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

    Node<char> *root = NULL;
    Tree<char> tree;

    char data, leftNodeData, rightNodeData;
    while(--N){
        std::cin >> data >> leftNodeData >> rightNodeData;
        
        root = tree.add(root, data, leftNodeData, rightNodeData);
    }
    
    std::cout << "\n";
    tree.preOrder(root);
    std::cout << "\n";
    tree.inOrder(root);
    std::cout << "\n";
    tree.postOrder(root);
    std::cout << "\n";
}