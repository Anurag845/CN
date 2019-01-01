import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class Client {
	public static void main(String[] args) throws Exception {
		DatagramSocket sock = new DatagramSocket();
		String data = "";
		String data2 = "";
		Scanner sc = null;
		
		while(!data.equals("stop")) {
			System.out.print("Client ");
			sc = new Scanner(System.in);
			data = sc.nextLine();
			
			byte[] buffer = new byte[1024];
			buffer = data.getBytes();
			InetAddress ia = InetAddress.getLocalHost();
			DatagramPacket packet = new DatagramPacket(buffer,buffer.length,ia,3000);
			sock.send(packet);
			//System.out.println("Client " + data);
			
			byte[] buff2 = new byte[1024];
			
			DatagramPacket pack2 = new DatagramPacket(buff2,buff2.length);
			sock.receive(pack2);
			data2 = new String(pack2.getData());
			System.out.println("Server " + data2);
			
		}
		
		sock.close();
		sc.close();
	}

}
