import java.net.*;
import java.io.*;
import java.util.Scanner;

public class CRCSender {
	public CRCSender() {
		Scanner sc = new Scanner(System.in);
		String dataword = "";
		String codeword = "";
		String divisor = "";
		System.out.print("Enter dataword- ");
		dataword = sc.next();
		System.out.print("Enter key- ");
		divisor = sc.next();
		int d = key.length;
		int k = dataword.length;
		int n = k + d - 1;
		int[] data = new int[k];
		int[] key = new int[d];
		for(int i = 0; i < k; i++) {
			data[i] = dataword[i] - '0';
		}
		for(int i = 0; i < d; i++) {
			key[i] = divisor[i] - '0';
		}
		int[] temp = new int[d];
		for(int i = 0; i < d; i++) {
			temp = retxor(data[i],key[i]);
		}
		int i = 0,j = 0;
		for(i = d; i < n; i++) {
			for(j = 0; j < d-1; j++) {
				temp[j] = temp[j+1];
			}
			temp[j] = data[i];
			if(temp[0] == 1) {
				for(j = 0; j < d; j++) {
					temp[j] = retxor(temp[j],data[i+j]);
				}
			}
		}
		System.out.println(temp[1] + " " + temp[2] + " " + temp[3]);
	}
	
	int retxor(int a,int b) {
		return (a==b ? 0:1);
	}
	
	public static void main(String[] args) {
		CRCSender crcsender = new CRCSender();
	}
}
