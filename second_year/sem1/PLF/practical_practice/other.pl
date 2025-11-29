% From a heterogeneous list, formed from positive integer numbers, write a predicate to create a list that includes the least common  
% multiple of every sub-list.
% a) [] -> []
% b) [1, [2,3], [4,4], 3, 6, [7,10,1], 5, [1,1,1], 7, []] -> [6,4,70,1,0]
% c) [1,2,3,4,5,6] -> []

%lcm(i,i,i,o)
%lcm(n1,n2, N) =
%{ N, if N % n1 == 0 and N % n2 == 0
%{ lcm(n1, n2, N + 1), otherwise
lcm(N1, N2, Mul, Res):- Mul mod N1 =:= 0, Mul mod N2 =:= 0, Res is Mul,!. 
lcm(N1, N2, Mul, Res):- Mul1 is Mul + 1, lcm(N1, N2, Mul1, Res).
lcm(N1, N2, Res):- lcm(N1, N2, 1, Res).

%common_lcm(i,i,o)
%common_lcm(l1...ln, current_lcm) = 
%{ current_lcm, if n = 0
%{ common_lcm(l2...ln, lcm(current_lcm, l1)), otherwise
common_lcm([],LCM, Res):- Res is LCM.
common_lcm([H|T], LCM, Res):- lcm(LCM, H, LCM1), common_lcm(T, LCM1, Res).
common_lcm(L, Res):- common_lcm(L, 1, Res).

%insert(i, i, o)
%insert(l1...ln, e) = 
%{ {e}, if n = 0
%{ l1 U insert(l2...ln, e), otherwise
insert([], E, [E]).
insert([H|T], E, [H|Res]):- insert(T, E, Res).

%is_empty(i)
%is_empty(l1..ln)=
%{false, n = 0
%{true, otherwise
is_empty([]).

%main(i,i,o)
%main(l1...ln)=
%{}, n = 0
% {0} U main(l2...ln), if is_list(H) and is_empty(H) == true and n > 0
%{common_lcm(l1)} U main(l2...ln), if is_list(H) and is_empty(H) == false and n > 0
%main(l2...ln), otherwise
main([], L, L).
main([H|T], L, Res):- is_list(H), is_empty(H),  insert(L, 0, L1), main(T, L1, Res),!.
main([H|T], L, Res):- is_list(H), common_lcm(H, LCM),  insert(L, LCM, L1), main(T, L1, Res),!.
main([_|T], L, Res):- main(T, L, Res).
main(L,Res):-main(L, [], Res). %wrapper