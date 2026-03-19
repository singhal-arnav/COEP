class FileDownloader extends Thread {
    private String fileName;
    private int fileSize; //in MB

    public FileDownloader(String fileName, int fileSize) {
        this.fileName = fileName;
        this.fileSize = fileSize;
    }

    public void run() {
        System.out.println("Downloading: " + fileName);
        for(int downloaded = 0; downloaded <= fileSize; downloaded += 10) {
            System.out.println(fileName + ": " + downloaded + "/" + fileSize + " MB downloaded...");
            try {
                Thread.sleep(500); //Simulating download delay
            }
            catch(InterruptedException e) {
                System.out.println(fileName + " download interrupted.");
            }
        }
        System.out.println(fileName + " download complete!");
    }
}

public class Main {
    public static void main(String[] args) {
        FileDownloader file1 = new FileDownloader("movie.mp4", 100);
        FileDownloader file2 = new FileDownloader("song.mp3", 50);
        FileDownloader file3 = new FileDownloader("document.pdf", 30);

        file1.start();
        file2.start();
        file3.start();
    }
}
