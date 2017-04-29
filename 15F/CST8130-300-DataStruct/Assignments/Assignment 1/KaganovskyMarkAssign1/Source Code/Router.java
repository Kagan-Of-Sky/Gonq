/*
 * Purpose - This class simulates a very simple network router.
 * 
 * Name ---- Mark Kaganovsky
 * 
 * Date ---- September 29, 2015
 * 
 * Course -- CST8130 Data Structures
 * 
 * Section - 302
 * 
 * Methods - Please refer to the JavaDoc comments above every method.
 * 
 * Fields -- routingTable: An array of RoutingTableEntry objects, the size is determined by the user in the constructor.
 *           nextIndex:    The next available index in the routing table (also the current number of entries in the routing table).
 *           maxEntries:   Not used in this program (routingTable.length will produce the same result)
 */

import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * This class simulates a very simple network router. It can add entries to its routing table
 * and it can route packets to their destination or drop them.
 * 
 * @author Mark
 * 
 * @see IPAddress
 * @see Packet
 * @see RoutingPacket
 * @see RoutingTableEntry
 * @see DataPacket
 */
public class Router {
	private RoutingTableEntry routingTable[]; //The routing table
	private int               nextIndex;      //The next available index in the routing table (also the current number of entries in the routing table).
	private int               maxEntries;     //Not used in this program (routingTable.length will give the same result)
	
	/**
	 * Simulates the router being booted up.
	 * Asks the user for the maximum size of the RoutingTable.
	 */
	public Router() {
		Scanner keyboardScanner = new Scanner(System.in);
		int maxRouterEntries = 0;
		boolean validRouterSize = false;
		
		while(validRouterSize == false){
			System.out.print("Enter the maximum number of entries allowed in the routing table: ");
			try{
				maxRouterEntries = keyboardScanner.nextInt();
				if(maxRouterEntries <= 0){
					System.out.println("Maximum number of entries allowed needs to be greater than zero.");
				}
				else{
					validRouterSize = true;
				}
			}
			catch(InputMismatchException e){
				System.out.println("Invalid size, please enter a valid routing table size.");
			}
			keyboardScanner.nextLine();
		}
		
		routingTable = new RoutingTableEntry[maxRouterEntries];
	}
	
	/**
	 * Processes a single packet.
	 * If it is a RoutingPacket, it is added to the table if it does not already exist.
	 * If it is a DataPacket, it is routed out the correct port if the destination IP is found in the routing table.
	 * 
	 * @param packet The Packet object to process.
	 */
	public void processPackets(Packet packet){
		boolean packetProcessed = false;
		for (int i = 0; i < nextIndex && packetProcessed == false; i++) {                            //For every entry in the routing table.
			String portCode = routingTable[i].searchForPort(packet.getDestNetwork());   
			if(portCode != null){                                                                    //If portCode is not null, then this entry's IPAddress matches the packets destination IP.
				packet.processFoundPacket(portCode);
				packetProcessed = true;
			}
		}
		if(packetProcessed == false){
			boolean addToRoutingTable = packet.processNotFoundPacket(null);                          //The return value of this method will be used to determine whether to add this packet to the routing table or not.
			if(addToRoutingTable && nextIndex != routingTable.length){                                                                   //true  = This is a RoutingPacket, add this entry to the table.
				routingTable[nextIndex] = new RoutingTableEntry();                                   //false = This is a DataPacket, do not add it to the table
				routingTable[nextIndex].addEntry(packet.getDestNetwork(), packet.getPacketData());
				nextIndex++;
			}
			else if(addToRoutingTable && nextIndex == routingTable.length){
				System.out.printf("Routing table is full, %d/%d entries\n", nextIndex, routingTable.length);
			}
		}
	}
	
	/**
	 * Prints out the routing table to the standard input stream.
	 */
	public void displayTable(){
		System.out.println();
		System.out.println("+---------------------------------+");
		System.out.println("|          Routing Table          |");
		System.out.println("+---------------------+-----------+");
		System.out.println("|      Network IP     |   Port    |");
		System.out.println("+---------------------+-----------+");
		
		for (int i = 0; i < nextIndex; i++) {
			String entry[] = routingTable[i].toString().split(" ");
			System.out.printf("| %-20s| %-10s|\n", entry[0], entry[1]);
		}
		System.out.println("+---------------------+-----------+");
	}
}