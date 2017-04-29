/*
 * Purpose - This class represents an entry in the routing table.
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
 * Fields -- destinationip: The network IPv4 address.
 *           portCode:      The hardware port to send the packet out in order to reach the destinationip.
 */

/**
 * This class represents an entry in the routing table.
 * 
 * @author Mark
 * @see IPAddress
 */
public class RoutingTableEntry {
	private IPAddress destinationip;
	private String portCode;
	
	/**
	 * Creates a new default destinationip {@link IPAddress}, and a new empty portCode {@link String}
	 */
	public RoutingTableEntry() {
		destinationip = new IPAddress();
		portCode = new String();
	}
	
	/**
	 * Sets the destinationip and portCode to their respective parameters.
	 * 
	 * @param ip The destination IP Address
	 * @param port The port code (ex. e0)
	 */
	public void addEntry(IPAddress ip, String port){
		this.destinationip = ip;
		this.portCode = port;
	}
	
	/**
	 * This method compares the destination IP address in this routing table entry to the parameter passed to it.
	 * 
	 * @param ip The <b>NETWORK</b> IPAddress to check this entry's IP against
	 * @return The port if they are equal, (example: e0) or null. 
	 */
	public String searchForPort(IPAddress ip){
		if(destinationip.isEqual(ip)){
			return portCode;
		}
		else{
			return null;
		}
	}
	
	/**
	 * @return The port code.
	 */
	public String getPort(){
		return String.format("%s", portCode);
	}
	
	/**
	 * @return A String containing the IP, the subnet mask, and the port to reach that IP.<br>Example: "192.168.12.32 /24 e0"
	 */
	@Override
	public String toString() {
		return destinationip.toString() + " " + portCode;
	}
}
