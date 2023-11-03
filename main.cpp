#include <iostream>
#include <string>
#include <map>
using namespace std;
struct state {
        int len, link, firstpos;
        map<char,int> next;
    };
    const int MAXLEN = 100000;
    state st[MAXLEN*2];
    int sz, last;

void sa_init() {
        sz = last = 0;
        st[0].len = 0;
        st[0].link = -1;
        ++sz;
        /*
        // этот код нужен, только если автомат строится много раз для разных строк:
        for (int i=0; i<MAXLEN*2; ++i)
            st[i].next.clear();
        */
    }
void sa_extend (char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        st[cur].firstpos = st[cur].len - 1;
        int p;
        for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
            st[p].next[c] = cur;
        if (p == -1)
            st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
                st[cur].link = q;
            else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].firstpos = st[q].firstpos;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
                    st[p].next[c] = clone;
                st[q].link = st[cur].link = clone;

            }
        }
        last = cur;
    }
int main()
{
    string s, t;
    int cur;
    getline(cin, s);
    getline(cin, t);
    sa_init();
    int n = s.length();
    for(int i = 0; i < n; ++i){
        sa_extend(s[i]);
    }
    n = t.length();
    for(int i = 0; i < n; ++i){
        if (st[cur].next[t[i]] != 0){
            cur = st[cur].next[t[i]];
        }
    }
    cout << st[cur].firstpos - t.length() + 1;
    return 0;
}
