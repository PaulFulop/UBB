package exceptions;

public class UndefinedIdException extends RuntimeException {
    public UndefinedIdException(String id) {super("Undefined id " + id);}
}
