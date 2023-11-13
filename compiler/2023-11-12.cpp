#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define re register
#define rep(i, s, k) for (int i = s; i <= k; i++)
#define per(i, s, k) for (int i = s; i >= k; i--)
#define INF 2147483647
inline ll gcd(ll x, ll y)
{
    return y ? gcd(y, x % y) : x;
}

struct Item
{
    bool isSignal;
    int sta;
    string sig;
};

struct Ins
{
    bool isAcc;
    bool isS;
    bool isR;
    int nxtState;
};

struct Signal
{
    string val;
    string sig;
};

class LRAnalyse
{
private:
    stack<Item> st;
    stack<string> chs;
    map<int, map<string, Ins>> LRtable;

    vector<string> Geners;

    string w;
    int point = 0;

    Signal getNxt()
    {
        int len = w.length();

        string res;

        while (w[point] == ' ')
        {
            point++;
        }

        if (w[point] != '\\' && w[point] != '{' && w[point] != '}' && point < len - 1)
        {
            while (w[point] != '\\' && w[point] != '{' && w[point] != '}' && point < len - 1)
            {
                while (w[point] == ' ')
                {
                    point++;
                }

                if (w[point] != '\\' && w[point] != '{' && w[point] != '}' && point < len - 1)
                {
                    res += w[point];
                    point++;
                }
                // cout << res << endl;
            }
            cout << res << endl;
            return {res, "id"};
        }
        else if (w[point] == '\\')
        {
            point++;
            string s;
            while (w[point] >= 'a' && w[point] <= 'z')
            {
                s += w[point];
                point++;
            }
            if (s == "frac")
            {
                return {"", "f"};
            }
            else
                return {"", "\\"};
        }
        else if (point == len - 1)
        {
            point += 2;
            return {"", "#"};
        }
        else if (w[point] == '{' || w[point] == '}')
        {
            res += w[point];
            point++;
            return {res, res};
        }
        else
        {
            cout << "Get Next Error!" << endl;
            return {"", "#"};
        }
    }

    string getLeft(int idx)
    {
        if (idx >= 2 && idx <= 4)
        {
            return "E";
        }
        else if (idx == 5)
        {
            return "S";
        }
        else
            return "#";
    }

    int getLen(int idx)
    {
        if (idx == 2 || idx == 5)
        {
            return 3;
        }
        else if (idx == 3)
        {
            return 2;
        }
        else if (idx == 4)
        {
            return 0;
        }
        else
            return INF;
    }

    // void calculate(int idx)
    // {
    //     if (idx == 2)
    //     {
    //         int x = cal.top();
    //         cal.pop();
    //         int y = cal.top();
    //         cal.pop();
    //         cal.push(x + y);
    //         // cout << x + y << endl;
    //     }
    //     else if (idx == 3)
    //     {
    //         int x = cal.top();
    //         cal.pop();
    //         int y = cal.top();
    //         cal.pop();
    //         cal.push(y - x);
    //     }
    //     else if (idx == 5)
    //     {
    //         int x = cal.top();
    //         cal.pop();
    //         int y = cal.top();
    //         cal.pop();
    //         // cout << x * y << endl;
    //         cal.push(x * y);
    //     }
    //     else if (idx == 6)
    //     {
    //         int x = cal.top();
    //         cal.pop();
    //         int y = cal.top();
    //         cal.pop();
    //         cal.push(y / x);
    //     }
    //     else if (idx < 1 || idx > 9)
    //     {
    //         cout << "Calculate Error!" << endl;
    //     }
    // }

    void decode(int idx)
    {
        if (idx == 0)
        {
            string x = chs.top();
            chs.pop();
            chs.push("<math xmlns=\"http://www.w3.org/1998/Math/MathML\" display=\"block\"> " + x + "</math>");
        }
        else if (idx == 2)
        {
            string y = chs.top();
            chs.pop();
            string x = chs.top();
            chs.pop();
            chs.push("<mfrac>    " + x + "  " + y + "  </mfrac>  ");
        }
        else if (idx == 4)
        {
            chs.push("");
        }
        else if (idx == 3)
        {
            string y = chs.top();
            chs.pop();
            string x = chs.top();
            chs.pop();
            // cout << x << y << endl;
            if (y == "")
                chs.push("<mi>" + x + "</mi>");
            else
                chs.push("<mi>  <mi>" + x + "</mi>" + y + "  </mi>");
        }
    }

    void init()
    {
        Geners.push_back("0");
        Geners.push_back("E'->E");
        Geners.push_back("E->fSS");
        Geners.push_back("E->idE");
        Geners.push_back("E-> ");
        Geners.push_back("S->{E}");

        LRtable[0]["id"] = {false, true, false, 3};
        LRtable[0]["f"] = {false, true, false, 2};
        LRtable[0]["E"] = {false, false, false, 1};
        LRtable[1]["#"] = {true, false, false, INF};
        LRtable[2]["{"] = {false, true, false, 5};
        LRtable[2]["S"] = {false, false, false, 4};
        LRtable[3]["id"] = {false, true, false, 3};
        LRtable[3]["f"] = {false, true, false, 2};
        LRtable[3]["}"] = {false, false, true, 4};
        LRtable[3]["#"] = {false, false, true, 4};
        LRtable[3]["E"] = {false, false, false, 6};
        LRtable[4]["{"] = {false, true, false, 5};
        LRtable[4]["S"] = {false, false, false, 7};
        LRtable[5]["id"] = {false, true, false, 3};
        LRtable[5]["f"] = {false, true, false, 2};
        LRtable[5]["}"] = {false, false, true, 4};
        LRtable[5]["#"] = {false, false, true, 4};
        LRtable[5]["E"] = {false, false, false, 8};
        LRtable[6]["}"] = {false, false, true, 3};
        LRtable[6]["#"] = {false, false, true, 3};
        LRtable[7]["}"] = {false, false, true, 2};
        LRtable[7]["#"] = {false, false, true, 2};
        LRtable[8]["}"] = {false, true, false, 9};
        LRtable[9]["{"] = {false, false, true, 5};
        LRtable[9]["}"] = {false, false, true, 5};
        LRtable[9]["#"] = {false, false, true, 5};
    }

    void analyse()
    {
        st.push({false, 0, "#"});
        Signal lookfor = getNxt();

        string ans;

        while (1)
        {
            Item s = st.top();

            if (s.isSignal)
            {
                cout << "Error for stack!" << endl;
                break;
            }

            if (LRtable.count(s.sta) > 0)
            {
                // cout << lookfor.sig << endl;
                if (LRtable[s.sta].count(lookfor.sig) > 0)
                {
                    Ins res = LRtable[s.sta][lookfor.sig];
                    if (res.isAcc)
                    {
                        cout << "接受" << endl;
                        decode(0);
                        cout << chs.top() << endl;
                        break;
                    }
                    else if (res.isS)
                    {
                        cout << "移进" << endl;
                        st.push({true, INF, lookfor.sig});
                        st.push({false, res.nxtState, "#"});
                        if (lookfor.sig == "id")
                        {
                            chs.push(lookfor.val);
                        }
                        lookfor = getNxt();
                    }
                    else if (res.isR)
                    {
                        cout << "按 ";
                        cout << Geners[res.nxtState];
                        cout << "归约" << endl;

                        int loop = getLen(res.nxtState);
                        // cout << loop << endl;
                        while (loop)
                        {
                            st.pop();
                            st.pop();
                            loop--;
                            // cout << loop;
                        }

                        Item check = st.top();
                        // cout << check.sta << endl;
                        // cout << st.size() << endl;

                        if (check.isSignal)
                        {
                            cout << "归约error1" << endl;
                            break;
                        }

                        if (LRtable.count(check.sta) > 0)
                        {
                            string ls = getLeft(res.nxtState);
                            // cout << ls << endl;
                            if (LRtable[check.sta].count(ls) > 0)
                            {
                                // cout << 1 << endl;
                                Ins nwt = LRtable[check.sta][ls];
                                st.push({true, INF, ls});
                                st.push({false, nwt.nxtState, "#"});
                                decode(res.nxtState);
                            }
                            else
                            {
                                cout << "归约error3" << endl;
                                break;
                            }
                        }
                        else
                        {
                            cout << "归约error2" << endl;
                            break;
                        }
                    }
                    else
                    {
                        cout << "Choose Error!" << endl;
                        break;
                    }
                }
                else
                {
                    cout << "输入有误！请重新输入";
                    break;
                }
            }
            else
            {
                cout << "Error for index!" << endl;
                break;
            }
        }
    }

public:
    LRAnalyse(string s) : w(s)
    {
        init();
        analyse();
    }
};

int main()
{
    string s;
    getline(cin, s);
    LRAnalyse lra(s + "#");
    return 0;
}