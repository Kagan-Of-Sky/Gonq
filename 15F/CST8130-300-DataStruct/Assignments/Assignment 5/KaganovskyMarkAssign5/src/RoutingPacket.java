import java.util.Scanner;

/*
 * Purpose - This class represents a packet which is sent by routers to communicate with each other.
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
 * Fields -- No extra fields, all the fields are inherited from Packet.
 */

/**
 * This class represents a packet which is sent by routers to communicate with each other.
 * 
 * @author Mark Kaganovsky
 * 
 * @see Packet
 * @see DataPacket
 * @see IPAddress
 */
public class RoutingPacket extends Packet{
	
	/**
	 * This method calls super.readPacket(scanner), it exists in order to get 
	 * rid of the leading and trailing whitespace which could be in the port code.
	 * 
	 * @param scanner A scanner object to read from.
	 * @return A boolean value indicating whether the packet was valid or not (false = invalid).
	 * @see Packet#readPacket(Scanner)
	 */
	@Override
	public boolean readPacket(Scanner scanner){
		boolean validPacket = super.readPacket(scanner);
		if(validPacket){
			packetData = packetData.trim(); // Remove leading and trailing whitespace.
		}
		
		if(packetData.length() == 0){ //This packet has length 0, drop it.
			validPacket = false;
		}
		return validPacket;
	}
	
	/**
	 * @param port The port code which this network can already be accessed by.
	 * @return false, do not add this packet to the routing table.
	 */
	@Override
	public boolean processFoundPacket(String port) {
		System.out.printf("Network %s already exists, or there is a hash collision (port %s)\n", getDestNetwork().toString(), port);
		return false;
	}
	
	/**
	 * @param port The port code which this network can now be accessed by.
	 * @return true, add this packet to the routing table.
	 */
	@Override
	public boolean processNotFoundPacket(String port, int index) {
		System.out.printf("Adding network %s (port %s, index %d)\n", getDestNetwork().toString()
		                                                                                , getPacketData()
		                                                                                , index);
		return true;
	}
}