import java.awt.*;
import javax.swing.*;
import java.util.*;

public class DrawPane extends JComponent implements Cloneable {

    private Map <Integer,ProcEntry>procs;
    private LinkedList <LogEntry>entries;
    private boolean showTicks;
    private int ruler;
    private int ruler_state = 0;
    
    public DrawPane(Map <Integer,ProcEntry>procs, LinkedList <LogEntry>entries, boolean showTicks, int ruler) {
        
        this.procs = procs;
        this.entries = entries;
        this.showTicks = showTicks;
        this.ruler = ruler;
        
        Dimension d = new Dimension(entries.size()+50, ((procs.size()*50)+30));
        this.setPreferredSize(d);
        this.setMaximumSize(d);
        this.setMinimumSize(d);
        this.setBackground(Color.red);
    }
    
    public Object getClone() throws CloneNotSupportedException {
        return this.clone();
    }

    public void paint(Graphics g) {
        int y = 25;
        g.setColor(Color.white);
        g.fillRect(0,0,this.getSize().width, this.getSize().height);
    
        g.setColor(Color.black);
        //g.drawLine(1,1,100,100);
        
        if (ruler != 0) {
            g.drawString("ruler scale: "+Integer.valueOf(ruler).toString()+" ticks",25,(procs.size()*50)+29);
            ruler_state=0;
        }
        
        Set<Map.Entry<Integer,ProcEntry>> s = procs.entrySet();
        for (Map.Entry<Integer,ProcEntry> e : s) {
                        ProcEntry pe = (ProcEntry)e.getValue();
            pe.y = y;
            pe.x = 25;
            g.drawLine(25,y+5,25,y+30); // draw left
            g.drawLine(pe.x+entries.size(),y+5,pe.x+entries.size(),y+30); // draw right
            g.drawLine(25,y+5,pe.x+entries.size(),y+5); // draw top
            g.drawLine(25,y+30,pe.x+entries.size(),y+30); // draw bottom
            g.drawString(pe.pname,25,y);
            y+=50;
        }

        int prev_tick = 0;
        for (int i = 0; i<entries.size();i++) {
            LogEntry le = entries.get(i);
            Integer in = new Integer(le.endpoint); 
            
            if (! procs.containsKey(in)) {
                System.out.println("Corrupt data");
                System.exit(-1);
            }
                
            ProcEntry pe = procs.get(in);
            
            g.drawLine(i+26,pe.y+5,i+26,pe.y+30);
            
            if (showTicks == true) {
                if (prev_tick != le.time && prev_tick != 0) {
                    for (Map.Entry<Integer,ProcEntry> e : s) {
                        pe = (ProcEntry)e.getValue();
                        g.drawLine(i+26,pe.y+31,i+26,pe.y+35);
                        
                        if ((le.time - prev_tick) > 1 && prev_tick != 0) {
                            //System.out.print("current: ");
                            //System.out.print(le.time);
                            //System.out.print(" prev: ");
                            //System.out.print(prev_tick);
                            //System.out.print("\n");
                            g.drawString(Integer.toString(le.time - prev_tick),i+23, pe.y+50);
                        }
                    }              
                }
                
                prev_tick = le.time;
            }
            
            if (ruler != 0) {
                
                ruler_state++;
                
               // System.out.println("ruler_state: "+Integer.valueOf(ruler_state));
                
                if (ruler_state >= ruler) {
                    //System.out.println(Integer.valueOf(ruler_state).toString()+" >= "+Integer.valueOf(ruler));
                    
                    for (Map.Entry<Integer,ProcEntry> e : s) {
                        pe = (ProcEntry)e.getValue();
                        g.drawLine(i+26,pe.y+31,i+26,pe.y+35);
                        
                        
                    }
                    
                    ruler_state = 0;
                }
            }
                        
        }
    }
}
