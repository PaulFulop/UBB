package com.battleships.repositories;

import com.battleships.model.Game;
import com.battleships.util.DBConnection;

import java.sql.*;

public class GameRepository {

    private Game mapRow(ResultSet rs) throws SQLException {
        Game g = new Game();
        g.setId(rs.getInt("id"));
        g.setPlayer1Id(rs.getInt("player1_id"));

        int p2 = rs.getInt("player2_id");
        g.setPlayer2Id(rs.wasNull() ? null : p2);
        g.setStatus(rs.getString("status"));

        int turn = rs.getInt("current_turn_player_id");
        g.setCurrentTurnPlayerId(rs.wasNull() ? null : turn);

        int winner = rs.getInt("winner_id");
        g.setWinnerId(rs.wasNull() ? null : winner);
        g.setPlayer1Ready(rs.getBoolean("player1_ready"));
        g.setPlayer2Ready(rs.getBoolean("player2_ready"));

        // optional join columns
        try { g.setPlayer1Username(rs.getString("p1_username")); } catch (SQLException ignored) {}
        try { g.setPlayer2Username(rs.getString("p2_username")); } catch (SQLException ignored) {}
        return g;
    }

    public int createGame(int player1Id) throws SQLException {
        String sql = "INSERT INTO games (player1_id, status) VALUES (?, 'WAITING')";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            ps.setInt(1, player1Id);
            ps.executeUpdate();
            try (ResultSet rs = ps.getGeneratedKeys()) {
                if (rs.next()) return rs.getInt(1);
            }
        }
        throw new SQLException("Failed to create game");
    }

    public void cancelGame(int gameId, int playerId) throws SQLException {
        String sql = "UPDATE games SET status = 'CANCELLED', updated_at = GETDATE() " +
                "WHERE id = ? AND player1_id = ? AND status = 'WAITING'";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, gameId);
            ps.setInt(2, playerId);
            ps.executeUpdate();
        }
    }

    public void abandonWaitingGamesFor(int playerId) throws SQLException {
        String sql = "UPDATE games SET status = 'CANCELLED', updated_at = GETDATE() " +
                "WHERE player1_id = ? AND status = 'WAITING'";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, playerId);
            ps.executeUpdate();
        }
    }

    public Game findActiveGameForPlayer(int playerId) throws SQLException {
        String sql = "SELECT g.*, u1.username as p1_username, u2.username as p2_username " +
                "FROM games g " +
                "LEFT JOIN users u1 ON g.player1_id = u1.id " +
                "LEFT JOIN users u2 ON g.player2_id = u2.id " +
                "WHERE (g.player1_id = ? OR g.player2_id = ?) " +
                "  AND g.status IN ('WAITING','PLACING','PLAYING')";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, playerId);
            ps.setInt(2, playerId);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) return mapRow(rs);
            }
        }
        return null;
    }

    public Game findById(int gameId) throws SQLException {
        String sql = "SELECT g.*, u1.username as p1_username, u2.username as p2_username " +
                "FROM games g " +
                "LEFT JOIN users u1 ON g.player1_id = u1.id " +
                "LEFT JOIN users u2 ON g.player2_id = u2.id " +
                "WHERE g.id = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, gameId);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) return mapRow(rs);
            }
        }
        return null;
    }

    public Game findWaitingGame(int notPlayerId) throws SQLException {
        String sql = "SELECT g.*, u1.username as p1_username, u2.username as p2_username " +
                "FROM games g " +
                "LEFT JOIN users u1 ON g.player1_id = u1.id " +
                "LEFT JOIN users u2 ON g.player2_id = u2.id " +
                "WHERE g.status = 'WAITING' AND g.player1_id <> ? " +
                "ORDER BY g.created_at ASC";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, notPlayerId);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) return mapRow(rs);
            }
        }
        return null;
    }

    public void joinGame(int gameId, int player2Id) throws SQLException {
        String sql = "UPDATE games SET player2_id = ?, status = 'PLACING', updated_at = GETDATE() WHERE id = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, player2Id);
            ps.setInt(2, gameId);
            ps.executeUpdate();
        }
    }

    public void setPlayerReady(int gameId, int playerId) throws SQLException {
        // First, get current game state
        Game game = findById(gameId);
        if (game == null) return;

        String col = (game.getPlayer1Id() == playerId) ? "player1_ready" : "player2_ready";
        String sql = "UPDATE games SET " + col + " = 1, updated_at = GETDATE() WHERE id = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, gameId);
            ps.executeUpdate();
        }

        game = findById(gameId);
        if (game != null && game.isPlayer1Ready() && game.isPlayer2Ready()) {
            // Start the game — player1 goes first
            startGame(gameId, game.getPlayer1Id());
        }
    }

    public void startGame(int gameId, int firstPlayerId) throws SQLException {
        String sql = "UPDATE games SET status = 'PLAYING', current_turn_player_id = ?, updated_at = GETDATE() WHERE id = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, firstPlayerId);
            ps.setInt(2, gameId);
            ps.executeUpdate();
        }
    }

    public void switchTurn(int gameId, int nextPlayerId) throws SQLException {
        String sql = "UPDATE games SET current_turn_player_id = ?, updated_at = GETDATE() WHERE id = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, nextPlayerId);
            ps.setInt(2, gameId);
            ps.executeUpdate();
        }
    }

    public void forfeitGame(int gameId, int losingPlayerId) throws SQLException {
        Game game = findById(gameId);
        if (game == null || !"PLAYING".equals(game.getStatus())) return;

        int winnerId = (game.getPlayer1Id() == losingPlayerId)
                ? game.getPlayer2Id()
                : game.getPlayer1Id();

        finishGame(gameId, winnerId);
    }


    public void finishGame(int gameId, int winnerId) throws SQLException {
        String sql = "UPDATE games SET status = 'FINISHED', winner_id = ?, updated_at = GETDATE() WHERE id = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, winnerId);
            ps.setInt(2, gameId);
            ps.executeUpdate();
        }
    }
}