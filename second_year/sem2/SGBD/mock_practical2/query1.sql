-- set transaction isolation level serializable
begin transaction
select * from Doctor
waitfor delay '00:00:08'
select * from Doctor
commit 