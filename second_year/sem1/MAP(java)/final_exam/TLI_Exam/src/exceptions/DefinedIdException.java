package exceptions;

public class DefinedIdException extends RuntimeException {
    public DefinedIdException(String id) {super("Id " + id + " is already defined");}
}
