#include "iostream"
#include "queue"
using namespace std;

class node{
public:
    string val,mng;
    node *left, *right;
    node(string data,string buff):val(data),mng(buff),left(NULL),right(NULL){}
};

class AVL{
public:
    node* root;
    AVL():root(NULL){}

    int height(node *temp){
        if(temp==NULL)
            return(-1);
        else
            return(max(height(temp->left),height(temp->right))+1);
    }

    int diff(node* temp){
        return (height(temp->left) - height(temp->right));
    }

    //Rotations
    node* LL(node* temp){
        cout<<"\nLeft of Left Rotation"<<endl;
        node* ptr = temp->left;
        node* ctr = ptr->right;
        ptr->right = temp;
        temp->left = ctr;
        return ptr;
    }

    node* RR(node* temp){
        cout<<"\nRight of Right Rotation"<<endl;
        node* ptr = temp->right;
        node* ctr = ptr->left;
        ptr->left = temp;
        temp->right = ctr;
        return ptr;
    }

    node* LR(node* temp){
        temp->left = RR(temp->left);
        return (LL(temp));
    }

    node* RL(node* temp){
        temp->right = LL(temp->right);
        return (RR(temp));
    }

    //Balancing Function
    node* balance(node* temp){
        int bal = diff(temp);
        if(bal>=2){
            if(diff(temp->left)<0)
                temp = LR(temp);
            else
                temp = LL(temp);
        }
        else if(bal<=-2){
            if(diff(temp->right)<0)
                temp = RR(temp);
            else
                temp = RL(temp);
        }
        return temp;
    }

    node* insert(node* root, node* new_node){
        if(root==NULL){
            root = new_node;
            return root;
        }
        if(root->val > new_node->val){
            root->left = insert(root->left,new_node);
            root = balance(root);
        }
        else{
            root->right = insert(root->right,new_node);
            root = balance(root);
        }
    }

    void BFS(node* root){
        queue<node* > q;
        q.push(root);
        q.push(NULL);
        while(!q.empty()){
            node* temp = q.front();
            q.pop();
            if(temp==NULL){
                cout<<endl;
                if(!q.empty()) q.push(NULL);
            }else{
                cout<<temp->val<<" ";
                if(temp->left)
                    q.push(temp->left);
                if(temp->right)
                    q.push(temp->right);
            }
        }
    }
    
    node* search(string key,node* root){
        node* temp = root;
        int lvl = 0;
        while(temp){
            if(temp->val==key){
                cout<<"\nFound at level "<<lvl<<endl;
                cout<<temp->val<<" --> "<<temp->mng<<endl;
                return temp;
            }else if(temp->val < key){
                temp = temp->right;
                lvl++;
            }else{
                temp = temp->left;
                lvl++;
            }
        }
        cout<<"Not Found"<<endl;
        return root;
    }

    node* update(string key,node* root){
        node* temp = search(key,root);
        if(temp){
            string nm;
            cout<<"Enter new meaning = ";
            cin>>nm;
            temp->mng = nm;
            return root;
        }
        cout<<"Key not in the dictionary"<<endl;
        return root;
    }

    node* deleteNode(string key, node* root){
        node* temp;
        if(root){
            if(key < root->val){
                root->left = deleteNode(key,root->left);
                if(diff(root)==-2){
                    if(diff(root->right)<=0)
                        root = RR(root);
                    else
                        root = RL(root);
                }
            }
            else if(key > root->val){
                root->right = deleteNode(key,root->right);
                if(diff(root)==2){
                    if(diff(root->left)>=0)
                        root = LL(root);
                    else
                        root = LR(root);
                }
            }
            else{
                if(!root->right)
                    return root->left;
                else{
                    temp = root->right;
                    while(temp->left)
                        temp = temp->left;
                    root->val = temp->val;
                    temp->right = deleteNode(temp->val, root->right);
                    if(diff(root)==2){
                        if(diff(root->left)>=0){
                            root = LL(root);
                        }
                        else{
                            root = LR(root);
                        }
                    }
                }
            }
        }
        else{
            return NULL;
        }
        return root;
    }

    void inorder(node* root){
        if(root){
            inorder(root->left);
            cout<<root->val<<" --> "<<root->mng<<endl;
            inorder(root->right);
        }
    }
};

int main(){
    AVL obj;
    node* root = NULL;
    string d,m;
    int op,n;
    while(true){
         cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ MENU _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n1)Insert Data.\n2)Search Data.\n3)Update Data.\n4)Display in Ascending Order.\n5)Delete Key.\n6)EXIT.\n = ";
        cin>>op;
        switch(op){
            case 1:
                cout<<"How many data objects u want to insert ? = ";
                cin>>n;
                for(int i=0;i<n;i++){
                    cout<<"Enter Key "<<(i+1)<<" = ";
                    cin>>d;
                    cout<<"Enter Meaning = ";
                    cin>>m;
                    node* new_node = new node(d,m);
                    root = obj.insert(root,new_node);
                }
                cout<<"\nData Entered"<<endl;
                obj.BFS(root);
                break;
            case 2:
                cout<<"Enter key to be searched ";
                cin>>d;
                obj.search(d,root);
                break;
            case 3:
                cout<<"Enter key whose meaning to be updated ";
                cin>>d;
                root = obj.update(d,root);
                cout<<"Data Updated\nAscending Order\n"<<endl;
                obj.inorder(root);
                break;
            case 4:
                obj.inorder(root);
                break;
            case 5:
                cout<<"Enter Key to be Deleted = ";
                cin>>d;
                root = obj.deleteNode(d,root);
                cout<<"\nAfter Deletion"<<endl;
                obj.BFS(root);
                break;
            case 6:
                return 0;
            default:
                cout<<"Invalid Option"<<endl;
                break;
        }
    }
}
