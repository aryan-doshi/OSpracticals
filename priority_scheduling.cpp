#include<iostream>
using namespace std;

int main()
{
    int n, burst_time[10], priority[10], wait_time[10], turn_around_time[10], remaining_time[10], highest_priority, time=0, completed=0, i, j;

    cout<<"Enter the number of processes: ";
    cin>>n;

    cout<<"Enter burst time and priority for each process: ";
    for(i=0; i<n; i++)
    {
        cin>>burst_time[i]>>priority[i];
        remaining_time[i]=burst_time[i];
    }

    while(completed!=n)
    {
        highest_priority=-1;
        for(i=0; i<n; i++)
        {
            if(remaining_time[i]>0 && (highest_priority==-1 || priority[i]<priority[highest_priority]))
            {
                highest_priority=i;
            }
        }

        time+=burst_time[highest_priority];
        remaining_time[highest_priority]=0;
        turn_around_time[highest_priority]=time;
        wait_time[highest_priority]=turn_around_time[highest_priority]-burst_time[highest_priority];
        completed++;
    }

    int total_wait_time=0, total_turnaround_time=0;

    cout<<"Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";

    for(i=0; i<n; i++)
    {
        cout<<"P"<<i+1<<"\t"<<burst_time[i]<<"\t\t"<<priority[i]<<"\t\t"<<wait_time[i]<<"\t\t"<<turn_around_time[i]<<endl;
        total_wait_time+=wait_time[i];
        total_turnaround_time+=turn_around_time[i];
    }

    cout<<"Average Waiting Time: "<<(float)total_wait_time/n<<endl;
    cout<<"Average Turnaround Time: "<<(float)total_turnaround_time/n<<endl;

    return 0;
}
