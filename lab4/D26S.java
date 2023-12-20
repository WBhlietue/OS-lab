import java.util.*;
import java.io.*;
import java.net.*;
import java.time.*;

public class D26S {
    public static void main(String[] args) {
        try {
            ServerSocket sock = new ServerSocket(17);
            while (true) {
                Socket client = sock.accept();
                Thread tr = new Thread(new DateWriter(client));
                tr.start();
                // client.close();
            }
        } catch (Exception err) {
            System.err.println(err);
        }
    }

    public static class DateWriter extends Thread {
        Socket client;

        public DateWriter(Socket client) {
            this.client = client;
        }

        public void run() {
            try {
                PrintWriter pout2 = new PrintWriter(client.getOutputStream(), true);
                pout2.println(new Date().toString());

            } catch (Exception err) {
                System.err.println(err);
            }
        }
    }
}
