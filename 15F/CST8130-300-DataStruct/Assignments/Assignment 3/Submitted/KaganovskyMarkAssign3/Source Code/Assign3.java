/*
 * Purpose - Retrieves file names from the user, opens the files, 
 *           fills the Course object and then processes every student
 *           in the student file, printing out their grades after processing
 *           each student.
 * 
 * Name ---- Mark Kaganovsky
 * 
 * Date ---- November 18, 2015
 * 
 * Course -- CST8130 Data Structures
 * 
 * Section - 302
 * 
 * Methods - Please refer to the JavaDoc comments above every method.
 * 
 * Fields -- None.
 */

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Assign3 {
	public static void main(String[] args) {
		String  courseInfoFilePath;
		Scanner courseInfoFileReader = null;
		
		String  studentFilePath;
		Scanner studentFileReader = null;
		
		Scanner keyboardReader = new Scanner(System.in);
		
		Course course;
		
		
		
		
		/* Open the course info file. */
		System.out.print("Enter the name of the course file to process: ");
		courseInfoFilePath = keyboardReader.nextLine();
		try{
			courseInfoFileReader = new Scanner(new FileReader(courseInfoFilePath));
		}
		catch(FileNotFoundException e){
			System.out.println("ERROR: Could not open file: " + courseInfoFilePath);
			return;
		}
		
		
		
		
		/* Read the Course file. */
		try{
			course = new Course(courseInfoFileReader);
			courseInfoFileReader.close();
		}
		catch(InputMismatchException e){
			System.out.println("ERROR: Course info file not in correct format: " + courseInfoFilePath);
			courseInfoFileReader.close();
			return;
		}
		catch(Exception e){
			System.out.println("ERROR: There was an error while reading the file.");
			courseInfoFileReader.close();
			return;
		}
		
		
		
		
		/* Process the student file. */
		System.out.print("Enter the name of the student file to process: ");
		studentFilePath = keyboardReader.nextLine();
		try{
			studentFileReader = new Scanner(new FileReader(studentFilePath));
			System.out.println("-------------------------------------------------------------------");
			
			while(studentFileReader.hasNext()){
				course.processStudent(studentFileReader);
				System.out.println(course.toString());
				System.out.println("-------------------------------------------------------------------");
			}
			studentFileReader.close();
		}
		catch(InputMismatchException e){
			System.out.println("ERROR: Student file not in correct format: " + studentFilePath);
			studentFileReader.close();
		}
		catch(FileNotFoundException e){
			System.out.println("ERROR: Could not open file: " + studentFilePath);
			return;
		}
		catch(Exception e){
			System.out.println("ERROR: There was an error while reading the file.");
			studentFileReader.close();
			return;
		}
	}
}
