package com.battleships.repositories;

import com.battleships.model.Ship;
import com.battleships.util.DBConnection;
import com.battleships.util.GameConstants;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ShipRepository {

    private Ship mapRow(ResultSet rs) throws SQLException {
        Ship s = new Ship();
        s.setId(rs.getInt("id"));
        s.setGameId(rs.getInt("game_id"));
        s.setOwnerPlayerId(rs.getInt("owner_player_id"));
        s.setShipIndex(rs.getInt("ship_index"));
        s.setStartRow(rs.getInt("start_row"));
        s.setStartCol(rs.getInt("start_col"));
        s.setLength(rs.getInt("length"));
        s.setOrientation(rs.getString("orientation"));
        return s;
    }

    public void saveShip(Ship ship) throws SQLException {
        String sql = "INSERT INTO ships (game_id, owner_player_id, ship_index, start_row, start_col, length, orientation) " +
                "VALUES (?, ?, ?, ?, ?, ?, ?)";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, ship.getGameId());
            ps.setInt(2, ship.getOwnerPlayerId());
            ps.setInt(3, ship.getShipIndex());
            ps.setInt(4, ship.getStartRow());
            ps.setInt(5, ship.getStartCol());
            ps.setInt(6, ship.getLength());
            ps.setString(7, ship.getOrientation());
            ps.executeUpdate();
        }
    }

    public List<Ship> getShipsForPlayer(int gameId, int playerId) throws SQLException {
        String sql = "SELECT * FROM ships WHERE game_id = ? AND owner_player_id = ? ORDER BY ship_index";
        List<Ship> ships = new ArrayList<>();
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, gameId);
            ps.setInt(2, playerId);
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) ships.add(mapRow(rs));
            }
        }
        return ships;
    }

    public void deleteShipsForPlayer(int gameId, int playerId) throws SQLException {
        String sql = "DELETE FROM ships WHERE game_id = ? AND owner_player_id = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, gameId);
            ps.setInt(2, playerId);
            ps.executeUpdate();
        }
    }

    public boolean isValidPlacement(int gameId, int playerId, int startRow, int startCol,
                                    int length, String orientation) throws SQLException {
        int gridSize = GameConstants.GRID_SIZE;

        // Check bounds
        if (startRow < 0 || startCol < 0) return false;
        if ("HORIZONTAL".equals(orientation)) {
            if (startCol + length > gridSize) return false;
            if (startRow >= gridSize) return false;
        } else {
            if (startRow + length > gridSize) return false;
            if (startCol >= gridSize) return false;
        }

        var newCells = Ship.setShipCells(startRow, startCol, length, orientation);
        
        List<Ship> existing = getShipsForPlayer(gameId, playerId);
        for (Ship s : existing) {
            for (int[] existingCell : s.getCells()) {
                for (int[] newCell : newCells) {
                    if (existingCell[0] == newCell[0] && existingCell[1] == newCell[1]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
}