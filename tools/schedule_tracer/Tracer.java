import java.io.*;
import java.util.*;

public class Tracer {

    static boolean showTicks = false;
    static String logFileName = new String("log.txt");
    static String imageFileName =  null;
    static int ruler = 0;
    static int maxEntries = 0;

    public static void main(String args[]) {    


        Map <Integer,ProcEntry>procs = new HashMap<Integer,ProcEntry>();
        LinkedList <LogEntry>entries = new LinkedList<LogEntry>();
            

        for (String s: args) {
            parseArg(s);
        }

        if (ruler != 0 && showTicks == true) {
            System.out.println("Cannot use the ruler and showticks option at the same time!");
            System.exit(-1);
        }
    
        File f = new File(logFileName);
        
        if (!f.exists()) {
            System.out.println("Log file "+f.getAbsolutePath()+" does not exist!");
            System.exit(-1);
        }
        
        LogAnalyzer la = new LogAnalyzer(f, procs, entries, maxEntries);
        la.analyze();
        
        System.out.println("found processes: "+Integer.toString(procs.size()) + "  found log entries: "+Integer.toString(entries.size()));
        
        GUI gui = new GUI(procs, entries, showTicks, ruler);
    
        if (imageFileName != null) {

            /*try { Thread.sleep(5); } catch (Exception e) { }
    
            try {
                ScreenImage.createImage(gui.p, imageFileName);
            } catch (Exception e) { e.printStackTrace(); } 
            
            System.out.println("Created image: "+imageFileName);         
            */
            new ScreenshotThread(GUI.p, imageFileName).run();
        }
        
        try {
                while(true) Thread.sleep(1);
        }  catch (Exception e) { }
    }
    
    private static void  parseArg(String s) {
        //System.out.print("Received arg: ");
        //System.out.print(s);
        //System.out.print("\n");
        
        if (s.contains("help")) {
            System.out.println("usage:");
            System.out.println("java Tracer <optional parameters>");
            System.out.println("Parameters:");
            System.out.println("maxentries=<number>    Max log entries to analyze");
            System.out.println("showticks=<true/false> Draw stripes for every new tick start.");
            System.out.println("                       If this parameter is not set, it is false");
            System.out.println("ruler=<number>         Draw ruler, the number is the scale in ticks");
            System.out.println("logfile=<filename>     Path to the log file");
            System.out.println("                       If this parameter is not set,");
            System.out.println("                       we asume the log file is log.txt");
            System.out.println("                       The logfile should be in the following format:");
            System.out.println("                       <timestamp in ticks> <endpoint> <process name>linebreak");
            System.out.println("imagefile=<filename>   Path to file to save screenshot.");
            System.out.println("                       If this parameter is not set,");
            System.out.println("                       no screenshot will be saved.");
            System.out.println("Example usage:");
            System.out.println("java Tracer showticks=true logfile=mylogfile.txt imagefile=myscreenshot.jpg");
            System.exit(-1);
        } else if (s.contains("showticks")) {
            String splitted[] = s.split("=");
            
            if (splitted.length != 2) {
                System.out.println("Error in argument!");
                System.exit(-1);
            } 
            
            if (splitted[1].equalsIgnoreCase("true")) {
                showTicks = true;
                System.out.println("Config: showticks=true");
            }
                
        } else if (s.contains("logfile")) {
            String splitted[] = s.split("=");
            
            if (splitted.length != 2) {
                System.out.println("Error in argument!");
                System.exit(-1);
            }
            
            if (splitted[0].equalsIgnoreCase("logfile")) {
                logFileName = splitted[1];
                System.out.println("Config: logfile="+splitted[1]);
            }
            
        } else if (s.contains("imagefile")) {
            String splitted[] = s.split("=");
            
            if (splitted.length != 2) {
                System.out.println("Error in argument!");
                System.exit(-1);
            }
            
            if (splitted[0].equalsIgnoreCase("imagefile")) {
                imageFileName = splitted[1];
                System.out.println("Config: imagefile="+splitted[1]);
            }
            
        } else if (s.contains("ruler")) {
            String splitted[] = s.split("=");
            
            if (splitted.length != 2) {
                System.out.println("Error in argument!");
                System.exit(-1);
            }
            
            if (splitted[0].equalsIgnoreCase("ruler")) {
                ruler = Integer.valueOf(splitted[1]).intValue();
                System.out.println("Config: ruler="+ruler);
            }
            
        } else if (s.contains("maxentries")) {
            String splitted[] = s.split("=");
            
            if (splitted.length != 2) {
                System.out.println("Error in argument!");
                System.exit(-1);
            }
            
            if (splitted[0].equalsIgnoreCase("maxentries")) {
                maxEntries = Integer.valueOf(splitted[1]).intValue();
                System.out.println("Config: maxentries="+maxEntries);
            }
            
        }
    }
}
