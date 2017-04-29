/* CST8221-JAP: HA 02, Example 4
   File name: MultipleStages.java 
*/ 
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
/** 
  This class demonstrates how to create a JavaFX application
  with multiple stages.
  @version 1.16.1
  @author S. Ranev
  @since JavaFX 8
*/
public class MultipleStages extends Application {
    /**
     Override the start() method and create the GUI.
    */
    @Override
    public void start(final Stage primaryStage) throws Exception {
        //set the primary stage
        primaryStage.setTitle("Primary Stage");
        primaryStage.setX(300);//set location on screen
        primaryStage.setWidth(800);
        primaryStage.setHeight(400);
        // make the GUI visible - show the primary stage.
        primaryStage.show();
        //set a secondary stage
        final Stage secondaryStage = new Stage();
        secondaryStage.setTitle("Secondary Stage");
        secondaryStage.setWidth(400);
        secondaryStage.setHeight(200);
        secondaryStage.setX(primaryStage.getX() + primaryStage.getWidth() / 2 - secondaryStage.getWidth() / 2);
        secondaryStage.setY(primaryStage.getY() + primaryStage.getHeight() / 2 - secondaryStage.getHeight() / 2);
        //Show this stage and wait for it to be hidden (closed) before returning to the caller.
        secondaryStage.showAndWait();
    }

    public static void main(String[] args) {
        Application.launch(args);
    }
}