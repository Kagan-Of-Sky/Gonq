/*  CST8221-JAP: HA 04 
    File name: TextAreaDemoFX.java
*/
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextArea;
import javafx.scene.layout.BorderPane;
import javafx.scene.text.Font;

/**
 * This class demonstrates how to create and use a test area UI control.
 * Right-click inside the text area to invoke the pop-up menu.
 * @author S. Ranev
 * @version 1.15.2
 * @since 1.8
 */
public class TextAreaDemoFX extends Application {
  @Override // Override the start method in the Application class
  public void start(Stage primaryStage) {
    // Declare and create a description pane
   BorderPane taContainer = new BorderPane();
   
   TextArea textArea = new TextArea();
   textArea.setFont(new Font("Serif", 14));
  // textArea.setWrapText(true);//enable text wrapping
  //  textArea.setEditable(false);//disable text entry - use as display area

    // Create a scroll pane to hold the text area
    ScrollPane scrollPane = new ScrollPane(textArea);
    taContainer.setCenter(scrollPane);
    taContainer.setPadding(new Insets(5, 5, 5, 5));
    // Create a scene and place it in the stage
    Scene scene = new Scene(taContainer, 450, 200);
    primaryStage.setTitle("Text Area Demo"); // Set the stage title
    primaryStage.setScene(scene); // Place the scene in the stage
    primaryStage.show(); // Display the stage
  }

  /**
   * The main method is only needed for the IDE with limited
   * JavaFX support. Not needed for running from the command line.
   * @param args Not used
   */
  public static void main(String[] args) {
    Application.launch(args);
  }
}
