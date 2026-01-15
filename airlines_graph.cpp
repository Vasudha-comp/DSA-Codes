#include "iostream"
using namespace std;
#define max 15

class node{
public:
    float time;
    //NO NEED
    int links[max]; //To realize links between airports
    node(int t){
        time = t;
        for(int i=0;i<max;i++)
            links[i] = -1;
    }
};

class Graph{
    node* adj[max][max];
    string cities[max]; //Array of cities names mapped with matrix indices
    int n;
public:
    Graph(){
        for(int i=0;i<max;i++){
            for(int j=0;j<max;j++)
                adj[i][j] = NULL;
            cities[i] = "";
        }
    }

    int search(string s){
        for(int i=0;i<n;i++){
            if(cities[i]==s){
                return i;
            }
        }
        cout<<"City not in the list\nTry again"<<endl;
        return -1;
    }

    void create(){
        int cn,d,k;
        float t;
        string city;
        cout<<"Enter Total Number of Available Cities = ";
        cin>>n;
        cout<<endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                adj[i][j] = new node(0);
            }
            cout<<"Enter Name of City "<<(i+1)<<" = ";
            cin>>city;
            cities[i] = city;
        }
        for(int i=0;i<n;i++){
            cout<<"\nEnter Number of Flights from "<<cities[i]<<" = ";
            cin>>cn;
            k= 0;
            for(int j=0;j<cn;j++){
                cout<<"Enter Neighbour City "<<(j+1)<<" = ";
                cin>>city;
                int index = search(city);
                cout<<"Enter time required for flight = ";
                cin>>t;
                if(index!=-1){
                    //In ast 6 we were directly setting 1, but here we need to read time reqd to travel from city A to city B as t and then set it 
                    adj[i][index]->time = t;
                    adj[i][0]->links[k] = index;
                    ++k;
                }
            }
        }
    }

    void displayMat(){
        cout<<endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                    cout<<adj[i][j]->time<<"\t";
            }
            cout<<endl;
        }
        for(int i=0;i<n;i++){
            cout<<"Time required for flights from "<<cities[i]<<endl;
            for(int j=0;j<n;j++){
                if(adj[i][j]->time!=0){
                    cout<<"to "<<cities[j]<<" = "<<adj[i][j]->time<<"hrs "<<endl;
                }
            }
            cout<<endl;
        }
    }

    void displayAdjacentsOf(int k){
        cout<<cities[k]<<" --> ";
        for(int i=0;i<n;i++){
            if((adj[k][0]->links[i]!=-1))
                cout<<cities[(adj[k][0]->links[i])]<<" --> ";
            else break;
        }cout<<endl;
    }

};

int main(){
    Graph g;
    int opt;
    while(true){
        cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ AIRLINES _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_.\n1)Create Routes.\n2)Display Routes.(Adjacency Matrix Format).\n3)Display Routes.(Adjacency List Format).\n4)Exit.\n = ";
        cin>>opt;
        switch (opt)
        {
        case 1:
            g.create();
            break;
        case 2:
            g.displayMat();
            break;
        case 3:
            for(int i=0;i<4;i++)
            g.displayAdjacentsOf(i);
            break;
        case 4:
            return 0;
        default:
            cout<<"Invalid Option"<<endl;
            break;
        }
    }
}
