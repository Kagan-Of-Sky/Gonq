/*
 * Purpose - This class simulates the reading of packets off of the data link layer.
 *           It asks the user for the file to read from, then keeps reading packets,
 *           one per line, until the end of file is encountered.
 * 
 * Name ---- Mark Kaganovsky
 * 
 * Date ---- December 9, 2015
 * 
 * Course -- CST8130 Data Structures
 * 
 * Section - 302
 * 
 * Methods - Please refer to the JavaDoc comments above every method.
 * 
 * Fields -- None.
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

/**
 * This class simulates the reading of packets off of the data link layer.<br><br>
 * It asks the user for the file to read from, then keeps reading packets,
 * one per line, until the end of file is encountered. <br><br>
 * 
 * The file should look similar to the following<br>
 * 
 * p 1 1 1 1 24 2 2 2 2 16 e0<br>
 * d 1 1 1 1 24 2 2 2 2 16 Hello World!<br><br>
 * 
 * The file should be in the following format:<br>
 * <ol>
 *     <li>The first character specifies the type of file (p for a routing packet, and d for a data packet).</li>
 *     <li>The next 4 numbers should be the octets of an IPv4 address in base 10, this is the destination address.</li>
 *     <li>The next number should be the subnet mask to the previous IPAddress(either 0, 8, 16, or 24).</li>
 *     <li>The next 4 numbers should be the octets of an IPv4 address in base 10, this is the source address.</li>
 *     <li>The next number should be the subnet mask to the previous IPAddress(either 0, 8, 16, or 24).</li>
 *     <li>The last part is either the data contained in a data packet, or the port code (example e0, e1, etc.).</li>
 * </ol>
 * 
 * @author Mark Kaganovsky
 * 
 * @see Router 
 * @see Packet
 * @see RoutingPacket
 * @see DataPacket
 */
public class Main {
	/**
	 * Asks for the name of a file to read packets from,
	 * then reads the first character of each line,
	 * determines the packet type,
	 * creates an appropriate packet based on that first character (RoutingPacket or DataPacket),
	 * or drops the packet if it is not a valid packet type,
	 * then passes off execution to Router.processPacket(Packet readPacket).
	 * 
	 * @param args Command Line Arguments (not used)
	 */
	public static void main(String[] args) {
		String     packetFilePath;                             //The relative or absolute path for the file to read packets from
		Scanner    packetReader     = null;                    //The Scanner object which will read from the user specified packet file
		Scanner    keyboardReader   = new Scanner(System.in);  //The Scanner which will read the file name from standard input
		Router     router           = new Router();            
		
		//Get file name
		System.out.print("Enter the name/path of the file to read packets from: ");
		packetFilePath = keyboardReader.nextLine();
		
		System.out.println();
		try{
			packetReader = new Scanner(new File(packetFilePath));
			while(packetReader.hasNext()){
				String packetType;
				Packet packet;
				
				packetType = packetReader.next();   //Read the packet type
				
				if(packetType.equals("p")){         //Routing packet was read
					packet = new RoutingPacket();
				}
				else if(packetType.equals("d")){    //Data packet was read
					packet = new DataPacket();
				}
				else{                               //Unknown packet type
					System.out.println("Unknown Packet type: " + packetReader.nextLine());
					continue;
				}

				if(packet.readPacket(packetReader) == true){  //A valid packet was read
					router.processPackets(packet);
				}
				else{                                         //Invalid packet
					System.out.println("Invalid packet read");
				}
			}
			router.displayTable();
		}
		catch(FileNotFoundException e){
			System.out.println("File '" + packetFilePath + "' does not exist.");
		}
		catch(IOException e){
			System.out.println("An Input/Output error occured on file '" + packetFilePath + "'.");
		}
		finally{
			if(packetReader != null){
				packetReader.close();
			}
		}
		keyboardReader.close();
	}
}