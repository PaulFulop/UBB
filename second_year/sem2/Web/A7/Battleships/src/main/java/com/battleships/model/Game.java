package com.battleships.model;

// TODO rename dao to repo (those are basically repos)
// TODO ask claude about the flow of all of this, and how does filter session work, maybe delete or understand its importance
// TODO fix game creation -> i want a user to be able to "abort" a game creation, and also it should reset on login
// TODO second user should be automatically notified about a game creation => able to join a game (see how this works also)
// TODO emojis removal, make app a bit more minimal without emojis, maybe fix some visual bugs
// TODO see if any cookies / localStorage are used, maybe its bad if I store everything in the db -> even game and winner etc, they should at least be removed after game ends or something


public class Game {
    private int id;
    private int player1Id;
    private Integer player2Id;
    private String status;        // WAITING, PLACING, PLAYING, FINISHED
    private Integer currentTurnPlayerId;
    private Integer winnerId;
    private boolean player1Ready;
    private boolean player2Ready;

    // Optional: for display
    private String player1Username;
    private String player2Username;

    public Game() {}

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public int getPlayer1Id() { return player1Id; }
    public void setPlayer1Id(int player1Id) { this.player1Id = player1Id; }

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