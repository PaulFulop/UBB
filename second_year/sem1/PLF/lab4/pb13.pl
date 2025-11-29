:- set_prolog_flag(answer_write_options, [max_depth(0)]). %to see the whole result

% I will consider that the elements of a list with a mountain aspect will be STRICTLY increasing and then STRICTLY decreasing

% is_mountain(l1...ln, flag):
% True, n = 1 and flag = 1
% is_mountain(l2...ln, 0), if l1 < l2 and flag = 0
% is_mountain(l2...ln, 1), if l1 > l2 and flag = 0
% is_mountain(l2...ln, 1), if l1 > l2 and flag = 1

is_mountain([_], 1):-!.
is_mountain([H1, H2|T], 0):- H1 < H2, is_mountain([H2|T], 0).
is_mountain([H1, H2|T], 0):- H1 > H2, is_mountain([H2|T], 1).
is_mountain([H1, H2|T], 1):- H1 > H2, is_mountain([H2|T], 1).

is_mountain([H1, H2, H3|T]):- H1 < H2, is_mountain([H1, H2, H3|T], 0). %wrapper


% all subsets of a list -> subs(l1...ln)
% subs(i, o)
% subs(l1...ln)=
% {}, n = 0
% {l1} U subs(l2...n), n > 0
% subs(l2...n)

subs([],[]).
subs([H|T], [H|R]):-subs(T, R).
subs([_|T], R):-subs(T, R).

subs([H|T]):-subs([H|T], []). %wrapper

onesol(L, Res):-subs(L, Res), is_mountain(Res).
allsols(L,Res):-findall(X,onesol(L,X),Res).