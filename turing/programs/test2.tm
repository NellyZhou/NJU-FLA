; This example program checks if the input string is in Language L={1mX1n = 1 mxn |m,n in N+}
; Input: a string of 1's and x and =, e.g. '11 x 111 = 111111'

; the finite set of states
#Q = {0,cp1,cp2,cp3,cmp,mh,accd,reject0,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}
; the finite set of input symbols
#S = {1,x,=}

; the complete set of tape symbols
#G = {1,x,=,_,t,r,u,e,f,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 3

; the transition functions

; State a: start state
0 1__ 1__ *** cp1
0 x__ ___ *** reject
0 =__ ___ *** reject 
0 ___ ___ *** reject

; State cp1: copy the string faciend  to the 2nd tape    tape2:  被乘数   111___
cp1 1__ _1_ rr* cp1
cp1 x__ ___ r** cp2
cp1 =__ ___ *** reject 
cp1 ___ ___ *** reject

;State cp2: copy the string multiplicator to the  3rd tape     tape3: 乘数 11_
cp2 1__ __1 r*r cp2
cp2 =__ ___ rll cmp
cp2 ___ ___ *** reject 
cp2 x__ ___ *** reject



;State cmp:every multiple, move head of tape 1 for every move head of tape2
cmp 111 _11 rl* cmp
cmp 1_1 1__ *rl mh
cmp _11 ___ *** reject
cmp __1 ___ **l accd


;State mh:after every multiple, move the head of tape2 to the right
mh 111 111 *r* mh
mh 11_ ___ r** reject0
mh 1_1 1_1 *l* cmp

;State accept doubt : check if tape3 is empty to confirm the result
accd ___ ___ *** accept
accd __1 ___ *** reject

; State accept*: write 'true' on bst tape
accept ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept

; State reject*: write 'false' on bst tape

reject0 1__ 1__ l** reject0
reject0 ___ ___ r** reject

reject 1__ 1__ r** reject
reject x__ ___ r** reject
reject =__ =__ r** reject


reject ___ f__ r** reject2
reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject
