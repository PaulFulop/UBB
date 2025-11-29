% a

% transform_list(l1...ln, num):
%   num, if n = 0
%   transform_list(l2...ln, num * 10 + l1), otherwise

transform_list([], NUM, Res):- Res is NUM.
transform_list([H|T], NUM, Res):- NEW_NUM is NUM * 10 + H, transform_list(T, NEW_NUM, Res).


% sum(i1...in, j1...jn):
%   transform_list(i1...in, 0) + transform_list(j1...jn, 0)

sum(L1, L2, Res):- transform_list(L1, 0, Res1), transform_list(L2, 0, Res2), 
    Res is Res1 + Res2.


% b -> [1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] => [8, 2, 2]

% append_elem(l1...ln, num)
%   {num} U {l1...ln}
append_elem(L, X, [X|L]).


% transform_in_list(num, l1...ln):
%   {num} U {l1..ln}, if num < 10
%   {num%10) U transform_in_list(num/10, l1...ln)

transform_in_list(NUM, List, Res):- NUM < 10, append_elem(List, NUM, Res).
transform_in_list(NUM, List, Res):- LastDig is mod(NUM, 10), RemNum is div(NUM, 10),
    append_elem(List, LastDig, NewList), transform_in_list(RemNum, NewList, Res).

% sum_list(l1...ln, sum):
%   transform_in_list(sum), if n = 0
%   sum_list(l2...ln, sum + transform_list(l1)), if l1 = list
%   sum_list(l2...ln, sum), otherwise

sum_list([], SUM, Res):- transform_in_list(SUM, [], Res).
sum_list([H|T], SUM, Res):- is_list(H), transform_list(H, 0, Res1),
    NEW_SUM is SUM + Res1, sum_list(T, NEW_SUM, Res), !. % cut operator -> don't go below if we got up to this point
sum_list([_|T], SUM, Res):- sum_list(T, SUM, Res).

sum_list([H|T], Res):- sum_list([H|T], 0, Res).