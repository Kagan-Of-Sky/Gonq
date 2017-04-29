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

import java.util.ArrayList;
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
	private ArrayList<RoutingTableEntry> routingTable;
	
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
		
		routingTable = new ArrayList<RoutingTableEntry>();
	}
	
	/**
	 * Processes a single packet.
	 * If it is a RoutingPacket, it is added to the table if it does not already exist.
	 * If it is a DataPacket, it is routed out the correct port if the destination IP is found in the routing table.
	 * Uses a binary search to find the index to route the packet out or to insert the packet.
	 * 
	 * @param packet The Packet object to process.
	 */
	public void processPackets(Packet packet){
		boolean packetProcessed = false;
		int low = 0;
		int up  = routingTable.size() - 1;
		int mid = 0;
		
		// Binary search to find the portCode.
		while(up >= low && packetProcessed == false){
			mid = (low + up) / 2;
			int compare = routingTable.get(mid).compareTo(packet.getDestNetwork());
			if(compare == 0){
				String portCode = routingTable.get(mid).searchForPort(packet.getDestNetwork());
				packet.processFoundPacket(portCode);
				packetProcessed = true;
			}
			else if(compare > 0){
				up = mid - 1;
			}
			else{
				low = mid + 1;
			}
		}
		
		if(packetProcessed == false){
			boolean addToRoutingTable = packet.processNotFoundPacket(null);                          //The return value of this method will be used to determine whether to add this packet to the routing table or not.
			if(addToRoutingTable){                                                                   //true  = This is a RoutingPacket, add this entry to the table.
				RoutingTableEntry newEntry = new RoutingTableEntry();
				newEntry.addEntry(packet.getDestNetwork(), packet.getPacketData());
				
				// mid will either be equal to the index to insert at, or one index less.
				// In the latter case, increment mid if it is not already equal to the size of the routing table array.
				
				if(mid != routingTable.size() && routingTable.get(mid).compareTo(newEntry) < 0){
					mid++;
				}
				
				routingTable.add(mid, newEntry);
			}
		}
	}
	
	/**
	 * Prints out the routing table to the standard output stream.
	 */
	public void displayTable(){
		System.out.println();
		System.out.println("+---------------------------------+");
		System.out.println("|          Routing Table          |");
		System.out.println("+---------------------+-----------+");
		System.out.println("|     Network IP      |    Port   |");
		System.out.println("+---------------------+-----------+");
		
		for (int i = 0; i < routingTable.size(); i++) {
			String entry[] = routingTable.get(i).toString().split(" ");
			System.out.printf("| %-20s| %-10s|\n", entry[0], entry[1]);
		}
		System.out.println("+---------------------+-----------+");
	}
}