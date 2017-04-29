/*
 * Purpose - Represents a grade category in a course.
 *           For example, if the course was DataStructures, then this
 *           category could be "Labs". 
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
 * Fields -- categoryName   - Name of the category (ex. Labs).
 *           assessments    - A list of the individual assessments that make up this category (ex. lab1, lab2, etc.).
 *           categoryWeight - The total weight of this category as a percent between 0.0 and 100.0 (ex 10.0).
 */

import java.util.LinkedList;
import java.util.Scanner;

public class GradeCategory {	
	private String categoryName;
	private LinkedList<Assessment> assessments;
	private float categoryWeight;
	
	/**
	 * Loads this grade category with the category name,  category weight, and the individual assessments.
	 * 
	 * @param scanner The stream to read from.
	 */
	public GradeCategory(Scanner scanner) {
		categoryName   = scanner.next();
		categoryWeight = scanner.nextFloat();
		assessments    = new LinkedList<>();
		
		/* Read the assessments. */
		int numAssessments = scanner.nextInt();
		for(int i=0; i<numAssessments; i++){
			assessments.add(new Assessment(scanner));
		}
		scanner.nextLine();
	}
	
	/**
	 * Processes a single category grade for a student.
	 * @param studentFileReader The stream to read from.
	 */
	public void processCategory(Scanner studentFileReader){
		for(Assessment assessment : assessments){
			assessment.processAssessment(studentFileReader);
		}
		if(studentFileReader.hasNextLine()){
			studentFileReader.nextLine();
		}
	}
	
	/**
	 * @return The grade received in this category (sum of grades 
	 * for each assessment divided by the number of assessments, 
	 * multiplied by the weight of the category).
	 */
	public float calculateCategoryGrade() {
		float sum = 0;
		for(Assessment assessment : assessments){
			sum += assessment.calculateAssessmentGrade();
		}
		
		return sum / assessments.size() * categoryWeight;
	}
	
	@Override
	public String toString(){
		StringBuilder sb = new StringBuilder();
		
		sb.append("        " + categoryName + " (" + categoryWeight + "%):\n");
		
		for(Assessment assessment : assessments){
			sb.append("            " + assessment.toString() + '\n');
		}
		
		sb.append("            Final Grade: " + String.format("%s", calculateCategoryGrade()) + "/ " + categoryWeight + "\n");
		
		return sb.toString();
	}

}