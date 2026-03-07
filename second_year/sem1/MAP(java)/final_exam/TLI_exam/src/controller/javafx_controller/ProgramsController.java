package controller.javafx_controller;

import controller.GarbageCollector;
import controller.ProgramService;
import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import repo.ArrayListRepository;
import repo.Repository;

import java.awt.event.MouseEvent;
import java.util.ArrayList;

public class ProgramsController  {
    @FXML
    private ListView<String> AllProgramsListView;

    private MainController mainController;

    @FXML
    public void initialize() {
        // ill see if I need something here
    }

    public void setMainController(MainController mainController) {
        this.mainController = mainController;
    }

    public void addProgramTxt(String programTxt) {
        AllProgramsListView.getItems().add(programTxt);
    }

    public void onMouseClicked() {
        int row = AllProgramsListView.getSelectionModel().getSelectedIndex();
        mainController.setProgramToTest(row);
    }
}
