package com.battleships.model;

public class Game {
    private int id;
    private Integer player1Id;
    private Integer player2Id;
    private String status; // WAITING, PLACING, PLAYING, FINISHED
    private Integer currentTurnPlayerId;
    private Integer winnerId;
    private boolean player1Ready;
    private boolean player2Ready;

    private String player1Username;
    private String player2Username;

    public Game() {}

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public Integer getPlayer1Id() { return player1Id; }
    public void setPlayer1Id(Integer player1Id) { this.player1Id = player1Id; }

    public Integer getPlayer2Id() { return player2Id; }
    public void setPlayer2Id(Integer player2Id) { this.player2Id = player2Id; }

    public String getStatus() { return status; }
    public void setStatus(String status) { this.status = status; }

    public Integer getCurrentTurnPlayerId() { return currentTurnPlayerId; }
    public void setCurrentTurnPlayerId(Integer currentTurnPlayerId) { this.currentTurnPlayerId = currentTurnPlayerId; }

    public Integer getWinnerId() { return winnerId; }
    public void setWinnerId(Integer winnerId) { this.winnerId = winnerId; }

    public boolean isPlayer1Ready() { return player1Ready; }
    public void setPlayer1Ready(boolean player1Ready) { this.player1Ready = player1Ready; }

    public boolean isPlayer2Ready() { return player2Ready; }
    public void setPlayer2Ready(boolean player2Ready) { this.player2Ready = player2Ready; }

    public String getPlayer1Username() { return player1Username; }
    public void setPlayer1Username(String player1Username) { this.player1Username = player1Username; }

    public String getPlayer2Username() { return player2Username; }
    public void setPlayer2Username(String player2Username) { this.player2Username = player2Username; }
}