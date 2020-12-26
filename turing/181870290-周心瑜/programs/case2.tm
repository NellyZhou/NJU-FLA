#Q = {0,cp_1,cp_1x,cp_1x1,cp_1x1_equal,cp_ans,cp_reject,mh,cmpl,cmpr,cmp_acc,change2l,change2r,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

#S = {1,x,=}

#G = {1,x,=,_,t,r,u,e,f,a,l,s}

#q0 = 0

#B = _

#N = 4

#F = {halt_accept}

; state 0: start state
0 1___ 1___ **** cp_1
0 x___ x___ **** cp_reject
0 =___ =___ **** cp_reject
0 ____ ____ **** reject ; empty input


; Input form 1^n x 1^m = 1^x
; State cp*: currently, input is in form of *
; Meanwhile, copy 1^n1^m in 3rd tape and 1^x in the 2nd tape
cp_1 1___ 1_1_ r*r* cp_1
cp_1 =___ =___ r*** cp_reject
cp_1 x___ x___ r*** cp_1x
cp_1 ____ ____ l*** reject

cp_1x 1___ 1__1 r**r cp_1x1
cp_1x =___ =___ r*** cp_reject
cp_1x x___ x___ r*** cp_reject
cp_1x ____ ____ l*** reject

cp_1x1 1___ 1__1 r**r cp_1x1
cp_1x1 =___ =___ r*** cp_1x1_equal
cp_1x1 x___ x___ r*** cp_reject
cp_1x1 ____ ____ l*** reject

cp_1x1_equal 1___ 11__ rr** cp_ans
cp_1x1_equal =___ =___ r*** cp_reject
cp_1x1_equal x___ x___ r*** cp_reject
cp_1x1_equal ____ ____ l*** reject

cp_ans 1___ 11__ rr** cp_ans           ; ans means in form of 1x1=1
cp_ans =___ =___ r*** cp_reject
cp_ans x___ x___ r*** cp_reject
cp_ans ____ ____ l*** mh

cp_reject 1___ 1___ r*** cp_reject
cp_reject =___ =___ r*** cp_reject
cp_reject x___ x___ r*** cp_reject
cp_reject ____ ____ l*** reject

; State mh: move 1st head to the left and clear 1st tape 
mh 1___ ____ l*** mh
mh =___ ____ l*** mh
mh x___ ____ l*** mh
mh ____ ____ rlll cmpl

; State cmp*: compare two strings
; tape1 = 1^x tape2 = 1^n tape3 = 1^m 

cmpl _111 __11 *l*l cmpl
cmpl _11_ _1__ **lr change2r   	; traverse to the leftmost(T2L) still have 1s in 1^x
cmpl __11 ____ **** reject
cmpl __1_ ____ **l* cmp_acc		; T2L and no 1s in 1^x, check whether at the last round

cmpr _111 __11 *l*r cmpr
cmpr _11_ _1__ **ll change2l	; traverse to the rightmost(T2R) still have 1s in 1^x
cmpr __11 ____ **** reject
cmpr __1_ ____ **l* cmp_acc		; T2R and no 1s in 1^x

cmp_acc ____ ____ **** accept	; at last round
cmp_acc __1_ ____ **** reject 	; not the last round

change2l _1_1 ____ **** reject 	; to edge but no rounds run
change2l _111 _111 **** cmpl	; continue and change direction
change2r _1_1 ____ **** reject
change2r _111 _111 **** cmpr

; State accept: write 'true' on 1st tape
accept ____ t___ r*** accept2
accept2 ____ r___ r*** accept3
accept3 ____ u___ r*** accept4
accept4 ____ e___ r*** halt_accept

; State reject: write 'false' on 1st tape
reject 1___ ____ l*** reject
reject x___ ____ l*** reject
reject =___ ____ l*** reject

reject ____ f___ r*** reject2
reject2 ____ a___ r*** reject3
reject3 ____ l___ r*** reject4
reject4 ____ s___ r*** reject5
reject5 ____ e___ **** halt_reject






