import java.util.*;

class Post {
    String content;
    int likes;

    public Post(String content, int likes) {
        this.content = content;
        this.likes = likes;
    }

    public String toString() {
        return "\"" + content + "\" (" + likes + " likes)";
    }
}

class User {
    private String name;
    private LinkedList<Post> posts; //maintains insertion order, allows duplicates
    private Set<String> followers;  //unique followers
    private PriorityQueue<Post> trendingPosts; //sorted by likes descending

    public User(String name) {
        this.name = name;
        this.posts = new LinkedList<>();
        this.followers = new HashSet<>();
        this.trendingPosts = new PriorityQueue<>(
                (p1, p2) -> Integer.compare(p2.likes, p1.likes) //max-heap
        );
    }

    public void addPost(String content, int likes) {
        Post post = new Post(content, likes);
        posts.add(post);
        trendingPosts.offer(post);
    }

    public void addFollower(String followerName) {
        followers.add(followerName);
    }

    public void showPosts() {
        System.out.println("Posts by " + name + ":");
        for (Post post : posts) {
            System.out.println(post);
        }
    }

    public void showFollowers() {
        System.out.println("Followers of " + name + ": " + followers);
    }

    public void showTopTrendingPosts(int topN) {
        System.out.println("Top " + topN + " Trending Posts of " + name + ":");
        Iterator<Post> it = trendingPosts.iterator();
        List<Post> temp = new ArrayList<>(trendingPosts);
        temp.sort((a, b) -> Integer.compare(b.likes, a.likes));
        for (int i = 0; i < Math.min(topN, temp.size()); i++) {
            System.out.println(temp.get(i));
        }
    }
}

public class SocialMediaApp {
    public static void main(String[] args) {
        User user = new User("Alice");

        user.addPost("Hello World!", 100);
        user.addPost("Enjoying the weather", 120);
        user.addPost("Hello World!", 70);
        user.addPost("New blog post!", 150);

        user.addFollower("Bob");
        user.addFollower("Charlie");
        user.addFollower("Bob"); // duplicate ignored

        user.showPosts();
        System.out.println();
        user.showFollowers();
        System.out.println();
        user.showTopTrendingPosts(3);
    }
}
