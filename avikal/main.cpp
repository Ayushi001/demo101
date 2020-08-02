#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif
// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
#include<iostream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#define ll long long int
#define mod 1000000007
using namespace std;
struct node
{
    ll sum=0 ;ll lazy=0; ll freq=0 ;
};
 
 
 
ll max(ll a,ll b)
{
    if( a>b ) return a;return b ;
}
 
 
 
ll min( ll a,ll b )
{
    if( a<b ) return a; return b ;
}
 
 
void updatetree( node tree[],ll s,ll e,ll pos,ll qs,ll qe,ll x )
{
    if( qs> e || qe<s  ) return ;
    if( s==e )
    {
        tree[pos].sum += tree[pos].lazy ;
        tree[pos].lazy=0 ;
        tree[pos].sum += x;
        return;
    }
    if( qs<=s && qe>=e )
    {
        tree[pos].lazy += x ;
        tree[pos].sum += ( tree[pos].freq*tree[pos].lazy );
        tree[2*pos+1].lazy += tree[pos].lazy;
        tree[2*pos+2].lazy += tree[pos].lazy;
        tree[pos].lazy=0 ;
        return ;
    }
    ll mid=(s+e)/2  ;
    
    if( tree[pos].lazy != 0 )
    {
        tree[2*pos+1].lazy += tree[pos].lazy;
        tree[2*pos+2].lazy += tree[pos].lazy;
        tree[pos].lazy=0 ;
    }
    
    updatetree( tree,s,mid,2*pos+1,qs,qe,x );
    updatetree( tree,mid+1,e,2*pos+2,qs,qe,x ) ;
    
    tree[pos].sum= ( tree[2*pos+1].freq*tree[2*pos+1].lazy ) +            ( tree[2*pos+2].freq*tree[2*pos+2].lazy ) + tree[2*pos+1].sum + tree[2*pos+2].sum ;
    
    return ;
}
 
ll getans( node tree[],ll s,ll e,ll pos,ll qs,ll qe )
{
    if( s>e ) return 0 ;
    if( qs>e || qe<s ) return 0 ;
    if( s==e )
    {
        tree[pos].sum+=tree[pos].lazy ;
        tree[pos].lazy=0 ;
        return tree[pos].sum ;
    }
    if( qs<=s && qe>=e )
    {
        
        tree[2*pos+1].lazy += tree[pos].lazy;
        tree[2*pos+2].lazy += tree[pos].lazy;
        
        tree[pos].sum= ( tree[2*pos+1].freq*tree[2*pos+1].lazy ) +            ( tree[2*pos+2].freq*tree[2*pos+2].lazy ) + tree[2*pos+1].sum + tree[2*pos+2].sum ;
        
        tree[pos].lazy=0 ;
        return tree[pos].sum ;
       
    }
    if( tree[pos].lazy !=0 )
    {
        tree[2*pos+1].lazy += tree[pos].lazy;
        tree[2*pos+2].lazy += tree[pos].lazy;
        tree[pos].lazy=0 ;
    }
    ll mid=(s+e)/2 ;
   
    ll r,l;
    
    
    
    l=getans( tree,s,mid,2*pos+1,qs,qe );
    r=getans( tree,mid+1,e,2*pos+2,qs,qe );
    
      tree[pos].sum= ( tree[2*pos+1].freq*tree[2*pos+1].lazy ) +            ( tree[2*pos+2].freq*tree[2*pos+2].lazy ) + tree[2*pos+1].sum + tree[2*pos+2].sum ;
    
    return l+r;
    
    
}
void buildtree( node tree[],ll s,ll e,ll pos )
{
    if( s>e ) return;
    if( s==e )
    {
        tree[pos].freq=1;
        tree[pos].lazy=0;
        tree[pos].sum=0;
        return ;
    }
    ll mid=(s+e)/2 ;
    buildtree( tree,s,mid,2*pos+1 );
    buildtree(tree, mid+1, e, 2*pos+2 ) ;
    tree[pos].freq=tree[2*pos+1].freq+tree[2*pos+2].freq ;
    tree[pos].sum=0 ;
    tree[pos].lazy=0 ;
    
}
int main()
 {
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
   
    ll n,q ;
     
     cin>>n>>q ;
     ll arr[n];
     for( ll i=0; i<n; i++ ) arr[i]=1  ;
     ll ht= ceil( log2(n) ) ;
     ll maxx= 2* (ll)pow(2,ht) -1 ;
     
     node tree[maxx] ;
     buildtree( tree,0,n-1,0 ) ;
     
     
     
     while(q--)
     {
         
         int type ;
         cin>>type;
        if( type==1 )
         {
             ll x,y,z;
             cin>>x>>y>>z ; y--;
             if( z==1 )  { goto sos; }
             updatetree(tree,0,n-1,0,x,y,z);
         sos:{}
         }
         else
         {
             ll x,y ;
             cin>>x>>y ; y--;
             ll ans;
             ans=getans(tree,0,n-1,0,x,y) ;
             
             cout<<ans<<"\n" ;
         }
         
     }
     
      
     
     
    return 0;
}
