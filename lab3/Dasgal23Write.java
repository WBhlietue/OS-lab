import java.util.*;
import java.io.*;
import java.net.*;
import java.time.*;

public class Dasgal23Write {
    static String[] texts = new String[] {

            "Every day is a new beginning.",
            "Every sunrise is a new opportunity.",
            "Smile at life, and life will smile back at you.",
            "Never give up until you succeed.",
            "Take the first step bravely; success is ahead.",
            "Believe in yourself; you can do it.",
            "Every day is a gift; make the most of it.",
            "Persistence leads to success.",
            "Your decisions shape your destiny.",
            "Success is the result of action.",
            "Treat others with love and kindness.",
            "Create your own happiness.",
            "Stay determined; victory is yours.",
            "Enjoy the present moment; cherish every second.",
            "Success comes from continuous learning and growth.",
            "Have faith in your abilities.",
            "Be kind to yourself and others.",
            "Move forward courageously; fear no obstacles.",
            "Happiness comes from within.",
            "Embrace change and welcome opportunities.",
            "Success is a habit.",
            "Be grateful for the hope of each day.",
            "Do what you love, and success will follow.",
            "Every step is a step forward.",
            "Dreams are the beginning of realization.",
            "Chase your dreams with courage.",
            "Give love, and you'll receive happiness.",
            "Believe in your potential.",
            "Stay resilient; success will come.",
            "Cultivate gratitude for a better life.",
            "Every day is a new opportunity; cherish it." };

    public static String GetText(int day) {
        return texts[day - 1];
    }

    public static class DateWriter extends Thread {
        public void run() {
            try {
                ServerSocket sock2 = new ServerSocket(6017);
                while (true) {
                    Socket client2 = sock2.accept();
                    PrintWriter pout2 = new PrintWriter(client2.getOutputStream(), true);
                    pout2.println(new Date().toString());
                    client2.close();
                }
            } catch (Exception err) {
                System.err.println(err);
            }
        }
    }
    public static class HaikuWriter extends Thread {
        public void run() {
            try {
                ServerSocket sock2 = new ServerSocket(5575);
                while (true) {
                    Socket client2 = sock2.accept();
                    PrintWriter pout2 = new PrintWriter(client2.getOutputStream(), true);
                    pout2.println("The light of a candle\nIs transferred to another candle why why\nSpring twilight why why why");
                    client2.close();
                }
            } catch (Exception err) {
                System.err.println(err);
            }
        }
    }

    public static void main(String[] args) {
        new DateWriter().start();
        new HaikuWriter().start();
        try {
            ServerSocket sock = new ServerSocket(17);
            while (true) {
                Socket client = sock.accept();
                PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
                pout.println(GetText(LocalDate.now().getDayOfMonth()));
                client.close();
            }
        } catch (Exception err) {
            System.err.println(err);
        }
    }
}
