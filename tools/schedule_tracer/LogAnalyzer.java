import java.util.*;
import java.io.*;

public class LogAnalyzer {

    private FileReader fr;
    private Map <Integer,ProcEntry>procs;
    private File f;
    private LinkedList<LogEntry> entries;
    private int maxEntries;
    private int currentEntry = 0;
    
    public LogAnalyzer(File f, Map<Integer,ProcEntry> procs, LinkedList<LogEntry> entries, int maxEntries) {
        this.f = f;
        this.procs = procs;
        this.entries = entries;
        this.maxEntries = maxEntries;
    
    }

    public void analyze() {
        
        System.out.println("Starting with analyzing the following log file: ");
        System.out.println(f.getAbsolutePath());
        
        try {
            fr = new FileReader(f);
            BufferedReader br = new BufferedReader(fr);
            LogEntry le = null;
            String line = br.readLine();

            while(line != null) {

                String splitted[] = line.split(" ");
                
                for (int i=0; i<splitted.length; i++) {
                    splitted[i] = splitted[i].trim();
                    
                }
                
                if (splitted.length < 3) {
                    System.out.printf("Something wrong with the log file!");
                    System.exit(-1);
                }
                le = new LogEntry(Integer.valueOf(splitted[0]).intValue(), Integer.valueOf(splitted[1]).intValue(), splitted[2]);                
                entries.addLast(le);
                Integer in = new Integer(le.endpoint);                
                if ( ! procs.containsKey(in)) {
                    procs.put(in, new ProcEntry(in.intValue(),le.pname));
                    System.out.println("Found process: " + Integer.toString(le.endpoint) + " " + le.pname);
                }
                //System.out.println(line);
                line = br.readLine();
                
                if (maxEntries != 0) {
                    currentEntry++;
                    if (currentEntry >= maxEntries) {
                        break;
                    }
                }
            }
            
            br.close();
            fr.close();
        } catch (Exception e) { e.printStackTrace(); }
        
        System.out.println("Finished analyzing the log file");
    }
}
