/*  CST8221-JAP: HA 05
    File name: StandardDialogFX.java 
*/

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import java.util.Optional;
/**
 * This class demonstrates how to display dialogs using the standard dialog classes
 * introduced in Java 1.8.40.
 * Before JavaFX 1.8.40 the developer has to use a second stage to create a custom build dialogs.
 * With the release of 1.8.40 a few specialized dialog classes have been introduced similar
 * to the ones in Swing API. Those classes are: Alert, Dialog, TextInputDialog and ChoiceDialog.
 * @author S. Ranev
 * @version 1.16.1
 * @since 1.8.40
 * @see Alert
 * @see Dialog
 * @see TextInputDialog
 * @see ChoiceDialog
 */
public class StandardDialogFX extends Application {
     /** Initial dialog text. */
     private final String initText = "Are you happy now?            ";
     /** A standard dialog reference */
     private Alert alert;
    /**
     * Creates and shows the Application GUI.
     * @param primaryStage the primary stage for this application.
     * @throws Exception General exception
     */
    @Override
    public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("JavaFX Standard Dialog");
        Button primaryButton = new Button("Try me!");
        //register event handler
        primaryButton.setOnAction(new EventHandler<ActionEvent>() {

            @Override
            public void handle(ActionEvent event) {
               //create a confirmation dialog (alert)
               alert = new Alert(AlertType.CONFIRMATION);
               //Optional title. If not used the standard title "Confiramation" will be displayed
               //To remove the title use alert.setTitle(null);
               alert.setTitle("Confirmation Dialog");
               //Optional header.If not used the standard header "Confiramation" will be displayed
               //To remove the title use alert.setHeaderText(null);  
               alert.setHeaderText("Please answer the question!");
               alert.setContentText(initText);
             //Display the dialog and get the result from the user action
             Optional<ButtonType> result = alert.showAndWait();
             if (result.get() == ButtonType.OK){
            // the user clicked OK
               alert = new Alert(AlertType.INFORMATION);
               alert.setTitle("Information Dialog");
               alert.setHeaderText("Important message for you!");
               alert.setContentText("Happiness is ephemeral!");
               alert.showAndWait();   
             //the user clocked Cancel
             } else {
            // ... user chose CANCEL or closed the dialog
              //Warning Dialog
              alert = new Alert(AlertType.WARNING);
              alert.setTitle("Warning Dialog");
              alert.setHeaderText("Read the Warning!");
              alert.setContentText("You must like Java - Shall make you Happy!");
              alert.showAndWait();           
             }
            }
        });
        //set primary application stage
        StackPane root = new StackPane();
        // add button to the stage
        root.getChildren().add(primaryButton);
        primaryStage.setScene(new Scene(root, 400, 250));
        primaryStage.show();
    }//end start
   
    /**
     * Launches the application.
     * @param args not used
     */
    public static void main(String[] args) {
        Application.launch(args);
    }//end main

}//end class



