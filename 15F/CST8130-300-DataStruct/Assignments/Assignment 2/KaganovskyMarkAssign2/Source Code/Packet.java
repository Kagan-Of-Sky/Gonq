/*
 * Purpose - This class represents a generic Packet which contains a destination IPAddress, 
 *           a source IPAddress, and some data represented by a String.
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
 * Fields -- destinationip: The destination IPAddress of the packet.
 *           sourceIP:      The source IPAddress of the packet.
 *           packetData:    The data contained in the packet.
 */

import java.util.Scanner;

/**
 * This class represents a generic Packet which contains a destination {@link IPAddress}, 
 * a source {@link IPAddress}, and some data represented by a {@link String}.<br><br>
 * Read packets by using the readPacket(Scanner scanner) method.<br>
 * The type of packet needs to be determined before hand.
 * 
 * @author Mark kaganovsky
 * 
 * @see RoutingPacket
 * @see DataPacket
 * @see IPAddress
 */
public abstract class Packet {
	protected IPAddress destinationip;
	protected IPAddress sourceip;
	protected String packetData;
	
	/**
	 * Default constructor, creates a new default destination {@link IPAddress}, source {@link IPAddress}, and an empty packetData String
	 */
	public Packet() {
		destinationip = new IPAddress();
		sourceip      = new IPAddress();
		packetData    = new String();
	}
	
	/**
	 * This packet reads the destination {@link IPAddress}, Source {@link IPAddress} and the packet Data {@link String}.
	 * If this method returns false, then the rest of the line is still in the buffer and needs to be consumed by the calling function.
	 * 
	 * @param scanner A scanner object to read from.
	 * @return A boolean value indicating whether the packet was valid or not (false = invalid).
	 */
	public boolean readPacket(Scanner scanner){
		boolean validData = true;
		if (destinationip.readAddress(scanner) == false){  //Read the destination ip address
			validData = false;
		}
		
		if(sourceip.readAddress(scanner) == false){        //Read the source ip address
			validData = false;
		}
		
		packetData = scanner.nextLine();                   //Read the rest of the data
		
		return validData;
	}
	
	/**
	 * @return An {@link IPAddress} object representing the destination <b>NETWORK</b> IP of this packet.
	 */
	public IPAddress getDestNetwork(){
		return destinationip.getNetwork();
	}
	
	/**
	 * @return The data contained in this packet, not including the source and destination IP
	 */
	public String getPacketData(){
		return packetData;
	}
	
	/**
	 * Processes a packet which is found in the routing table (Simply prints what action is taken on this packet by the {@link Router} class).
	 * 
	 * @param port The port code String (example 'e0') which the packet is being sent out.
	 * @return A boolean value indicating to the Router whether or not to add this packet to the routing table (true = add to table).
	 */
	public abstract boolean processFoundPacket(String port);
	
	/**
	 * Processes a packet which is not found in the routing table (Simply prints what action is taken on this packet by the {@link Router} class).
	 * 
	 * @param port The port code String (example 'e0') which the packet is being sent out.
	 * @return A boolean value indicating to the Router whether or not to add this packet to the routing table (true = add to table).
	 */
	public abstract boolean processNotFoundPacket(String port);
}