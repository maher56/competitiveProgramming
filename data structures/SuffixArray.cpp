struct SuffixArray {
SuffixArray(const string& s) : s(s), logn(0) {
    for (int n = (int)s.size(); n >= 2; n /= 2) {
        ++logn;
    }
    buildSuffixArray(s);
    buildLcp();
}
// tested
void buildSuffixArray(string t) {
    t += " ";
    sortedShifts = sortCyclicShifts(t);
    sortedShifts.erase(sortedShifts.begin());
}
// tested
void buildLcp() {
    const int n = s.size();
    rank.resize(n);
    for (int i = 0; i < n; i++) {
        rank[sortedShifts[i]] = i;
    }
    int k = 0;
    lcp.resize(n - 1);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sortedShifts[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
            k++;
        }
        lcp[rank[i]] = k;
        if (k) {
            k--;
        }
    }
}
// tested
vector<int> sortCyclicShifts(const string& t) {
    const int ALPHABET = 256;
    const int n = t.size();
    eClass.push_back(vector<int>(n));
    vector<int> position(n), frequency(max(n,ALPHABET));
    for (int i = 0; i < n; ++i) {
        ++frequency[t[i]];
    }
    for (int i = 1; i < ALPHABET; ++i) {
        frequency[i] += frequency[i - 1];
    }
    for (int i = 0; i < n; ++i) {
        position[--frequency[t[i]]] = i;
    }
    eClass[0][position[0]] = 0;
    int classesCount = 1;
    for (int i = 1; i < n; ++i) {
        if (t[position[i]] != t[position[i - 1]]) {
            ++classesCount;
        }
        eClass[0][position[i]] = classesCount - 1;
    }
    vector<int> newPosition(n);
    for (int k = 0; (1 << k) < n; ++k) {
        eClass.push_back(vector<int>(n));
        for (int i = 0; i < n; ++i) {
            newPosition[i] = position[i] - (1 << k);
            if (newPosition[i] < 0) {
                newPosition[i] += n;
            }
        }
        fill(frequency.begin(), frequency.begin() + classesCount, 0);
        for (int i = 0; i < n; ++i) {
            ++frequency[eClass[k][newPosition[i]]];
        }
        for (int i = 1; i < classesCount; ++i) {
            frequency[i] += frequency[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            position[--frequency[eClass[k][newPosition[i]
            ]]] = newPosition[i];
        }
        eClass[k + 1][position[0]] = 0;
        classesCount = 1;
        for (int i = 1; i < n; ++i) {
            pair<int, int> current = {eClass[k][position
            [i]], eClass[k][(position[i] + (1 << k)) % n]};
            pair<int, int> previous = {eClass[k][
            position[i - 1]], eClass[k][(position[i-1] + (1 << k)) % n]};
            if (current != previous) {
                ++classesCount;
            }
            eClass[k + 1][position[i]] = classesCount -1;}
    }
    return position;
}
// tested
int compareTwoSubstrings(int i, int j, int length, int k) {
    int n = s.size();
    pair<int,int> a = {eClass[k][i],eClass[k][(i+length-(1<<k))%n]};
    pair<int,int> b = {eClass[k][j],eClass[k][(j+length-(1<<k))%n]};
    if (a > b) {
        return 1;
    }
    if(a == b) {
        return 0;
    }
    return -1;
}
// tested
vector<int> getAllOccurrences(const string& t) {
    pair<int, int> range = getOccurrencesRangeInP(t);
    if (range.first == -1) {
        return vector<int>();
    }
    vector<int> occurrences;
    for (int i = range.first; i <= range.second; ++i) {
        occurrences.push_back(sortedShifts[i]);
    }
    return occurrences;
}
// tested
pair<int, int> getOccurrencesRangeInP(const string& t) {
    int L = getFirstOccurrence(t);
    if (L == -1) {
        return make_pair(-1, -1);
    }
    int R = getLastOccurrence(t);
    return make_pair(L, R);
}
// tested
int getFirstOccurrence(const string& t) {
    const int n = s.size();
    int low = 0;
    int high = n - 1;
    int result = -1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        string substring = s.substr(sortedShifts[mid], t.size());
        if (substring > t) {
            high = mid - 1;
        }else if (substring == t) {
            result = mid;
            high = mid - 1;
        }else {
            low = mid + 1;
        }
    }
    return result;
}
// tested
int getLastOccurrence(const string& t) {
    const int n = s.size();
    int low = 0;
    int high = n - 1;
    int result = -1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        string substring = s.substr(sortedShifts[mid], t.size());
        if (substring > t) {
            high = mid - 1;
        }else if (substring == t) {
            result = mid;
            low = mid + 1;
        } else {
            low = mid + 1;
        }
    }
    return result;
}
// tested
// return longest common prefix of two suffixess
int getLongestCommonPrefix(int i, int j) {
    int lcp = 0;
    for (int k = logn; k >= 0; --k) {
        if (eClass[k][i] == eClass[k][j]) {
            lcp += (1 << k);
            i += (1 << k);
            j += (1 << k);
        }
    }
    return lcp;
}
// tested
long long countDifferentSubstrings() {
    int n = s.size();
    return 1LL * n * (n + 1) / 2
    - accumulate(lcp.begin(), lcp.end(), 0LL);
}
void update(int &l,int &r,char x,int len) {
    if(l == -1) return;
    int al = l , ar = r ,mid, ans = -1;
    while(al <= ar) {
        mid = (al+ar)/2;
        if(s.size()-sortedShifts[mid] < len) {
            al = mid+1;
        }else if(s[sortedShifts[mid]+len-1] > x) {
            ar = mid-1;
        }else if(s[sortedShifts[mid]+len-1] < x) {
            al = mid+1;
        }else {
            ans = mid;
            ar = mid-1;
        }
    }
    if(ans == -1) {
        l = r = -1;
        return;
    }
    l = ans;
    al = l , ar = r, ans=-1;
    while(al <= ar) {
        mid = (al+ar)/2;
        if(s.size()-sortedShifts[mid] < len) {
            al = mid+1;
        }else if(s[sortedShifts[mid]+len-1] > x) {
            ar = mid-1;
        }else if(s[sortedShifts[mid]+len-1] < x) {
            al = mid+1;
        }else {
            ans = mid;
            al = mid+1;
        }
    }
    r = ans;
}
int logn;
string s;
vector<vector<int>> eClass;
vector<int> sortedShifts;
vector<int> lcp;
vector<int> rank;
};
