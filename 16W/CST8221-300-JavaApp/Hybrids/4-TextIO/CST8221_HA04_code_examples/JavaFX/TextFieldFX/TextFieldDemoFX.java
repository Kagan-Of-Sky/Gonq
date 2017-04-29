/*  CST8221-JAP: HA 04 (see Lab 4 first)
    File name: TextFieldDemoFX.java
    Original source: Intro to Java Programming by Y. Liang, 10ed
    Modified by S. Ranev
*/
import static javafx.application.Application.launch;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
/**
 * This class demonstrates how to create and use a text field UI control.
 * Right-click no the text field to see the context menu (pop-up menu)
 * @author S. Ranev
 * @version 1.16.1
 * @since 1.8
 * @see BasePane, CheckBoxDemo, RadioButtonDemo
 */
public class TextFieldDemoFX extends RadioButtonDemo {
  @Override // Override the getPane() method in the super class
  protected BorderPane getPane(String textContent){
    BorderPane pane = super.getPane(textContent);
    
    BorderPane paneForTextField = new BorderPane();
    paneForTextField.setPadding(new Insets(5, 5, 5, 5)); 
    paneForTextField.setStyle("-fx-border-color: green");
    paneForTextField.setLeft(new Label("Enter a new message: "));
    
    TextField tf = new TextField();
    tf.setAlignment(Pos.BOTTOM_LEFT);//Pos.BOTTOM_RIGHT
    paneForTextField.setCenter(tf);
    pane.setTop(paneForTextField);
    //to triger this event the user must press Enter
    tf.setOnAction(e -> text.setText(tf.getText()));
    
    return pane;
  }
@Override // Override the start method in the Application class
  public void start(Stage primaryStage) {
    // Create a scene and place it in the stage
    Scene scene = new Scene(getPane("Programming with JavaFX"), 450, 200);
    primaryStage.setTitle("Text Filed Demo"); // Set the stage title
    primaryStage.setScene(scene); // Place the scene in the stage
    primaryStage.show(); // Display the stage
  }
  /**
   * The main method is only needed for the IDE with limited
   * JavaFX support. Not needed for running from the command line.
   * @param args Not used
   */
  public static void main(String[] args) {
    launch(args);
  }
}
