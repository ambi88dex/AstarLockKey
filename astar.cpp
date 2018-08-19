#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<vll> vvll;
typedef vector<vpll> vvpll;
const ll GMAX = 9999;
int SOURCE; 
int DESTINATION;

struct pair_compare{
    bool operator()(const pll& a, const pll& b){
        return a.second > b.second;
    }
};

class AstarQ{
	public:
		int current_node;
		ll fcost;
		ll gcost;
		int parent_node;

		AstarQ(int _cn, ll _f, ll _g,ll _pn):current_node(_cn),fcost(_f),parent_node(_pn),gcost(_g){}
		AstarQ(const AstarQ& elem):current_node(elem.current_node),fcost(elem.fcost),parent_node(elem.parent_node),gcost(elem.gcost){}

		friend ostream& operator<<(ostream& o, const AstarQ& elem){
			o << elem.current_node << " , " << elem.fcost << " , " << elem.gcost << " , " << elem.parent_node;
			return o;
		}
};

struct Astar_compare{
	bool operator()(const AstarQ& a, const AstarQ& b){
		return a.fcost > b.fcost;
	}
};

void printQ(auto pq){
	cout << "Printing the queue" << endl;
	while(!pq.empty()){
		cout << pq.top() << endl;
		pq.pop();
	}
	cout << "done" << endl;
}

int main(){
	int n;
    cin >> n;
    vvll graph(n,vll(n,GMAX));
    for(int i = 0 ; i < n ; i++){
    	for(int j = 0 ;j < n ; j++){
    		cin >> graph[i][j];
    	}
    }
   	SOURCE = 0;
	DESTINATION = n - 1;
    priority_queue<pll,vpll,pair_compare >pq;
    pq.push(pll(DESTINATION,0));  

    vll h_value(n,LONG_MAX);
    vll visited(n,0);
    h_value[DESTINATION] = 0;

	
    while(!pq.empty())
    {
        ll parent = pq.top().first;
        ll pdist = pq.top().second;
        pq.pop();
		// cout << parent << endl;
        if(visited[parent] == 0){
            visited[parent] = 1;
            h_value[parent] = pdist;
            for(int i = 0 ; i < n ; i++){
                if(graph[parent][i] != GMAX && i != parent ){
                    if(h_value[i] > pdist + graph[parent][i] && visited[i] == 0){
                        h_value[i] = pdist + graph[parent][i];	
						// cout << i << " " << h_value[i] << endl;
                        // cout << parent << " " << i << " " << h_value[i] << endl;
                        pq.push(pll(i,h_value[i]));    
                    }
                    
                }
            }
        }
    }
	for(auto e: h_value){
		cout << e << " ";
	}
	cout << endl;
	
	visited = vll(n,0);
    vll unlocked(n,0);
    vvll keys(n,vll(n,0));
	vll astar_distance(n,0);
	
    int unlocked_node_count;
    cin >> unlocked_node_count;

    for(int i = 0;i < unlocked_node_count; i++){
    	int x;
    	cin >> x;
    	unlocked[x] = 1;
    }
    // number of nodes with keys
    int q;
    cin >> q;
    while(q--){	
    	int parent_node;
    	cin >> parent_node;
    	int node_key_frequency;
    	cin >> node_key_frequency;
    	while(node_key_frequency --){
    		int x;
    		cin >> x;
    		keys[parent_node][x] = 1;
    	}
    }
	// for(int i = 0 ; i < n ; i++){
	// 	cout << unlocked[i] << " ";
	// }
	// cout << endl;
	
	// for(int i = 0 ; i < n ; i++){
	// 	cout << visited[i] << " ";
	// }
	// cout << endl;

	priority_queue< AstarQ, vector<AstarQ> ,Astar_compare> apq;
	// cout << h_value[0] << endl;		
	// cout << SOURCE << endl;
	// cout << h_value[SOURCE] << endl;
	AstarQ init = AstarQ(SOURCE,h_value[SOURCE],0,-1);
	// cout << init << endl;
	// cout << init.current_node <<  " " << init.fcost << " " << init.gcost << " " << init.parent_node << endl; 
	apq.push(init);
	deque<ll> path;
	int current_node  = -1;
	while(!apq.empty() && apq.top().current_node != n - 1){
		
		current_node = apq.top().current_node;
		ll fcost = apq.top().fcost;
		ll gcost = apq.top().gcost;
		int parent_node = apq.top().parent_node;
		
		cout << apq.top() <<  " " << apq.size() << endl;

		
		
		
		if(unlocked[current_node] == 1){
			if(current_node != SOURCE){
				if(path.back() != parent_node){
					while(!path.empty() && path.back() != parent_node){
						path.pop_back();
					}
				}				
			}
			path.push_back(current_node);
			if(visited[current_node] == 0){
				for(int i = 0 ; i < n; i++){
					if(keys[current_node][i]){
						unlocked[i] = 1;
					}
				}
			}
			
			apq.pop();
			for(int i = 0 ; i < n ; i++){
				if(graph[current_node][i] != GMAX){
					ll next_node_gcost = gcost + graph[current_node][i];
					if((visited[i] == 0) || (visited[i] != 0 && unlocked[i] == 1)){
						cout << i << " inserted ";
						apq.push(AstarQ(i,next_node_gcost + h_value[i],next_node_gcost,current_node));				
					}
				}
			}			
		}
		else{
			apq.pop();
		}
		cout << endl;
		visited[current_node] ++;
		printQ(apq);

	}
	
	ll distance = apq.top().gcost;
	cout << "Total distance from the source to destination is " << distance << endl; 
	cout << "The path taken to reach the destination is" << endl;
	cout << path.front();
	path.pop_front();

	while(!path.empty()){
		cout << " -> " << path.front();
		path.pop_front();
	}
	cout << " -> " << DESTINATION;
	cout << endl;

	while(!apq.empty()){
		apq.pop();
	}
	return 0;
}