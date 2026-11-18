#include <stdio.h>
#define MAX 100

void inputProcesses(int n, int arrival[], int burst[], int remaining[]);
void simulateSRTF(int n, int arrival[],int burst[], int remaining[], int finish[], int waiting[], int turn_around[], float *total_wait, float *total_turnaround);
void displayResults(int n, int arrival[], int burst[], int finish[], int turn_around[], int waiting[], float total_wait, float total_turnaround); 

int main()
{ 
int n;
int arrival[MAX], burst[MAX], remaining[MAX];
int finish[MAX], waiting[MAX], turn_around[MAX];
float total_wait = 0, total_turnaround = 0;
printf("Enter number of processses:");
scanf("%d",&n);
inputProcesses(n, arrival, burst, remaining);
simulateSRTF(n, arrival, burst, remaining, finish,waiting,turn_around,&total_wait, &total_turnaround );
displayResults(n, arrival, burst,finish,turn_around, waiting, total_wait, total_turnaround);
return 0;
}
void inputProcesses(int n, int arrival[], int burst[], int remaining[])
{
 for(int i=0;i<n;i++){
   printf("Enter arrival time and burts time for Process %d:",i+1);
   scanf("%d%d",&arrival[i],&burst[i]);
   remaining[i]=burst[i];
 }
}
void simulateSRTF(int n, int arrival[],int burst[], int remaining[], int finish[], int waiting[], int turn_around[], float *total_wait, float *total_turnaround)
{
 
 int time = 0, completed = 0;
 
 while (completed!=n) {
 int idx = -1;
 int min_time = 1e9;
  for(int i=0;i<n;i++){
  if(arrival[i] <= time && remaining[i] > 0 && remaining[i] < min_time)
  {
   min_time  = remaining[i];
   idx = i;
  }
 }
 if (idx!=-1)
 {
  remaining[idx]--;
  time++;
  if(remaining[idx]==0)
  {
  completed++;
  finish[idx]=time;
  turn_around[idx] = finish[idx] - arrival[idx];
  waiting[idx] = turn_around[idx] - burst[idx];
  *total_wait += waiting[idx];
  *total_turnaround+=turn_around[idx];
  }
 }
 else{
 time++;
 }
 }
}
void displayResults(int n, int arrival[], int burst[], int finish[], int turn_around[], int waiting[], float total_wait, float total_turnaround) 
{
 printf("\nProcess\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
 for(int i=0;i<n;i++){
  printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1, arrival[i],burst[i],finish[i],turn_around[i],waiting[i]);
  
 }
 printf("\nAverage waiting time: %.2f",total_wait/n);
 printf("\nAverage Turnaround time: %.2f",total_turnaround/n);
 
}



