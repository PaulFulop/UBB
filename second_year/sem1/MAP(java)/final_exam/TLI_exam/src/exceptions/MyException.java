package exceptions;

public class MyException extends Exception {
    public MyException() {
        super("Invalid message from my own exception");
    }

    public MyException(String message) {
        super(message);
    }
}
