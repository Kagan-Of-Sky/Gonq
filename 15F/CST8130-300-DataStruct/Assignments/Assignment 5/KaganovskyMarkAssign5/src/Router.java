/*
 * Purpose - This class simulates a very simple network router.
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
 * @author Mark Kaganovsky
 * 
 * @see IPAddress
 * @see Packet
 * @see RoutingPacket
 * @see RoutingTableEntry
 * @see DataPacket
 */
public class Router {
	private RoutingTableEntry routingTable[]; //The routing table
	
	/**
	 * Simulates the router being booted up.
	 * Asks the user for the maximum size of the RoutingTable.
	 */
	public Router() {
		Scanner keyboardScanner  = new Scanner(System.in);
		int     maxRouterEntries = 0;
		boolean validRouterSize  = false;
		
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
		int index = packet.getDestNetwork().hashCode() % routingTable.length;
		
		if(routingTable[index] == null){
			boolean addToRoutingTable = packet.processNotFoundPacket(null, index);
			if(addToRoutingTable){
				routingTable[index] = new RoutingTableEntry();
				routingTable[index].addEntry(packet.getDestNetwork(), packet.getPacketData());
			}
		}
		else{
			String portCode = routingTable[index].searchForPort(packet.getDestNetwork());
			if(portCode != null){
				packet.processFoundPacket(portCode);
			}
			else{
				packet.processNotFoundPacket(null, index);
			}
		}
	}
	
	/** Prints out the routing table. */
	public void displayTable(){
		System.out.println();
		System.out.println("+-----------------------------------------+");
		System.out.println("|             Routing Table               |");
		System.out.println("+-------+---------------------+-----------+");
		System.out.println("| Index |      Network IP     |   Port    |");
		System.out.println("+-------+---------------------+-----------+");
		
		for (int i = 0; i < routingTable.length; i++) {
			if(routingTable[i] != null){
				String entry[] = routingTable[i].toString().split(" ");
				System.out.printf("| %-6d| %-20s| %-10s|\n", i, entry[0], entry[1]);
			}
		}
		System.out.println("+-------+---------------------+-----------+");
	}
}