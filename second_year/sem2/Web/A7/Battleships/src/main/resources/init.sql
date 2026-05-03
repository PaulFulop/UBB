-- Battleships Game Database Schema
-- Run this in SQL Server Management Studio (SSMS)
-- Make sure to create the database first: CREATE DATABASE BattleshipsDB;
-- Then USE BattleshipsDB;
 
CREATE DATABASE BattleshipsDB;
GO
 
USE BattleshipsDB;
GO
 
-- Users table
CREATE TABLE users (
    id INT IDENTITY(1,1) PRIMARY KEY,
    username NVARCHAR(50) NOT NULL UNIQUE,
    password NVARCHAR(255) NOT NULL,  -- store hashed passwords
    created_at DATETIME DEFAULT GETDATE()
);
 
-- Games table: tracks each game session
-- status: 'WAITING' (1 player), 'PLACING' (both joined, placing ships), 'PLAYING', 'FINISHED'
CREATE TABLE games (
    id INT IDENTITY(1,1) PRIMARY KEY,
    player1_id INT NOT NULL REFERENCES users(id),
    player2_id INT REFERENCES users(id),
    [status] NVARCHAR(20) NOT NULL DEFAULT 'WAITING',
    current_turn_player_id INT REFERENCES users(id),  -- whose turn it is
    winner_id INT REFERENCES users(id),
    player1_ready BIT DEFAULT 0,  -- has placed ships
    player2_ready BIT DEFAULT 0,
    created_at DATETIME DEFAULT GETDATE(),
    updated_at DATETIME DEFAULT GETDATE()
);
 
-- Ships table: each ship occupies multiple cells
-- owner_player_id: which player owns this ship
-- ship_index: 1 or 2 (each player has 2 ships)
CREATE TABLE ships (
    id INT IDENTITY(1,1) PRIMARY KEY,
    game_id INT NOT NULL REFERENCES games(id),
    owner_player_id INT NOT NULL REFERENCES users(id),
    ship_index INT NOT NULL,          -- 1 or 2
    start_row INT NOT NULL,           -- 0-based row index
    start_col INT NOT NULL,           -- 0-based col index
    [length] INT NOT NULL,              -- number of cells
    orientation NVARCHAR(10) NOT NULL -- 'HORIZONTAL' or 'VERTICAL'
);
 
-- Shots table: each bombing attempt
CREATE TABLE shots (
    id INT IDENTITY(1,1) PRIMARY KEY,
    game_id INT NOT NULL REFERENCES games(id),
    shooter_player_id INT NOT NULL REFERENCES users(id),
    target_row INT NOT NULL,
    target_col INT NOT NULL,
    result NVARCHAR(10) NOT NULL,  -- 'HIT', 'MISS', 'SUNK'
    shot_at DATETIME DEFAULT GETDATE()
);
 
-- Insert two test users (password = "password" hashed with SHA-256 style, 
-- but we'll use plain for demo — see DBUtil for hashing)
-- Actually we'll let users register, but here are two defaults for testing:
-- You can insert them manually or use the register page
-- INSERT INTO users (username, password) VALUES ('player1', 'password');
-- INSERT INTO users (username, password) VALUES ('player2', 'password');
 
GO

SELECT * FROM users
DELETE FROM users