import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.util.Scanner;

class UDPServer {
	public static void main(String[] args) throws Exception {
		DatagramSocket sock = new DatagramSocket(3000);
		String data1 = "";
		String data2 = "";
		byte[] b1;
		byte[] b2;
		Scanner sc = new Scanner(System.in);
		
		while(!data2.equalsIgnoreCase("ok")) {
			
			b1 = new byte[1024];
			DatagramPacket pack1 = new DatagramPacket(b1,b1.length);
			sock.receive(pack1);
			data1 = new String(pack1.getData());
			System.out.println("Client- " + data1);
			
			System.out.print("Server- ");
			data2 = sc.nextLine();
			b2 = data2.getBytes();
			DatagramPacket pack2 = new DatagramPacket(b2,b2.length,pack1.getAddress(),pack1.getPort());
			sock.send(pack2);
		}
		
	}
}
