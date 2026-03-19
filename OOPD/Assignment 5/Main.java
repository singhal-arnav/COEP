import java.util.Scanner;

abstract class GameCharacter {
    private int health;

    GameCharacter(int health) {
        this.health = health;
    }

    public abstract void attack();

    public final void respawn() {
        System.out.println("Respawning...");
    }

    public int getHealth() {
        return this.health;
    }

    public void setHealth(int health) {
        this.health = health;
    }

    public void takeDamage(int damage) {
        this.setHealth(this.getHealth() - damage);
    }

    public void heal(int amount) {
        this.setHealth(this.getHealth() + amount);
    }
}

class Warrior extends GameCharacter {
    Warrior(int health) {
        super(health);
    }

    public void attack() {
        System.out.println("Warrior swings a sword!");
    }

    public void setHealth(int health) {
        super.setHealth(health);
        if(this.getHealth() <= 0) {
            System.out.println("The warrior was slain on the battlefield. Press Enter to respawn.");
            Scanner sc = new Scanner(System.in);
            sc.nextLine();
            this.respawn();
        }
    }
}

class Mage extends GameCharacter {
    Mage(int health) {
        super(health);
    }

    public void attack() {
        System.out.println("Mage casts a fireball!");
    }

    public void setHealth(int health) {
        super.setHealth(health);
        if(this.getHealth() <= 0) {
            System.out.println("The mage died a hero's death. Press Enter to respawn.");
            Scanner sc = new Scanner(System.in);
            sc.nextLine();
            this.respawn();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        GameCharacter warrior = new Warrior(100);
        GameCharacter mage = new Mage(200);

        warrior.attack();
        mage.attack();

        System.out.println("The enemy strikes back! Mage takes 200 damage and Warrior takes 100 damage.");

        mage.takeDamage(200);
        warrior.takeDamage(100);
    }
}
