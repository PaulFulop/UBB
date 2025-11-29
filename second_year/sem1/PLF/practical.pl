% :- set_prolog_flag(answer_write_options, [max_depth(0)]).


% gcd(i, i, o).
% gcd (a, b) =
% a, if b = 0
% gcd(b, a % b), otherwise
gcd(A, 0, Res):- Res is A.
gcd(A, B, Res):- A1 is A mod B, gcd(B, A1, Res),!.

%list_gcd(i,o)
%list_gcd(l1...ln)=
% l1, if n = 1
% gcd(l1, list_gcd(l2...ln)), otherwise

list_gcd([H], H).
list_gcd([H|T], GCD) :-
     list_gcd(T, TailGCD),
     gcd(H, TailGCD, GCD), !.