/* CST8221-JAP: HA 02, Example 3
   File name: JavaFXAppLifeCycle.java
   Run this example from the command line (window).
   It prints on the console.
   use:
     java JavaFXAppLifeCycle
   and then
     java JavaFXAppLifeCycle 1 2 3
*/ 
 
import javafx.application.*; 
import javafx.scene.*; 
import javafx.stage.*; 
import javafx.scene.layout.FlowPane; 
import java.util.List;
/** 
  This class demonstrates the life-cycle of a JavaFX application.
  and how to access the command line parameters
  @version 1.16.1
  @author S. Ranev
  @since JavaFX 2.0
*/
public class JavaFXAppLifeCycle extends Application { 
 
  /**
    The main() method is not required for JavaFX applications 
    when the JAR file for the application is created with the JavaFX Packager tool
    which embeds the JavaFX Launcher in the JAR file.
    The main method is not needed if you launch the application from the command line.
    When you run a JavaFX application without a main() method, the Java Virtual Machine (JVM)
    will use automatically the static launch() method to run the application.
    However, it is useful to include the main() method 
    so you can run the applications that were created without the JavaFX Launcher,
    such as when using an IDE in which the JavaFX tools are not fully integrated. 
    Also, Swing applications that embed JavaFX code require the main() method.
    @param args command line arguments
   */
  public static void main(String[] args) { 
  
    System.out.println("Launching JavaFX application."); 
  
    // Start the JavaFX application by calling launch(). 
     Application.launch(args);   
  } 

 /** 
     Override the init() method. This method is called first
     when a JavaFX appplication is launched. 
     As the name implies, this method can be used for
     initialization purposes only.
     No GUI elements can be created inside this method.
     Overriding the init() method is not necessary 
     because a default empty implementation is provided
     by the Application class.
 */
  @Override
  public void init() { 
    System.out.println("The init() method is called."); 
  } 
 
  /**
    Override the start() method.
    This method must always be overridden. 
    The GUI should be created inside that method.
  */ 
  @Override
  public void start(Stage primaryStage) { 
 
    System.out.println("The start() method is called."); 
    //Process the command line arguments
    final Parameters params = getParameters();
    //Get the the command line parameters
    final List<String> parameters = params.getRaw();
    //Do something with the parameters
    if(parameters.isEmpty())
     System.out.println("No command line parameters have been provided at launch.");
    else{
    //print the comand line parameters 
     System.out.println("Printing the command line parameters:");
     for(String p:parameters){
      System.out.println(p);
     }
    }
    
    //Set the GUI
    // Give the stage a title. 
    primaryStage.setTitle("JavaFX Life-Cycle."); 
 
    // Create a root node with a flow layout 
    FlowPane rootNode = new FlowPane(); 
 
    // Create an application scene with a specific size. 
    Scene appScene = new Scene(rootNode, 400, 200); 
 
    // Set the scene on the stage. 
    primaryStage.setScene(appScene); 
 
    // Show the stage and its scene. 
    primaryStage.show(); 
  } 
 
  /**
   Override the stop() method.
   This method is called when the application is closed.
   It can be used for closing resources or for safely shutting down
   the application. 
   Overriding the init() method is not necessary 
   because a default empty implementation is provided
   by the Application class.
  */
  @Override
  public void stop() { 
    System.out.println("The stop() method is called."); 
  } 
}

