#include <bits/stdc++.h> 
using namespace std; 
 
struct State { 
    int id; 
    map<char, vector<int>> transitions; 
}; 
 
struct NFA { 
    int start; 
    vector<int> finals; 
    map<int, State> states; 
}; 
 
NFA basicNFA(char c) { 
    NFA nfa; 
    State s1 = {0, {}}; 
    State s2 = {1, {}};  
    s1.transitions[c].push_back(1); 
    nfa.start = 0; 
    nfa.finals.push_back(1); 
    nfa.states[0] = s1;  
    nfa.states[1] = s2; 
    return nfa; 
} 
 
NFA unionNFA(NFA a, NFA b) { 
    NFA nfa; 
    State start = {0, {}}; 
    start.transitions['e'].push_back(a.start + 1); 
    start.transitions['e'].push_back(b.start + a.states.size() + 1); 
     
    for (auto &st : a.states) { 
        nfa.states[st.first + 1] = st.second; 
    } 
     
    for (auto &st : b.states) {  
        nfa.states[st.first + a.states.size() + 1] = st.second; 
    } 
     
    nfa.start = 0; 
    nfa.finals.push_back(a.finals[0] + 1);  
    nfa.finals.push_back(b.finals[0] + a.states.size() + 1); 
    nfa.states[0] = start; 
    return nfa; 
} 
 
NFA kleeneStar(NFA a) { 
    NFA nfa; 
    State start = {0, {}}; 
    start.transitions['e'].push_back(a.start + 1);  
    State end = {(int)(a.states.size() + 1), {}}; 
    end.transitions['e'].push_back(0); 
     
    for (auto &st : a.states) { 
        nfa.states[st.first + 1] = st.second; 
    } 
     
    nfa.start = 0; 
    nfa.finals.push_back(end.id); 
    nfa.states[0] = start;  
    nfa.states[end.id] = end;  
    return nfa; 
} 
 
int main() { 
    NFA nfaA = basicNFA('A'); 
    NFA nfaB = basicNFA('B'); 
    NFA unionAB = unionNFA(nfaA, nfaB); 
    NFA finalNFA = kleeneStar(unionAB); 
     
    cout << "Successfully generated the NFA for the regular expression (A-B)*!" << endl; 
    return 0; 
}