package com.battleships.model;

import java.util.ArrayList;
import java.util.List;

public class Ship {
    private int id;
    private int gameId;
    private int ownerPlayerId;
    private int shipIndex;       // 1 or 2
    private int startRow;
    private int startCol;
    private int length;
    private String orientation;  // HORIZONTAL or VERTICAL

    public Ship() {}

    /**
     * Returns all cells occupied by this ship as [row, col] pairs.
     */
    public List<int[]> getCells() {
        List<int[]> cells = new ArrayList<>();
        for (int i = 0; i < length; i++) {
            if ("HORIZONTAL".equals(orientation)) {
                cells.add(new int[]{startRow, startCol + i});
            } else {
                cells.add(new int[]{startRow + i, startCol});
            }
        }
        return cells;
    }

    /**
     * Checks whether a given cell is part of this ship.
     */
    public boolean occupies(int row, int col) {
        for (int[] cell : getCells()) {
            if (cell[0] == row && cell[1] == col) return true;
        }
        return false;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public int getGameId() { return gameId; }
    public void setGameId(int gameId) { this.gameId = gameId; }

    public int getOwnerPlayerId() { return ownerPlayerId; }
    public void setOwnerPlayerId(int ownerPlayerId) { this.ownerPlayerId = ownerPlayerId; }

    public int getShipIndex() { return shipIndex; }
    public void setShipIndex(int shipIndex) { this.shipIndex = shipIndex; }

    public int getStartRow() { return startRow; }
    public void setStartRow(int startRow) { this.startRow = startRow; }

    public int getStartCol() { return startCol; }
    public void setStartCol(int startCol) { this.startCol = startCol; }

    public int getLength() { return length; }
    public void setLength(int length) { this.length = length; }

    public String getOrientation() { return orientation; }
    public void setOrientation(String orientation) { this.orientation = orientation; }
}