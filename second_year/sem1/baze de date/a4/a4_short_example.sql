-- TestRunds -> test run id, test id, run date, duration (T3)

--T1 insert a run date etc
AS
BEGIN
	SET NOCOUNT ON:
		insert into TestRuns (TestID, RunDate) values
		(@TestID, GETDATE())
		set @TestRunID = SCOPE_IDENTITY()

END

--T2 idk really (delete from position and all the columns above it? or below it)
DECLARE table_cursor CURSOR FOR
SELECT t.TableName
from Tables t -- i guess my tables or something
INNER JOIN TestTables tt ON t.TableID = tt.tableID
where tt.TestID = @TestID 
ORDER BY tt.Position ASC

OPEN table.cursor
FETCH NEXT FROM table.cursor INTO @TableName
SET @SQL = 'DELETE ' + @TableName


-- T3 kind of the opposite of T2
DECLARE table_cursor CURSOR FOR
SELECT t.TableName, tt.NOOFROWS -- -> column inside TestTables
FROM Tables t
INNER JOIN TestTables t1 ON t.TableID = tt.TableID
where tt.TestID = @TestID
ORDER BY tt.Position DESC
-- this is for the cursor part
FETCH NEXT FROMT table.cursor INTO @TableName, @NOOFROWS

SET start = SYSUTCDATETIME() -- -> for duration in TestRuns
SET @SQL = 'INSERT INTO ' -- insert into table test times duration
SET STOP = SYSUTCDATETIME() -- use DIFFDATE from stop to start