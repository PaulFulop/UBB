package exceptions;

public class ValueNotFoundException extends RuntimeException {
    public ValueNotFoundException() {super("Value not found");}
    public ValueNotFoundException(String message) {
        super(message);
    }
}
