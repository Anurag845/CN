import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.net.Socket;
import java.util.Scanner;

class TCPClient {
	
	private Socket sock;
	private DataOutputStream dos;
	private DataInputStream dis;
	
	TCPClient() throws Exception {
		sock = new Socket("localhost",3000);
		dos = new DataOutputStream(sock.getOutputStream());
		dis = new DataInputStream(sock.getInputStream());
	}
	
	public void calculator() throws Exception{
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter 1 for addition");
		System.out.println("Enter 2 for subtraction");
		System.out.println("Enter 3 for multiplication");
		System.out.println("Enter 4 for division");
		System.out.println("Enter 5 for sine function");
		System.out.println("Enter 6 for cos function");
		int ch = sc.nextInt();
		dos.writeInt(ch);
		float num1,num2;
		double deg;
		switch(ch) {
		case 1: System.out.println(dis.readUTF());
				num1 = sc.nextFloat();
				dos.writeFloat(num1);
				System.out.println(dis.readUTF());
				num2 = sc.nextFloat();
				dos.writeFloat(num2);
				break;
		case 2: System.out.println(dis.readUTF());
				num1 = sc.nextFloat();
				dos.writeFloat(num1);
				System.out.println(dis.readUTF());
				num2 = sc.nextFloat();
				dos.writeFloat(num2);
				break;
		case 3: System.out.println(dis.readUTF());
				num1 = sc.nextFloat();
				dos.writeFloat(num1);
				System.out.println(dis.readUTF());
				num2 = sc.nextFloat();
				dos.writeFloat(num2);
				break;
		case 4:	System.out.println(dis.readUTF());
				num1 = sc.nextFloat();
				dos.writeFloat(num1);
				System.out.println(dis.readUTF());
				num2 = sc.nextFloat();
				dos.writeFloat(num2);
				break;
		case 5: System.out.println(dis.readUTF());
				deg = sc.nextDouble();
				dos.writeDouble(deg);
				break;
		case 6: System.out.println(dis.readUTF());
				deg = sc.nextDouble();
				dos.writeDouble(deg);
				break;
		}
		System.out.println(dis.readUTF());
	}
	
	public void FileTransfer() throws Exception{
		String data = dis.readUTF();
		FileOutputStream fos = new FileOutputStream("Receive.txt");
		byte b[] = data.getBytes();
		fos.write(b);
		fos.close();
	}
	
	public static void main(String[] args) throws Exception {
		TCPClient obj = new TCPClient();
		System.out.println("Enter 1 for calculator");
		System.out.println("Enter 2 for file transfer");
		Scanner sc = new Scanner(System.in);
		int ch = sc.nextInt();
		obj.dos.writeInt(ch);
		switch(ch) {
		case 1: obj.calculator();
		break;
		case 2: obj.FileTransfer();
		break;
		}
		obj.dis.close();
		obj.dos.close();
		obj.sock.close();
	}
}
