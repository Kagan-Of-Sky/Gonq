/*
 * Purpose - This is the front end menu for the user. It allows the
 *           user to perform various operations on a Dictionary
 *           object.
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

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.InputMismatchException;
import java.util.Scanner;


public class Main {
	/** Clear the dictionary. */
	private static final int OPTION_CLEAR_DICTIONARY = 1;
	
	/** Add a word to the dictionary from the standard input. */
	private static final int OPTION_ADD_KEYBOARD = 2;
	
	/** Read through a file and add every word from it to the dictionary. */
	private static final int OPTION_ADD_FILE = 3;
	
	/** Get the word count for a specific word. */
	private static final int OPTION_WORD_COUNT = 4;
	
	/** Display the number of nodes in the dictionary (number of unique word). */
	private static final int OPTION_NUM_NODES = 5;
	
	/** Quit the program. */
	private static final int OPTION_QUIT = 6;
	
	public static void main(String args[]) {
		Scanner stdinReader   = new Scanner(System.in);
		Dictionary dictionary = new Dictionary();
		int choice = -1;
		
		while(choice != OPTION_QUIT){
			/* Get the users choice. */
			printMenu();
			System.out.print("Choice: ");
			try{
				choice = stdinReader.nextInt();
			}
			catch(InputMismatchException e){
				System.out.println("ERROR: Invalid Input, please enter a choice from 1 to 6.");
				choice = -1;
				continue;
			}
			finally {
				stdinReader.nextLine();
			}
			
			/* Carry out that choice. */
			switch(choice){
				case OPTION_CLEAR_DICTIONARY: {
					dictionary.clear();
					System.out.println("Dictionary cleared.");
					break;
				}
				case OPTION_ADD_KEYBOARD: {
					System.out.print("Enter a word: ");
					
					if(dictionary.addWord(stdinReader.nextLine())){
						System.out.println("Word added to dictionary.");
					}
					else{
						System.out.println("ERROR: The string you entered is not a word.");
					}
					break;
				}
				case OPTION_ADD_FILE: {
					/* Get the file path. */
					System.out.print("Enter the file path: ");
					String filePath = stdinReader.nextLine();
					
					/* Read through the file. */
					try(Scanner fileReader = new Scanner(new File(filePath))){
						while(fileReader.hasNext()){
							String word = fileReader.next();
							dictionary.addWord(word);
						}
					}
					catch(FileNotFoundException e){
						System.out.println("ERROR: This file does not exist.");
					}
					catch(IOException e){
						System.out.println("ERROR: An error occured while reading the file.");
					}
					break;
				}
				case OPTION_WORD_COUNT: {
					/* Get the word from the user. */
					System.out.print("Enter the word to search for: ");
					String word = stdinReader.nextLine();
					
					/* Get the number of occurrences. */
					Integer numOccurances = dictionary.countOccurances(word);
					if(numOccurances == null){
						System.out.printf("The word '%s' does not appear in the dictionary.\n", word);
					}
					else{
						System.out.printf("The word '%s' appears %d times in the dictionary.\n", word, numOccurances);
					}
					break;
				}
				case OPTION_NUM_NODES: {
					System.out.println("Node Count: " + dictionary.nodeCount());
					break;
				}
				case OPTION_QUIT: {
					System.out.println("Quitting...");
					break;
				}
				
				/* Invalid choice. */
				default: {
					System.out.println("ERROR: Choice out of range. Please enter a choice from 1 to 6.");
					break;
				}
			}
		}
		
	}
	
	/** Simply prints out the menu used in this program. */
	public static void printMenu(){
		System.out.println();
		System.out.println();
		System.out.println("1 - Clear dictionary");
		System.out.println("2 - Add word from keyboard");
		System.out.println("3 - Add text from file");
		System.out.println("4 - Search for word count");
		System.out.println("5 - Display number of nodes");
		System.out.println("6 - Quit");
	}
	
}