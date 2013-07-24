
public class LogEntry {
	public int time;
	public String pname;
	public int endpoint;

	public LogEntry(int time, int endpoint, String pname) {
		this.pname = pname;
		this.time = time;
		this.endpoint = endpoint;
	}
	
}
