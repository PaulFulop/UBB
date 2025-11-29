package exceptions;

public class ProgramException extends RuntimeException {
    public ProgramException() {
        super("Program Exception, something went wrong (probably the exe stack was empty).");
    }
    public ProgramException(String message) {
        super(message);
    }
}
