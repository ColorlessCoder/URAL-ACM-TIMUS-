//#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#define vi vector<int>
#define vll vector<LL>
#define pii pair<int,int>
#define pli pair<LL,int>
#define pll pair<LL,LL>
#define fr first
#define sc second
#define MAX 50010
#define LL   long long int
#define ll   long long int
//#define LLL long long int
#define inf 1ll<<62
#define INF 1000000
#define mod 1000000007
#define PI acos(-1)
#define NN 50003
#define mMax 100010
#define nMax 200
#define MAXN MAXLEN
#define SZ(a) a.size()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define rep1(i,b) for(int i=1;i<=b;i++)
#define rep2(i,b) for(int i=0;i<b;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define all(A) A.begin(),A.end()
#define isf(a) scanf("%d",&a);
#define Lsf(a) scanf("%I64d",&a);
#define lsf(a) scanf("%lld",&a);
#define csf(a) scanf("%c",&a);
using namespace std;
typedef pair<int, int> ii;
const int MAXLEN = 300000+ 5;
#define Min(a,b) ((a<b)?a:b)
    char s[MAXLEN];int next[26][MAXLEN];
    int len[MAXLEN];
    int link[MAXLEN];
    int semi_link[MAXLEN];
    int dp1[MAXLEN];//even
    int dp2[MAXLEN];//odd
    int ans1[MAXLEN];//even
    int ans2[MAXLEN];//odd
    int diff[MAXLEN];
struct PalindromicTree {
    
    /**
        every node represents a palindrome
        len - the length of palindrome represented by current node
        next - transition from this node to other nodes by different characters
        link - node number of longest suffix palindrome of current node
    **/
    unsigned cnt[MAXLEN];
    //state tree[MAXLEN];

    int sz;
    int last;

    ///For finding total number of palindromes
    ///For finding total number of palindromes

    /**
        node 1 is root with len = -1
        node 2 is root with len = 0
    **/
    void init(int i)
    {
    //  tree[i].next.clear();
      cnt[i]=0;
    // memset(next[i],0,sizeof(next[i]));
    }
    PalindromicTree(int n) {
        //cnt2 = vector <long long> (n+10, 0);
        ///For finding total number of palindromes
        sz = last = 2;
        diff[2]=0;
        diff[1]=0;
    }
    void buildTree() {
        sz=last=2; 
        len[1] = -1; link[1] =semi_link[1] = 1;
        init(1);
        len[2] = 0; link[2] = 1;
        semi_link[2] =2;
        init(2);
        ans1[0]=0;ans2[0]=MAXLEN;
        dp1[2]=0;dp2[2]=MAXLEN;
        int n = strlen(s);
        for (int i = 0; i < n; i++) {
            Insert(i, s[i]-'a');
        }
        return;
    }
    /**
        returns true is a new palindromic substring is found adding new character c and false otherwise
    **/
    void calculate(int i,int pos)
    {
      pos++;
      int cur=i;
      ans1[pos]=MAXLEN;
      ans2[pos]=MAXLEN;
      while(len[cur]>0)
      {
        dp1[cur]=ans1[pos- len[cur]];
        dp2[cur]=ans2[pos- len[cur]];
        if(diff[cur]==diff[link[cur]]){
          dp1[cur]=Min(dp1[cur],dp1[link[cur]]);
          dp1[cur]=Min(dp1[cur],ans1[pos-diff[cur]-len[semi_link[cur]]]);
          dp2[cur]=Min(dp2[cur],dp2[link[cur]]);
          dp2[cur]=Min(dp2[cur],ans2[pos-diff[cur]-len[semi_link[cur]]]);
        }
        int temp1=dp1[cur]+1;
        int temp2=dp2[cur]+1;
        ans1[pos]= Min(ans1[pos],temp2);
        ans2[pos]= Min(ans2[pos],temp1);
        cur=semi_link[cur];
      }
      i=pos;
      printf("%d %d\n",(ans2[i]==MAXN)?-1:ans2[i],(ans1[i]==MAXN)?-2:ans1[i]);
      
    }
    bool Insert(int pos, char c) {
        int cur = last, curlen = 0;

        while (true) {
            curlen = len[cur];
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
                break;
            cur = link[cur];
        }

       // if (next[cur][c]!=-1) {
        if (next[c][cur]) {
            last = next[c][cur];
            cnt[last]++;
            calculate(last,pos);
            // Common , !Unique
            return false;
        }
        sz++;
        last = sz;
        len[sz] = len[cur] + 2;
        init(sz);
        next[c][cur] = sz;

        if (len[sz] == 1) {
            diff[sz]=1;
            link[sz] = 2;
            cnt[sz] = 1;
            semi_link[sz]=2;
            calculate(sz,pos);
            return true;
        }

        while (true) {
            cur = link[cur];
            curlen = len[cur];
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                link[sz] = next[c][cur];
                break;
            }
        }
        int t=link[sz];
        diff[sz]=len[sz]-len[t];
        if(diff[sz]==diff[t])
        {
          semi_link[sz]=semi_link[t]; // that means we link a palindrome which is 
                                           // of a structure like xxx....xxy
                                           // where x is a string(x needs not to be a single letter)
                                           // and xy is a palindrome
                                           // and y is a string (and I think palindrome too) , empty allowed
                                           // abbaabbaabba   , y="",x="abba"
                                           // baabaab        ,y='b',x="baa"
        }
        else semi_link[sz]=t; // (I think) Link's len is <= half(sz node's len)
        calculate(sz,pos);
        cnt[sz] = 1;
        return true;
      } 
    
    /**
        call this function before working with different palindromic substring frequency
        cnt[i] - total frequency of palindromic node i
        palindromes - total number of palindromes(Unique + Non-unique)
        total number of unique palindromes is just the number of nodes in the tree except the 2 roots
    **/
   void palindromeCount() {
        for (int i = sz; i >= 3; i--) {
            cnt[link[i]] += cnt[i];
        }
        cnt[1] = cnt[2] = 0;
        return ;
    }   
};
int x,y;
//char str[MAXLEN]="aaaa";
PalindromicTree pal(MAXLEN);

int main()
{
  memset(next,0,sizeof(next));
    scanf("%s",s);
    //memset(ans,0,sizeof(ans));
    int n=strlen(s);
    pal.buildTree();
  return 0;
}
