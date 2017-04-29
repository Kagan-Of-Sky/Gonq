/*
 * Purpose - This class represents a course for a single student.
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
 * Fields -- courseName  - The name of the course (ex. DataStructures), no spaces.
 *           studentName - The name of the student (ex MarkKaganovsky), no spaces. 
 *           allGrades   - The grades categories for the course (ex. Labs, Assignments, Hybrids, etc.).
 */

import java.util.LinkedList;
import java.util.Scanner;

public class Course {
	private String courseName;
	private String studentName;
	private LinkedList<GradeCategory> allGrades;
	
	/**
	 * Load this class up with the blueprint for the grade categories of the course.
	 * 
	 * @param scanner The stream to read from.
	 */
	public Course(Scanner scanner) {
		courseName  = scanner.next();
		studentName = "Unknown";
		allGrades   = new LinkedList<>();
		
		/* Read the grade categories. */
		int numCategories = scanner.nextInt();
		scanner.nextLine();
		for(int i=0; i<numCategories; i++){
			allGrades.add(new GradeCategory(scanner));
		}
	}
	
	/**
	 * Processes the grade categories for a single student.
	 * @param studentFileReader The stream to read from.
	 */
	public void processStudent(Scanner studentFileReader) {
		studentName = studentFileReader.nextLine();
		for(GradeCategory gc : allGrades){
			gc.processCategory(studentFileReader);
		}
	}
	
	/**
	 * @return The final grade for the student (a number from 0.0 to 100.0).
	 */
	public float calculateGrade() {
		float grade = 0;
		for(GradeCategory gc : allGrades){
			grade += gc.calculateCategoryGrade();
		}
		return grade;
	}
	
	/**
	 * Returns a String representation of the students grades.
	 */
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		
		sb.append(studentName + ":\n");
		sb.append("    " + courseName + ":\n");
		
		for(GradeCategory category : allGrades){
			sb.append(category.toString());
			sb.append('\n');
		}
		
		sb.append("Final Grade: " + String.format("%.2f", calculateGrade()) + '%');
		
		return sb.toString();
	}

}