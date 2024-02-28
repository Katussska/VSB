module cz.vsb {
    requires transitive javafx.controls;
    requires javafx.fxml;
	requires static lombok;
	requires org.apache.logging.log4j;
    opens cz.vsb to javafx.fxml;
    exports cz.vsb;
}