import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

class Product {
    private int id;
    private String name;
    private double price;

    public Product(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
    }

    public int getId() { return id; }
    public String getName() { return name; }
    public double getPrice() { return price; }

    @Override
    public String toString() {
        return name + " (₹" + price + ")";
    }
}

class Cart {
    private List<Product> items = new ArrayList<>();

    public void addProduct(Product p) {
        items.add(p);
    }

    public List<Product> getItems() {
        return items;
    }

    public double getTotal() {
        double total = 0;
        for (Product p : items) {
            total += p.getPrice();
        }
        return total;
    }
}

public class ECommerceSwingApp extends JFrame {
    private DefaultListModel<Product> productListModel;
    private JList<Product> productList;
    private JTextArea cartArea;
    private JButton addToCartButton, viewCartButton;

    private List<Product> products;
    private Cart cart;

    public ECommerceSwingApp() {
        setTitle("Mini E-Commerce Platform");
        setSize(500, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        products = new ArrayList<>();
        cart = new Cart();

        initProducts();

        productListModel = new DefaultListModel<>();
        for (Product p : products) productListModel.addElement(p);
        productList = new JList<>(productListModel);
        add(new JScrollPane(productList), BorderLayout.CENTER);

        JPanel bottomPanel = new JPanel();
        addToCartButton = new JButton("Add to Cart");
        viewCartButton = new JButton("View Cart");
        bottomPanel.add(addToCartButton);
        bottomPanel.add(viewCartButton);
        add(bottomPanel, BorderLayout.SOUTH);

        cartArea = new JTextArea();
        cartArea.setEditable(false);
        add(new JScrollPane(cartArea), BorderLayout.EAST);

        addToCartButton.addActionListener(e -> addToCart());
        viewCartButton.addActionListener(e -> viewCart());
    }

    private void initProducts() {
        products.add(new Product(1, "Laptop", 55000));
        products.add(new Product(2, "Headphones", 1500));
        products.add(new Product(3, "Smartphone", 25000));
        products.add(new Product(4, "Charger", 500));
        products.add(new Product(5, "Book", 300));
    }

    private void addToCart() {
        Product selected = productList.getSelectedValue();
        if (selected != null) {
            cart.addProduct(selected);
            JOptionPane.showMessageDialog(this, selected.getName() + " added to cart.");
        } else {
            JOptionPane.showMessageDialog(this, "Please select a product.");
        }
    }

    private void viewCart() {
        if (cart.getItems().isEmpty()) {
            JOptionPane.showMessageDialog(this, "Your cart is empty.");
            return;
        }

        JDialog cartDialog = new JDialog(this, "Your Cart", true);
        cartDialog.setSize(300, 300);
        cartDialog.setLayout(new BorderLayout());

        JTextArea cartText = new JTextArea();
        cartText.setEditable(false);
        StringBuilder sb = new StringBuilder("Items in Cart:\n");
        for (Product p : cart.getItems()) {
            sb.append("- ").append(p).append("\n");
        }
        sb.append("\nTotal: ₹").append(cart.getTotal());
        cartText.setText(sb.toString());
        cartDialog.add(new JScrollPane(cartText), BorderLayout.CENTER);

        // Place Order button
        JButton placeOrderBtn = new JButton("Place Order");
        cartDialog.add(placeOrderBtn, BorderLayout.SOUTH);

        placeOrderBtn.addActionListener(e -> {
            JOptionPane.showMessageDialog(cartDialog, "Order Placed Successfully!");
            cartDialog.dispose(); // Close cart window after placing order
        });

        cartDialog.setLocationRelativeTo(this);
        cartDialog.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new ECommerceSwingApp().setVisible(true));
    }
}
