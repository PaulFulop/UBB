package com.battleships.model;

public class Shot {
    private int id;
    private int gameId;
    private int shooterPlayerId;
    private int targetRow;
    private int targetCol;
    private String result;  // HIT, MISS, SUNK

    public Shot() {}

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public int getGameId() { return gameId; }
    public void setGameId(int gameId) { this.gameId = gameId; }

    public int getShooterPlayerId() { return shooterPlayerId; }
    public void setShooterPlayerId(int shooterPlayerId) { this.shooterPlayerId = shooterPlayerId; }

    public int getTargetRow() { return targetRow; }
    public void setTargetRow(int targetRow) { this.targetRow = targetRow; }

    public int getTargetCol() { return targetCol; }
    public void setTargetCol(int targetCol) { this.targetCol = targetCol; }

    public String getResult() { return result; }
    public void setResult(String result) { this.result = result; }
}