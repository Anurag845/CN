import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class Server {

	public static void main(String[] args) throws Exception {
		DatagramSocket sock = new DatagramSocket(3000);
		String data = "";
		String data2 = "";
		Scanner sc = new Scanner(System.in);
		
		while(!data2.equals("stop")) {
			byte[] buffer = new byte[1024];
			DatagramPacket packet = new DatagramPacket(buffer,buffer.length);
			sock.receive(packet);
			data = new String(packet.getData());
			System.out.println("Client " + data);
			
			System.out.print("Server ");
			data2 = sc.nextLine();
		
			byte[] buff2 = new byte[1024];
			buff2 = data2.getBytes();
		
			InetAddress ia = InetAddress.getLocalHost();
			DatagramPacket pack2 = new DatagramPacket(buff2,buff2.length,ia,packet.getPort());
			sock.send(pack2);	
		}
		sock.close();
		sc.close();
	}

}
