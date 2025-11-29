% a

% sum(i,i,i,i,o)
% sum(i1...in, j1...jm, t):
% 0, if n = 0 and m = 0
% i1...in if m = 0
% j1...jm if n = 0
% {(in + jm) % 10} U sum(i1...in-1, j1...jm-1, (in + jm) / 10)

sum([],[], L, _, L).
sum([H|T], [], L, TC, Res):- DIGIT is TC + H, sum(T, [], [DIGIT|L], 0, Res).
sum([], [H|T], L, TC, Res):- DIGIT is TC + H, sum([], T, [DIGIT|L], 0, Res).
sum([H1|T1], [H2|T2], L, TC, Res):-
  NEW_DIG is H1 + H2 + TC,
  NEW_DIG1 is NEW_DIG mod 10,
  NEW_T is NEW_DIG // 10,
  sum(T1, T2, [NEW_DIG1|L], NEW_T, Res).

sum(L1, L2, Res):-sum(L1,L2,[],0,Res).

% reverseL(i,i,o)
% reverseL(l1...ln)=
% { {}, if n = 0
% { reverseL(l2...ln) U l1, otherwise

reverseL([], L, L).
reverseL([H|T], L, Res):-reverseL(T, [H|L], Res).
reverseL(L, Res):-reverseL(L,[],Res).

%mainA(i,i,o)
%mainA(l1...ln, v1...vm)=
%sum(reverseL(l1...ln), reverseL(v1...vm))s
mainA(L1, L2, Res):-
    reverseL(L1,NEW_L1),
    reverseL(L2, NEW_L2),
    sum(NEW_L1, NEW_L2, Res). 


% b -> [1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] => [8, 2, 2]

% append_elem(l1...ln, num)
%   {num} U {l1...ln}
append_elem(L, X, [X|L]).

%sum_list(i,i,o);
% sum_list(l1...ln, v1..vm):
%   {}, if n = 0
%   sum(l1...ln, v1...vm) U sum_list(l2...ln, sum + transform_list(l1)), if is_list(l1)
%   sum_list(l2...ln, sum), otherwise
sum_list([], L, L).
sum_list([H|T], L, Res):- is_list(H), mainA(L, H, NEW_SUM), sum_list(T, NEW_SUM, Res), !. % cut operator -> don't go below if we got up to this point
sum_list([_|T], L, Res):- sum_list(T, L, Res).
sum_list([H|T], Res):- sum_list([H|T], [], Res).