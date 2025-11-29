:- set_prolog_flag(answer_write_options, [max_depth(0)]). %to see the whole result
% a. For a list of integer numbers, define a predicate to write twice in list every prime number.
% b. For a heterogeneous list, formed from integer numbers and list of numbers, define a predicate to write in 
% every sublist twice every prime number.
% Eg.: [1, [2, 3], 4, 5, [1, 4, 6], 3, [1, 3, 7, 9, 10], 5] =>
% [1, [2, 2, 3, 3], 4, 5, [1, 4, 6], 3, [1, 3, 3, 7, 7, 9, 10], 5]

%a

% is_prime(i,i)
% is_prime(num, div)=
% true, if div = num - 1
% is_prime(num, div+1), if div % num != 0
is_prime(NUM, NUM):- !.
is_prime(NUM, DIV):- NUM > 1, NUM mod DIV =\= 0, DIV1 is DIV + 1, is_prime(NUM, DIV1).
is_prime(NUM):-is_prime(NUM, 2).

%double_primes(i,o)
%double_primes(l1...ln)=
%{ {}, if n = 0
% {l1, l1} U double_primes(l2...ln), if is_prime(l1)
% {l1} U double_primes(l2...ln), oterwise 

double_primes([], []).
double_primes([H|T], [H,H|Res]):- is_prime(H), !, double_primes(T, Res).
double_primes([H|T], [H|Res]):- double_primes(T, Res).

%parse_list(i,i,o)
%parse_list(LIST, L, Res)

parse_list([], []).
parse_list([H|T], [Res1|Res]):-
    is_list(H),
    !,
    double_primes(H, Res1),
    parse_list(T, Res).
parse_list([H|T], [H|Res]):- parse_list(T, Res).