CREATE DATABASE EventsTicketing;
GO
USE EventTicketing;
GO

CREATE TABLE Organizer (
    Oid INT IDENTITY(1,1) PRIMARY KEY,
    Name NVARCHAR(50) NOT NULL
);

CREATE TABLE Venues (
    Vid INT IDENTITY(1,1) PRIMARY KEY,
    Oid INT NOT NULL,
    Name NVARCHAR(50) NOT NULL,
    CONSTRAINT FK_Venues_Organizer
        FOREIGN KEY (Oid) REFERENCES Organizer(Oid)
);

CREATE TABLE Events (
    Eid INT IDENTITY(1,1) PRIMARY KEY,
    Vid INT NOT NULL,
    Name NVARCHAR(50) NOT NULL,
    Event_Date DATETIME NOT NULL,
    TicketPrice INT NOT NULL,
    TicketsNum INT NOT NULL,
    CONSTRAINT FK_Events_Venues
        FOREIGN KEY (Vid) REFERENCES Venues(Vid)
);

CREATE TABLE Customers (
    Cid INT IDENTITY(1,1) PRIMARY KEY,
    [Name] NVARCHAR(50) NOT NULL
);

CREATE TABLE Sales (
    Sid INT IDENTITY(1,1) PRIMARY KEY,
    Eid INT NOT NULL,
    Cid INT NOT NULL,
    SaleDate DATETIME,
    CONSTRAINT FK_Sales_Events
        FOREIGN KEY (Eid) REFERENCES Events(Eid),
    CONSTRAINT FK_Sales_Customers
        FOREIGN KEY (Cid) REFERENCES Customers(Cid)
);

GO
CREATE PROCEDURE GetEventSalesStats
    @EventId INT
AS
BEGIN
    SELECT
        e.[Name] AS EventName,
        COUNT(s.Sid) AS TicketsSold,
        COUNT(s.Sid) * e.TicketPrice AS TotalRevenue
    FROM Events e
    LEFT JOIN Sales s ON e.Eid = s.Eid
    WHERE e.Eid = @EventId
    GROUP BY e.Name, e.TicketPrice;
END;
GO

CREATE VIEW vw_EventTicketsAvailable
AS
SELECT
    e.[Name] AS EventName,
    v.[Name] AS VenueName,
    e.Event_Date,
    e.TicketsNum - COUNT(s.[Sid]) AS TicketsAvailable
FROM Events e
JOIN Venues v ON e.Vid = v.Vid
LEFT JOIN Sales s ON e.Eid = s.Eid
GROUP BY
    e.[Name],
    v.[Name],
    e.Event_Date,
    e.TicketsNum;
GO

CREATE FUNCTION dbo.fn_OrganizerEventCustomers
(
    @OrganizerId INT
)
RETURNS TABLE
AS
RETURN
(
    SELECT
        e.Name AS EventName,
        COUNT(DISTINCT s.Cid) AS UniqueCustomers
    FROM Organizer o
    JOIN Venues v ON o.Oid = v.Oid
    JOIN Events e ON v.Vid = e.Vid
    LEFT JOIN Sales s ON e.Eid = s.Eid
    WHERE o.Oid = @OrganizerId
    GROUP BY e.Name
);