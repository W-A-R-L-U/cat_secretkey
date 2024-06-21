#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll baseval(int base,string val)
{
    long long ans=0;
    long long b=1;
    int n=val.length();
    for(int i=n-1;i>=0;i--){
        if('0'<=val[i] && val[i]<='9'){
            // cout<<"con: "<<val[i]<<" "<<(val[i]-'0')<<" ";
            ans+=(val[i]-'0')*b;
        }else{
            ans+=((val[i]-'A')+10)*b;
        }
        b*=base;
    }
    return ans;
}

class point{
    public: 
    long long x,y;
    point(ll x1,ll y1):x(x1),y(y1){};
};

void generate(vector<point>& vec,vector<point>& tmp,vector<vector<point>>& points,vector<bool>& vis,int k){
    if(tmp.size()==k){
        points.push_back(tmp);
        return;
    }
    for(int i=0;i<vec.size();i++){
        if(!vis[i]){
            vis[i]=true;
            tmp.push_back(vec[i]);
            generate(vec,tmp,points,vis,k);
            tmp.pop_back();
            vis[i]=false;
        }
    }
}

double findprod(vector<ll>& vecx,vector<ll>& vecy,int k,int in)
{
    ll prod=vecy[in];
    if(k%2==0){
        prod*=-1;
    }
    for(int i=0;i<k;i++){
        if(i!=in){
            prod*=vecx[i];
        }
    }


    ll div=1;
    for(int i=0;i<k;i++){
        if(i!=in){
            div*=vecx[in]-vecx[i];
        }
    }

    return (prod)/div;
}

long long cnst(vector<point>& vec,int k)
{
    vector<ll> vecx,vecy;
    for(int i=0;i<k;i++){
        vecx.push_back(vec[i].x);
        vecy.push_back(vec[i].y);
    }


    long long ans=0;
    for(int i=0;i<k;i++){
        ans+=findprod(vecx,vecy,k,i);
    }

    return ans;

}

int main()
{
    ifstream inputfile("case2.txt");

    stringstream ss;
    string line;
    while(getline(inputfile,line)){
        ss<<line;
        ss<<" ";
    }
    inputfile.close();
    // cout<<ss.str();
    int n,k;
    ss>>n>>k;
    vector<point> vec;
    for(int i=0;i<n;i++){
        int x,base;
        string y;
        ss>>x>>base;
        ss>>y;
        // cout<<x<<" "<<base<<" "<<y<<"\n";
        vec.push_back(point(x,baseval(base,y)));
    }
    // for(auto p:vec){
    //     cout<<p.x<<" "<<p.y<<"\n";
    // }

    vector<vector<point>> points;
    vector<point> tmp;
    vector<bool> vis(n,false);
    generate(vec,tmp,points,vis,k);

    // for(int i=0;i<points.size();i++){
    //     for(int j=0;j<k;j++){
    //         cout<<points[i][j].x<<" "<<points[i][j].y<<"\n";
    //     }
    //     cout<<"\n";
    // }


    unordered_map<long long,int> mp;
    for(int i=0;i<points.size();i++){
        ll c=cnst(points[i],k);
        mp[c]++;
    }

    int mx=0;
    long long ans=0;
    for(auto p:mp){
        if(p.second>mx){
            mx=p.second;
            ans=p.first;
        }
        // cout<<fixed<<p.first<<" "<<p.second<<"\n";
    }

    ofstream outputfile;
    outputfile.open("output.txt");
    outputfile<<"The secret key is: "<<ans<<"\n";
    outputfile.close();
    return 0;
}