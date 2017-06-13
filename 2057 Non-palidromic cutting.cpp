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
const int MAXLEN = 200000+ 50;
#define Min(a,b) ((a<b)?a:b)

//courtesy: Implementaion of Segtree -> Competitive Programming 3
// Implementation of Palindromic Tree -> I modify some part of it and add extra features
//  but basic structure was made by Sakibul Mowla(SUST) 

    char s[MAXLEN];int next[26][MAXLEN];
    int len[MAXLEN];
    int link[MAXLEN];
    int semi_link[MAXLEN];
    int dp1[MAXLEN];//even
    int dp2[MAXLEN];//odd
    int ans1[MAXLEN];//even
    int ans2[MAXLEN];//odd
    int diff[MAXLEN];

class SegmentTree {         // the segment tree is stored like a heap array
private: vi st, A;            // recall that vi is: typedef vector<int> vi;
  int n;
  int left (int p) { return p << 1; }     // same as binary heap operations
  int right(int p) { return (p << 1) + 1; }

  void build(int p, int L, int R) {                           // O(n log n)
    if (L == R)                            // as L == R, either one is fine
      st[p] = L;                                         // store the index
    else {                                // recursively compute the values
      build(left(p) , L              , (L + R) / 2);
      build(right(p), (L + R) / 2 + 1, R          );
      int p1 = st[left(p)], p2 = st[right(p)];
      st[p] = (A[p1] <= A[p2]) ? p1 : p2;
  } }

  int rmq(int p, int L, int R, int i, int j) {                  // O(log n)
    if (i >  R || j <  L) return -1; // current segment outside query range
    if (L >= i && R <= j) return st[p];               // inside query range

     // compute the min position in the left and right part of the interval
    int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
    int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

    if (p1 == -1) return p2;   // if we try to access segment outside query
    if (p2 == -1) return p1;                               // same as above
    return (A[p1] <= A[p2]) ? p1 : p2; }          // as as in build routine

  int update_point(int p, int L, int R, int idx, int new_value) {
    // this update code is still preliminary, i == j
    // must be able to update range in the future!
    int i = idx, j = idx;

    // if the current interval does not intersect 
    // the update interval, return this st node value!
    if (i > R || j < L)
      return st[p];

    // if the current interval is included in the update range,
    // update that st[node]
    if (L == i && R == j) {
      A[i] = new_value; // update the underlying array
      return st[p] = L; // this index
    }

    // compute the minimum pition in the 
    // left and right part of the interval
    int p1, p2;
    p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
    p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

    // return the pition where the overall minimum is
    return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
  }

public:
  SegmentTree(int a) {
    n = a;              // copy content for local usage
    A.assign(n+1,MAXLEN);
    st.assign(4 * n, 0);                                 // recursive build
  }

  int rmq(int i, int j) {
    if(i>j) return MAXLEN; 
   return A[rmq(1, 0, n - 1, i, j)]; 
   }   // overloading

  int update_point(int idx, int new_value) {
    return update_point(1, 0, n - 1, idx, new_value); }
};
  

class SegmentTree2 {         // the segment tree is stored like a heap array
private: vi st, A;            // recall that vi is: typedef vector<int> vi;
  int n;
  int left (int p) { return p << 1; }     // same as binary heap operations
  int right(int p) { return (p << 1) + 1; }

  void build(int p, int L, int R) {                           // O(n log n)
    if (L == R)                            // as L == R, either one is fine
      st[p] = L;                                         // store the index
    else {                                // recursively compute the values
      build(left(p) , L              , (L + R) / 2);
      build(right(p), (L + R) / 2 + 1, R          );
      int p1 = st[left(p)], p2 = st[right(p)];
      st[p] = (A[p1] <= A[p2]) ? p1 : p2;
  } }

  int rmq(int p, int L, int R, int i, int j) {                  // O(log n)
    if (i >  R || j <  L) return -1; // current segment outside query range
    if (L >= i && R <= j) return st[p];               // inside query range

     // compute the min position in the left and right part of the interval
    int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
    int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

    if (p1 == -1) return p2;   // if we try to access segment outside query
    if (p2 == -1) return p1;                               // same as above
    return (A[p1] >= A[p2]) ? p1 : p2; }          // as as in build routine

  int update_point(int p, int L, int R, int idx, int new_value) {
    // this update code is still preliminary, i == j
    // must be able to update range in the future!
    int i = idx, j = idx;

    // if the current interval does not intersect 
    // the update interval, return this st node value!
    if (i > R || j < L)
      return st[p];

    // if the current interval is included in the update range,
    // update that st[node]
    if (L == i && R == j) {
      A[i] = new_value; // update the underlying array
      return st[p] = L; // this index
    }

    // compute the minimum pition in the 
    // left and right part of the interval
    int p1, p2;
    p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
    p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

    // return the pition where the overall minimum is
    return st[p] = (A[p1] >= A[p2]) ? p1 : p2;
  }

public:
  SegmentTree2(int a) {
    n = a;              // copy content for local usage
    A.assign(n+1,-MAXLEN);
    st.assign(4 * n, 0);                                 // recursive build
  }

  int rmq(int i, int j) {
    if(i>j) return -MAXLEN; 
   return A[rmq(1, 0, n - 1, i, j)]; 
   }   // overloading

  int update_point(int idx, int new_value) {
    return update_point(1, 0, n - 1, idx, new_value); }
};
  
SegmentTree Minst(MAXLEN);
SegmentTree2 Maxst(MAXLEN);
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
      ans2[pos]=-MAXLEN;
      int left=0,right;
      while(len[cur]>0)
      {
        right=pos-len[cur]-1;
        ans1[pos]=min(ans1[pos], Minst.rmq(left,right)+1);
        ans2[pos]=max(ans2[pos], Maxst.rmq(left,right)+1);
        left=pos-cur[len]+1;
        if(diff[cur]==diff[link[cur]]){
          dp1[cur]=Minst.rmq(left,left+diff[cur]-2)+1;
          dp2[cur]=Maxst.rmq(left,left+diff[cur]-2)+1;
          if(len[link[cur]] != diff[cur]+len[semi_link[cur]])
          {
            dp1[cur]=min(dp1[cur],dp1[link[cur]]+1);
            dp2[cur]=max(dp2[cur],dp2[link[cur]]+1);
          }
          ans1[pos]=min(ans1[pos],dp1[cur]);
          ans2[pos]=max(ans2[pos],dp2[cur]);
          left=pos-len[semi_link[cur]]-diff[cur]+1;
        }
        cur=semi_link[cur];
      }
      Minst.update_point(pos,ans1[pos]);
      Maxst.update_point(pos,ans2[pos]);
      
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
                                     //details -> http://codeforces.com/blog/entry/52555
        }
        else semi_link[sz]=t; // Else (I think) Link's len is <= half(sz node's len)
        calculate(sz,pos);
        cnt[sz] = 1;
        return true;
      } 
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
  memset(next,0,sizeof(next));// is not necessary but that time I couldn't Trust acm timus :p (still not though)
  Minst.update_point(0,0);
  Maxst.update_point(0,0);
  scanf("%s",s);
  int n=strlen(s);
  pal.buildTree();
  if(ans1[n]>=MAXN)
    printf("-1\n");
  else printf("%d %d\n",ans1[n],ans2[n]);
  return 0;
}
