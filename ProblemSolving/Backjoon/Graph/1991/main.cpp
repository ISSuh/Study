/*
https://www.acmicpc.net/problem/1991

이진 트리를 입력받아 전위 순회(preorder traversal), 중위 순회(inorder traversal), 후위 순회(postorder traversal)한 결과를 출력하는 프로그램을 작성하시오.
*/

#include <iostream>

class Node{
    public : 
        Node(char data) { 
            this->data = data;
            this->leftNode = nullptr;
            this->rightNode = nullptr; 
        }
        
        char data;
        Node *leftNode, *rightNode;
};

class Tree{
public :
    Node* add(Node *root, char data, char left, char right) {
        if(root == nullptr){
            Node *head = new Node(data);

            if(left != '.'){
                Node *headLeft = new Node(left);
                head->leftNode = headLeft;
            }
            if(right != '.'){
                Node *headRight = new Node(right);
                head->rightNode = headRight;
            }

            return head;        
        }
        else{
            std::cout << "1" << "\n";

            Node *tmp = search(root, data);

            std::cout << "2" << "\n";

            if(left != '.'){
                Node *tmpLeft = new Node(left);
                tmp->leftNode = tmpLeft;
            }
            if(right != '.'){
                Node *tmpRight = new Node(right);
                tmp->rightNode = tmpRight;
            }

            return root;    
        }
    }

    void preOrder(Node *root) {
        if(root != NULL){
            std::cout << root->data << " ";
            preOrder(root->leftNode);
            preOrder(root->rightNode);
        }
    }

private :
    Node *search(Node *root, char val){
        Node *tmp = root;

        if(tmp->data == val) 
            return tmp;
        else{
            search(tmp->leftNode, val);
            search(tmp->rightNode, val);
        }
    } 
};


int main(){
    std::ios::sync_with_stdio(false);
    int N = 0;
    std::cin >> N;

    Node *root = nullptr;
    Tree tree;

    char data, leftNodeData, rightNodeData;
    while(N--){
        std::cin >> data >> leftNodeData >> rightNodeData;
        
        root = tree.add(root, data, leftNodeData, rightNodeData);
    }

    tree.preOrder(root);
}