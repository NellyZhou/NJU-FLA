; This example program checks if the input string is in Language L = {aibjaibj|i,j>0}
; Input: a string of a's and b's, e.g. 'abbabb'

; the finite set of states
#Q = {0,cpa,cpb,cmp,mh,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {a,b,_,t,r,u,e,f,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 2

; the transition functions

; State a: start state
0 a_ _a rr cpa
0 b_ __ r* reject
0 __ __ ** reject
s
; State cpa: copy the left half string a to the 2nd tape 
cpa a_ _a rr cpa
cpa b_ _b rr cpb
cpa __ __ ** reject

; State cpb: copy the left half string b to the 2nd tape 
cpb a_ a_ ll mh
cpb b_ _b rr cpb
cpb __ __ ** reject

; State mha: move  2 head  to the left until meeting _
mh _a _a *l mh
mh _b _b *l mh
mh __ __ rr cmp

; State cmp: compare two strings
cmp aa __ rr cmp
cmp bb __ rr cmp
cmp ab __ rr reject
cmp ba __ rr reject
cmp __ __ ** accept
cmp _b __ ** reject
cmp _a __ ** reject
cmp b_ __ r* reject
cmp a_ __ r* reject

; State accept*: write 'true' on bst tape
accept __ t_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ ** halt_accept

; State reject*: write 'false' on bst tape
reject a_ __ rr reject
reject b_ __ rr reject
reject aa __ rr reject
reject ab __ rr reject
reject ba __ rr reject
reject bb __ rr reject
reject __ f_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ ** halt_reject;aas
