package model.states;

import com.sun.source.tree.BinaryTree;
import com.sun.source.tree.ExpressionTree;
import exceptions.EmptyCollectionException;
import exceptions.MyException;
import model.statements.StatementInterface;

import java.util.Stack;

//Note that each stack position must be saved as a
//string that contains the statement which is on that position of the stack.

public class LinkedListExecutionStack implements ExecutionStackInterface {
    Stack<StatementInterface> stack;

    public LinkedListExecutionStack() {
        stack = new Stack<>();
    }

    @Override
    public StatementInterface pop() throws EmptyCollectionException {
        if (isEmpty()) throw new EmptyCollectionException();
        return stack.pop();
    }

    @Override
    public void push(StatementInterface v) {
        stack.push(v);
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public String toString() {
        String text = "";
        for (int i = stack.size() - 1; i >= 0; i--) {
            text += stack.get(i).toString() + '\n';
        }

        return text;
    }
}
