package cz.vsb.fei.java2.testjpa;

import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

import cz.vsb.fei.java2.testjpa.entities.Bird;
import cz.vsb.fei.java2.testjpa.entities.LetterLog;
import cz.vsb.fei.java2.testjpa.entities.Nest;
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
		//1.3
		try {
			em.getTransaction().begin();

			for (int i = 0; i < 10; i++) { // Generate and save 10 instances of LetterLog
				LetterLog letterLog = LetterLog.createRandom();
				em.persist(letterLog);
			}

			em.getTransaction().commit();
		} catch (Exception e) {
			if (em.getTransaction().isActive()) {
				em.getTransaction().rollback();
			}
			log.error("Error while saving LetterLog instances.", e);
		}

		//1.5, 1.6, 1.7
		try {
			em.getTransaction().begin();


			for (int i = 0; i < 10; i++) {
				Nest nest = Nest.createRandom();
				em.persist(nest);
			}


			for (int i = 0; i < 10; i++) {
				Bird bird = Bird.createRandom();
				bird.setNest(em.find(Nest.class, i+1));
				em.persist(bird);
			}

			em.getTransaction().commit();
		} catch (Exception e) {
			if (em.getTransaction().isActive()) {
				em.getTransaction().rollback();
			}
			log.error("Error while saving Nest and Bird instances.", e);
		}


		List<Nest> nests = em.createQuery("SELECT n FROM Nest n", Nest.class).getResultList();
		for (Nest nest : nests) {
			System.out.println("Nest ID: " + nest.getId());
			for (Bird bird : nest.getBirds()) {
				System.out.println("Bird ID: " + bird.getId() + ", Bird Name: " + bird.getBirdName());
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