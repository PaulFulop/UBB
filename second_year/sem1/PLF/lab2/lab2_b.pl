% list_gcd([l1 l2 ... ln]):
%     l1, if n = 1,
%     pair_gcd(l1, list_gcd[l2 l3...ln]), otherwise

% pair_gcd(a, b) -> helper function. computes the gcd between 2 numbers:
%     a, if b = 0,
%     pair_gcd(b, a mod b), otherwise

pair_gcd(A, 0, A) :- A > 0.
pair_gcd(A, B, GCD) :-
    B > 0,
    R is A mod B,
    pair_gcd(B, R, GCD).


list_gcd([H], H).
list_gcd([H|T], GCD) :-
     list_gcd(T, TailGCD),
     pair_gcd(H, TailGCD, GCD).