#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>

using namespace std;

/*bool compare_burst_times(int burst_time_a, int burst_time_b) 
{ 
    return (burst_time_a< burst_time_b); 
} */

//comparator function
//compares two pairs according to the arrival time first and then according to their burst times
struct compare_burst_times{
    bool operator()(pair<int,int>arrival_with_burst_time_A,pair<int,int>arrival_with_burst_time_B)
    {
        if(arrival_with_burst_time_A.first<arrival_with_burst_time_B.first)  //compare based on arrival times
        return 1;
        else if(arrival_with_burst_time_A.first==arrival_with_burst_time_B.first)
        {
            if(arrival_with_burst_time_A.second>arrival_with_burst_time_B.second)  //compare based on burst times
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
    int num_processes;
    cin>>num_processes;    //number of processes
    vector<int>arrival_times(num_processes);   //arrival time of processes 
    vector<float>burst_times(num_processes);   //burst time of processes
    
    //input 
    for(int process_no=1;process_no<=num_processes;++process_no)
    {
        cin>>arrival_times[process_no]>>burst_times[process_no];
    }

    multimap<pair<int,int>,int,compare_burst_times>map_comparing_burst_times;//multimap using comparator function
    
    for(int process_no=1;process_no<=num_processes;++process_no)
    {
        map_comparing_burst_times.insert(make_pair(make_pair(arrival_times[process_no],burst_times[process_no]),process_no));
    }
    

    vector<int>gnatt;    //gantt chart
    queue<int>waiting_queue;         //waiting queue
    set<int>processes_already_executed;
    float rem_time[num_processes];
    float end_time[100];
    float final_time[num_processes];
    int process_count=0;
    bool finish[num_processes];
    bool visited[num_processes];
    float time_quantum;
    vector<int>sum_of_burst_time_of_processes;
    
    memset(finish,num_processes,false);    
    memset(visited,num_processes,false);
    end_time[0]=0;
    
    int max=*max_element(burst_times.begin(),burst_times.end());
    int min=*min_element(burst_times.begin(),burst_times.end());
    time_quantum=0.85*max;
    int threshold=(max+min)/2;
    
    auto iterator_comparing_processes=map_comparing_burst_times.begin();
    if(burst_times[iterator_comparing_processes->second]>=time_quantum)        //if burst time of the first process is higher than the calculated time quantum
    {
        gnatt.push_back(iterator_comparing_processes->second);
        process_count+=1;
        end_time[process_count]=end_time[process_count-1]+time_quantum;
        rem_time[iterator_comparing_processes->second]=burst_times[iterator_comparing_processes->second]-time_quantum;
        burst_times[iterator_comparing_processes->second]=burst_times[iterator_comparing_processes->second]-time_quantum;
        visited[iterator_comparing_processes->second]=true;
        processes_already_executed.insert(iterator_comparing_processes->second);
    }
    else
    {
        gnatt.push_back(iterator_comparing_processes->second);
        process_count+=1;
        end_time[process_count]=end_time[process_count-1]+time_quantum;
        burst_times[iterator_comparing_processes->second]=0;
        rem_time[iterator_comparing_processes->second]=0;
        finish[iterator_comparing_processes->second]=true;
        visited[iterator_comparing_processes->second]=true;
        processes_already_executed.erase(iterator_comparing_processes->second);
    }
    iterator_comparing_processes++;
    while(iterator_comparing_processes!=map_comparing_burst_times.end())
    {
        if(iterator_comparing_processes->first.first<=time_quantum)
        {
        waiting_queue.push(iterator_comparing_processes->second);
        processes_already_executed.insert(iterator_comparing_processes->second);
        visited[iterator_comparing_processes->second]=true;
        }
        iterator_comparing_processes++;
    }
    auto first_process_no=map_comparing_burst_times.begin();
    waiting_queue.push(first_process_no->second);
    visited[first_process_no->second]=true;
    processes_already_executed.insert(first_process_no->second);
    
        
    while(!waiting_queue.empty())
    {
        int current_process=waiting_queue.front();
        cout<<current_process<<"  ";
        gnatt.push_back(current_process);
        visited[current_process]=true;
        processes_already_executed.insert(current_process);
        
        int sum=0;
    int queue_size=waiting_queue.size();
    int average=0;
    
    int process_at_start_of_queue; 
    while(!waiting_queue.empty())
    {
        process_at_start_of_queue=waiting_queue.front();
        sum_of_burst_time_of_processes.push_back(process_at_start_of_queue);
        waiting_queue.pop();
    }
    
    for(int i=0;i<sum_of_burst_time_of_processes.size();++i)
    {
        waiting_queue.push(sum_of_burst_time_of_processes[i]);
    }
    
        for(int v=sum_of_burst_time_of_processes.size()-1;v>=0;--v)
    {
        sum+=burst_times[sum_of_burst_time_of_processes[v]];
    }
    average=sum/queue_size;
    time_quantum=0.85*average;
    
    process_count+=1;
    end_time[process_count]=end_time[process_count-1]+time_quantum;
    
    if(burst_times[current_process]>=threshold)
    {
        rem_time[current_process]=burst_times[current_process]-time_quantum;
        burst_times[current_process]=rem_time[current_process];
    }
    else if(burst_times[current_process]<threshold)
    {
        rem_time[current_process]=0;
        burst_times[current_process]=0;
        processes_already_executed.erase(current_process);
    }
    
    
    if(rem_time[current_process]<=0)
    {
        finish[current_process]=true;
    }
    else
    {
    finish[current_process]=false;
    }
    
    for(int process_no=1;process_no<=num_processes;++process_no)
    {
        if((arrival_times[process_no]<=end_time[process_count])&&(finish[process_no]==false)&&(burst_times[process_no]<=time_quantum)&&(processes_already_executed.find(process_no)==processes_already_executed.end())&&(visited[process_no]==false))
        {
            waiting_queue.push(process_no);
            cout<<process_no;
            visited[process_no]=true;
            processes_already_executed.insert(process_no);
        }
    }
    
    
    if(burst_times[current_process]>0)
    {
    waiting_queue.push(current_process);
    }
    
    sum_of_burst_time_of_processes.clear();
        waiting_queue.pop();
    }
    
    for(int process_no=0;process_no<gnatt.size();++process_no)
    {
        cout<<gnatt[process_no];
    }
return 0;
}