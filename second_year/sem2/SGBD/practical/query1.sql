set transaction isolation level serializable
begin transaction
select * from Chiefs
waitfor delay '00:00:05'
select* from Chiefs
commit