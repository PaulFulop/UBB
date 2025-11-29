 %insertE(l1...ln, p, e, count):
 	%{e} U {l1...ln}, p = count
 	%l1 U insertE({l2...ln}, p, e, count+1}, otherwise

insertE([], E, [E]).
insertE([H|T], E, [H|R]):- insertE(T, E, R).

 %insert([1,2,3], 5, [1, 2, 3, 5]) ->
 		%insert([2, 3] 5, [2, 3, 5]) ->
 			%insert([3], 5, [3,5]) -> 
 				%insert([], 5, [5]) -> [5]