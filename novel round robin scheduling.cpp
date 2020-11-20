#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>

using namespace std;

bool comp(int a, int b) 
{ 
    return (a < b); 
} 

//comparator function
//compares two pairs according to the arrival time first and then according to their burst times
struct comp1{
    bool operator()(pair<int,int>a,pair<int,int>b)
    {
        if(a.first<b.first)
        return 1;
        else if(a.first==b.first)
        {
            if(a.second>b.second)
            return 1;
            return 0;
        }
        else
        return 0;
    }
};

//main
int main()
{
    int n;
    cin>>n;    //number of processes
    vector<int>a(n);   //arrival time of processes 
    vector<float>b(n);   //burst time of processes
    
    //input 
    for(int i=1;i<=n;++i)
    {
        cin>>a[i]>>b[i];
    }

    multimap<pair<int,int>,int,comp1>mp1;//multimap using comparator function
    
    for(int i=1;i<=n;++i)
    {
        mp1.insert(make_pair(make_pair(a[i],b[i]),i));
    }
    

    vector<int>gnatt;    //gantt chart
    queue<int>q;         //waiting queue
    set<int>inqueue;
    float rem_time[n];
    float end_time[100];
    float final_time[n];
    int k=0;
    bool finish[n];
    bool visited[n];
    float time_quantum;
    vector<int>temp;
    
    memset(finish,n,false);    
    memset(visited,n,false);
    end_time[0]=0;
    
    int max=*max_element(b.begin(),b.end());
    int min=*min_element(b.begin(),b.end());
    time_quantum=0.85*max;
    int threshold=(max+min)/2;
    
    auto u=mp1.begin();
    if(b[u->second]>=time_quantum)
    {
        gnatt.push_back(u->second);
        k+=1;
        end_time[k]=end_time[k-1]+time_quantum;
        rem_time[u->second]=b[u->second]-time_quantum;
        b[u->second]=b[u->second]-time_quantum;
        visited[u->second]=true;
        inqueue.insert(u->second);
    }
    else
    {
        gnatt.push_back(u->second);
        k+=1;
        end_time[k]=end_time[k-1]+time_quantum;
        b[u->second]=0;
        rem_time[u->second]=0;
        finish[u->second]=true;
        visited[u->second]=true;
        inqueue.erase(u->second);
    }
    u++;
    while(u!=mp1.end())
    {
        if(u->first.first<=time_quantum)
        {
        q.push(u->second);
        inqueue.insert(u->second);
        visited[u->second]=true;
        }
        u++;
    }
    auto it=mp1.begin();
    q.push(it->second);
    visited[it->second]=true;
    inqueue.insert(it->second);
    
        
    while(!q.empty())
    {
        int m=q.front();
        cout<<m<<"  ";
        gnatt.push_back(m);
        visited[m]=true;
        inqueue.insert(m);
        
        int sum=0;
    int n1=q.size();
    int average=0;
    
    int val; 
    while(!q.empty())
    {
        val=q.front();
        temp.push_back(val);
        q.pop();
    }
    
    for(int i=0;i<temp.size();++i)
    {
        q.push(temp[i]);
    }
    
        for(int v=temp.size()-1;v>=0;--v)
    {
        sum+=b[temp[v]];
    }
    average=sum/n1;
    time_quantum=0.85*average;
    
    k+=1;
    end_time[k]=end_time[k-1]+time_quantum;
    
    float zero=0;
    int temp1;
    
    if(b[m]>=threshold)
    {
        rem_time[m]=b[m]-time_quantum;
        b[m]=rem_time[m];
    }
    else if(b[m]<threshold)
    {
        rem_time[m]=0;
        b[m]=0;
        inqueue.erase(m);
    }
    
    
    if(rem_time[m]<=0)
    {
        finish[m]=true;
    }
    else
    {
    finish[m]=false;
    }
    
    for(int i=1;i<=n;++i)
    {
        if((a[i]<=end_time[k])&&(finish[i]==false)&&(b[i]<=time_quantum)&&(inqueue.find(i)==inqueue.end())&&(visited[i]==false))
        {
            q.push(i);
            cout<<i;
            visited[i]=true;
            inqueue.insert(i);
        }
    }
    
    
    if(b[m]>0)
    {
    q.push(m);
    }
    
    temp.clear();
        q.pop();
    }
    
    for(int i=0;i<gnatt.size();++i)
    {
        cout<<gnatt[i];
    }
return 0;
}