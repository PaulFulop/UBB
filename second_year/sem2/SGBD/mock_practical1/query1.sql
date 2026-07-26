-- set transaction isolation level repeatable read
begin transaction
select [name] from users
waitfor delay '00:00:08'
select [name] from users
commit