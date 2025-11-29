package exceptions;

public class LogProgramStateException extends RuntimeException {
    public LogProgramStateException() {
        super("Error when logging the state of the program to the file.");
    }
    public LogProgramStateException(String message) {
        super(message);
    }
}
