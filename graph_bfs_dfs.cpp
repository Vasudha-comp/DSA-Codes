#include "iostream"
#include "stack"
#include "queue"
using namespace std;
#define max 15
int n;
string label[max];  //An array to maintain names of vertices

int getIndex(string s){
    for(int i=0;i<n;i++){
        if(s==label[i])
            return i;
    }
    return -1;
}

class node{
public:
    int ver;
    string links[max]; //to actually realize graph network in adj matrix
    node* next;        //to actually realize graph network in adj list
    node():ver(0),next(NULL){}
    node(int data){
        ver = data;
        for(int i=0;i<n;i++)
            links[i] = "";
    }
};

class Graph{
    int visited[max];   //Array to know whether vertices are visited yet or not
public:
    node* adj[max][max]; //2 dimensional array
    node* heads[max];    //Array of objects (node) in which each element represents a vertex and is a linked list of adjacent vertices
    Graph(){
        for(int i=0;i<max;i++){
            for(int j=0;j<max;j++){
                adj[i][j] = NULL;
                heads[i] = NULL;
            }
        }
    }

    //After performing a DFS/BFS operation values in visited array is changed but if we try to perform it again then it won't work because to work properly values in visited array should be 0, so we set them again to 0
    void refresh(){
    	for(int k=0;k<n;k++)
         visited[k] = 0;
    }
    
    void create(){
        int cn,neighbourIndex,flag;
        string place;
        bool done = false;
        node *curr, *prev;
        cout<<"1)Press 1 for Undirected Graph.\n2)Press 2 for Directed Graph.\n = ";
        cin>>flag;
        cout<<"Enter Number of vertices = ";
        cin>>n;
        for(int i=0;i<n;i++){
            cout<<"Enter Place Name = ";
            cin>>place;
            label[i] = place;
            for(int j=0;j<n;j++){
                adj[i][j] = new node();
            }
        }
        for(int i=0;i<n;i++){
            heads[i] = new node();
            heads[i]->ver = i;
            prev = heads[i];
            if(flag==1)
            	cout<<"Enter Number of All Neighbours of Vertex "<<label[i]<<" = ";
            else
            	cout<<"Enter OutDegree Neighbours of Vertex"<<label[i]<<" = ";
            cin>>cn;
            int k = 0;
            for(int j=0;j<cn;j++){
                curr = new node();
                cout<<"Enter neighbour "<<(j+1)<<" = ";
                cin>>place;
                neighbourIndex = getIndex(place);
                //Manipulations for Adj Matrix
                if(neighbourIndex!=-1){
                    adj[i][neighbourIndex]->ver = 1;
                    adj[i][0]->links[k] = label[neighbourIndex];
                    cout<<label[i]<<" linked to "<<label[neighbourIndex]<<endl;
                    ++k;
                }
                //Manipulations for Adj List
                curr->ver = neighbourIndex;
                prev->next = curr;
                prev = curr;
                prev->next = NULL;
            }
            if(cn==0)
                prev->next = NULL;
        }
}
    
    void displayMat(){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<adj[i][j]->ver<<"  ";
            }
            cout<<endl;
        }
    }

    void dispList(){
        for(int i=0;i<n;i++){
            node* temp = heads[i];
            while(temp){
                cout<<label[temp->ver]<<" -> ";
                temp = temp->next;
            }cout<<"NULL"<<endl;
        }
    }

    void displayAdjacentsOf(int k){
        cout<<"Neighbours of "<<label[k]<<" = ";
        for(int i=0;i<n;i++){
            if((adj[k][0]->links[i])!="")
                cout<<(adj[k][0]->links[i])<<" --> ";
            else break;
        }cout<<endl;
    }

    void DFS(int v);
    
    void BFS(int v);
};

//DFS using Adjacency Matrix
void Graph::DFS(int v){
    refresh();
    stack<int > s;
    s.push(v);
    int j;
    while(!s.empty()){
        j = s.top();
        s.pop();
        if(!visited[j]){
             //cout<<j+1<<" ";
             cout<<label[j]<<"  ";
             visited[j] = 1;
        }
        for(int k=0;k<n;k++){
            if(adj[j][k]->ver==1 && !(visited[k])){
                s.push(k);
            }
        }
    }
}

//DFS using Adjacency List
void Graph::BFS(int v){
    refresh();
    queue<node* > q;
    node* curr;
    visited[v] = true;
    //cout<<heads[v]->ver<<" ";
    cout<<label[v]<<"  ";
    q.push(heads[v]);
    while(!q.empty()){
        curr = q.front();
        q.pop();
        curr = curr->next;
        while(curr){
            if(!visited[curr->ver]){
                q.push(heads[curr->ver]);
                //cout<<curr->ver<<" ";
                cout<<label[curr->ver]<<"  ";
                visited[curr->ver] = true;
            }
            curr = curr->next;
        }
    }
}  

int main(){
    Graph g;
    int opt;
    while(true){
    	cout<<"\n-_-_-_-_-_-_-_-_-_-_-_-_- MENU -_-_-_-_-_-_-_-_-_-_-_-_-\n1)Create Graph.\n2)Display Adjacency Matrix & Adjacency List.\n3)Display BFS.\n4)Display DFS.\n5)Exit.\n = ";
    	cin>>opt;
    	switch(opt){
    		case 1:
    			g.create();
                g.displayAdjacentsOf(0);
    			break;
    		case 2:
                cout<<"Adjacent Matrix of given graph is :"<<endl;
    			g.displayMat();
                cout<<endl;
                cout<<"\nAdjacent List of given graph is :"<<endl;
                g.dispList();
    			break;
    		case 3:
    			cout<<"Adjacent List of given graph is :"<<endl;
    			g.dispList();
    			cout<<"\nBFS of above graph"<<endl;
    			g.BFS(0);
    			break;
    		case 4:
    			cout<<"Adjacent Matrix of given graph is :"<<endl;
    			g.displayMat();
    			cout<<"\nDFS of above graph"<<endl;
    			g.DFS(0);
    			break;
    		case 5:
    			return 0;
    		default:
    			cout<<"Invalid Option"<<endl;
    			break;
    	}
    }
    
    return 0;
}
