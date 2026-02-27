package model.states.stack;

import model.statements.StatementInterface;

public class ExecutionStack extends MyStack<StatementInterface> {
    public ExecutionStack deepcopy () {
        ExecutionStack stackCopy = new ExecutionStack();
        for(var elem : stack)
            stackCopy.push(elem);

        return stackCopy;
    }
}
