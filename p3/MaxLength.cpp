#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct maxlenftn {
    maxlenftn() { maxlen = 0; }
    void operator()(string s) {
        maxlen = max(maxlen, s.size());
    }
    string::size_type maxlen;
};

int main() {
    vector<string> names{"Smith", "Jones", "Johnson", "Grant"};
    maxlenftn maxf;

    // pass-by value, need to update maxf (see answer.txt)
    maxf = for_each(names.begin(), names.end(), maxf);
    cout << maxf.maxlen << endl;
    return 0;
}