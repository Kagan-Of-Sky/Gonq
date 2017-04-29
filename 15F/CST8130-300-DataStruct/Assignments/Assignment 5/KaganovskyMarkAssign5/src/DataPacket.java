/*
 * Purpose - This class represents a regular packet (not a router communication packet).
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
 * This class represents a regular packet (not a router communication packet).
 * 
 * @author Mark Kaganovsky
 * 
 * @see Packet
 * @see RoutingPacket
 * @see IPAddress
 */
public class DataPacket extends Packet{
	
	/**
	 * @param port The port code which this packet is sent out
	 * @return false, do not add this entry to the routing table.
	 */
	@Override
	public boolean processFoundPacket(String port) {
		System.out.printf("Data to %s (%s) sent out port %s\n", destinationip, getDestNetwork(), port);
		return false;
	}
	
	/**
	 * @param string The port code which this packet is sent out (not used).
	 * @return false, do not add this entry to the routing table.
	 */
	@Override
	public boolean processNotFoundPacket(String string, int index) {
		System.out.printf("Data to %s (%s) dropped, no entry found\n", destinationip, getDestNetwork());
		return false;
	}
}