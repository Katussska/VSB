CREATE TABLE Student
(
    login         CHAR(6)
        CONSTRAINT Student_PK PRIMARY KEY,
    fname         VARCHAR(30) NOT NULL,
    lname         VARCHAR(50) NOT NULL,
    email         VARCHAR(50) NOT NULL,
    grade         INTEGER     NOT NULL,
    date_of_birth DATE        NOT NULL
);

CREATE TABLE Teacher
(
    login      CHAR(6)
        CONSTRAINT Teacher_PK PRIMARY KEY,
    fname      VARCHAR(30) NOT NULL,
    lname      VARCHAR(50) NOT NULL,
    department VARCHAR(50) NOT NULL
);

CREATE TABLE Course
(
    code          CHAR(11) PRIMARY KEY,
    name          VARCHAR(50) NOT NULL,
    capacity      INT         NOT NULL,
    teacher_login CHAR(6),
    CONSTRAINT Course_Teacher_FK FOREIGN KEY (teacher_login) REFERENCES Teacher (login)
);

CREATE TABLE StudentCourse
(
    student_login CHAR(6),
    course_code   CHAR(11),
    year          INT,
    CONSTRAINT StudentCourse_PK PRIMARY KEY (student_login, course_code, year),
    CONSTRAINT StudentCourse_Student_FK FOREIGN KEY (student_login) REFERENCES Student (login),
    CONSTRAINT StudentCourse_Course_FK FOREIGN KEY (course_code) REFERENCES Course (code)
);

INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('smi324', 'Mary', 'Smith', 'smith@gmail.com', 1, to_date('1998/05/31', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('joh357', 'Patricia', 'Johnson', 'patricia.johnson@vsb.cz', 1, to_date('1997/09/23', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('wil986', 'Linda', 'Williams', 'williams.linda@tieto.com', 1, to_date('1998/02/02', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('jon067', 'Barbara', 'Jones', 'jones.barbara@tieto.com', 1, to_date('1997/12/12', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('bro654', 'Elizabeth', 'Brown', 'brown.elizabeth@tieto.com', 1, to_date('1998/06/06', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('gan098', 'James', 'Gannon', 'jimmyg@gmail.com', 1, to_date('1998/04/22', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('far483', 'John', 'Farnsworth', 'farnie@yahoo.com', 1, to_date('1998/04/02', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('bau764', 'Robert', 'Baughman', 'robert.baughman@vsb.cz', 2, to_date('1997/02/25', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('sil012', 'Michael', 'Silverman', 'silverman@gmail.com', 2, to_date('1997/03/15', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('sat767', 'William', 'Satterfield', 'satter@hotmail.com', 2, to_date('1996/11/11', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('rol087', 'David', 'Royal', 'david.royal@vsb.cz', 2, to_date('1996/10/12', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('mcc676', 'Richard', 'McCrary', 'mccrary@dell.com', 2, to_date('1996/12/20', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('kow007', 'Charles', 'Kowalski', 'charliw@yahoo.com', 3, to_date('1995/05/12', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('joy087', 'Joseph', 'Joy', 'joy@oracle@com', 3, to_date('1995/01/04', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('gri453', 'Thomas', 'Grigsby', 'thomas.grigsby@vsb.cz', 3, to_date('1994/09/27', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('gre227', 'Christopher', 'Greco', 'greco.gmail.com', 3, to_date('1994/11/07', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('cab466', 'Daniel', 'Cabral', 'daniel.cabral@vsb.cz', 4, to_date('1994/05/05', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('tro552', 'Paul', 'Trout', 'paul.trout@vsb.cz', 4, to_date('1993/11/29', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('rin766', 'Mark', 'Rinehard', 'rino@yahoo.com', 5, to_date('1992/04/10', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('pen048', 'Erika', 'Pena', 'erika.pena@vsb.cz', 5, to_date('1992/02/22', 'yyyy/mm/dd'));


INSERT INTO Teacher (login, fname, lname, department)
VALUES ('jor012', 'Jerry', 'Jordon', 'Department of Computer Science');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('gil233', 'Dennis', 'Gilman', 'Department of Computer Science');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('per085', 'Walter', 'Perryman', 'Department of Computer Science');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('new056', 'Patrick', 'Newsom', 'Department of Mathematic');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('men623', 'Peter', 'Menard', 'Department of Mathematic');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('mar118', 'Harold', 'Martino', 'Department of Management');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('gra198', 'Douglas', 'Graf', 'Department of Management');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('art035', 'Carl', 'Artis', 'Department of Management');


INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-ds1-011', 'Database Systems I', 5, 'jor012');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-ds2-012', 'Database Systems II', 5, 'jor012');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-cns-922', 'Computer Networks', 10, 'jor012');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-img-101', 'Image Processing', 5, 'jor012');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-jav-226', 'Java Technologies', 8, 'per085');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-pyt-001', 'Python', 10, 'per085');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-web-654', 'Web Technologies', 15, 'per085');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('470-alg-220', 'Algebra', 15, 'new056');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('470-dis-902', 'Discrete Math', 15, 'new056');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-mic-061', 'Microeconomics', 8, 'art035');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-mac-022', 'Macroeconomics', 8, 'art035');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-man-111', 'Management', 8, 'art035');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-toe-166', 'Theory of Economy', 15, 'art035');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-adv-061', 'Advertisement', 8, 'art035');

INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-man-111', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-toe-166', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-adv-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-man-111', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-man-111', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-man-111', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '470-dis-902', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('far483', '470-dis-902', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bau764', '460-ds1-011', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sil012', '460-ds1-011', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rol087', '460-ds1-011', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '470-alg-220', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '470-dis-902', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('kow007', '470-dis-902', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-img-101', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '460-img-101', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-img-101', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-jav-226', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-img-101', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-web-654', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-web-654', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-adv-061', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-man-111', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-adv-061', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-man-111', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-adv-061', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('far483', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bau764', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bau764', '460-ds2-012', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sil012', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sil012', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sil012', '460-ds2-012', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sat767', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sat767', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sat767', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '420-man-111', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-img-101', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-jav-226', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-jav-226', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-img-101', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-jav-226', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-img-101', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-jav-226', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '420-man-111', 2021);

-- 2.1. Vypište kódy a názvy kurzů, které vyučuje Jerry Jordon.
SELECT Course.Code, Course.Name
FROM
    Course
    JOIN Teacher ON Course.teacher_login = Teacher.login
WHERE Teacher.fname = 'Jerry' AND Teacher.lname = 'Jordon';

-- 2.2. Vypište studenty, které v roce 2020 nebo 2021 učil Jerry Jordon.
SELECT DISTINCT Student.fname, Student.lname
FROM
    Student
    JOIN StudentCourse ON Student.login = StudentCourse.student_login
    JOIN Course ON StudentCourse.course_code = Course.code
    JOIN Teacher ON Course.teacher_login = Teacher.login
WHERE
    StudentCourse.year IN (2020, 2021) AND Teacher.fname = 'Jerry' AND Teacher.lname = 'Jordon';


-- 2.3. Pro všechny studenty v doméně @vsb.cz vypište počet zapsaných kurzů.
SELECT Student.fname, Student.lname, COUNT(StudentCourse.course_code) AS cnt
FROM
    Student
    LEFT JOIN StudentCourse ON Student.login = StudentCourse.student_login
WHERE Student.email LIKE '%vsb.cz'
GROUP BY Student.login, Student.fname, Student.lname;

-- 2.4. Pro všechny studenty vypište, kolik je v roce 2020 učilo různých učitelů.
SELECT Student.fname, Student.lname, COUNT(DISTINCT Course.teacher_login) AS cnt
FROM
    Student
    LEFT JOIN StudentCourse ON Student.login = StudentCourse.student_login AND StudentCourse.year = 2020
    LEFT JOIN Course ON StudentCourse.course_code = Course.code
GROUP BY Student.login, Student.fname, Student.lname;

-- 2.5. Pro každého učitele (jméno a příjmení) vypište kurz(y) s nejvyšší kapacitou, kapacita bude součástí výsledku. Učitele bez kurzů nevypisujte.
SELECT Teacher.fname, Teacher.lname, c1.name, c1.capacity
FROM
    Teacher
    JOIN Course c1 ON Teacher.login = c1.teacher_login
WHERE c1.capacity >= ALL (
    SELECT c2.capacity
    FROM Course c2
    WHERE c1.teacher_login = c2.teacher_login);

-- 2.6. Vypište učitele (jméno a příjmení), kteří vyučují největší počet kurzů.
WITH T AS
(
    SELECT Teacher.fname, Teacher.lname, COUNT(Course.code) AS cnt
    FROM
        Teacher
        LEFT JOIN Course ON Teacher.login = Course.teacher_login
    GROUP BY Teacher.login, Teacher.fname, Teacher.lname
)
SELECT *
FROM T
WHERE cnt >= ALL (SELECT cnt FROM T);

-- 2.7. Vypište studenty, které v roce 2020 nevyučoval Jerry Jordon, ale zároveň tito studenti měli v tomto roce zapsán alespoň jeden kurz.
SELECT fname, lname
FROM Student
WHERE login NOT IN (
    SELECT StudentCourse.student_login
    FROM
        StudentCourse
        JOIN Course ON StudentCourse.course_code = Course.code
        JOIN Teacher ON Course.teacher_login = Teacher.login
    WHERE Teacher.fname = 'Jerry' AND Teacher.lname = 'Jordon' AND StudentCourse.year = 2020
) AND login IN
(
    SELECT student_login
    FROM StudentCourse
    WHERE year = 2020
);

-- 2.8. Pro každý kurz vypište průměrný počet studentů, kteří měli daný kurz zapsán v jednotlivých letech.
-- Uvažujte jen kurzy, na které byl či je zapsán alespoň jeden student.
SELECT code, name, AVG(cnt) AS average
FROM
(
    SELECT Course.code, Course.name, COUNT(StudentCourse.student_login) AS cnt
    FROM
        Course
        JOIN StudentCourse ON Course.code = StudentCourse.course_code
    GROUP BY Course.code, Course.name, StudentCourse.year
) T
GROUP BY code, name

-- 3.1. Přidejte do tabulky Teacher učitele Peter Burton s loginem bur154 a katedrou Department of Mathematic.
INSERT INTO Teacher(login, fname, lname, department) VALUES ('bur154', 'Peter', 'Burton', 'Department of Mathematic');

-- 3.2. Nastavte kurzu Database Systems II nově vloženého učitele bur154.
UPDATE Course set teacher_login = 'bur154' where name = 'Database Systems II';

-- 3.3. Zrušte jedním SQL příkazem zápis kurzů (tj., záznamy v tab. StudentCourse), které vyučuje Carl Artis.
DELETE FROM StudentCourse
WHERE course_code IN (
    SELECT code
    FROM Course JOIN Teacher ON Course.teacher_login = Teacher.login
    WHERE fname = 'Carl' AND lname = 'Artis'
);

-- 3.4. Nastavte v databázi studentovi Barbara Jones účast pro rok 2021 na všech kurzech, které vyučuje Walter Perryman.
INSERT INTO StudentCourse
(
    year,
    student_login,
    course_code
)
SELECT 2021,
    (
        SELECT login
        FROM Student
        WHERE fname = 'Barbara' AND lname = 'Jones'
    ),
    Course.code
FROM Course JOIN Teacher ON Course.teacher_login = Teacher.login
WHERE Teacher.fname = 'Walter' AND Teacher.lname = 'Perryman';


-- 4.1. Nastavte studentovi 'smi324' datum narození na 2.3.1997.
UPDATE Student
SET date_of_birth = TO_DATE('1997-03-02', 'YYYY-MM-DD')
WHERE login = 'smi324';

-- 4.2. Pro každého studenta vypište jeho věk.
SELECT fname, lname, FLOOR(MONTHS_BETWEEN(current_timestamp, date_of_birth) / 12)
FROM Student

-- 4.3. Ke každému studentovi vypište datum, kdy oslavil své 18-té narozeniny.
SELECT fname, lname, ADD_MONTHS(date_of_birth, 18 * 12) AS age18
FROM Student

-- 4.4. Vypište ke každému studentovi v samostatných sloupcích rok, měsíc a den jeho narození.
SELECT
    fname, lname,
    EXTRACT(YEAR FROM date_of_birth) AS year,
    EXTRACT(MONTH FROM date_of_birth) AS month,
    EXTRACT(DAY FROM date_of_birth) AS day
FROM Student

-- 4.5. Vypište studenty, kteří se narodili ve stejné datum jako student Michael Silverman s tolerancí 3 měsíce.
SELECT Student.fname, Student.lname
FROM Student ms, Student
WHERE
    ms.fname = 'Michael' AND ms.lname = 'Silverman' AND
    Student.date_of_birth BETWEEN ADD_MONTHS(ms.date_of_birth, -3) AND ADD_MONTHS(ms.date_of_birth, +3)

-- 5.1. Vypište celá jména všech učitelů převedená na velká písmena. Celé jméno bude tvořeno jménem, mezerou a příjmením.
SELECT UPPER(fname || ' ' || lname) AS full_name
FROM Teacher

-- 5.2. Pro každého učitele vypište délku (počet znaků) jeho příjmení.
SELECT fname, lname, LENGTH(lname) AS len
FROM Teacher

-- 5.3. Vypište názvy všech kurzů bez mezer, tj. např. 'Discrete Math' bude vypsáno jako 'DiscreteMath'.
SELECT REPLACE(name, ' ', '') AS name_without_spaces
FROM Course

-- 5.4. Pro všechny kurzy vypište jejich kapacitu zarovnanou na 3 číslice, tj. např. kapacita 5 bude vypsána jako '005'.
SELECT code, LPAD(capacity, 3, '0') AS padded_cap
FROM Course

-- 5.5. Vypište podřetězce kódů kurzů mezi 5-tým až 7-mým znakem, tj. mezi pomlčkami.
SELECT code, SUBSTR(code, 5, 3)
FROM Course

-- 5.6. Vypište názvy kurzů s vynecháním prvních dvou znaků.
SELECT name, SUBSTR(name, 3, LENGTH(name) - 2)
FROM Course

-- 5.7. Pro všechny kurzy vypište pozici první mezery v jejich názvu.
SELECT name, INSTR(name, ' ') AS first_space
FROM Course
