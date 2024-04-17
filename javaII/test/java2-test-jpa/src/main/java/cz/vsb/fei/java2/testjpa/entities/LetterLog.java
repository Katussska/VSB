package cz.vsb.fei.java2.testjpa.entities;

import cz.vsb.fei.java2.testjpa.Tools;
import lombok.Getter;
import lombok.Setter;
import java.time.LocalDateTime;

//1.1,1.2
@Setter
@Getter
public class LetterLog {
    int id;
    String addressCity;
    String addressName;
    LocalDateTime logTime;

     public static LetterLog createRandom(){
        LetterLog letterLog = new LetterLog();
        letterLog.logTime = LocalDateTime.now();
        letterLog.addressCity = Tools.CITIES.get(Tools.RANDOM.nextInt(Tools.CITIES.size()));
        letterLog.addressName = Tools.STREETS.get(Tools.RANDOM.nextInt(Tools.STREETS.size()));

        return letterLog;
    }
}
