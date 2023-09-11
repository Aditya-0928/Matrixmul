// C++ program to solve fractional
// Knapsack Problem
#include <bits/stdc++.h>
using namespace std;
// Structure for an item which stores
// weight & corresponding value of Item
struct Item {
int value, weight;
// Constructor
Item(int value, int weight)
: value(value), weight(weight)
{
}
};
bool cmp(struct Item a, struct Item b)
{
double r1 = (double)a.value / a.weight;
double r2 = (double)b.value / b.weight;
return r1 > r2;
}
// Main greedy function to solve problem
double fractionalKnapsack(struct Item arr[],
int N, int size)
{
sort(arr, arr + size, cmp);
int curWeight = 0;
double finalvalue = 0.0;
for (int i = 0; i < size; i++) {
if (curWeight + arr[i].weight <= N) {
curWeight += arr[i].weight;
finalvalue += arr[i].value;
}
else {
int remain = N - curWeight;
finalvalue += arr[i].value
* ((double)remain
/ arr[i].weight);
break;
}
}
return finalvalue;
}
int knapSack(int W, int wt[], int val[], int n)
{
// Base Case
if (n == 0 || W == 0)
return 0;
// If weight of the nth item is more than Knapsack capacity W, then
// this item cannot be included in the optimal solution
if (wt[n - 1] > W)
return knapSack(W, wt, val, n - 1);
// Return the maximum of two cases: (1) nth item included (2) not included
else
return max(val[n - 1] + knapSack(W - wt[n - 1], wt, val, n - 1),
knapSack(W, wt, val, n - 1));
}
// Driver Code
int main()
{
// Weight of knapsack
int N = 60;
// Given weights and values as a pairs
Item arr[] = { { 100, 10 },
{ 280, 40 },
{ 120, 20 },
{ 120, 24 } };
int size = sizeof(arr) / sizeof(arr[0]);
cout << "Maximum profit earned by using fractional knapsack = "
<< fractionalKnapsack(arr, N, size)<<endl;
cout << "Enter the number of items in a Knapsack for 0-1 knapsach:";
int n, W;
cin >> n;
int val[n], wt[n];
for (int i = 0; i < n; i++)
{
cout << "Enter value and weight for item " << i << ":";
cin >> val[i];
cout<<endl;
cin >> wt[i];
}
cout << "Enter the capacity of knapsack";
cin >> W;
cout << "Maximum profit earned by using 0-1 knapsack = "
<< knapSack(W, wt, val, n)<<endl;
return 0;
}     