-- 1.1
CREATE OR REPLACE PROCEDURE PPrint(p_text VARCHAR2) AS
BEGIN
    dbms_output.put_line(p_text);
END;

-- 1.2
CREATE OR REPLACE PROCEDURE PAddStudent1(p_login Student.login%TYPE, p_fname Student.fname%TYPE,
                                         p_lname Student.lname%TYPE,
                                         p_email Student.email%TYPE, p_grade Student.grade%TYPE,
                                         p_dateOfBirth Student.date_of_birth%TYPE) AS
BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (p_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
END;

-- 1.3
CREATE OR REPLACE PROCEDURE PAddStudent2(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
                                         p_email Student.email%TYPE, p_grade Student.grade%TYPE,
                                         p_dateOfBirth Student.date_of_birth%TYPE) AS

    v_login Student.login%TYPE;
BEGIN
    v_login := LOWER(SUBSTR(p_lname, 1, 3)) || '000';

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
END;

-- 1.4
CREATE OR REPLACE PROCEDURE PAddStudent3(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
                                         p_email Student.email%TYPE, p_grade Student.grade%TYPE,
                                         p_dateOfBirth Student.date_of_birth%TYPE) AS

    v_studentCount INT;
    v_login        Student.login%TYPE;
BEGIN
    SELECT COUNT(*) + 1
    INTO v_studentCount
    FROM Student;

    v_login := LOWER(SUBSTR(p_lname, 1, 3)) || LPAD(v_studentCount, 3, '0');

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);
END;


-- 2.1
CREATE OR REPLACE FUNCTION FAddStudent1(p_login Student.login%TYPE, p_fname Student.fname%TYPE,
                                        p_lname Student.lname%TYPE,
                                        p_email Student.email%TYPE, p_grade Student.grade%TYPE,
                                        p_dateOfBirth Student.date_of_birth%TYPE) RETURN VARCHAR AS
BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (p_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);

    RETURN 'OK';
EXCEPTION
    WHEN OTHERS THEN
        RETURN 'error';
END;

-- Ukazka volani funkce.
EXECUTE PPrint(FAddStudent1('abc123', 'Jan', 'Novak', 'jan.novak@vsb.cz', 1, TO_DATE('2000-01-01', 'yyyy-mm-dd')));

-- 2.2
CREATE OR REPLACE FUNCTION FAddStudent2(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
                                        p_email Student.email%TYPE, p_grade Student.grade%TYPE,
                                        p_dateOfBirth Student.date_of_birth%TYPE) RETURN VARCHAR AS

    v_studentCount INT;
    v_login        Student.login%TYPE;
BEGIN
    SELECT COUNT(*) + 1
    INTO v_studentCount
    FROM Student;

    v_login := LOWER(SUBSTR(p_lname, 1, 3)) || LPAD(v_studentCount, 3, '0');

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);

    RETURN v_login;

EXCEPTION
    WHEN OTHERS THEN
        RETURN 'error';
END;

-- Ukazka volani funkce.
EXECUTE PPrint(FAddStudent2('Jan', 'Novak', 'jan.novak@vsb.cz', 1, TO_DATE('2000-01-01', 'yyyy-mm-dd')));

-- 2.3
CREATE OR REPLACE FUNCTION FGetLogin(p_lname Student.lname%TYPE) RETURN Student.login%TYPE AS
    v_studentCount INT;
BEGIN
    SELECT COUNT(*) + 1
    INTO v_studentCount
    FROM Student;

    RETURN LOWER(SUBSTR(p_lname, 1, 3)) || LPAD(v_studentCount, 3, '0');
END;

-- 2.4
CREATE OR REPLACE FUNCTION FAddStudent3(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
                                        p_email Student.email%TYPE, p_grade Student.grade%TYPE,
                                        p_dateOfBirth Student.date_of_birth%TYPE) RETURN VARCHAR AS

    v_login Student.login%TYPE;
BEGIN
    v_login := FGetLogin(p_lname);

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);

    RETURN v_login;

EXCEPTION
    WHEN OTHERS THEN
        RETURN 'error';
END;

-- 3.1
CREATE OR REPLACE TRIGGER TInsertStudent
    AFTER INSERT
    ON Student
    FOR EACH ROW
BEGIN
    PPrint(:new.login || ': ' || :new.fname || ' ' || :new.lname);
END;

-- Ukazka volani. Po zavolani se do konzoloveho vystupu musi vypsat login a jmeno studenta.
EXECUTE PAddStudent3('Jan', 'Novak', 'jan.novak@vsb.cz', 1, TO_DATE('2000-01-01', 'yyyy-mm-dd'));

-- 3.2
CREATE OR REPLACE TRIGGER TDeleteStudent
    BEFORE DELETE
    ON Student
    FOR EACH ROW
BEGIN
    PPrint(:old.login || ': ' || :old.fname || ' ' || :old.lname);
END;

DELETE
FROM Student
WHERE login = 'nov000';

-- 3.3
CREATE OR REPLACE TRIGGER TUpdateStudent
    AFTER UPDATE
    ON Student
    FOR EACH ROW
BEGIN
    PPrint('Pred zmenou: ' || :old.fname || ' ' || :old.lname || ', rocnik ' || :old.grade);
    PPrint('Po zmene:    ' || :new.fname || ' ' || :new.lname || ', rocnik ' || :new.grade);
END;

UPDATE Student
SET grade = grade + 1
WHERE login IN ('mcc676', 'kow007');

-- 3.4
CREATE OR REPLACE TRIGGER TInsertStudent1
    AFTER INSERT
    ON Student
    FOR EACH ROW
DECLARE
    v_login Student.login%TYPE;
    v_year  INT;
BEGIN
    v_login := :new.login;
    v_year := EXTRACT(YEAR FROM CURRENT_TIMESTAMP);

    INSERT INTO StudentCourse (student_login, course_code, year)
    SELECT v_login, code, v_year
    FROM Course
    WHERE grade = 1;
END;

-- 3.5
CREATE OR REPLACE TRIGGER TInsertStudent2
    BEFORE INSERT
    ON Student
    FOR EACH ROW
BEGIN
    :new.login := FGetLogin(:new.lname);
END;

INSERT INTO Student (fname, lname, email, grade, date_of_birth)
VALUES ('Jan', 'Novak', 'jan.novak@vsb.cz', 1, TO_DATE('2000-01-01', 'yyyy-mm-dd'));

-- 3.6
DROP TRIGGER TInsertStudent;
DROP TRIGGER TDeleteStudent;
DROP TRIGGER TUpdateStudent;
DROP TRIGGER TInsertStudent1;
DROP TRIGGER TInsertStudent2;

--------------------------------------------------------------------------------------------------------------------------------

-- 4.1
CREATE OR REPLACE PROCEDURE PStudentBecomeTeacher(p_login Student.login%TYPE,
                                                  p_department Teacher.department%TYPE) AS

BEGIN
    INSERT INTO Teacher (login, fname, lname, department)
    SELECT login, fname, lname, p_department
    FROM Student
    WHERE login = p_login;

    DELETE
    FROM Student
    WHERE login = p_login;

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
END;



-- 4.2
CREATE OR REPLACE PROCEDURE PStudentAssignment(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
                                               p_dateOfBirth DATE) AS

    v_login Student.login%TYPE;
    v_email Student.email%TYPE;
    v_year  StudentCourse.year%TYPE;
BEGIN
    v_login := FGetLogin(p_lname);
    v_email := v_login || '@vsb.cz';
    v_year := EXTRACT(YEAR FROM CURRENT_TIMESTAMP);

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, v_email, 1, p_dateOfBirth);

    INSERT INTO StudentCourse (student_login, course_code, year)
    SELECT v_login, code, v_year
    FROM Course
    WHERE grade = 1;

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
END;

--------------------------------------------------------------------------------------------------------------------------------
