import controller.GarbageCollector;
import controller.ProgramService;
import controller.javafx_controller.MainController;
import controller.javafx_controller.ProgramsController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import model.expressions.*;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.RefType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;
import repo.ArrayListRepository;
import repo.Repository;
import view.ExitCommand;
import view.RunProgramCommand;
import view.TextMenu;

import java.util.ArrayList;
import java.util.List;

public class MainFX extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        // load views
        FXMLLoader primaryLoader = new FXMLLoader(getClass().getResource("view/javafx_view/MainView.fxml"));
        FXMLLoader secondaryLoader = new FXMLLoader(getClass().getResource("view/javafx_view/ProgramsView.fxml"));

        Scene primaryScene = new Scene(primaryLoader.load());
        primaryStage.setScene(primaryScene);
        primaryStage.setTitle("My Interpreter");


        Scene secondaryScene = new Scene(secondaryLoader.load());
        Stage secondaryStage = new Stage();
        secondaryStage.setScene(secondaryScene);
        secondaryStage.setTitle("All Programs");

        // initialize controllers with the hard-coded data
        MainController mainController = primaryLoader.getController();
        ProgramsController programsController = secondaryLoader.getController();
        populateControllers(mainController, programsController);
        programsController.setMainController(mainController);

        // show the stages
        primaryStage.show();
        secondaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    private void populateControllers(MainController mainController, ProgramsController programsController) {
        List<ProgramService> programs = new ArrayList<>();

        // int v; v = 2; Print(v)
        StatementInterface ex1 = new CompoundStatement(
                new VariableDeclarationStatement("v", IntType.INSTANCE),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))
                )
        );

        // int a; int b; a = 2 + 3 * 5; b = a + 1; Print(b)
        StatementInterface ex2 = new CompoundStatement(
                new VariableDeclarationStatement("a", IntType.INSTANCE),
                new CompoundStatement(
                        new VariableDeclarationStatement("b", IntType.INSTANCE),
                        new CompoundStatement(
                                new AssignStatement(
                                        "a",
                                        new ArithmeticExpression(
                                                "+",
                                                new ValueExpression(new IntValue(2)),
                                                new ArithmeticExpression(
                                                        "*",
                                                        new ValueExpression(new IntValue(3)),
                                                        new ValueExpression(new IntValue(5))
                                                )
                                        )
                                ),
                                new CompoundStatement(
                                        new AssignStatement(
                                                "b",
                                                new ArithmeticExpression(
                                                        "+",
                                                        new VariableExpression("a"),
                                                        new ValueExpression(new IntValue(1))
                                                )
                                        ),
                                        new PrintStatement(new VariableExpression("b"))
                                )
                        )
                )
        );

        // bool a; int v; a = true; (If a Then v = 2 Else v = 3); Print(v)
        StatementInterface ex3 = new CompoundStatement(
                new VariableDeclarationStatement("a", BoolType.INSTANCE),
                new CompoundStatement(
                        new VariableDeclarationStatement("v", IntType.INSTANCE),
                        new CompoundStatement(
                                new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompoundStatement(
                                        new IfStatement(
                                                new VariableExpression("a"),
                                                new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                                new AssignStatement("v", new ValueExpression(new IntValue(3)))
                                        ),
                                        new PrintStatement(new VariableExpression("v"))
                                )
                        )
                )
        );


        // string varf; varf="test.in"; openRFile(varf); int varc; readFile(varf,varc);print(varc);readFile(varf,varc);print(varc);closeRFile(varf)
        StatementInterface ex4 =
                new CompoundStatement(
                        new VariableDeclarationStatement("varf", StringType.INSTANCE),
                        new CompoundStatement(
                                new AssignStatement("varf", new ValueExpression(new StringValue("src/test.in"))),
                                new CompoundStatement(
                                        new OpenFileStatement(new VariableExpression("varf")),
                                        new CompoundStatement(
                                                new VariableDeclarationStatement("varc", IntType.INSTANCE),
                                                new CompoundStatement(
                                                        new ReadFileStatement(
                                                                new VariableExpression("varf"),
                                                                new VariableExpression("varc").toString()
                                                        ),
                                                        new CompoundStatement(
                                                                new PrintStatement(new VariableExpression("varc")),
                                                                new CompoundStatement(
                                                                        new ReadFileStatement(
                                                                                new VariableExpression("varf"),
                                                                                new VariableExpression("varc").toString()
                                                                        ),
                                                                        new CompoundStatement(
                                                                                new PrintStatement(new VariableExpression("varc")),
                                                                                new CloseFileStatement(new VariableExpression("varf"))
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                );

        // int v; string str; v = 5; (If v < 10 Then str = "less" Else v = "greater"); Print(str)
        StatementInterface ex5 = new CompoundStatement(
                new VariableDeclarationStatement("v", IntType.INSTANCE),
                new CompoundStatement(
                        new VariableDeclarationStatement("str", StringType.INSTANCE),
                        new CompoundStatement(
                                new AssignStatement("v", new ValueExpression(new IntValue(5))),
                                new CompoundStatement(
                                        new IfStatement(
                                                new RelationalExpression("<", new VariableExpression("v"), new ValueExpression(new IntValue(10))),
                                                new AssignStatement("str", new ValueExpression(new StringValue("less"))),
                                                new AssignStatement("str", new ValueExpression(new StringValue("greater")))
                                        ),
                                        new PrintStatement(new VariableExpression("str"))
                                )
                        )
                )
        );



        // Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
        StatementInterface ex6 =
                new CompoundStatement(
                        new VariableDeclarationStatement("v", new RefType(IntType.INSTANCE)),
                        new CompoundStatement(
                                new HeapAllocationStatement(
                                        "v",
                                        new ValueExpression(new IntValue(20))
                                ),
                                new CompoundStatement(
                                        new VariableDeclarationStatement(
                                                "a",
                                                new RefType(new RefType(IntType.INSTANCE))
                                        ),
                                        new CompoundStatement(
                                                new HeapAllocationStatement(
                                                        "a",
                                                        new VariableExpression("v")
                                                ),
                                                new CompoundStatement(
                                                        new PrintStatement(new VariableExpression("v")),
                                                        new PrintStatement(new VariableExpression("a"))
                                                )
                                        )
                                )
                        )
                );

        // Ref int v;new(v,20);Ref Ref int a; new(a,v);print(rH(v));print(rH(rH(a))+5)
        StatementInterface ex7 =
                new CompoundStatement(
                        new VariableDeclarationStatement(
                                "v",
                                new RefType(IntType.INSTANCE)
                        ),
                        new CompoundStatement(
                                new HeapAllocationStatement(
                                        "v",
                                        new ValueExpression(new IntValue(20))
                                ),
                                new CompoundStatement(
                                        new VariableDeclarationStatement(
                                                "a",
                                                new RefType(new RefType(IntType.INSTANCE))
                                        ),
                                        new CompoundStatement(
                                                new HeapAllocationStatement(
                                                        "a",
                                                        new VariableExpression("v")
                                                ),
                                                new CompoundStatement(
                                                        new PrintStatement(
                                                                new HeapReadingExpression(
                                                                        new VariableExpression("v")
                                                                )
                                                        ),
                                                        new PrintStatement(
                                                                new ArithmeticExpression(
                                                                        "+",
                                                                        new HeapReadingExpression(
                                                                                new HeapReadingExpression(
                                                                                        new VariableExpression("a")
                                                                                )
                                                                        ),
                                                                        new ValueExpression(new IntValue(5))
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                );


        //Ref int v;new(v,20);print(rH(v)); wH(v,30);print(rH(v)+5);
        StatementInterface ex8 =
                new CompoundStatement(
                        new VariableDeclarationStatement(
                                "v",
                                new RefType(IntType.INSTANCE)
                        ),
                        new CompoundStatement(
                                new HeapAllocationStatement(
                                        "v",
                                        new ValueExpression(new IntValue(20))
                                ),
                                new CompoundStatement(
                                        new PrintStatement(
                                                new HeapReadingExpression(
                                                        new VariableExpression("v")
                                                )
                                        ),
                                        new CompoundStatement(
                                                new HeapWritingStatement(
                                                        "v",
                                                        new ValueExpression(new IntValue(30))
                                                ),
                                                new PrintStatement(
                                                        new ArithmeticExpression(
                                                                "+",
                                                                new HeapReadingExpression(
                                                                        new VariableExpression("v")
                                                                ),
                                                                new ValueExpression(new IntValue(5))
                                                        )
                                                )
                                        )
                                )
                        )
                );

        //Ref int v;new(v,20);Ref Ref int a; new(a,v); new(v,30);print(rH(rH(a)))
        StatementInterface ex9 =
                new CompoundStatement(
                        new VariableDeclarationStatement(
                                "v",
                                new RefType(IntType.INSTANCE)
                        ),
                        new CompoundStatement(
                                new HeapAllocationStatement(
                                        "v",
                                        new ValueExpression(new IntValue(20))
                                ),
                                new CompoundStatement(
                                        new VariableDeclarationStatement(
                                                "a",
                                                new RefType(new RefType(IntType.INSTANCE))
                                        ),
                                        new CompoundStatement(
                                                new HeapAllocationStatement(
                                                        "a",
                                                        new VariableExpression("v")
                                                ),
                                                new CompoundStatement(
                                                        new HeapAllocationStatement(
                                                                "v",
                                                                new ValueExpression(new IntValue(30))
                                                        ),
                                                        new PrintStatement(
                                                                new HeapReadingExpression(
                                                                        new HeapReadingExpression(
                                                                                new VariableExpression("a")
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                );


        // Ref int v; new(v,20); new(v,30); print(rH(v)) -> HERE WE SHOULD HAVE GARBAGE
        StatementInterface ex10 =
                new CompoundStatement(
                        new VariableDeclarationStatement(
                                "v",
                                new RefType(IntType.INSTANCE)
                        ),
                        new CompoundStatement(
                                new HeapAllocationStatement(
                                        "v",
                                        new ValueExpression(new IntValue(20))
                                ),
                                new CompoundStatement(
                                        new HeapAllocationStatement(
                                                "v",
                                                new ValueExpression(new IntValue(30))
                                        ),
                                        new PrintStatement(
                                                new HeapReadingExpression(
                                                        new VariableExpression("v")
                                                )
                                        )
                                )
                        )
                );

        // int v; v=4; (while (v>0) print(v);v=v-1);print(v)
        StatementInterface ex11 =
                new CompoundStatement(
                        new VariableDeclarationStatement("v", IntType.INSTANCE),
                        new CompoundStatement(
                                new AssignStatement("v", new ValueExpression(new IntValue(4))),
                                new CompoundStatement(
                                        new WhileStatement(
                                                new RelationalExpression(
                                                        ">",
                                                        new VariableExpression("v"),
                                                        new ValueExpression(new IntValue(0))
                                                ),
                                                new CompoundStatement(
                                                        new PrintStatement(new VariableExpression("v")),
                                                        new AssignStatement(
                                                                "v",
                                                                new ArithmeticExpression(
                                                                        "-",
                                                                        new VariableExpression("v"),
                                                                        new ValueExpression(new IntValue(1))
                                                                )
                                                        )
                                                )
                                        ),
                                        new PrintStatement(new VariableExpression("v"))
                                )
                        )
                );

        //int v; Ref int a; v=10;new(a,22);
        //fork(wH(a,30);v=32;print(v);print(rH(a)));
        //print(v);print(rH(a))
        StatementInterface ex12 =
                new CompoundStatement(
                        new VariableDeclarationStatement("v", IntType.INSTANCE),
                        new CompoundStatement(
                                new VariableDeclarationStatement(
                                        "a",
                                        new RefType(IntType.INSTANCE)
                                ),
                                new CompoundStatement(
                                        new AssignStatement(
                                                "v",
                                                new ValueExpression(new IntValue(10))
                                        ),
                                        new CompoundStatement(
                                                new HeapAllocationStatement(
                                                        "a",
                                                        new ValueExpression(new IntValue(22))
                                                ),
                                                new CompoundStatement(
                                                        new ForkStatement(
                                                                new CompoundStatement(
                                                                        new HeapWritingStatement(
                                                                                "a",
                                                                                new ValueExpression(new IntValue(30))
                                                                        ),
                                                                        new CompoundStatement(
                                                                                new AssignStatement(
                                                                                        "v",
                                                                                        new ValueExpression(new IntValue(32))
                                                                                ),
                                                                                new CompoundStatement(
                                                                                        new PrintStatement(new VariableExpression("v")),
                                                                                        new PrintStatement(
                                                                                                new HeapReadingExpression(
                                                                                                        new VariableExpression("a")
                                                                                                )
                                                                                        )
                                                                                )
                                                                        )
                                                                )
                                                        ),
                                                        new CompoundStatement(
                                                                new PrintStatement(new VariableExpression("v")),
                                                                new PrintStatement(
                                                                        new HeapReadingExpression(
                                                                                new VariableExpression("a")
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                );

//        int v; int x; int y; v=0;
//        (repeat (fork(print(v);v=v-1);v=v+1) until v==3);
//        x=1;nop;y=3;nop;
//        print(v*10)

        //new AssignStatement("v", new ArithmeticExpression("-", new VariableExpression("v"), new ValueExpression(new IntValue(1)))))
        StatementInterface ex13 =
                new CompoundStatement(
                        new VariableDeclarationStatement("v", IntType.INSTANCE),
                        new CompoundStatement(
                                new VariableDeclarationStatement("x", IntType.INSTANCE),
                                new CompoundStatement(
                                        new VariableDeclarationStatement("y", IntType.INSTANCE),
                                        new CompoundStatement(
                                                new AssignStatement(
                                                        "v",
                                                        new ValueExpression(new IntValue(0))
                                                ),
                                                new CompoundStatement(
                                                        new RepeatUntilStatement(
                                                                new CompoundStatement(
                                                                        new ForkStatement(
                                                                                new CompoundStatement(
                                                                                        new PrintStatement(
                                                                                                new VariableExpression("v")
                                                                                        ),
                                                                                        new AssignStatement(
                                                                                                "v",
                                                                                                new ArithmeticExpression(
                                                                                                        "-",
                                                                                                        new VariableExpression("v"),
                                                                                                        new ValueExpression(new IntValue(1))
                                                                                                )
                                                                                        )
                                                                                )
                                                                        ),
                                                                        new AssignStatement(
                                                                                "v",
                                                                                new ArithmeticExpression(
                                                                                        "+",
                                                                                        new VariableExpression("v"),
                                                                                        new ValueExpression(new IntValue(1))
                                                                                )
                                                                        )
                                                                ),
                                                                new RelationalExpression(
                                                                        "==",
                                                                        new VariableExpression("v"),
                                                                        new ValueExpression(new IntValue(3))
                                                                )
                                                        ),
                                                        new CompoundStatement(
                                                                new AssignStatement(
                                                                        "x",
                                                                        new ValueExpression(new IntValue(1))
                                                                ),
                                                                new CompoundStatement(
                                                                        new NoOperationStatement(),
                                                                        new CompoundStatement(
                                                                                new AssignStatement(
                                                                                        "y",
                                                                                        new ValueExpression(new IntValue(3))
                                                                                ),
                                                                                new CompoundStatement(
                                                                                        new NoOperationStatement(),
                                                                                        new PrintStatement(
                                                                                                new ArithmeticExpression(
                                                                                                        "*",
                                                                                                        new ValueExpression(new IntValue(10)),
                                                                                                        new VariableExpression("v")
                                                                                                )
                                                                                        )
                                                                                )
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                );

        Repository repository1 = new ArrayListRepository("src/logs/log1.txt");
        ProgramService programServ1 = new ProgramService(repository1);
        programServ1.addNewProgram(ex1);
        programsController.addProgramTxt(ex1.toString());
        mainController.addProgramService(programServ1);

        Repository repository2 = new ArrayListRepository("src/logs/log2.txt");
        ProgramService programServ2 = new ProgramService(repository2);
        programServ2.addNewProgram(ex2);
        programsController.addProgramTxt(ex2.toString());
        mainController.addProgramService(programServ2);


        Repository repository3 = new ArrayListRepository("src/logs/log3.txt");
        ProgramService programServ3 = new ProgramService(repository3);
        programServ3.addNewProgram(ex3);
        programsController.addProgramTxt(ex3.toString());
        mainController.addProgramService(programServ3);

        Repository repository4 = new ArrayListRepository("src/logs/log4.txt");
        ProgramService programServ4 = new ProgramService(repository4);
        programServ4.addNewProgram(ex4);
        programsController.addProgramTxt(ex4.toString());
        mainController.addProgramService(programServ4);

        Repository repository5 = new ArrayListRepository("src/logs/log5.txt");
        ProgramService programServ5 = new ProgramService(repository5);
        programServ5.addNewProgram(ex5);
        programsController.addProgramTxt(ex5.toString());
        mainController.addProgramService(programServ5);

        Repository repository6 = new ArrayListRepository("src/logs/log6.txt");
        ProgramService programServ6 = new ProgramService(repository6);
        programServ6.addNewProgram(ex6);
        programsController.addProgramTxt(ex6.toString());
        mainController.addProgramService(programServ6);


        Repository repository7 = new ArrayListRepository("src/logs/log7.txt");
        ProgramService programServ7 = new ProgramService(repository7);
        programServ7.addNewProgram(ex7);
        programsController.addProgramTxt(ex7.toString());
        mainController.addProgramService(programServ7);


        Repository repository8 = new ArrayListRepository("src/logs/log8.txt");
        ProgramService programServ8 = new ProgramService(repository8);
        programServ8.addNewProgram(ex8);
        programsController.addProgramTxt(ex8.toString());
        mainController.addProgramService(programServ8);

        Repository repository9 = new ArrayListRepository("src/logs/log9.txt");
        ProgramService programServ9 = new ProgramService(repository9);
        programServ9.addNewProgram(ex9);
        programsController.addProgramTxt(ex9.toString());
        mainController.addProgramService(programServ9);


        Repository repository10 = new ArrayListRepository("src/logs/log10.txt");
        ProgramService programServ10 = new ProgramService(repository10);
        programServ10.addNewProgram(ex10);
        programsController.addProgramTxt(ex10.toString());
        mainController.addProgramService(programServ10);

        Repository repository11 = new ArrayListRepository("src/logs/log11.txt");
        ProgramService programServ11 = new ProgramService(repository11);
        programServ11.addNewProgram(ex11);
        programsController.addProgramTxt(ex11.toString());
        mainController.addProgramService(programServ11);


        Repository repository12 = new ArrayListRepository("src/logs/log12.txt");
        ProgramService programServ12 = new ProgramService(repository12);
        programServ12.addNewProgram(ex12);
        programsController.addProgramTxt(ex12.toString());
        mainController.addProgramService(programServ12);


        Repository repository13 = new ArrayListRepository("src/logs/log13.txt");
        ProgramService programServ13 = new ProgramService(repository13);
        programServ13.addNewProgram(ex13);
        programsController.addProgramTxt(ex13.toString());
        mainController.addProgramService(programServ13);
    }
}