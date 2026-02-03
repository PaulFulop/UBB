package controller.javafx_controller;

import controller.ProgramService;
import exceptions.ProgramException;
import javafx.beans.property.SimpleStringProperty;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import model.states.ProgramState;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class MainController {

    @FXML
    private ListView<String> ExeStackListView;

    @FXML
    private TableView<Map.Entry<String, String>> FileTableView;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> FiletableBufCol;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> FiletableNameCol;

    @FXML
    private TableView<Map.Entry<String, String>> HeapTableView;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> HeapAddressCol;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> HeapValueCol;

    @FXML
    private ListView<String> OutListView;

    @FXML
    private TextField PrgStatesTextField;

    @FXML
    private ListView<Integer> ProgramIDsListView;

    @FXML
    private TableView<Map.Entry<String, String>> SymTableView;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> SymtableNameCol;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> SymtableValueCol;

    @FXML
    private TableView<Map.Entry<Map.Entry<String, String>, String>> BarrierTableView;

    @FXML
    private TableColumn<Map.Entry<Map.Entry<String, String>, String>, String> BarrierTableIndex;

    @FXML
    private TableColumn<Map.Entry<Map.Entry<String, String>, String>, String> BarrierTableValue;

    @FXML
    private TableColumn<Map.Entry<Map.Entry<String, String>, String>, String> BarrierTableList;

    @FXML
    private TableView<Map.Entry<String, String>> LockTableView;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> LockTableLocation;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> LockTableValue;

    @FXML
    private TableView<Map.Entry<String, String>> LatchTableView;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> LatchLocationTableColumn;

    @FXML
    private TableColumn<Map.Entry<String, String>, String> LatchValueTableColumn;

    @FXML
    private TableView<Map.Entry<Map.Entry<String, String>, String>> SemTableView;

    @FXML
    private TableColumn<Map.Entry<Map.Entry<String, String>, String>, String> SemTableIndex;

    @FXML
    private TableColumn<Map.Entry<Map.Entry<String, String>, String>, String> SemTableValue;

    @FXML
    private TableColumn<Map.Entry<Map.Entry<String, String>, String>, String> SemTableList;

    private List<ProgramService> programServiceList;
    private ProgramService mainProgramService;
    private List<ProgramState> programStates;
    private int programId;

    @FXML
    public void initialize() {
        programServiceList = new ArrayList<ProgramService>();

        FiletableNameCol.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getKey())
        );

        FiletableBufCol.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getValue())
        );

        HeapAddressCol.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getKey()));

        HeapValueCol.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getValue()));

        SymtableNameCol.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getKey()));

        SymtableValueCol.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getValue()));

        BarrierTableIndex.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getKey().getKey()));

        BarrierTableValue.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getKey().getValue()));

        BarrierTableList.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getValue()));

        LockTableLocation.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getKey()));

        LockTableValue.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getValue()));

        LatchLocationTableColumn.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getKey()));

        LatchValueTableColumn.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getValue()));

        SemTableIndex.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getKey().getKey()));

        SemTableValue.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getKey().getValue()));

        SemTableList.setCellValueFactory(cellData ->
                new SimpleStringProperty(cellData.getValue().getValue()));
    }

    public int getNumOfPrograms() {
        return programStates.size();
    }

    public void addProgramService(ProgramService programService) {
        programServiceList.add(programService);
    }

    public void setProgramToTest(int pos) {
        clearView();

        mainProgramService = programServiceList.get(pos);
        var repo = mainProgramService.getRepo();
        programStates = repo.getProgramStates();
        PrgStatesTextField.setText(String.valueOf(getNumOfPrograms()));
        programId = repo.getMainProgram().getProgramId();
        ProgramIDsListView.getItems().add(programId);
    }

    public void onProgramIDListViewClicked() {
        try{
            programId = ProgramIDsListView.getSelectionModel().getSelectedItem();
            populateExeStackListView(programId);
            populateSymTableView(programId);
        }
        catch (Exception e){
            IO.print("Choose a program first!");
        }

    }

    public void populateProgramIDListView() {
        ProgramIDsListView.getItems().clear();
        ProgramIDsListView.getItems().addAll(programStates.stream()
                .map(ProgramState::getProgramId)
                .toList());
    }

    public void populateExeStackListView(int programID){
        ExeStackListView.getItems().clear();
        var exeStack = mainProgramService.getRepo().getProgram(programID).exeStack();

        for(int i = exeStack.size() - 1; i > -1; --i){
            ExeStackListView.getItems().add(exeStack.get(i).toString());
        }
    }

    public void populateSymTableView(int programID){
        SymTableView.getItems().clear();
        var symTable = mainProgramService.getRepo().getProgram(programID).symTable();

        SymTableView.getItems().addAll(
                symTable.getMap().entrySet().stream()
                        .map(entry -> Map.entry(
                                entry.getKey(),                    // Already String
                                entry.getValue().toString()        // Convert Value to String
                        ))
                        .toList()
        );
    }

    public void populateHeapTableView(){
        HeapTableView.getItems().clear();
        var heapTable = mainProgramService.getRepo().getMainProgram().heapTable();

        HeapTableView.getItems().addAll(
                heapTable.getMap().entrySet().stream()
                        .map(entry -> Map.entry(
                                entry.getKey().toString(),
                                entry.getValue().toString()
                        ))
                        .toList()
        );
    }

    public void populateFileTableView(){
        FileTableView.getItems().clear();
        var fileTable = mainProgramService.getRepo().getMainProgram().fileTable();

        FileTableView.getItems().addAll(
          fileTable.getMap().entrySet().stream()
                  .map(entry -> Map.entry(
                          entry.getKey().toString(),
                          entry.getValue().toString()
                  ))
                  .toList()
        );
    }

    public void populateOutListView(){
        var output = mainProgramService.getRepo().getMainProgram().out();
        OutListView.getItems().clear();
        OutListView.getItems().addAll(output.getElements().stream().map(Object::toString).toList());
    }

    public void populateBarrierTableView(){
        var barrierTable = mainProgramService.getRepo().getMainProgram().barrierTable();
        BarrierTableView.getItems().clear();
        BarrierTableView.getItems().addAll(
                barrierTable.getMap().entrySet().stream()
                .map(entry -> Map.entry(
                        Map.entry(entry.getKey().toString(),
                                entry.getValue().getKey().toString()),
                        entry.getValue().getValue().toString()
                ))
                .toList()
        );
    }

    public void populateLockTableView(){
        LockTableView.getItems().clear();
        var lockTable = mainProgramService.getRepo().getMainProgram().lockTable();

        LockTableView.getItems().addAll(
                lockTable.getMap().entrySet().stream()
                        .map(entry -> Map.entry(
                                entry.getKey().toString(),
                                entry.getValue().toString()
                        ))
                        .toList()
        );
    }

    public void populateLatchTableView(){
        LatchTableView.getItems().clear();

        var latchTable = mainProgramService.getRepo().getMainProgram().latchTable();

        LatchTableView.getItems().addAll(
                latchTable.getMap().entrySet().stream()
                        .map(entry -> Map.entry(
                                entry.getKey().toString(),
                                entry.getValue().toString()
                        ))
                        .toList()
        );
    }

    public void populateSemTableView(){
        var semTable = mainProgramService.getRepo().getMainProgram().semaphoreTable();
        SemTableView.getItems().clear();
        SemTableView.getItems().addAll(
                semTable.getMap().entrySet().stream()
                        .map(entry -> Map.entry(
                                Map.entry(entry.getKey().toString(),
                                        entry.getValue().getKey().toString()),
                                entry.getValue().getValue().toString()
                        ))
                        .toList()
        );
    }

    // similar to executeMainProgram() but for the gui
    public void clickOneStep() throws ProgramException, InterruptedException {
        try{
            if (programStates.isEmpty()) {
                mainProgramService.getExecutor().shutdownNow();
                mainProgramService.getRepo().setProgramStates(programStates);
                IO.print("Program has been terminated!");
                return;
            }
        }
        catch (Exception e){
            IO.print("Choose a program first!");
        }

        try{
            programStates = mainProgramService.removeCompletedPrograms(mainProgramService.getRepo().getProgramStates());
            var allSymbolTables = programStates.stream()
                    .map(ProgramState::symTable)
                    .toList();
            mainProgramService.getGarbageCollector().run(allSymbolTables, programStates.getFirst().heapTable());
            mainProgramService.executeOneStepForAllPrograms(programStates);
            programStates = mainProgramService.removeCompletedPrograms(mainProgramService.getRepo().getProgramStates());

            PrgStatesTextField.setText(String.valueOf(getNumOfPrograms()));
            populateProgramIDListView();
            populateFileTableView();
            populateOutListView();
            populateHeapTableView();
            populateExeStackListView(programId);
            populateSymTableView(programId);
            populateBarrierTableView();
            populateLockTableView();
            populateLatchTableView();
            populateSemTableView();
        }
        catch (Exception e){
            IO.print("Unexpected error:\n" + e.getMessage());
        }
    }

    public void clearView(){
        ExeStackListView.getItems().clear();
        FileTableView.getItems().clear();
        HeapTableView.getItems().clear();
        ProgramIDsListView.getItems().clear();
        SymTableView.getItems().clear();
        PrgStatesTextField.clear();
        BarrierTableView.getItems().clear();
        LockTableView.getItems().clear();
        LatchTableView.getItems().clear();
        SemTableView.getItems().clear();
    }
}
