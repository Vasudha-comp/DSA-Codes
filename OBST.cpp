#include "iostream"
#include "stack"
#include "queue"
using namespace std;
#define max 20
string leaf[max];
int i,j,k,l,min, n, r[max][max];
float p[max], q[max], w[max][max], c[max][max];

class node{
public:
    string data;
    node* left;
    node* right;
    node(string val):data(val),left(NULL),right(NULL){}
};
/*
                                                   FORMULAE
                            1)w[i][j] = p[j] + q[j] + w[i][j-1] .....taken , j = i + 1

                            2) c[i][j] = min(c[i][a-1] + c[a][j]) + w[i][j]

                            3) r[i][j] = value of a , at which cost minimizes
*/
void OBST(){
    //Step 1 :- Initialisation at j - i = 1, i.e.., For first node
    //w00, w11, w22, ...... wNN
	for(i=0;i<n;i++){ 
        //Row 1 Manipulation
		c[i][i]=0.0;
		r[i][i]=0;
		w[i][i]=q[i];

        //Row 2 Manipulation
		// for j-i=1 ----> j=i+1
		w[i][i+1]=w[i][i]+q[i+1]+p[i+1];
		c[i][i+1]=w[i][i+1];
		r[i][i+1]=i+1;
	  }
	c[n][n]=0.0;
	r[n][n]=0;
	w[n][n]=q[n];

    //After processing for root
	//for j-i=2,3,4....,n
	for(i=2;i<=n;i++){
		for(j=0;j<=n-i;j++){
            //Step 2 : Calculation weight by putting i = j and j = j + i in above formula
			w[j][j+i]=q[j+i]+p[j+i]+w[j][j+i-1];
            //Step 3 : Initialising cost with random value
			c[j][j+i]=9999;
			for(l=j+1;l<=j+i;l++){ //l is apna a
                //Step 3 : Calculating Cost
				if(c[j][j+i]>(c[j][l-1]+c[l][j+i]))
				  {
					c[j][j+i]=c[j][l-1]+c[l][j+i];
					r[j][j+i]=l;
				  }
			  }
			c[j][j+i] += w[j][j+i];
		  }
	  }
  }

void print_tab(){
    cout<<"\nOUTPUT : "<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    //Step 4 : Print row 0
    for(i=0;i<=n;i++){
        cout<<"w"<<i<<i<<" = 0"<<w[i][i]<<"\t";
    }
    cout<<endl;
    for(i=0;i<=n;i++){
        cout<<"c"<<i<<i<<" = 0"<<c[i][i]<<"\t";
    }
    cout<<endl;
    for(i=0;i<=n;i++){
        cout<<"r"<<i<<i<<" = 0"<<r[i][i]<<"\t";
    }
    cout<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    //Printing Remaining Rows 
    k = 1;
    while(k<=n){
        cout<<"\n-------------------------------------------------------------------------"<<endl;
        //0<= i < n | (i+k)<= j <= n
        for(i=0,j=i+k;i<n,j<=n;i++,j++){
            if(w[i][j]<=9)
                cout<<"w"<<i<<j<<" = 0"<<w[i][j]<<"\t";
            else
                cout<<"w"<<i<<j<<" = "<<w[i][j]<<"\t";
        }
        cout<<endl;
        //0<= i < n | (i+k)<= j <= n
        for(i=0;j=i+k,i<n,j<=n;i++,j++){
            if(c[i][j]<=9)
                cout<<"c"<<i<<j<<" = 0"<<c[i][j]<<"\t";
            else
                cout<<"c"<<i<<j<<" = "<<c[i][j]<<"\t";
        }
        cout<<endl;
        //0<= i < n | (i+k)<= j <= n
        for(i=0;j=i+k,i<n,j<=n;i++,j++){
            if(r[i][j]<=9)
                cout<<"r"<<i<<j<<" = 0"<<r[i][j]<<"\t";
            else
                cout<<"r"<<i<<j<<" = "<<r[i][j]<<"\t";
        }
        cout<<"\n-------------------------------------------------------------------------"<<endl;
        k++;
    }
    //Last Remaining Diagonal Box
    cout<<"\n\nOptimal BST is :: ";
	cout<<"\nw[0]["<<n<<"] :: "<<w[0][n];
	cout<<"\nc[0]["<<n<<"] :: "<<c[0][n];
	cout<<"\nr[0]["<<n<<"] :: "<<r[0][n];
    
}

void print(int l, int rr){
    if(l>=rr)
        return;
    //Left Child = r[l][parent-1]
    if(r[l][r[l][rr]-1]!=0){
        cout<<"\nLeft Child of "<<leaf[r[l][rr]]<<" = "<<leaf[r[l][r[l][rr]-1]];
    }
    //Left Child = r[parent][rr]
    if(r[r[l][rr]][rr]!=0){
        cout<<"\nRight Child of "<<leaf[r[l][rr]]<<" = "<<leaf[r[r[l][rr]][rr]];
    }
    print(l,r[l][rr]-1);
    print(r[l][rr],rr);
    return;
}

node* constructTree(int low, int high){
    if(low >= high)
        return NULL;
    int rootIndex = r[low][high];
    node* root = new node(leaf[rootIndex]);
    root->left = constructTree(low, rootIndex-1);
    root->right = constructTree(rootIndex,high);
    return root;
}

void BFS(node* root){
        cout<<endl;
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
                cout<<temp->data<<" ";
                if(temp->left)
                    q.push(temp->left);
                if(temp->right)
                    q.push(temp->right);
            }
        }
    }

void display(node* root){
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
                cout<<temp->data;
                s1.push(temp->left);
                s1.push(temp->right);
                if(temp->left != NULL || temp->right != NULL)
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

int main(){
    cout<<"\nEnter Number of Nodes = ";
    cin>>n;
    int i;
    for(i=1;i<=n;i++){
        cout<<"Enter Node Label "<<"for node "<<(i)<<" = ";
        cin>>leaf[i];
    }
    cout<<"\nEnter Probabilities of Successful Search "<<endl;
    for(i=1;i<=n;i++){
        cout<<"p["<<(i)<<"] = ";
        cin>>p[i];
    }
    cout<<"\nEnter Probabilities of Unsuccessful Search "<<endl;
    for(i=0;i<=n;i++){
        cout<<"q["<<(i)<<"] = ";
        cin>>q[i];
    }
    cout<<endl;
    cout<<"p[1:"<<n<<"] = [";
    for(i=0;i<n;i++){
        cout<<p[i]<<" , ";
    }cout<<"]"<<endl;
    cout<<"q[0:"<<n<<"] = [";
    for(i=0;i<=n;i++){
        cout<<q[i]<<" , ";
    }cout<<"]"<<endl;
    OBST();
    print_tab();
    cout<<endl;
    cout<<"\nRoot : "<<leaf[r[0][n]]<<endl;
    print(0,n);
    node* root;
    root = constructTree(0,n);
    BFS(root);
    return 0;
}
