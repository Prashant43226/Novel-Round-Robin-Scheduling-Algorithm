# Novel-Round-Robin-Scheduling-Algorithm
This repository contains a novel Round Robin Scheduling Alggorithm and was created as part of our Operating System ProjectWork.
The uniqueness of thsi algorithm lies in the fact that unlike previous round robin scheduling algorithms this one uses a dynamic time quantum and a threshold value to calculate the gnatt chart.
<br/>Our work has been largely inspired from the work suggested in the research papers mentioned in references where a dynamic time quantum calculation is used.Our work includes improvements in the previous existing models by some amounts and is a vast improvement of the original Round Robin Scheduling Algorithm.The Round Robin Scheduling Algorithm uses a fixed value of time quantum which increases the context switching.Our aim has been to reduce the context switching.We take idea from the papers referenced and improve upon them using different techniques which include sorting the processes first based on arrival time then burst time;then using a dynamic time quantum by calculating the average of remaining burst time in the waiting queue and then using a threshold value to further preempt the working of processes. In a brief the idea suggested in this paper is a minor improvement over the previous mentioned round robin scheduling techniques and a significant improvement over the original Round Robin Scheduling in terms of context switching.

# Proposed work :

1.Sort the processes according to their arrival time and then based on their burst time.<br/>
2.Calculate the time quantum for the first process.This is given by 
TQ=0.85x(Maximum of burst time amongst all processes)<br/>
3.Calculate the threshold value below which if the burst time falls it will be completely executed.
This is given by Threshold=(Max burst time+Min burst time)/2<br/>
4.Complete the execution of the first process and push the other processes which have  arrived so far into the waiting queue.Then push the first process to the end of waiting queue after decreasing its burst time.<br/>
5.For the processes in queue dynamically calculate the time quantum using the formula:<br/>
For i in queue<br/>
Calculate the sum of remaining burst time of all the i<br/>
Find the average <br/>
Calculate the time quantum as 0.85Xaverage<br/>
6.Now for the processes in queue,begin the execution if the burst time is less than the time quantum.If some process arrives within this period push it into the waiting queue.<br/>
7.Repeat the process form 5 to 6 till the waiting queue is not completely empty.<br/>

# References:

<br/>
1.A new Improved Round Robin-Based Scheduling Algorithm-A comparative Analysis (DOI:10.1109/ICCISci.2019.8716476)(LINK:https://ieeexplore.ieee.org/document/8716476)<br/>
2.Smart Round Robin CPU Scheduling Algorithm For Operating Systems (DOI: 10.1109/ICEECCOT46775.2019.9114602)(LINK:https://ieeexplore.ieee.org/document/9114602)<br/>
3.Improved Round Robin CPU scheduling algorithm: Round Robin, Shortest Job First and priority algorithm coupled to increase throughput and decrease waiting time and turnaround time(DOI: 10.1109/ICGTSPICC.2016.7955294)(LINK:https://ieeexplore.ieee.org/document/7955294)
