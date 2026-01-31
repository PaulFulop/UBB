package exceptions;

public class FullCollectionException extends RuntimeException {
    public FullCollectionException() {super("Collection is full");}
    public FullCollectionException(String message) {
        super(message);
    }
}
