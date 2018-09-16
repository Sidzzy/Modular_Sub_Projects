#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<algorithm>
typedef long long ll;
typedef long l;
typedef short int si;
#define f(x,n)for(long i=x;i<=n;i++)
#define g(x,n)for(long j=x;j<=n;j++)
#define fr(x,n)for(long k=x;k<=n;k++)
using namespace std;
void initialize();
void find_xyz();
int n;
//l n;
//ll ;
string s,source,dest;
vector<string> a,x; 
vector<vector<int> > paths;
vector<pair<ll,int> > money;
class Graph
{
    int V;  
    list<int> *adj; 
    void printAllPathsUtil(int , int , bool [], int [], int &);
 
	public:
	    Graph(int V);
	    void addEdge(int u, int v);
	    void printAllPaths(int s, int d);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void Graph::printAllPaths(int s, int d)
{

    bool *visited = new bool[V];
    int *path = new int[V];
    int path_index = 0;
    for (int i = 0; i < V; i++)
        visited[i] = false;
        
    printAllPathsUtil(s, d, visited, path, path_index);
}
void Graph::printAllPathsUtil(int u, int d, bool visited[],
                              int path[], int &path_index)
{
    visited[u] = true;
    path[path_index] = u;
    path_index++;
    if (u == d)
    {
//        for (int i = 0; i<path_index; i++){
//        	cout<<path[i]<<" ";
//        }
		vector<int> temp;
		temp.insert(temp.begin(),path,path+path_index);
        paths.push_back(temp);
//        cout << endl;
    }
    else
    {
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtil(*i, d, visited, path, path_index);
    }
    path_index--;
    visited[u] = false;
}
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	initialize();
	find_xyz();
	return 0;	
}
void initialize(){
	
	do{
		getline(cin,s);
		a.push_back(s);
	}while(!s.empty());
	n=a.size()-1;
}
bool sortbyequal(const pair<ll,int> &a,const pair<ll,int> &b){
	if(a.first==b.first)
		return (paths[a.second].size()<paths[b.second].size());
}
void find_xyz(){
	string u,v;
	int pos,pos1;
	bool p;
	Graph h(2*n);
	pos=a[0].find(" ");
	u=a[0].substr(0,pos);
	x.push_back(u);
	pos1=a[0].find(" ",pos+1);
	v=a[0].substr(pos+1,pos1-pos-1);
	if(u.compare(v))
		x.push_back(v);
	f(1,n-1){
	 	p=1;	
		pos=a[i].find(" ");
		u=a[i].substr(0,pos);
		g(0,x.size()-1)
			if(!u.compare(x[j])){
				p=0;
				break;
			}
		if(p)
			x.push_back(u);
		
		p=1;	
		pos1=a[i].find(" ",pos+1);
		v=a[i].substr(pos+1,pos1-pos-1);
		g(0,x.size()-1)
			if(!v.compare(x[j])){
				p=0;
				break;
			}
		if(p)
			x.push_back(v);
		g(0,x.size()-1)
			if(!u.compare(x[j])){
				pos=j;
				break;
			}
		g(0,x.size()-1)
			if(!v.compare(x[j])){
				pos1=j;
				break;
			}
		h.addEdge(pos,pos1);
	}
	pos=a[0].find(" ");
	u=a[0].substr(0,pos);
	g(0,x.size()-1)
		if(!u.compare(x[j])){
			pos1=j;
			break;
		}
	u=a[0].substr(pos+1);
	g(0,x.size()-1)
		if(!u.compare(x[j])){
			pos=j;
			break;
		}
	h.printAllPaths(pos1,pos);

	money.resize(paths.size());
	long cost;
	f(0,paths.size()-1){
		g(0,paths[i].size()-2){
			cost=0;
			u=x[paths[i][j]];
			v=x[paths[i][j+1]];
			fr(1,n-1){
				if (a[k].find(u) != std::string::npos && a[k].find(v) != std::string::npos){
					pos=a[k].find(" ");			
					pos1=a[k].find(" ",pos+1);
					u=a[k].substr(pos1+1);
					break;
				}
			}
			fr(0,u.length()-1){
				cost*=10;
				cost+=u[k]-48;
			}
			money[i].first+=cost;
			money[i].second=i;
		}
	}
	sort(money.begin(),money.end(),sortbyequal);
	f(0,money.size()-1){
		g(0,paths[money[i].second].size()-1)
			cout<<x[paths[money[i].second][j]]<<"->";
		cout<<money[i].first<<endl;
	}
}

//Take this as a sample data:

//Bangalore Hyderabad
//Bangalore Hyderabad 10000
//Bangalore Chennai 4000
//Chennai Hyderabad 4000
