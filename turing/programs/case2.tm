#Q = {0,cp_1,cp_1x,cp_1x1,cp_ans,cp_reject,mh,cmp,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

#S = {1,x,=}

#G = {1,x,=,_,t,r,u,e,f,a,l,s}

#q0 = 0

#B = _

#N = 3

#F = {halt_accept}


; state 0: start state
0 1__ 1__ *** cp_1
0 x__ x__ *** cp_reject
0 =__ =__ *** cp_reject
0 ___ ___ *** reject ; empty input

; State cp: copy the string last a^k b^l to the 2nd tape
cp_1 1__ 1_1 r*r cp_1
cp_1 =__ =__ r** cp_reject
cp_1 x__ x__ r** cp_1x
cp_1 ___ ___ lll reject

cp_1x 1__ 1_1 r*r cp_1x1
cp_1x =__ =__ r** cp_reject
cp_1x x__ x__ r** cp_reject
cp_1x ___ ___ lll reject

cp_1x1 1__ 1_1 r*r cp_1x1
cp_1x1 =__ =__ r** cp_1x1=
cp_1x1 x__ x__ r** cp_reject
cp_1x1 ___ ___ lll reject

cp_1x1= 1__ 11_ rr* cp_ans
cp_1x1= =__ =__ r** cp_reject
cp_1x1= x__ x__ r** cp_reject
cp_1x1= ___ ___ lll reject

cp_ans 1__ 11_ rr* cp_ans
cp_ans =__ =__ r** cp_reject
cp_ans x__ x__ r** cp_reject
cp_ans ___ ___ l** mh

cp_reject 1__ 1__ r** cp_reject
cp_reject =__ =__ r** cp_reject
cp_reject x__ x__ r** cp_reject
cp_reject ___ ___ lll reject

; State mh: move 1st head to the left and clear 1st tape 
mh 1__ ___ l** mh
mh =__ ___ l** mh
mh x__ ___ l** mh
mh ___ ___ *ll cmp

; State cmp: compare two strings
cmp _11 ___ *ll cmp
cmp __1 ___ **l reject
cmp _1_ ___ *l* reject
cmp ___ ___ *** accept

; State accept: 
accept ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ r** halt_accept

; State reject:
reject 1__ ___ l** reject
reject 1_1 ___ l*l reject
reject 11_ ___ ll* reject
reject 111 ___ lll reject

reject x__ ___ l** reject
reject x_1 ___ l*l reject
reject x1_ ___ ll* reject
reject x11 ___ lll reject

reject =__ ___ l** reject
reject =_1 ___ l*l reject
reject =1_ ___ ll* reject
reject =11 ___ lll reject

reject __1 ___ **l reject
reject _1_ ___ *l* reject

reject ___ f__ r** reject2
reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject






