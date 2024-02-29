BEGIN
    dbms_output.put_line('ahoj');

END;

BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES ('abc123', 'Petr', 'Novak', 'petr.novak@vsb.cz', 1, TO_DATE('1992/05/06', 'yyyy/mm/dd'));
    dbms_output.put_line('Student byl vlozen');

EXCEPTION
    WHEN OTHERS THEN
        dbms_output.put_line('Student nebyl vlozen');
END;

DECLARE
    v_login Student.login%type;
    v_fname VARCHAR(30);
    v_lname VARCHAR(30);
    v_email VARCHAR(30);
    v_grade NUMBER;
    v_dob   DATE;
BEGIN
    v_login := 'abc123';
    INSERT INTO STUDENT (login, fname, lname, email, grade, DATE_OF_BIRTH)
    VALUES (v_login, 'Petr', 'Novak', 'petr.novak@vsb.cz', 1, TO_DATE('1992/05/06', 'yyyy/mm/dd'));

    DBMS_OUTPUT.PUT_LINE('student byl vlozen');
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('stydent nebyl vlozen lmao');
END;

DECLARE
    v_login Student.login%type;
    v_fname VARCHAR(30);
    v_lname VARCHAR(30);
    v_email VARCHAR(30);
    v_grade NUMBER;
    v_dob   DATE;
BEGIN
    SELECT FNAME
    INTO v_fname
    FROM STUDENT
    WHERE login = 'abc123';

    DBMS_OUTPUT.PUT_LINE('Jmeno: ' || v_fname);
END;

DECLARE
    v_student STUDENT%rowtype;
BEGIN
    SELECT *
    INTO v_student
    FROM STUDENT
    WHERE login = 'abc123';

    DBMS_OUTPUT.PUT_LINE('Jmeno: ' || v_student.LNAME);

EXCEPTION
    WHEN no_data_found THEN
        DBMS_OUTPUT.PUT_LINE('Nenalezena data');

    WHEN too_many_rows THEN
        DBMS_OUTPUT.PUT_LINE('Moc radku');
END;

BEGIN
    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES ('svo001', 'Josef', 'Svoboda', 'josef.svoboda@vsb.cz', 1, TO_DATE('1993/07/02', 'yyyy/mm/dd'));

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES ('cer001', 'Jana', 'Cerna', 'jana.cerna@vsb.cz', 2, TO_DATE('1991/12/05', 'yyyy/mm/dd'));

    COMMIT;
    dbms_output.put_line('OK');

EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
        dbms_output.put_line('Chyba');
END;

DECLARE
    v_login1 Teacher.login%TYPE := 'jor012';
    v_login2 Teacher.login%TYPE := 'per085';

BEGIN
    INSERT INTO Teacher (login, fname, lname, department)
    VALUES ('temp123', 'Temporary', 'Teacher', 'Temp');

    UPDATE Course
    SET teacher_login = 'temp123'
    WHERE teacher_login = v_login1;

    UPDATE Course
    SET teacher_login = v_login1
    WHERE teacher_login = v_login2;

    UPDATE Course
    SET teacher_login = v_login2
    WHERE teacher_login = 'temp123';

    DELETE
    FROM Teacher
    WHERE login = 'temp123';

    COMMIT;
    dbms_output.put_line('OK');

EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
        dbms_output.put_line('Chyba');
END;