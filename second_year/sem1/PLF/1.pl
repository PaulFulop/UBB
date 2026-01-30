prod([], 1).
prod([H|T], P):- prod(T, P1), P is H * P1.

insert(E, L, [E|L]).
insert(E, [H|T], [H|R]):- insert(E, T, R).

arr([H|_], 1, [H]).
arr([_|T], K, R):- K >= 1, arr(T,K,R).
arr([H|T], K, R):- K > 1, K1 is K - 1, arr(T, K1, R1), insert(H, R1, R).

valid_arr([], _, []).
valid_arr([H|T], V, [H|R]):- prod(H, P), P < V, !, valid_arr(T, V, R).
valid_arr([_|T], V, R):- valid_arr(T, V, R).

main(L, K, V, AllRes):- findall(R, arr(L, K, R), R1), valid_arr(R1, V, AllRes).

p(1).
p(2).
q(1).
q(2).
r(1).
r(2).

s:- p(X),q(Y),r(Z), !,write((X, Y, Z)), nl.