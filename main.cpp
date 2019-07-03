//
//  main.cpp
//  Project 3
//
//  Created by Mai Pham on 10/26/17.
//  Copyright © 2017 Mai Pham. All rights reserved.
//

#include "LinkedQueue.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

int main()
{
    //input data
    string fileName;
    int l;                              //# of line
    int t;                              //total run time
    int n;                              //max minutes between every call
    int m;                              //max minutes for serve time

    int nextCall;                       //next random call
    int servedTime = 0;                 //minutes to serve current call
    bool serving = false;               //on call or not
    int numOfCall = 0;                  //total # of customers called
    int customerServed = 0;             //total # of customers got served
    int totalServedTime = 0;            //total served time
    int estimated;                      //estimate wait time
    
    //end of program calculation
    int maxInLine = 0;                  //highest amount of customers wait in line
    int currentWaitTime = 0;            //current customer wait time
    int maxWaitTime = 0;                //longest wait time for 1 customers
    int totalWaitTime = 0;              //total wait time for all customers
    
    cout << "Please enter input file name: ";
    cin >> fileName;
    ifstream inputFile;
    inputFile.open(fileName);
    if (!inputFile)
    {
        cout << "Error opening file. \n";
        cout << "The file was not found" << endl;
        return 1;
    }
    while (!inputFile.eof())
    {
        inputFile >> l >> t >> n >> m;
    }
    
    LinkedQueue<int> callLine;
    srand(time(0));
    
    ofstream outFile;
    outFile.open("CallSimulation.txt");
    outFile << "Project 3: Queues & Simulation\n";
    outFile << "By Mai Pham\n\n";
    
    nextCall = rand() % n + 1;
    for (int i = 1; i <= t; i++)
    {
        outFile << "Minute " << i << ":";
        if (i == nextCall)
        {
            numOfCall++;
            outFile << "\n  => Customer " << numOfCall << " call.";
            
            callLine.enqueue(nextCall);
            if (maxInLine < callLine.size())
                maxInLine = callLine.size();
            
            if (serving == false)
                estimated = 0;
            else
                estimated = (totalServedTime/(customerServed+1))*callLine.size();
            outFile << "\n  => Estimate wait time for customer " << numOfCall << " is " << estimated << ".";
            
            nextCall += (rand() % n + 1);
        }
        if (i == servedTime)
        {
            customerServed++;
            serving = false;
            outFile << "\n  => Customer " << customerServed << " completed.";
        }
        if (serving == false && !callLine.empty())
        {
            currentWaitTime = i - callLine.front();
            totalWaitTime += currentWaitTime;
            if (maxWaitTime < currentWaitTime)
                maxWaitTime = currentWaitTime;
            
            callLine.dequeue();
            outFile << "\n  => Serving customer " << (customerServed+1) << ".";
            servedTime = (rand() % m + 1);
            totalServedTime += servedTime;
            servedTime += i;
            serving = true;
        }
        outFile << endl;
    }
    
    outFile << "\nEnd of Program Report\n";
    outFile << "=================================================";
    outFile << "\nNumbers of customers called: \t\t\t" << numOfCall;
    outFile << "\nNumbers of customers served: \t\t\t" << customerServed;
    outFile << "\nNumber of customers left in line: \t\t" << callLine.size();
    outFile << "\nMaximum number of customers in line: \t" << maxInLine;
    outFile << "\nLongest wait time for a customer: \t\t" << maxWaitTime;
    outFile << "\nAverage wait time for customers: \t\t" << (double)totalWaitTime/customerServed;
    outFile << endl;
    return 0;
}

