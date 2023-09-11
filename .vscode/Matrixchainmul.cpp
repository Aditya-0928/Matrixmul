#include<iostream>
#include<climits>
using namespace std;
 
int matrixChain(int n, int order[])
{
    int i,j,k;
    int tempValue;
 
    int dp[n+1][n+1];
    for(i=1;i<=n;i++)
    {
        dp[i][i]=0;
    }
    for(int size=2;size<=n;size++)
    {
        for(i=1;i<=(n-size+1);i++)
        {
            j=i+size-1;
            dp[i][j]=INT_MAX;
            for(k=i;k<j;k++)
            {
                tempValue=dp[i][k]+dp[k+1][j]+order[i-1]*order[k]*order[j];
 
                //if tempValue is lesser than the current value of dp[i][j], replace it
                if(tempValue<dp[i][j])
                {
                    dp[i][j]=tempValue;
                }
            }
 
        }
 
    }
 
    //return the min. multiplication operations for the original matrix
    return dp[1][n];
 
}
 
int main()
{
    int i,j;
    int n;
 
    cout<<"Enter the number of matrices in the chain( should be greater than 1)  ";
    cin>>n;
 
    int order[n+1];
 
    //order of matrix i will be given by order[i-1]*order[i]
    cout<<"Enter the order array of the matrix chain ("<<n+1<<" elements)"<<endl;
    for(i=0;i<=n;i++)
    {
        cin>>order[i];
    }
 
    cout<<"The minimum number of multiplication operations required to multiply the matrix chain is "<<matrixChain(n,order);
 
    cout<<endl;
    return 0;
}