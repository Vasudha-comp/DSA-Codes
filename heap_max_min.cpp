#include "iostream"
using namespace std;
#define max 20

class node{
public:
    int data;
    node(int val):data(val){}
};

class Heap{
    node* heapArr[max];
    int maxSize;
    int n;
public:
    Heap(int size){
        maxSize = size;
        n = 0;
        for(int i=0;i<max;i++){
            heapArr[i] = NULL;
        }
    }

    void reHeapUp(int index){
        int parent = (index - 1)/2;
        node* bottom = heapArr[index];
        while(index > 0 && (heapArr[parent])->data < bottom->data){
            heapArr[index] = heapArr[parent];
            index = parent;
            parent = (parent-1)/2;
        }
        heapArr[index] = bottom;
    }

    void reHeapDown(int index){
        int larger;
        node* top = heapArr[index];
        while(index < n/2){
            int left = 2*index + 1;
            int right = left + 1;
            if(right < n && heapArr[left]->data < heapArr[right]->data){
                larger = right;
            }else{
                larger = left;
            }
            if(top->data >= heapArr[larger]->data){
                break;
            }
            heapArr[index] = heapArr[larger];
            index = larger;
        }
        heapArr[index] = top;
    }

    bool insert(int key){
        if(n==maxSize){
            return false;
        }
        node* new_node = new node(key);
        heapArr[n] = new_node;
        reHeapUp(n++);
        return true;
    }

    void deleteNode(){
        node* root = heapArr[0];
        heapArr[0] = heapArr[--n];
        reHeapDown(0);
        return;
    }    
    
//No need
    void display(){
        cout<<"Heap Array : ";
        for(int i=0;i<n;i++){
            if(heapArr[i]!=NULL){
                cout<<heapArr[i]->data<<" ";
            }
            else{
                cout<<"--";
            }
        }cout<<endl;
        int blanks = 32;
        int itemsPerRow = 1;
        int c = 0;
        int j = 0;
        string dots =  "...............................";
        cout<<(dots+dots)<<endl;
        while(n>0){
            if(c==0){
                for(int k=0;k<blanks;k++){
                    cout<<" ";
                }
            }
            cout<<heapArr[j]->data;
            if(++j==n)
                break;
            if(++c==itemsPerRow){
                blanks /= 2;
                itemsPerRow *= 2;
                c = 0;
                cout<<endl;
            }else{
                for(int k=0;k<blanks*2-2;k++)
                    cout<<" ";
            }
        }cout<<endl;
        cout<<dots+dots<<endl;
    }

    void getMaxMin(){
        int minElement = heapArr[n/2]->data;
        for(int i=n/2 + 1;i<n;i++){
            minElement = min(minElement,heapArr[i]->data);
        }
        cout<<"\nMaximum Score = "<<heapArr[0]->data<<"\nMinimum Score = "<<minElement<<endl;
    }

};

int main(){
    Heap h(15);
    int data;
    for(int i=0;i<12;i++){
        cout<<"Enter Marks scored by Student "<<(i+1)<<" = ";
        cin>>data;
        h.insert(data);
    }
    h.display();
    h.getMaxMin();
    h.deleteNode();
    cout<<"\nAfter Deleting Node"<<endl;
    h.display();
    return 0;
}
