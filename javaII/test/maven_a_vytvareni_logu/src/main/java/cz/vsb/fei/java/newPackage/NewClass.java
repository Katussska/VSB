package cz.vsb.fei.java.newPackage;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class NewClass {
    private static final Logger logger = LogManager.getLogger(NewClass.class);

    public NewClass() {
        logger.debug("NewClass object created. Debug");
    }
}