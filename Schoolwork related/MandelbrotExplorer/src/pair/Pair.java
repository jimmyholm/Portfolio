package pair;

/**
 * Simple generic tuple class
 * @author Jimmy Holm
 *
 * @param <F> Type of the first item in the tuple
 * @param <S> Type of the second item in the tuple
 */
public class Pair<F, S> {
	private F First;
	private S Second;
	
	public Pair() {
		First = null;
		Second = null;
	}
	
	public Pair(F First, S Second) {
		this.First = First;
		this.Second = Second;
	}
	
	/**
	 * Retrieve the first of the tuple's two elements
	 * @return The first element in the tuple
	 */
	public F First() {
		return First;
	}
	
	/**
	 * Retrieve the second of the tuple's two elements
	 * @return The second element in the tuple
	 */
	public S Second() {
		return Second;
	}
}
