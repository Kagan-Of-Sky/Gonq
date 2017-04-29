/*
 * Purpose - Represent a single assessment for a grade category.
 *           For example, this class would represent the individual
 *           lab assessments (lab1, lab2, lab3, etc.) for the grade
 *           category 'Labs'.
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
 * Fields -- assessmentName - Name of assessment (ex lab1). No spaces.
 *           gradeRecieved  - The grade a student received (loaded by processAssessment()).
 *           outOfGrade     - The total grades possible for the assessment.
 */

import java.util.Scanner;

public class Assessment {
	private String assessmentName;
	private float  gradeRecieved;
	private float  outOfGrade;
	
	/**
	 * Loads this assessment with the 'out of grade' for the assessment. 
	 * @param scanner The stream to read from.
	 */
	public Assessment(Scanner scanner) {
		assessmentName = scanner.next();
		gradeRecieved  = -1;
		outOfGrade     = scanner.nextFloat();
	}
	
	/**
	 * Gets the students grade for a single assessment.
	 * @param studentFileReader The stream to read from.
	 */
	public void processAssessment(Scanner studentFileReader){
		gradeRecieved = studentFileReader.nextFloat();
	}
	
	/**
	 * @return The grade the student got for this assessment (grade received / grades possible).
	 */
	public float calculateAssessmentGrade(){
		return (gradeRecieved / outOfGrade);
	}
	
	@Override
	public String toString(){
		return assessmentName + ": " + gradeRecieved + " / " + outOfGrade; 
	}

}