struct monoStack {
public:
    stack<pair<int,int>> st;
    monoStack() {
        st.emplace(mp(INT_MIN,INT_MIN));
    }
    void push(int x) {
        st.emplace(mp(x , ::max(x , st.top().second)));
    }
    int top() {
        return st.top().first;
    }
    void pop() {
        st.pop();
    }
    int max() {
        return st.top().second;
    }
    int size() {
        return st.size() - 1;
    }
    bool empty() {
        return st.size() == 1;
    }
};
struct monoQueue {
    monoStack add,rem;
    void push(int x) {
        add.push(x);
    }
    int top() {
        if(rem.empty()) move();
        return rem.top();
    }
    void pop() {
        if(rem.empty()) move();
        rem.pop();
    }
    int max() {
        return ::max(rem.max(),add.max());
    }
    int size() {
        return add.size()+rem.size();
    }
    bool empty() {
        return !size();
    }
    void move() {
        while(add.size()) {
            rem.push(add.top());
            add.pop();
        }
    }
};
