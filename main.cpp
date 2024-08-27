#include<fstream> 
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include <stack>
#include <algorithm>





using namespace std; 

void dfs1(int v, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& stk) 
{
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs1(u, adj, visited, stk);
        }
    }
    stk.push(v);
}

void dfs2(int v, vector<vector<int>>& revAdj, vector<bool>& visited, vector<int>& component) 
{
    visited[v] = true;
    component.push_back(v);
    for (int u : revAdj[v]) {
        if (!visited[u]) {
            dfs2(u, revAdj, visited, component);
        }
    }
}
 
int main() 
{

	fstream in,out;
	int flag=0;
	int N;
	stack<int> stk;
	vector<vector<int>> adj;

	

	in.open("input.txt",ios::in);
	

	if(in.is_open()){

		string line;
		while(getline(in, line))
		{
				char * c = line.data();
			
				char *ptr=strtok(c,"->\n");

				if(flag==0)
				{
					//cout<<ptr<<endl;
					flag=1;
					N=stoi(ptr);
					continue;
				}
				else
				{
					ptr=ptr+1;
					//cout<<ptr<<endl;
					//i=stoi(ptr);
				}
			

			vector<int> temp;

			while((ptr=strtok(NULL,"->"))!=NULL)
			{
				ptr=ptr+1;
				int v=stoi(ptr);
				v--;
				temp.push_back(v);
				//cout<<ptr<<endl;
			}
			adj.push_back(temp);
			
		}

		in.close();
		
	}


	vector<vector<int>> revAdj(N);


	for(int i=0;i<adj.size();i++)
	{
		for(int j=0;j<adj[i].size();j++)
			{
			
				revAdj[adj[i][j]].push_back(i);
			}
		
	}


	




	


	
	vector<bool> visited(N, false);

    for (int i = 0; i < N; i++) 
	{
        if (!visited[i]) 
		{
            dfs1(i, adj, visited, stk);
        }
    }

    
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> strConCom;

    while (!stk.empty()) 
	{
        int v = stk.top();
        stk.pop();
        if (!visited[v]) 
		{
            vector<int> component;
            dfs2(v, revAdj, visited, component);
            strConCom.push_back(component);
        }
    }

	vector<int> strConComID(N, -1);

    for (int i = 0; i < strConCom.size(); i++) 
	{
        for (auto v : strConCom[i]) 
		{
            strConComID[v] = i;
        }
    }

    vector<bool> inEdge(strConCom.size(), false), outEdge(strConCom.size(), false);

    for (int v = 0; v < N; v++) 
	{
        for (auto u : adj[v]) 
		{
            if (strConComID[v] != strConComID[u]) 
			{
                outEdge[strConComID[v]] = true;
                inEdge[strConComID[u]] = true;
            }
        }
    }

	int sourceCount = 0, sinkCount = 0;
    int sourceStrConCom = -1, sinkStrConCom = -1;

    for (int i = 0; i < strConCom.size(); i++) 
	{
        if (!inEdge[i]) 
		{
            ++sourceCount;
            sourceStrConCom = i;
        }
        if (!outEdge[i]) 
		{
            ++sinkCount;
            sinkStrConCom = i;
        }
    }

	
	out.open("output.txt",ios::app);
	 if (sourceCount == 1 && sinkCount == 1) 
	 {
		string answer="";
		string sugestion="v";
		answer+="yes";
		out<<answer<<endl;
        
        int u = strConCom[sinkStrConCom][0];  
        int v = strConCom[sourceStrConCom][0];  
		u++;
		v++;
		sugestion=sugestion+to_string(u)+"->v"+to_string(v);
		out<<sugestion;
        
    } else 
	{
		string answer="no";
        out<<answer<<endl;
    }

	out.close();

    return 0;



}

