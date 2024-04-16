package cz.vsb.fei.java2.testjpa;

import java.io.IOException;
import java.sql.SQLException;

import org.h2.tools.Server;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;
import lombok.extern.log4j.Log4j2;

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