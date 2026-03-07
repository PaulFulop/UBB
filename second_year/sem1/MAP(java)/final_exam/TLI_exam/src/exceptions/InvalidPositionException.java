package exceptions;

public class InvalidPositionException extends RuntimeException {
    public InvalidPositionException(int pos) {
        super("Trying to access position " + pos + ", which is invalid");
    }

  public InvalidPositionException(String message) {
    super(message);
  }
}
