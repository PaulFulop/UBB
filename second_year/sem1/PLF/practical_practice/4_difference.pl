%same as with problem 4 but with difference, not sum
%I will consider that the first list always gives a bigger number than the first one, dont want to deal with negatives tbh
%in order to make it work i could see if i can find the biggest list between the two, subtract the smaller one from the bigger one
% and change the sign of the first digit in the result accordingly

%diff(i,i,i,i,o)
%diff(L1, L2, TC, L, Res).
diff([], [], _, L, L):-!.
diff([H|T], [], TC, L, Res):-H1 is H - TC, diff(T, [], 0, [H1|L], Res), !.
diff([H1|T1], [H2|T2], TC, L, Res):-
    NEW_H1 is H1 - TC,
    NEW_DIG is ((NEW_H1 + 10) - H2) mod 10,
    NEW_TC is ((H2 + 10) - NEW_H1 - 1) // 10,
    diff(T1, T2, NEW_TC, [NEW_DIG|L], Res), !.

diff(L1, L2, Res):-diff(L1, L2, 0, [], Res).

% reverseL(i,i,o)
% reverseL(l1...ln)=
% { {}, if n = 0
% { reverseL(l2...ln) U l1, otherwise

reverseL([], L, L).
reverseL([H|T], L, Res):-reverseL(T, [H|L], Res).
reverseL(L, Res):-reverseL(L,[],Res).


elim_first_zero([0|T], T) :- !.
elim_first_zero([H|T], [H|T]).

mainA(L1, L2, Res):-
    reverseL(L1, NEW_L1),
    reverseL(L2, NEW_L2),
    diff(NEW_L1, NEW_L2, Res1),
    elim_first_zero(Res1, Res).

%b

% Helper to find the first list and use it as starting accumulator
diff_list_helper([], L, L).
diff_list_helper([H|T], L, Res):- is_list(H), mainA(L, H, NEW_LIST), diff_list_helper(T, NEW_LIST, Res), !.
diff_list_helper([_|T], L, Res):- diff_list_helper(T, L, Res).

% Main predicate: find first list, then process rest
diff_list([H|T], Res):- is_list(H), !, diff_list_helper(T, H, Res).
diff_list([_|T], Res):- diff_list(T, Res).