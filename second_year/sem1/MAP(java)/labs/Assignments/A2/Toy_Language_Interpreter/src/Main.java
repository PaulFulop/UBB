import controller.Controller;
import controller.GarbageCollector;
import exceptions.MyException;
import model.expressions.*;
import model.statements.*;
import model.states.Heap;
import model.states.ProgramState;
import model.types.BoolType;
import model.types.IntType;
import model.types.RefType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import repo.ArrayListRepository;
import repo.Repository;
import view.ExitCommand;
import view.RunProgramCommand;
import view.TextMenu;
import java.util.Scanner;

void main() {

    // TODO make the whole interpreter thread-safe
    // TODO conservativeGarbageCollector -> i'll see about this.
    // When you prepare the arguments of the conservativeGarbageCollector call you must take into
    //account the fact that now there is one HEAP shared by multiple PrgStates and multiple
    //SymbolTables(one for each PrgState).

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


    Repository repository1 = new ArrayListRepository("src/logs/log1.txt");
    Controller controller1 = new Controller(repository1, new GarbageCollector());
    controller1.addNewProgram(ex1);

    Repository repository2 = new ArrayListRepository("src/logs/log2.txt");
    Controller controller2 = new Controller(repository2, new GarbageCollector());
    controller2.addNewProgram(ex2);


    Repository repository3 = new ArrayListRepository("src/logs/log3.txt");
    Controller controller3 = new Controller(repository3, new GarbageCollector());
    controller3.addNewProgram(ex3);

    Repository repository4 = new ArrayListRepository("src/logs/log4.txt");
    Controller controller4 = new Controller(repository4, new GarbageCollector());
    controller4.addNewProgram(ex4);

    Repository repository5 = new ArrayListRepository("src/logs/log5.txt");
    Controller controller5 = new Controller(repository5, new GarbageCollector());
    controller5.addNewProgram(ex5);

    Repository repository6 = new ArrayListRepository("src/logs/log6.txt");
    Controller controller6 = new Controller(repository6, new GarbageCollector());
    controller6.addNewProgram(ex6);


    Repository repository7 = new ArrayListRepository("src/logs/log7.txt");
    Controller controller7 = new Controller(repository7,new GarbageCollector());
    controller7.addNewProgram(ex7);


    Repository repository8 = new ArrayListRepository("src/logs/log8.txt");
    Controller controller8 = new Controller(repository8, new GarbageCollector());
    controller8.addNewProgram(ex8);

    Repository repository9 = new ArrayListRepository("src/logs/log9.txt");
    Controller controller9 = new Controller(repository9, new GarbageCollector());
    controller9.addNewProgram(ex9);


    Repository repository10 = new ArrayListRepository("src/logs/log10.txt");
    Controller controller10 = new Controller(repository10, new GarbageCollector());
    controller10.addNewProgram(ex10);


    Repository repository11 = new ArrayListRepository("src/logs/log11.txt");
    Controller controller11 = new Controller(repository11, new GarbageCollector());
    controller11.addNewProgram(ex11);


    Repository repository12 = new ArrayListRepository("src/logs/log12.txt");
    Controller controller12 = new Controller(repository12, new GarbageCollector());
    controller12.addNewProgram(ex12);

    TextMenu textMenu = new TextMenu();
    textMenu.addCommand(new ExitCommand("0", "exit"));
    textMenu.addCommand(new RunProgramCommand("1", ex1.toString(), controller1));
    textMenu.addCommand(new RunProgramCommand("2", ex2.toString(), controller2));
    textMenu.addCommand(new RunProgramCommand("3", ex3.toString(), controller3));
    textMenu.addCommand(new RunProgramCommand("4", ex4.toString(), controller4));
    textMenu.addCommand(new RunProgramCommand("5", ex5.toString(), controller5));
    textMenu.addCommand(new RunProgramCommand("6", ex6.toString(), controller6));
    textMenu.addCommand(new RunProgramCommand("7", ex7.toString(), controller7));
    textMenu.addCommand(new RunProgramCommand("8", ex8.toString(), controller8));
    textMenu.addCommand(new RunProgramCommand("9", ex9.toString(), controller9));
    textMenu.addCommand(new RunProgramCommand("10", ex10.toString(), controller10));
    textMenu.addCommand(new RunProgramCommand("11", ex11.toString(), controller11));
    textMenu.addCommand(new RunProgramCommand("12", ex12.toString(), controller12));
    textMenu.show();

}