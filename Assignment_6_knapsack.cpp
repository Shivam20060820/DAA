#include <iostream>
#include <string>
using namespace std;

class Knapsack
{


    int n,m; 
    int p[20];  
    int w[20]; 
    
    int max(int a, int b)
    {
        int ans;
        
        if(a>b)
            ans = a;
        else
            ans = b;
        return ans;
   } 
   
   int B[20][20]; 
   
   public:
    
    void knap();
    void display();
    void finditem();
    
    
};

void Knapsack :: knap()
{
     cout << "Enter no of objects ";
    cin >> n;
    cout << "Enter max capacity ";
    cin >> m;
    
    cout << "Enter weights of objects ";
    for (int i = 0; i<n; i++) 
    cin >> w[i];

    cout << "Enter profits ";
    for (int i = 0; i< n ; i++)
    cin >> p[i];
                                                
    for (int i = 0; i<=n; i++)  
    B[i][0] = 0;
    
    for (int j = 0; j <=m; j++) 
    B[0][j] = 0;
    
    for (int i=1 ; i<=n ;i++)     
    {
        for(int j=0; j<=m; j++)     
        {
            
            if (w[i-1] <= j)      
            
             {
                    if (p[i-1] + B[i-1][j - w[i-1]] > B[i-1][j])   
                    {
                             B[i][j] = p[i-1] + B[i-1][j - w[i-1]];  
                    } 
                    else 
                    {
                                B[i][j] = B[i-1][j];
                    }
             }
            else 
                B[i][j] = B[i-1][j] ;   
        }
   }
}
    
    
void Knapsack::display() 
    {
    cout << "Tabular format\n";
    
    for (int i = 0; i <= n; i++) 
    {
        for (int j = 0; j <= m; j++) 
        {
            cout << B[i][j] << "\t";   
        }
        
        cout << "\n";
    }
    cout << "\n Maximum Profit is " << B[n][m] << endl;
}

void Knapsack::finditem() 
{
    int i = n;
    int k = m;
    
    
    
    while (i > 0) 
    {
        if (k >= w[i - 1] && B[i][k] != B[i - 1][k]) 
        {
            cout << "Item " << i << " 1" << endl;
            k = k - w[i - 1];
        } 
        else 
        {
            cout << "Item " << i << " 0" << endl;
        }
        i--;
    }
}
   
int main()
 {
    Knapsack k;
    
    k.knap();
    k.display();
    k.finditem();
    
    return 0;
 }