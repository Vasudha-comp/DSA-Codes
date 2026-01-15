#include"iostream"
#include"queue"
using namespace std;

class node{
public:
    string key;
    string mng;
    node *right, *left;
    node(string k, string val):key(k), mng(val), left(NULL), right(NULL){}
};

class Dictionary{
public:
    node* root;
    Dictionary():root(NULL){}

    void insert(string key, string mng){
        node* new_node = new node(key,mng);
        if(!root){
            root = new_node;
            return;
        }
        node* temp = root;
        while(temp){
            if(temp->key > key){
                if(!(temp->left)){
                    temp->left = new_node;
                    return;
                }
                temp = temp->left;
            }else{
                if(!(temp->right)){
                    temp->right = new_node;
                    return;
                }
                temp = temp->right; 
            }
        }
    }

    void inorderTraversal(node* root){
        if(root==NULL) return;
        inorderTraversal(root->left);
        cout<<root->key<<" --> "<<root->mng<<endl;
        inorderTraversal(root->right);
    }

    node* search(string key){
        node* temp = root;
        int lvl = 0;
        while(temp){
            if(temp->key==key){
                cout<<"\nFound at level "<<lvl<<endl;
                cout<<temp->key<<" --> "<<temp->mng<<endl;
                return temp;
            }else if(temp->key < key){
                temp = temp->right;
                lvl++;
            }else{
                temp = temp->left;
                lvl++;
            }
        }
        cout<<"Not Found"<<endl;
        return NULL;
    }

    void update(string key){
        node* temp = search(key);
        if(temp){ //if(temp!=NULL)
            string nm;
            cout<<"Enter new meaning = ";
            cin>>nm;
            temp->mng = nm;
            return;
        }
        cout<<"Key not in the dictionary"<<endl;
        return;
    }

    node* getSuccessor(node* delNode){
        node* successorParent = delNode;
        node* successor = delNode;
        node* current = delNode->right;
        while(current){
            successorParent = successor;
            successor = current;
            current = current->left;
        }
        if(successor!=delNode->right){
            successorParent->left = successor->right;
            successor->right = delNode->right;
        }
        return successor;
    }

    bool deleteNode(string key){
    if(root==NULL){
        cout<<"\nEmpty BST"<<endl;
        return true;
    }
    node* curr = root;
    node* parent = root;
    bool isLeftChild = true;
    while(curr->key!=key){
        parent = curr;
        if(key < curr->key){
            isLeftChild = true;
            curr = curr->left;
        }else{
            isLeftChild = false;
            curr = curr->right;
        }
        if(curr==NULL){
            cout<<"Key to be deleted Not Found"<<endl;
            return false;
        }
    }
    if(curr->left==NULL && curr->right==NULL){
        if(curr==root){
            root = NULL;
        }else if(isLeftChild){
            parent->left = NULL;
        }else{
            parent->right = NULL;
        }
    }
    else if(curr->right==NULL){ 
        if(curr==root){
            root = curr->left;
        }else if(isLeftChild){
            parent->left = curr->left;
        }else{
            parent->right = curr->left;
        }
    }
    else if(curr->left==NULL){
        if(curr==root){
            root = curr->right;
        }else if(isLeftChild){
            parent->left = curr->right;
        }else{
            parent->right = curr->right;
        }
    }
    else{
        node* successor = getSuccessor(curr);
        if(curr==root)
            root = successor;
        else if(isLeftChild)
            parent->left = successor;
        else   
            parent->right = successor;
        successor->left = curr->left;
    }
    cout<<"DELETED"<<endl;
    return true;
}
};

int main(){
    Dictionary obj;
    int op,n;
    string d,m;
    while(true){
         cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ MENU _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n1)Insert Data.\n2)Search Data.\n3)Update Data.\n4)Display in Ascending Order.\n5)Delete.\n6)EXIT.\n = ";
        cin>>op;
        switch(op){
            case 1:
                cout<<"How many data objects u want to insert ? = ";
                cin>>n;
                for(int i=0;i<n;i++){
                    cout<<"Enter Key = ";
                    cin>>d;
                    cout<<"Enter Meaning = ";
                    cin>>m;
                    obj.insert(d,m);
                }
                break;
            case 2:
                cout<<"Enter key to be searched ";
                cin>>d;
                obj.search(d);
                break;
            case 3:
                cout<<"Enter key whose meaning to be updated ";
                cin>>d;
                obj.update(d);
                break;
            case 4:
                obj.inorderTraversal(obj.root);
                break;
            case 5:
                cout<<"Enter key to be deleted ";
                cin>>d;
                obj.deleteNode(d);
                break;
            case 6:
                return 0;
            default:
                cout<<"Invalid Option"<<endl;
                break;
        }
    }
}
