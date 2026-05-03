package com.battleships.repositories;

import com.battleships.model.User;
import com.battleships.util.DBConnection;
import com.battleships.util.PasswordUtil;

import java.sql.*;

public class UserRepository {

    /**
     * Register a new user. Returns the new user's ID, or -1 if username taken.
     */
    public int register(String username, String password) throws SQLException {
        String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            ps.setString(1, username);
            ps.setString(2, PasswordUtil.hash(password));
            ps.executeUpdate();
            try (ResultSet rs = ps.getGeneratedKeys()) {
                if (rs.next()) return rs.getInt(1);
            }
        } catch (SQLException e) {
            // Unique constraint violation (username taken)
            if (e.getErrorCode() == 2627 || e.getErrorCode() == 2601) {
                return -1;
            }
            throw e;
        }
        return -1;
    }

    /**
     * Authenticate a user. Returns the User object if credentials match, null otherwise.
     */
    public User login(String username, String password) throws SQLException {
        String sql = "SELECT id, username, password FROM users WHERE username = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, username);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    String stored = rs.getString("password");
                    if (PasswordUtil.verify(password, stored)) {
                        User u = new User();
                        u.setId(rs.getInt("id"));
                        u.setUsername(rs.getString("username"));
                        return u;
                    }
                }
            }
        }
        return null;
    }

    /**
     * Find user by ID.
     */
    public User findById(int id) throws SQLException {
        String sql = "SELECT id, username FROM users WHERE id = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    return new User(rs.getInt("id"), rs.getString("username"));
                }
            }
        }
        return null;
    }
}