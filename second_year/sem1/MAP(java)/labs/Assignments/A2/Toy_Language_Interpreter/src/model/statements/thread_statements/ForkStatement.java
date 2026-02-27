package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.*;
import model.states.map.tables.TypeTable;
import model.states.stack.ExecutionStack;

public record ForkStatement(StatementInterface statement) implements StatementInterface {

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        var executionStack = new ExecutionStack();
        executionStack.push(statement);

//        var newSymbolTable = new SymbolTable();
//        for (var elem : state.symTable().getMap().entrySet()) {
//            newSymbolTable.add(elem.getKey(), elem.getValue().copy());
//        }

        return new ProgramState(
                executionStack,
                state.symTable().deepcopy(), // -> a copy of it, not reference
                state.out(),
                state.fileTable(),
                state.heapTable(),
                state.barrierTable(),
                state.lockTable(),
                state.latchTable(),
                state.semaphoreTable());
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        // WHY DO I NEED TO CLONE THE TYPE TABLE?
        // If the child process after fork contains variable declarations
        //int temp = 5;  -> temp added to typeTable in some program
        //fork(string temp = "hi"); -> creating a child process which creates a new variable inside it
        //                          -> different temp, should be in separate scope

        statement.typecheck(typeTable.deepcopy());
        return typeTable;
    }

    @Override
    public String toString() {
        return "fork( " + statement.toString() + " )";
    }
}
