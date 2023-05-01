const int ALPH = 26;
struct TrieNode {
    int go[ALPH];
    int child[ALPH];
    int suffixLink = -1;
    int exitLink = 0;
    int freq = 0;
    int patternIndex = -1;
    int patternCount = 0;
    vector<int> occur;
    TrieNode() {
        memset(child,-1,sizeof child);
        memset(go,-1,sizeof go);
    }
};
struct AhoCorasick {
    vector<TrieNode> trie;
    AhoCorasick() {
        trie.push_back(TrieNode());
    }
    int addString(string &s,int idx = -1) {
        int cur = 0;
        for(int i = 0 ; i < s.size() ; i++) {
            int c = getId(s[i]);
            if(trie[cur].child[c] == -1) {
                trie[cur].child[c] = trie.size();
                trie.push_back(TrieNode());
            }
            cur = trie[cur].child[c];
        }
        trie[cur].patternCount++;
        trie[cur].occur.push_back(idx);
        trie[cur].patternIndex = idx;
        return cur;
    }
    void build() {
        queue<int> q;
        for(int c = 0 ; c < ALPH ; c++) {
            int child = trie[0].child[c];
            if(child != -1) {
                trie[0].go[c] = child;
                trie[child].suffixLink = 0;
                q.push(child);
            }else {
                trie[0].go[c] = 0;
            }
        }
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            int link = trie[node].suffixLink;
            for(int c = 0 ; c < ALPH ; c++) {
                int child = trie[node].child[c];
                if(child != -1) {
                    trie[node].go[c] = child;
                    int childLink = trie[link].go[c];
                    trie[child].suffixLink = childLink;
                    if(trie[childLink].patternIndex != -1) {
                        trie[child].exitLink = childLink;
                    }else {
                        trie[child].exitLink = trie[childLink].exitLink;
                    }
                    trie[child].patternCount += trie[trie[child].suffixLink].patternCount;
                    q.push(child);
                }else {
                    trie[node].go[c] = trie[link].go[c];
                }
            }
        }
    }
    vector<int> getPattensOccurrences(string &s) {
        vector<int> ret;
        int cur = 0;
        for(auto it:s) {
            cur = trie[cur].go[getId(it)];
            int z = cur;
            while(z != 0) {
                for(auto it:trie[z].occur) {
                    ret.pb(it);
                }
                z = trie[z].exitLink;
            }
        }
        return ret;
    }
    int getId(char c) {
        return c-'a';
    }
} aho;
