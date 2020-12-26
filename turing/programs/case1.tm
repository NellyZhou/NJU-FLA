#Q = {0,cp_a,cp_ab,cp_aba,cp_abab,cp_reject,mh_1,cc_a,cc_ab,mh_1_r,cmp,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

#S = {a,b}

#G = {a,b,_,t,r,u,e,f,a,l,s}

#q0 = 0

#B = _

#N = 2

#F = {halt_accept}


; state 0: start state
0 a_ a_ ** cp_a
0 b_ b_ ** cp_reject
0 __ __ ** reject ; empty input

; Next, copy the last a^k b^l to the 2nd tape
; state cp_a: string a^i
; state cp_ab: string a^i b^j
; state cp_aba: string a^i b^j a^k
; state cp_abab: string a^i b^j a^k b^l
; state cp_reject: string is not in form of abab, but still have symbols on tape
cp_a a_ a_ r* cp_a
cp_a b_ b_ r* cp_ab
cp_a __ __ ll reject

cp_ab a_ aa rr cp_aba
cp_ab b_ b_ r* cp_ab
cp_ab __ __ ll reject

cp_aba a_ aa rr cp_aba
cp_aba b_ bb rr cp_abab
cp_aba __ __ ll reject

cp_abab a_ aa rr cp_reject
cp_abab b_ bb rr cp_abab
cp_abab __ __ ll mh_1

cp_reject a_ aa rr cp_reject
cp_reject b_ bb rr cp_reject
cp_reject __ __ ll reject

; State mh_1: move 1st head to the left
mh_1 ab ab l* mh_1
mh_1 bb bb l* mh_1
mh_1 _b _b rr cc_a

; Following, copy the string first a^i b^j to the 2nd tape
; state cc_a: currently copy in form of a^i
; state cc_ab: currently copy in form of a^i b^j
cc_a a_ aa rr cc_a
cc_a b_ bb rr cc_ab
cc_ab b_ bb rr cc_ab
cc_ab a_ a_ r* mh_1_r

; State mt_1_r: move 1st head to the right
mh_1_r a_ a_ r* mh_1_r
mh_1_r b_ b_ r* mh_1_r
mh_1_r __ __ ll cmp

; State cmp: compare two strings
cmp aa __ ll cmp
cmp bb __ ll cmp
cmp ab __ ll reject
cmp ba __ ll reject
cmp __ __ ** accept

; State accept: write 'true' on 1st tape
accept __ t_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ r* halt_accept


; State reject: write 'false' on 1st tape
reject aa __ ll reject
reject ab __ ll reject
reject ba __ ll reject
reject bb __ ll reject
reject a_ __ l* reject
reject b_ __ l* reject
reject _a __ *l reject
reject _b __ *l reject
reject __ f_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ ** halt_reject
