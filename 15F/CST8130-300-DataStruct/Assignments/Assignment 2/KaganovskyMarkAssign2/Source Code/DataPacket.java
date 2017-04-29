/*
 * Purpose - This class represents a regular packet (not a router communication packet).
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
 * Fields -- No extra fields, all the fields are inherited from Packet.
 *           destinationip: The destination IPAddress of the packet.
 *           sourceIP:      The source IPAddress of the packet.
 *           packetData:    The data contained in the packet.
 */

/**
 * This class represents a regular packet (not a router communication packet).
 * 
 * @author Mark kaganovsky
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
		System.out.printf("Data to %s on network %s is being sent out port %s\n", destinationip, getDestNetwork(), port);
		return false;
	}
	
	/**
	 * @param string The port code which this packet is sent out (not used).
	 * @return false, do not add this entry to the routing table.
	 */
	@Override
	public boolean processNotFoundPacket(String string) {
		System.out.printf("Packet to %s on network %s is being dropped, no routing table entry found\n", destinationip, getDestNetwork());
		return false;
	}
}