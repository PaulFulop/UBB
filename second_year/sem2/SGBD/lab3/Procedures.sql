-- 1. LOGGING SYSTEM
IF OBJECT_ID('Logs', 'U') IS NULL
BEGIN
    CREATE TABLE Logs (
        LogID         INT            IDENTITY(1,1) PRIMARY KEY,
        ProcedureName NVARCHAR(100)  NOT NULL,
        Action        NVARCHAR(200)  NOT NULL,
        Status        NVARCHAR(10)   NOT NULL,   -- 'INFO' / 'SUCCESS' / 'ERROR'
        Message       NVARCHAR(MAX),
        CreatedAt     DATETIME       NOT NULL DEFAULT GETDATE()
    );
END;

SELECT * FROM Bundle
SELECT * FROM Item
SELECT * FROM Item_Bundle

-- Helper procedure: instead of writing INSERT INTO Logs every time
GO
CREATE OR ALTER PROCEDURE sp_Log
    @Proc   NVARCHAR(100),
    @Action NVARCHAR(200),
    @Status NVARCHAR(10),
    @Msg    NVARCHAR(MAX)
AS
BEGIN
    SET NOCOUNT ON;
    INSERT INTO Logs(ProcedureName, Action, Status, Message)
    VALUES (@Proc, @Action, @Status, @Msg);
END;
GO


-- 2. GRADE 3 ─ FULL ROLLBACK
--   Creates a new Bundle and links existing Items to it.
--   If ANYTHING fails → ROLLBACK → nothing is saved at all.
GO
CREATE OR ALTER PROCEDURE sp_AddBundle_FullRollback
    @BundleName  NVARCHAR(200),
    @BundlePrice DECIMAL(10,2),
    @ItemNames   NVARCHAR(MAX)
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @Bid       INT;
    DECLARE @Iid       INT;
    DECLARE @ItemName  NVARCHAR(200);
    DECLARE @Remaining NVARCHAR(MAX);
    DECLARE @Pos       INT;
    DECLARE @LogMsg NVARCHAR(MAX);
    DECLARE @ErrMsg NVARCHAR(MAX);

    IF @BundleName IS NULL
    BEGIN
        EXEC sp_Log 'sp_AddBundle_FullRollback','VALIDATE','ERROR','Bundle name is empty.';
        SELECT 'ERROR: Bundle name cannot be empty.' AS Result; RETURN;
    END

    IF @BundlePrice IS NULL OR @BundlePrice < 0
    BEGIN
        EXEC sp_Log 'sp_AddBundle_FullRollback','VALIDATE','ERROR','Invalid price.';
        SELECT 'ERROR: Bundle price must be 0 or greater.' AS Result; RETURN;
    END

    IF @ItemNames IS NULL
    BEGIN
        EXEC sp_Log 'sp_AddBundle_FullRollback','VALIDATE','ERROR','No item names provided.';
        SELECT 'ERROR: You must provide at least one item name.' AS Result; RETURN;
    END

    IF EXISTS (SELECT 1 FROM Bundle WHERE Name = @BundleName)
    BEGIN
        EXEC sp_Log 'sp_AddBundle_FullRollback','VALIDATE','ERROR', 'Bundle already exists';
        SELECT 'ERROR: A bundle with that name already exists.' AS Result; RETURN;
    END

    -- If ANY statement inside TRY fails, CATCH fires → full rollback
    BEGIN TRY
        BEGIN TRANSACTION;

        SET @LogMsg = 'Bundle="' + @BundleName + '" Items="' + @ItemNames + '"';
        EXEC sp_Log 'sp_AddBundle_FullRollback','START TRANSACTION','INFO', @LogMsg;

        -- Step 1: Insert the new Bundle
        INSERT INTO Bundle([Name], Price)
        VALUES (@BundleName, @BundlePrice);

        SET @Bid = SCOPE_IDENTITY();   -- gets the auto-generated Bid

        SET @LogMsg = 'Bid=' + CAST(@Bid AS NVARCHAR) + ' Name="' + @BundleName + '"';
        EXEC sp_Log 'sp_AddBundle_FullRollback','INSERT Bundle','SUCCESS', @LogMsg;

        -- Step 2: Loop through each item name and link it
        SET @Remaining = @ItemNames;

        WHILE LEN(@Remaining) > 0
        BEGIN
            -- Split off the next name from the comma-separated list
            SET @Pos = CHARINDEX(',', @Remaining);

            IF @Pos > 0
            BEGIN
                SET @ItemName  = LTRIM(RTRIM(SUBSTRING(@Remaining, 1, @Pos - 1)));
                SET @Remaining = LTRIM(RTRIM(SUBSTRING(@Remaining, @Pos + 1, LEN(@Remaining))));
            END
            ELSE
            BEGIN
                SET @ItemName  = LTRIM(RTRIM(@Remaining));
                SET @Remaining = '';
            END

            -- Look up the Iid by name
            SET @Iid = NULL;
            SELECT @Iid = Iid FROM Item WHERE [Name] = @ItemName;

            -- If not found, THROW sends control to CATCH → full rollback
            IF @Iid IS NULL
                THROW 50001, 'Item not found', 1;

            -- Step 3: Link item to bundle in the junction table
            INSERT INTO Item_Bundle(Iid, Bid) VALUES (@Iid, @Bid);

            SET @LogMsg = 'Linked "' + @ItemName + '" (Iid=' + CAST(@Iid AS NVARCHAR) + ') → Bid=' + CAST(@Bid AS NVARCHAR);
            EXEC sp_Log 'sp_AddBundle_FullRollback','INSERT Item_Bundle','SUCCESS', @LogMsg;

            SET @Iid = NULL;   -- reset for next loop
        END

        -- All steps succeeded → commit everything
        COMMIT TRANSACTION;

        EXEC sp_Log 'sp_AddBundle_FullRollback','COMMIT','SUCCESS','All inserts committed.';
        SELECT CONCAT('SUCCESS – Bundle "', @BundleName, '" created with Bid=', @Bid) AS Result;

    END TRY
    BEGIN CATCH
        -- Something failed → undo EVERYTHING
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION;

        SET @ErrMsg = ERROR_MESSAGE();
        EXEC sp_Log 'sp_AddBundle_FullRollback','ROLLBACK','ERROR', @ErrMsg;
        SELECT CONCAT('FAILED – everything rolled back. Reason: ', ERROR_MESSAGE()) AS Result;
    END CATCH;
END;
GO

-- TEST GRADE 3
--
-- TEST 1 all valid
EXEC sp_AddBundle_FullRollback 'Summer1 Bundle', 199.99, 'wooden parallettes,high bars';

-- TEST 2 One item doesn't exist → full rollback (bundle also disappears)
EXEC sp_AddBundle_FullRollback 'Winter Bundle', 99.99, 'wooden parallettes,DOESNOTEXIST';

-- TEST 3 Bundle name already exists
EXEC sp_AddBundle_FullRollback 'Summer Bundle', 50.00, 'wooden parallettes';

-- TEST 4 Negative price
EXEC sp_AddBundle_FullRollback 'Promo Bundle', -10.00, 'wooden parallettes';

-- Verify 'Winter Bundle' does NOT exist (was rolled back)
SELECT * FROM Bundle;
SELECT * FROM Item_Bundle;
SELECT * FROM Logs WHERE ProcedureName = 'sp_AddBundle_FullRollback';

-- 3. GRADE 5 ─ PARTIAL RECOVERY
--
-- What it does:
--   Inserts a new Item + a new Bundle then links them.
--   Partial recovery rules:
--      Item fails   → nothing saved  (nothing to link)
--      Bundle fails → Item IS kept, bundle + link rolled back
--      Link fails   → Item IS kept, link rolled back, bundle also rolled back

GO
CREATE OR ALTER PROCEDURE sp_AddItemAndBundle_Partial
    @ItemName    NVARCHAR(200),
    @TypeName    NVARCHAR(100),
    @ItemPrice   DECIMAL(10,2),
    @BundleName  NVARCHAR(200),
    @BundlePrice DECIMAL(10,2)
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @Tid      INT;
    DECLARE @Iid      INT;
    DECLARE @Bid      INT;
    DECLARE @ItemOK   BIT = 0;
    DECLARE @BundleOK BIT = 0;
    DECLARE @LinkOK   BIT = 0;
    DECLARE @LogMsg   NVARCHAR(MAX);
    DECLARE @ErrMsg   NVARCHAR(MAX);

    IF @ItemName IS NULL
    BEGIN
        SELECT 'ERROR: Item name is required.' AS Result; RETURN;
    END

    IF @ItemPrice IS NULL OR @ItemPrice < 0
    BEGIN
        SELECT 'ERROR: Item price must be 0 or greater.' AS Result; RETURN;
    END

    IF @BundleName IS NULL
    BEGIN
        SELECT 'ERROR: Bundle name is required.' AS Result; RETURN;
    END

    IF @BundlePrice IS NULL OR @BundlePrice < 0
    BEGIN
        SELECT 'ERROR: Bundle price must be 0 or greater.' AS Result; RETURN;
    END

    -- Look up Type by name
    SELECT @Tid = Tid FROM Type WHERE [Name] = LTRIM(RTRIM(@TypeName));

    IF @Tid IS NULL
    BEGIN
        SELECT CONCAT('ERROR: Type "', @TypeName, '" not found in Type table.') AS Result;
        RETURN;
    END

    -- Open transaction
    BEGIN TRANSACTION;

    SET @LogMsg = 'Item="' + @ItemName + '" Bundle="' + @BundleName + '"';
    EXEC sp_Log 'sp_AddItemAndBundle_Partial','START TRANSACTION','INFO', @LogMsg;

    -- STEP 1: Insert the new Item
    -- If this fails → roll back ALL (nothing useful to keep)
    BEGIN TRY
        INSERT INTO Item(Tid, Name, Price)
        VALUES (@Tid, LTRIM(RTRIM(@ItemName)), @ItemPrice);

        SET @Iid   = SCOPE_IDENTITY();
        SET @ItemOK = 1;

        SET @LogMsg = 'Iid=' + CAST(@Iid AS NVARCHAR) + ' "' + @ItemName + '"';
        EXEC sp_Log 'sp_AddItemAndBundle_Partial','INSERT Item','SUCCESS', @LogMsg;
    END TRY
    BEGIN CATCH
        SET @ErrMsg = ERROR_MESSAGE();
        EXEC sp_Log 'sp_AddItemAndBundle_Partial','INSERT Item','ERROR', @ErrMsg;
    END CATCH

    -- Item failed → rollback everything and stop
    IF @ItemOK = 0
    BEGIN
        ROLLBACK TRANSACTION;
        SET @LogMsg = 'Item failed, nothing saved. Error: ' + @ErrMsg;
        EXEC sp_Log 'sp_AddItemAndBundle_Partial','ROLLBACK ALL','ERROR',@LogMsg;
        SELECT CONCAT('FAILED – Item not inserted. Nothing saved. Error: ', @ErrMsg) AS Result;
        RETURN;
    END

    -- Item is safely in the transaction
    -- SAVE TRANSACTION
    -- If Bundle or Link fails, we roll back to HERE (keeping the Item).
    SAVE TRANSACTION sp_after_item;

    -- STEP 2: Insert the new Bundle
    --   If this fails → roll back to savepoint (Item is kept)
    BEGIN TRY
        -- Check for duplicate bundle name before inserting
        IF EXISTS (SELECT 1 FROM Bundle WHERE Name = LTRIM(RTRIM(@BundleName)))
            THROW 50002, 'Bundle name already exists.', 1;

        INSERT INTO Bundle(Name, Price)
        VALUES (LTRIM(RTRIM(@BundleName)), @BundlePrice);

        SET @Bid      = SCOPE_IDENTITY();
        SET @BundleOK = 1;

        SET @LogMsg = 'Bid=' + CAST(@Bid AS NVARCHAR) + ' "' + @BundleName + '"';
        EXEC sp_Log 'sp_AddItemAndBundle_Partial','INSERT Bundle','SUCCESS', @LogMsg;
    END TRY
    BEGIN CATCH
        SET @ErrMsg = ERROR_MESSAGE();
        -- Roll back ONLY the Bundle insert; Item is still in the transaction
        ROLLBACK TRANSACTION sp_after_item;
        SET @LogMsg = 'Bundle rolled back. Item kept. Reason: ' + @ErrMsg;
        EXEC sp_Log 'sp_AddItemAndBundle_Partial','INSERT Bundle','ERROR', @LogMsg;
    END CATCH

    -- STEP 3: Link Item ↔ Bundle  (only runs if Bundle was saved)
    --   If this fails → roll back to savepoint (Item is kept, Bundle gone)
    IF @BundleOK = 1
    BEGIN
        BEGIN TRY
            INSERT INTO Item_Bundle(Iid, Bid) VALUES (@Iid, @Bid);
            SET @LinkOK = 1;

            SET @LogMsg = 'Linked Iid=' + CAST(@Iid AS NVARCHAR) + ' <-> Bid=' + CAST(@Bid AS NVARCHAR);
            EXEC sp_Log 'sp_AddItemAndBundle_Partial','INSERT Item_Bundle','SUCCESS', @LogMsg;
        END TRY
        BEGIN CATCH
            SET @ErrMsg = ERROR_MESSAGE();
            ROLLBACK TRANSACTION sp_after_item;   -- undo Bundle too
            SET @BundleOK = 0;
            SET @LogMsg = 'Link failed. Bundle also rolled back. Reason: ' + @ErrMsg;
            EXEC sp_Log 'sp_AddItemAndBundle_Partial','INSERT Item_Bundle','ERROR', @LogMsg;
        END CATCH
    END

    -- Commit whatever survived the savepoint logic
    COMMIT TRANSACTION;

    -- Show what actually happened
    IF @ItemOK = 1 AND @BundleOK = 1 AND @LinkOK = 1
    BEGIN
        EXEC sp_Log 'sp_AddItemAndBundle_Partial','COMMIT','SUCCESS','Full success.';
        SELECT CONCAT('FULL SUCCESS – Item Iid=', @Iid,
                      ' and Bundle Bid=', @Bid, ' created and linked.') AS Result;
    END
    ELSE IF @ItemOK = 1
    BEGIN
        EXEC sp_Log 'sp_AddItemAndBundle_Partial','COMMIT','INFO',
            'Partial – only Item was saved.';
        SELECT CONCAT('PARTIAL SUCCESS – Item Iid=', @Iid,
                      ' saved. Bundle/Link failed and was rolled back.',
                      ' Error: ', @ErrMsg) AS Result;
    END
END;
GO

SELECT * FROM [Type]

-- TO TEST GRADE 5
--
-- TEST 1 Happy path – all three steps succeed
-- Use a real Type name from your Type table
EXEC sp_AddItemAndBundle_Partial 'new_gloves', 'equipment', 299.99, '2024 Bundle', 350.00;
-- Expected: FULL SUCCESS

-- TEST 2 Partial – Item saves, Bundle name already exists
-- (run TEST 1 first so 'Summer Bundle' already exists)
EXEC sp_AddItemAndBundle_Partial 'new chalk', 'equipment', 49.99, 'Summer Bundle', 100.00;
-- Expected: PARTIAL – 'new_ chalk' is in Item, no new bundle created

-- TEST 3 Bad type name – caught before transaction even opens
EXEC sp_AddItemAndBundle_Partial 'newest chalk', 'FAKETYPE', 199.99, 'SW Bundle', 200.00;
-- Expected: ERROR about Type not found

SELECT * FROM Logs WHERE ProcedureName = 'sp_AddItemAndBundle_Partial' ORDER BY LogID DESC;

-- 5. GRADE 10 ─ OPTIMISTIC LOCKING
--
-- Concept:
--   No row locks. Instead we use a Version column.
--   When you read a row you also read its Version number.
--   When you update, you check that Version hasn't changed.
--   If it changed → someone else updated it first → CONFLICT.
--   The application must re-read and retry.

GO
CREATE OR ALTER PROCEDURE sp_UpdateBundlePrice_Optimistic
    @BundleName NVARCHAR(200),
    @NewPrice   DECIMAL(10,2),
    @Version    INT
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @Bid      INT;
    DECLARE @RowCount INT;
    DECLARE @LogMsg NVARCHAR(MAX);

    IF @NewPrice IS NULL OR @NewPrice < 0
    BEGIN
        SELECT 'ERROR: New price must be 0 or greater.' AS Result; RETURN;
    END

    -- Look up bundle by name
    SELECT @Bid = Bid FROM Bundle WHERE Name = LTRIM(RTRIM(@BundleName));

    IF @Bid IS NULL
    BEGIN
        SELECT CONCAT('ERROR: Bundle "', @BundleName, '" not found.') AS Result; RETURN;
    END

    -- The optimistic update
    UPDATE Bundle
    SET    Price   = @NewPrice,
           [Version] = [Version] + 1
    WHERE  Bid     = @Bid
      AND  [Version] = @Version;   -- this is the entire conflict detection

    SET @RowCount = @@ROWCOUNT;  -- 1 = success, 0 = conflict

    IF @RowCount = 1
    BEGIN
        SET @LogMsg = '"' + @BundleName + '" price -> ' + CAST(@NewPrice AS NVARCHAR) + ' | new Version=' + CAST((@Version + 1) AS NVARCHAR);
        EXEC sp_Log 'sp_UpdateBundlePrice_Optimistic','UPDATE Bundle','SUCCESS', @LogMsg;
        SELECT CONCAT('SUCCESS – Price updated to ', @NewPrice,
                      '. New version is ', @Version + 1, '.') AS Result;
    END
    ELSE
    BEGIN
        SET @LogMsg = 'Conflict on "' + @BundleName + '". Expected Version=' + CAST(@Version AS NVARCHAR) + ' but row was already modified.';
        EXEC sp_Log 'sp_UpdateBundlePrice_Optimistic','UPDATE Bundle','ERROR', @LogMsg;
        SELECT CONCAT('CONFLICT – "', @BundleName,
                      '" was modified by someone else. ',
                      'Re-read the row and try again.') AS Result;
    END
END;
GO

-- Step 1: Check the current state of any bundle
SELECT Bid, Name, Price, [Version] FROM Bundle WHERE [Name] = 'Summer Bundle';


-- Step 2: User A updates (has version=0) → succeeds, version becomes 1
EXEC sp_UpdateBundlePrice_Optimistic 'Summer Bundle', 149.99, 0;
-- Result: SUCCESS

-- Step 3: User B also read version=0 earlier → CONFLICT
EXEC sp_UpdateBundlePrice_Optimistic 'Summer Bundle', 99.99, 0;
-- Result: CONFLICT – 0 rows updated because version is now 1

-- Step 4: User B re-reads the row to get the current version
SELECT Bid, Name, Price, [Version] FROM Bundle WHERE Name = 'Summer Bundle';
-- Now sees Version=1

-- Step 5: User B retries with correct version → succeeds, version becomes 2
EXEC sp_UpdateBundlePrice_Optimistic 'Summer Bundle', 99.99, 1;
-- Result: SUCCESS

-- Final check
SELECT Bid, Name, Price, [Version] FROM Bundle WHERE Name = 'Summer Bundle';
-- Price=99.99  Version=2

SELECT * FROM Logs WHERE ProcedureName = 'sp_UpdateBundlePrice_Optimistic' ORDER BY LogID DESC;


-- 6. VIEW ALL LOGS
SELECT * FROM Logs ORDER BY LogID DESC;

-- Filter by outcome:
SELECT * FROM Logs WHERE Status = 'ERROR'   ORDER BY LogID DESC;
SELECT * FROM Logs WHERE Status = 'SUCCESS' ORDER BY LogID DESC;