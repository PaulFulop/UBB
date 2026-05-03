package com.battleships.repositories;

import com.battleships.model.Shot;
import com.battleships.util.DBConnection;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ShotRepository {

    private Shot mapRow(ResultSet rs) throws SQLException {
        Shot s = new Shot();
        s.setId(rs.getInt("id"));
        s.setGameId(rs.getInt("game_id"));
        s.setShooterPlayerId(rs.getInt("shooter_player_id"));
        s.setTargetRow(rs.getInt("target_row"));
        s.setTargetCol(rs.getInt("target_col"));
        s.setResult(rs.getString("result"));
        return s;
    }

    /**
     * Record a shot in the database.
     */
    public void saveShot(Shot shot) throws SQLException {
        String sql = "INSERT INTO shots (game_id, shooter_player_id, target_row, target_col, result) " +
                "VALUES (?, ?, ?, ?, ?)";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, shot.getGameId());
            ps.setInt(2, shot.getShooterPlayerId());
            ps.setInt(3, shot.getTargetRow());
            ps.setInt(4, shot.getTargetCol());
            ps.setString(5, shot.getResult());
            ps.executeUpdate();
        }
    }

    /**
     * Get all shots fired BY a specific player in a game.
     */
    public List<Shot> getShotsByPlayer(int gameId, int shooterPlayerId) throws SQLException {
        String sql = "SELECT * FROM shots WHERE game_id = ? AND shooter_player_id = ?";
        List<Shot> shots = new ArrayList<>();
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, gameId);
            ps.setInt(2, shooterPlayerId);
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) shots.add(mapRow(rs));
            }
        }
        return shots;
    }

    /**
     * Get all shots fired AT a specific player in a game (i.e., by the other player targeting them).
     * Used to show the opponent's attacks on your board.
     */
    public List<Shot> getShotsAgainstPlayer(int gameId, int targetPlayerId) throws SQLException {
        // Shots fired by the other player
        String sql = "SELECT * FROM shots WHERE game_id = ? AND shooter_player_id <> ?";
        List<Shot> shots = new ArrayList<>();
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, gameId);
            ps.setInt(2, targetPlayerId);
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) shots.add(mapRow(rs));
            }
        }
        return shots;
    }

    /**
     * Check whether a cell has already been targeted by a shooter in this game.
     */
    public boolean alreadyShot(int gameId, int shooterPlayerId, int row, int col) throws SQLException {
        String sql = "SELECT COUNT(*) FROM shots WHERE game_id = ? AND shooter_player_id = ? AND target_row = ? AND target_col = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, gameId);
            ps.setInt(2, shooterPlayerId);
            ps.setInt(3, row);
            ps.setInt(4, col);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    /**
     * Count hits on a specific player's ships in a game.
     * Used to detect if all their ships have been sunk (winning condition).
     */
    public int countHitsOnPlayer(int gameId, int targetPlayerId) throws SQLException {
        // Hits fired at the target player = shots NOT by that player with result HIT or SUNK
        String sql = "SELECT COUNT(*) FROM shots WHERE game_id = ? AND shooter_player_id <> ? AND result IN ('HIT','SUNK')";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, gameId);
            ps.setInt(2, targetPlayerId);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) return rs.getInt(1);
            }
        }
        return 0;
    }
}