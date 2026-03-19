class BankAccount {
    String accountHolderName;
    double balance;
    static String bankName;

    public BankAccount(String accountHolderName, double balance) {
        this.accountHolderName = accountHolderName;
        this.balance = balance;
    }

    void depositAmount(double amount) {
        this.balance += amount;
    }

    void withdrawAmount(double amount) {
        double originalBalance = this.balance;
        this.balance = (this.balance >= amount && amount <= 5000) ? this.balance - amount : this.balance;
        String msg = (this.balance == originalBalance) ? "Insufficient funds. Amount could not be withdrawn" : "Amount withdrawn successfully";
        System.out.println(msg);
    }

    void displayAccountDetails() {
        System.out.println("Bank Name: " + bankName);
        System.out.println("Account Holder: " + this.accountHolderName);
        System.out.println("Balance: " + this.balance);
    }

    static void setBankName(String name) {
        bankName = name;
    }
}

public class Main1 {
    public static void main(String[] args) {
        BankAccount b1 = new BankAccount("Arnav Singhal", 10000), b2 = new BankAccount("John Doe", 5000);

        BankAccount.setBankName("HDFC Bank");

        System.out.println("Details of Bank Account 1:");
        b1.displayAccountDetails();
        System.out.println("Depositing INR 5000 in Bank Account 1");
        b1.depositAmount(5000);
        System.out.println("Details of Bank Account 1:");
        b1.displayAccountDetails();

        System.out.println("Details of Bank Account 2:");
        b2.displayAccountDetails();
        System.out.println("Withdrawing INR 3000 from Bank Account 2");
        b2.withdrawAmount(3000);
        System.out.println("Withdrawing INR 4000 from Bank Account 2");
        b2.withdrawAmount(4000);
        System.out.println("Details of Bank Account 2:");
        b2.displayAccountDetails();
    }
}