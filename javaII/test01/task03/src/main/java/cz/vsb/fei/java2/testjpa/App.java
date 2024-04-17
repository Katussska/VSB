package cz.vsb.fei.java2.testjpa;

import cz.vsb.fei.java2.testjpa.entities.Order;
import cz.vsb.fei.java2.testjpa.entities.OrderItem;
import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;
import lombok.extern.log4j.Log4j2;
import org.h2.tools.Server;

import java.io.IOException;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.List;

/**
 * Class <b>App</b> - extends class Application and it is an entry point of the
 * program
 *
 * @author Java I
 */
@Log4j2
public class App {

    public static void main(String[] args) {
        log.info("Launching Java application.");

        EntityManagerFactory emf = Persistence.createEntityManagerFactory("java2");
        EntityManager em = emf.createEntityManager();

        //TODO:
        em.getTransaction().begin();

        for (int i = 0; i < 5; i++) {
            Order order = new Order();
            order.setRestaurante("Restaurant " + (i + 1));

            for (int j = 0; j < 3; j++) {
                OrderItem item = new OrderItem();
                item.setMealname("Meal " + (j + 1));
                item.setPrice((j + 1) * 10);
                item.setTimeAdded(LocalDateTime.now());
                item.setOrder(order);

                order.getOrderItems().add(item);
            }

            em.persist(order);
        }

        em.getTransaction().commit();

        // Retrieve all Order instances from the database
        List<Order> orders = em.createQuery("SELECT o FROM Order o", Order.class).getResultList();

// Iterate over each Order
        for (Order order : orders) {
            System.out.println("Order ID: " + order.getId() + ", Restaurant: " + order.getRestaurante());

            // Iterate over each OrderItem in the current Order
            for (OrderItem item : order.getOrderItems()) {
                System.out.println("  Item ID: " + item.getId() + ", Meal: " + item.getMealname() + ", Price: " + item.getPrice());
            }
        }

        em.close();
        startDBWebServerAndWait();
    }

    private static void startDBWebServerAndWait() {
        // Start HTTP server for access H2 DB for look inside
        try {
            Server server = Server.createWebServer();
            log.info(server.getURL());
            server.start();
            log.info("Waitnig for Key press (ENTER)");
            waitForKeyPress();
            log.info("Ending DB web server BYE.");
            server.stop();
        } catch (SQLException e) {
            log.error("Cannot create DB web server.", e);
        }
    }

    private static void waitForKeyPress() {
        try {
            System.in.read();
        } catch (IOException e) {
            log.error("Cannot read input from keyboard.", e);
        }
    }
}