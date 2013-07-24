import javax.swing.*;
import java.util.*;

public class GUI extends JFrame {

    private Map <Integer,ProcEntry>procs;
    private LinkedList <LogEntry>entries;
    public static DrawPane p;

    public GUI(Map <Integer,ProcEntry>procs, LinkedList <LogEntry>entries, boolean showTicks, int ruler) {
        super("Minix 3 Schedule Tracer");

        this.procs = procs;
        this.entries = entries;        

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Add the ubiquitous "Hello World" label.
        //Label label = new JLabel("Hello World");
        p = new DrawPane(procs,entries, showTicks, ruler);
        JScrollPane sp = new JScrollPane(p);
        this.getContentPane().add(sp);

        //Display the window.
        this.pack();
        this.setVisible(true);

    }

}
