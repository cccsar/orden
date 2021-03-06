#include<iostream> 
#include<stdio.h>
#include<algorithm> 
#include<set> 
#include<vector>
#include<deque>
#include<stack>
#include<queue>
#include<utility>
#include<climits> 
#include<unordered_map>

using namespace std; 

#define FOR(i ,u ,l) for(i=l; i<u; i++) 
#define ROF(l,u) for(int i=u; i>l-1; i--) 
#define ri(c) scanf("%d",&c)
#define rii(c,cc) scanf("%d %d", &c, &cc)
#define riii(c,cc,ccc) scanf("%d %d %d", &c, &cc, &ccc)
#define rw(s) scanf("%s",&s)

typedef pair <int, int> pi; 
typedef pair <int, pair<int, int> > pii; 
typedef vector< int > vi; 
typedef vector< pi > vii; 
typedef vector< pii > viii; 
typedef vector< pi > *adl; 
typedef vector< pii > *wadl; 


const int TCASES = 1000;
const int MATMAX = 100;
const int WSIZE = 10; 
const int SSIZE = 6; 

const char* ALLIZZWELL = "ALLIZZWELL";
const char* WORD = "AEILWZ";

bool resp[TCASES];
bool vtd[MATMAX][MATMAX];
char letters[MATMAX+1][MATMAX+1];

void successors(vii &suc,  int i, int j , int height, int wedth) { 

	if ( i > 0 && !vtd[i-1][j])  		//up
		suc.push_back( { i-1, j}  ) ; 

	if ( i < height - 1 && !vtd[i+1][j])   	//down
		suc.push_back( { i+1, j} );

	if ( j > 0 && !vtd[i][j-1]) 		//left
		suc.push_back( {i, j-1} ); 
	
	if ( j < wedth - 1 && !vtd[i][j+1])  	//right
		suc.push_back( {i, j+1} );
	

	if( i > 0 && j > 0 && !vtd[i-1][j-1]) 			//top left corner
		suc.push_back( {i-1, j-1} );
	
	if( i > 0 && j < wedth - 1 && !vtd[i-1][j+1])  		//top right corner
		suc.push_back( {i-1, j+1} ); 
	
	if( i < height - 1 && j > 0 && !vtd[i+1][j-1]) 		//bottom left corner
		suc.push_back( {i+1, j-1} );
	
	if ( i < height - 1 && j < wedth - 1 && !vtd[i+1][j+1])	//bottom right corner
		suc.push_back( {i+1, j+1} );
}


bool traversing(int i, int j, int height, int wedth, const int index) { 
	bool guard; 
	vii surr; 

	guard = false; 

	successors(surr, i, j, height, wedth); 

	for(pi succ: surr ) { 
		if( letters[ succ.first ][ succ.second ] == ALLIZZWELL[ index ] ) {

			vtd[ succ.first ][ succ.second ] = true; 

			

			if ( index == WSIZE - 1) {
				vtd[ succ.first ][ succ.second ] = false; 
				return true; 
			}


			guard = traversing(succ.first, succ.second, height, wedth, index + 1); 	
			
			vtd[ succ.first ][ succ.second ] = false; 

			if ( guard ) 	//if the call returned true, skip traverse
				break; 

		}
	}
	
	return guard; 
}



bool setCheck(unordered_map<char, int> letter_set) { 
	
	for(pair<char, int> k: letter_set ) { 
		if ( k.first == 'Z' ) {
			if ( k.second < 2 ) 
				return false; 
		}
		else if ( k.first == 'L' ) { 
			if ( k.second < 4 ) 
				return false; 
		}
		else if ( k.second == 0 ) {
		       return false; 
		}	       
	}

	return true; 
}


int main() 
{
	int t, r, c, i_, j_, k_; 
	char letra[MATMAX+1]; 
	vector< vector<bool> > visited; 
	unordered_map<char, int> letter_set; 
	vii begins; 	


	for(i_=0; i_<SSIZE ; i_++) 
		letter_set[ WORD[i_] ] = 0; 

	visited.resize(MATMAX); 
	for(i_=0; i_< MATMAX ; i_++) 
		visited[i_].resize( MATMAX ) ;		


	ri(t); 
	for (i_=0 ; i_<t ; i_++) {

		
		rii(r, c);		
		for (j_=0 ; j_<r ; j_++) { 	

			scanf("%s", letra); 
			for (k_=0 ; k_<c ; k_++) { 

				letters[j_][k_] = letra[k_];
				if ( letter_set.count( letra[k_] ) != 0 ) 
					letter_set[ letra[k_] ] += 1; 

				if ( letra[k_] == 'A' )  
					begins.push_back( {j_, k_} ); 
				
			}	
		}	


		if ( !setCheck( letter_set ) ) 	//if not all letters then avoid traversing
			resp[i_] = false; 
		else {
			for(pi source : begins )  {
				resp[i_] = traversing(source.first, source.second, r, c, 1); 
	
				if (resp[i_])
					break; 		
			}	
		}

		begins.clear(); 	
		for(j_=0; j_<SSIZE ; j_++) 
			letter_set[ WORD[j_] ] = 0; 
	}


	for(i_=0; i_<t ; i_++) 
		(resp[i_])? cout<<"YES"<<endl : cout<<"NO"<<endl; 	
	

	return 0; 
}
