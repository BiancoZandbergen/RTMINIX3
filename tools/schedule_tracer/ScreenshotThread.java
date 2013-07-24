class ScreenshotThread extends Thread {

    private DrawPane p;
    private DrawPane clone;
    private String imageFileName;
    
    public ScreenshotThread(DrawPane p, String imageFileName) {
        this.p = p;
        this.imageFileName = imageFileName;
    } 
    
    public void run() {
        try {
            this.sleep(5);
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        try {
            clone = (DrawPane)p.getClone();
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        try {
    			ScreenImage.createImage(clone, imageFileName);
    	} catch (Exception e) { e.printStackTrace(); } 
            
        System.out.println("Created image: "+imageFileName);
        
        while (true) {
            try {
                this.sleep(5);
            } catch (Exception e) {
                e.printStackTrace();
            }
        } 
    }

}
