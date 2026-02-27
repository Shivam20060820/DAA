#include<iostream>
// implement mege and wuick sort and find its time complexity
// accept mobil user info 4 fields-uid/isername/mobile no./bill amount
// dsiplay the data in descending order along with uid using recursive merge sort
// display the number of passes and comparisons for different test cases-worst and best
#include<string>
using namespace std;
class userinfo
{
    public:
    int uid;
    string username;
    int bill;
    int static pass;
    // int comparison=0;
    static int comparisons;
    void linear_search(class userinfo obj1[],int n,string key);
    void binary_search(class userinfo obj1[],int low,int high,string key);
    void bub_sort(class userinfo obj1[],int n);
    void merge_sort(class userinfo obj1[],userinfo obj,int low,int high);
    void accept();
    void merge(class userinfo obj1[],userinfo obj,int low, int mid, int high);
    void display();
    void quick(class userinfo obj1[],int p,int r);
    int partition(class userinfo obj1[],int p,int r);
    int bin_rec(class userinfo obj1[],int low,int high,string key);
    // int x;
};
int userinfo::comparisons=0;
int userinfo::pass=0;
void userinfo::bub_sort(class userinfo obj1[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(obj1[j].username>obj1[j+1].username)
            {
                userinfo temp=obj1[j];
                obj1[j]=obj1[j+1];
                obj1[j+1]=temp;
            }
        }
    }
}
void userinfo::binary_search(class userinfo obj1[],int low,int high,string key)
{
    int flag=0;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(obj1[mid].username==key)
        {
            cout<<"The user is found at location "<<mid+1<<endl;
            flag=1;
            return;
        }
        else if(key<obj1[mid].username)
        {
            high=mid-1;
        }
        else
        low=mid+1;
    }
    if(flag==0)
    {
        cout<<"The user is not found"<<endl;
    }
}
void userinfo::linear_search(class userinfo obj1[],int n,string key)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(obj1[i].username==key)
        {
            cout<<"The person is found at"<<i+1<<endl;
            obj1[i].display();
            return;
        }
    }
    cout<<"The user is not found"<<endl;
}
void userinfo::accept()
{
    // for(int i=0;i<n;i++)
    // {
        cout<<"Enter uid\n";
        cin>>uid;


        cout<<"Enter username\n";
        cin>>username;

        cout<<"Enter Bill no";
        cin>>bill;
        cout<<"\n";
    // }
}

void userinfo::display()
{
    cout<<"uid: "<<uid<<"\t"<<"username: "<<username<<endl;;
    // cout<<"\n";
    cout<<"Bill no."<<bill;
}

void userinfo::merge_sort(class userinfo obj1[],userinfo obj,int low,int high)
{
    int mid;
    if(low<high)
    {
        pass++;
        mid=(low+high)/2;
        merge_sort(obj1,obj,low,mid);
        merge_sort(obj1,obj,mid+1,high);
        merge(obj1,obj,low,mid,high);
    }
}
void userinfo::merge(class userinfo obj1[],userinfo obj,int low, int mid, int high)
{
    userinfo temp[10];
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high)
    {
        if (obj1[i].username > obj1[j].username)
            {
                temp[k++] = obj1[i++];
            }
        else
            {
                temp[k++] = obj1[j++];
            }
            comparisons++;
    }

    while (i <= mid)
        temp[k++] = obj1[i++];

    while (j <= high)
        temp[k++] = obj1[j++];

    for (int i = low; i <= high; i++)
        obj1[i] = temp[i];
}

void userinfo::quick(class userinfo obj1[],int p,int r)
{
    int q;
    if(p<r)
    {
        q=partition(obj1,p,r);
        quick(obj1,p,q-1);
        quick(obj1,q+1,r);
        // passes++;
    }
    // cout<<"passes: "<<endl;
}

int userinfo::partition(class userinfo obj1[],int p,int r)
{
    // int passes=0;
    string x=obj1[r].username;
    // userinfo x=obj1[r];
    int i=p-1;
    for(int j=p;j<=r-1;j++)
    {
        comparisons++;
        if(obj1[j].username>x)
        {
            i++;
            class userinfo temp=obj1[i];
            obj1[i]=obj1[j];
            obj1[j]=temp;
        }
    }
    class userinfo temp2=obj1[i+1];
    obj1[i+1]=obj1[r];
    obj1[r]=temp2;
    return i+1;
}

int bin_rec(class userinfo obj1[],int low,int high,string key)
{
    int mid;
    if(low<=high)
    {
        mid=(low +high)/2;
        if(obj1[mid].username==key)
        {
            return mid;
        }
        else if(key<obj1[mid].username)
        {
            return bin_rec(obj1,low,mid-1,key);
        }
        else
        {
        return bin_rec(obj1,mid+1,high,key);
        }
    }
    return -1;
}
int main()
{
    int n,cho,f;
    string key;
    cout<<"Enter the number of users\n";
    cin>>n;
    userinfo obj1[n],obj;

    for(int i=0;i<n;i++)
    {
        obj1[i].accept();
    }

    // for(int i=0;i<n;i++)
    // {
    //     obj1[i].display();
    //     cout<<"\n";
    // }
    cout<<"Enter choice\n1.linear search\n2.binary search\n3.binary search_recursive\n4.merge sort\n5.quick sort\n6.exit\n";
    cin>>cho;
    switch(cho)
    {
        // cout<<"\n";
        case 1:
        cout<<"Enter the user's name you want to find\n";
        cin>>key;
        obj.linear_search(obj1,n,key);
        break;


        case 2:
        cout<<"Enter the user's name you want to find\n";
        cin>>key;
        obj.bub_sort(obj1,n);
        obj.binary_search(obj1,0,n-1,key);
        break;

        case 3:
        cout<<"Enter the user's name you want to find\n";
        cin>>key;
        obj.bub_sort(obj1,n);
        f=bin_rec(obj1,0,n-1,key);
        cout<<"user is found at location: "<<f+1<<endl;
        break;

        case 4:
        obj.merge_sort(obj1,obj,0,n-1);
        cout<<"passes= "<<userinfo::pass<<endl;
        cout<<"no. of comparisons= "<<userinfo::comparisons<<endl;
        for(int i=0;i<n;i++)
        {
            obj1[i].display();
            cout<<"\n";
        }
        break;
        

        case 5:
        // userinfo::comparisons = 0;
        obj.quick(obj1,0,n-1);
        cout<<"Comparisons: "<<userinfo::comparisons<<endl;
        cout<<endl;
        for(int i=0;i<n;i++)
        {
            obj1[i].display();
            cout<<"\n";
        }
        break;
        // break;

        case 6:
        cout<<"exiting...";
        break;


        default:
        cout<<"Invalid choice";
        
    }
    return 0;
}
