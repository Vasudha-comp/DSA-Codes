#include "iostream"
#include "queue"
#include "stack"
using namespace std;

class node{
public:
    int key;
    node *Lchild, *Rchild;
    node(int val):key(val),Lchild(NULL),Rchild(NULL){}
};

class BST{
public:
    node* root;
    BST():root(NULL){}
    
    void insertNode(int key){
        node* new_node = new node(key);
        if(root==NULL){
            root = new_node;
            return;
        }
        node* temp = root;
        while(temp){
            if(temp->key > key){
                if(temp->Lchild==NULL){
                    temp->Lchild = new_node;
                    return;
                }
                temp = temp->Lchild;
            }
            else{
                if(temp->Rchild==NULL){
                    temp->Rchild = new_node;
                    return;
                }
                temp = temp->Rchild;
            }
        }
    }

    void search(int key){
        node* temp = root;
        int lvl = 0;
        while(temp){        //while temp is not NULL
            if(temp->key==key){
                cout<<"\nFound at level "<<lvl<<endl;
                return;
            }
            else if(temp->key < key){
                temp = temp->Rchild;
                lvl++;
            }
            else{
                temp = temp->Lchild;
                lvl++;
            }
        }
        cout<<"Not Found"<<endl;
        return;
    }

    void minVal(){
        if(root==NULL){
            cout<<"Tree is empty"<<endl;
            return;
        }
        node* temp = root;
        while(temp->Lchild!=NULL){
            temp = temp->Lchild;
        }
        cout<<"Minimum Value is "<<temp->key<<endl;
    }

    void breadthFirstTraversal(){
        cout<<"\n"<<endl;
        queue<node*> q;
        q.push(root);
        q.push(NULL);
        while(!q.empty()){
            node* temp = q.front();
            q.pop();
            if(temp==NULL){
                cout<<endl;
                if(!q.empty()) q.push(NULL);
            }else{
                cout<<temp->key<<" ";
                if(temp->Lchild)
                    q.push(temp->Lchild);
                if(temp->Rchild)
                    q.push(temp->Rchild);
            }
        }
    }


//No need of this function at all, just for show off
    void display(){
        stack<node*> s;
        s.push(root);
        int nb = 32;
        cout<<"-----------------------------------------------------------"<<endl;
        bool isRowEmpty = false;
        while(isRowEmpty==false){
            stack<node*> s1;
            isRowEmpty = true;
            for(int j=0;j<nb;j++){
                cout<<" ";
            }
            while(s.empty()==false){
                node* temp = s.top();
                s.pop();
                if(temp!=NULL){
                    cout<<temp->key;
                    s1.push(temp->Lchild);
                    s1.push(temp->Rchild);
                    if(temp->Lchild != NULL || temp->Rchild != NULL)
                        isRowEmpty = false;
                }
                else{
                    cout<<"--";
                    s1.push(NULL);
                    s1.push(NULL);
                }
                for(int j=0;j<nb*2-2;j++){
                    cout<<" ";
                } 
                }
                cout<<endl;
                nb /= 2;
                while(s1.empty()==false){
                    s.push(s1.top());
                    s1.pop();
                }
            }
            cout<<"-----------------------------------------------------------"<<endl;
        }

    node* swapChildren(node* temp){
        if(temp!=NULL){
            node* ptr = temp->Lchild;
            temp->Lchild = swapChildren(temp->Rchild);
            temp->Rchild = swapChildren(ptr);
        }
        return temp;
    }

    node* swapChildren2(node* temp){
        if(temp!=NULL){
            swapChildren2(temp->Lchild);
            swapChildren2(temp->Rchild);
            node * ptr = temp->Lchild;
            temp->Lchild = temp->Rchild;
            temp->Rchild = ptr;
        }
        return temp;
    }

    void inorderTraversal(node* root){
        if(root==NULL) return;
        inorderTraversal(root->Lchild);
        cout<<root->key<<endl;
        inorderTraversal(root->Rchild);
    }

    void getNodesInPath(node* root,int count, int &maxCount, int lvl, int &maxlvl){
        if(root==NULL){
            if(lvl>maxlvl){
                maxlvl = lvl;
                maxCount = count;
            }
            else if(lvl==maxlvl){
                maxCount = max(count, maxCount);
            }
            return;
        }
        count += 1;
        getNodesInPath(root->Lchild,count, maxCount, lvl+1, maxlvl);
        getNodesInPath(root->Rchild,count, maxCount, lvl+1, maxlvl);
    }

    int countNodeinLP(){
        int lvl = 0, maxlvl = 0;
        int count = 0;
        int maxCount = 0;
        getNodesInPath(root,count, maxCount, lvl, maxlvl);
        return maxCount;
    }

    
};

int main(){
    BST b;
    int data,op,n;
    while(true){
        cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ MENU _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n1)Insert a Node.\n2)Search a Node.\n3)Breadth First Traversal.\n4)Display Tree.\n5)Number of Nodes in Longest Path.\n6)Minimum Value in Tree.\n7)Swap Subtrees.\n8)EXIT.\n = ";
        cin>>op;
        switch(op){
            case 1:
                cout<<"How many Nodes you want to insert ? = "; cin>>n;
                for(int i=0;i<n;i++){
                    cout<<"Enter Data for Node "<<(i+1)<<" = ";
                    cin>>data;
                    b.insertNode(data);
                }
                break;
            case 2:
                cout<<"Enter Node to be searched = ";
                cin>>data;
                b.search(data);
                break;
            case 3:
                cout<<"Breadth First Traversal "<<endl;
                b.breadthFirstTraversal();
                break;
            case 4:
                b.display();
                break;
            case 5:
                cout<<"Longest Nodes in Path = "<<b.countNodeinLP()<<endl;
                break;
            case 6:
                b.minVal();
                break;
            case 7:
                cout<<"Tree After Swapping"<<endl;
                b.swapChildren2(b.root);    //swapped once for required
                b.breadthFirstTraversal();
                b.display();
                b.swapChildren(b.root);     //swapped again to regain BST properties
                break;
            case 8:
                return 0;
            default:
                cout<<"Choose Valid Option"<<endl;
                break;
        }
    }
}
