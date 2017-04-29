/*  CST8221-JAP: HA 05
    File name: CustomDialogFX.java 
*/
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
/**
 * This class demonstrates how to create a simple custom dialog in JavaFX using another stage.
 * Before JavaFX 1.8.40 this was the only available approach.
 * With the release of 1.8.40 a few specialized dialog classes have been introduced similar
 * to the ones in Swing API. Those classes are: Alert, Dialog, TextInputDialog and ChoiceDialog.
 * @author S. Ranev
 * @version 1.15.2
 * @since 1.8
 */
public class CustomDialogFX extends Application {
     /** Dialog stage. */
     private Stage dialog;
     /** Dialog label containing the dialog text. */
     private Label textLabel;
     /** Initial dialog text. */
     private final String initText = "Are you happy now?            ";
    /**
     * Creates and shows Application GUI.
     */
    @Override
    public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("JavaFX Custom Dialog");
        Button primaryButton = new Button("Try me!");
        //register event handler
        primaryButton.setOnAction(new EventHandler<ActionEvent>() {

            @Override
            public void handle(ActionEvent event) {
                //create and show dialog window
                if(dialog ==null){
                  textLabel = new Label(initText);
                  dialog = buildDialog(new Stage(), textLabel);
                }else
                  textLabel.setText(initText); 
               //show dilaog                 
               // dialog.show();
               // Shows this stage and waits for it to be hidden (closed) before returning to the 
                dialog.showAndWait();
               //Send the Window to the background
               //dialog.toBack();
            }
        });
        //set main application stage
        StackPane root = new StackPane();
        root.getChildren().add(primaryButton);
        primaryStage.setScene(new Scene(root, 400, 250));
        primaryStage.show();
    }//end start
    /**
     Builds a modal undecorated dialog window with a given text.
     @param dialog the window to be built
     @param textLabel the label containing the initial text of the dialog window
     @return returns the built dialog or null
    */
    public Stage buildDialog(Stage dialog, Label textLabel){      
      if (dialog == null || textLabel == null) return null;
      dialog.setTitle("Happy Dialog");
      Button yesButton = new Button("Yes");
                yesButton.setOnAction(new EventHandler<ActionEvent>() {

                    @Override
                    public void handle(ActionEvent arg0) {
                        //dialog.close();
                        dialog.hide();
                    }
                });
                Button noButton = new Button("No");
                noButton.setOnAction(new EventHandler<ActionEvent>() {

                    @Override
                    public void handle(ActionEvent arg0) {
                       textLabel.setText("Why not? Do you like Java?"); 
                    }
                });
                HBox hBox = new HBox();
                hBox.setAlignment(Pos.BASELINE_CENTER);
                hBox.setSpacing(20.0);
                hBox.getChildren().addAll(yesButton, noButton);

                VBox vBox = new VBox();
                vBox.setSpacing(40.0);
                vBox.getChildren().addAll(textLabel, hBox);
                //dialog.initStyle(StageStyle.UTILITY  );//remove decorations
                //make it modal
                dialog.initModality(Modality.APPLICATION_MODAL);//Modality.WINDOW_MODAL
                dialog.setScene(new Scene(vBox));
                dialog.setResizable(false);
                //dialog.setHeight(400);
                //dialog.setWidth(300);
                //pack to prefered sizes
                dialog.sizeToScene();
               // dialog.toFront();
               return dialog;
    }//end create
    public static void main(String[] args) {
        launch(args);
    }//end main

}//end class



