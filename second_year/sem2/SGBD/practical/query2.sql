-- set transaction isolation level serializable
begin transaction
insert into Chiefs values ('Andreea', 'Romanian');
commit