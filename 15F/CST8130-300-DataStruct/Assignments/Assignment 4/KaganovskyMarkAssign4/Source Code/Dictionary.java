/*
 * Purpose - This class represents a dictionary which stores the word,
 *           along with the number of times that word occurs.<br>
 *           It does not store the definition of that word.
 * 
 * Name ---- Mark Kaganovsky
 * 
 * Date ---- December 2, 2015
 * 
 * Course -- CST8130 Data Structures
 * 
 * Section - 302
 * 
 * Methods - Please refer to the JavaDoc comments above every method.
 * 
 * Fields -- Please refer to the JavaDoc comments above every field.
 */

import java.util.Map;
import java.util.TreeMap;

/**
 * This class represents a dictionary which stores the word, along with the number of times that word occurs.<br>
 * It does not store the definition of that word.
 * 
 * @author Mark Kaganovsky
 */
public class Dictionary {
	/** Maps a word to the number of times it occurs. */
	private Map<String, Integer> dictionary;
	
	/**
	 * Creates a new empty dictionary.
	 */
	public Dictionary() {
		dictionary = new TreeMap<>();
	}
	
	/**
	 * Clears the dictionary to a size of 0.
	 */
	public void clear(){
		dictionary.clear();
	}
	
	/**
	 * Adds a word to a dictionary. First it processes the word to remove non-alphabetic characters.<br><br>
	 * 
	 * If the word already exists in the dictionary, then it increments the Integer count of
	 * that word, otherwise it adds the word to the dictionary with a count of 1. If the length
	 * of the word is 0 after being processed, then the word is not added.
	 * 
	 * @param string The word to add.
	 * 
	 * @return True if the word was added, False if the word 
	 *         was a length of 0 after being processed.
	 */
	public boolean addWord(String string){
		/* Process the word to remove non-alphabetic characters. */
		string = string.replaceAll("[^a-zA-Z]", "").toLowerCase();
		
		/* Add the word to the dictionary. */
		if(string.length() > 0){
			Integer value = dictionary.get(string);
			/* Does not exist yet. */
			if(value == null){
				dictionary.put(string, 1);
			}
			else{
				dictionary.put(string, value+1);
			}
			return true;
		}
		
		return false;	
	}
	
	/**
	 * @param string The string to search the dictionary for.
	 * @return The number of times the string occurs in the dictionary. 
	 */
	public Integer countOccurances(String string){
		/* Process the word to remove non-alphabetic characters. */
		string = string.replaceAll("[^a-zA-Z]", "").toLowerCase();
		
		return dictionary.get(string);
	}
	
	/**
	 * Returns the number of node in the dicitonary (number of unique words). 
	 * @return
	 */
	public int nodeCount(){
		return dictionary.size();
	}
}
