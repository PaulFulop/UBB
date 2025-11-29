:- set_prolog_flag(answer_write_options, [max_depth(0)]). %to see the whole result

% a. Sort a list with keeping double values in resulted list. E.g.: [4 2 6 2 3 4] --> [2 2 3 4 4 6]
% b. For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to sort every 
% sublist, keeping the doubles.
% Eg.: [1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
% [1, 2, [1, 4, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1, 1, 1], 7].


% a

% insert(l1...ln, e)
% {e}, if n = 0
% e U {l1...ln}, if e < l1
% l1 U insert_at_pos(l2..ln,e), otherwise
insert([], E, [E]).
insert([H|T], E, [E|[H|T]]):- E < H, !.
insert([H|T], E, [H|Res]):- insert(T, E, Res).

%sort(l1...ln, v1...vm)
%v1...vm, if n = 0
%sort(l2...ln, insert(v1...vm, l1)), otherwise

sortL([], L, L).
sortL([H|T], List, Res):- insert(List, H, NewList), sortL(T, NewList, Res).
sortL(L, Res):- sortL(L,[],Res). %wrapper

mainA(L,Res1):-sortL(L, Res1).


%b

%reverseL(l1...ln, v1..vm)
%v1...vm, if n = 0
%reverse(l2...ln, {l1} U v1...vm), otherwise
reverseL([], L, L).
reverseL([H|T], L, Res):- reverseL(T, [H|L], Res).
reverseL(L, Res):- reverseL(L, [], Res).

%parseList(l1...ln, v1...vm)
%parseList(l2...ln, sort(remove_duplicates(v1...vm)) U v1...vm), if is_list(l1)
%parseList(l2...ln, l1 U v1...vm), otherwise

parseList([], L, L).
parseList([H|T], List, Res):-is_list(H), mainA(H, Res1), parseList(T, [Res1|List], Res).
parseList([H|T], List, Res):- parseList(T, [H|List], Res).

mainB(L, Res):- parseList(L, [], Res1), reverseL(Res1, Res).