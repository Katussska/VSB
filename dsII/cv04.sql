-- 1.1

CREATE OR REPLACE PROCEDURE PAddStudentToCourse(p_student_login Student.login%TYPE, p_course_code Course.code%TYPE,
                                                p_year INT) AS
    v_capacity INT;
    v_cnt      INT;
BEGIN
    SELECT capacity
    INTO v_capacity
    FROM Course
    WHERE code = p_course_code;

    SELECT COUNT(*)
    INTO v_cnt
    FROM StudentCourse
    WHERE course_code = p_course_code;

    IF v_cnt < v_capacity THEN
        INSERT INTO StudentCourse (student_login, course_code, year)
        VALUES (p_student_login, p_course_code, p_year);
    ELSE
        PPrint('Kurz je jiz plne obsazen.');
    END IF;
END;


-- 1.2

CREATE OR REPLACE TRIGGER TInsertStudentCourse
    BEFORE INSERT
    ON StudentCourse
    FOR EACH ROW
DECLARE
    v_capacity INT;
    v_cnt      INT;
BEGIN
    SELECT capacity
    INTO v_capacity
    FROM Course
    WHERE code = :new.course_code;

    SELECT COUNT(*)
    INTO v_cnt
    FROM StudentCourse
    WHERE course_code = :new.course_code;

    IF v_cnt >= v_capacity THEN
        PPrint('Kurz je jiz plne obsazen.');
    END IF;
END;

-- 1.3
CREATE OR REPLACE TRIGGER TInsertStudentCourse
    BEFORE INSERT
    ON StudentCourse
    FOR EACH ROW
DECLARE
    v_capacity INT;
    v_cnt      INT;
    v_capacity_exceeded EXCEPTION;
BEGIN
    SELECT capacity
    INTO v_capacity
    FROM Course
    WHERE code = :new.course_code;

    SELECT COUNT(*)
    INTO v_cnt
    FROM StudentCourse
    WHERE course_code = :new.course_code;

    IF v_cnt >= v_capacity THEN
        RAISE v_capacity_exceeded;
    END IF;
END;

